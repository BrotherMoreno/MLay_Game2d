#pragma once
#include "Jugador.h"
#include "Obstaculo.h"
#include "Enemigo.h"
#include "ProyectilCorteVital.h"
#include "Coins.h"
#include "Roca.h"
#include <ctime>


ref class ClaseControladora2
{
private:
	Jugador* jugador;
	Obstaculos* obstaculos;
	Enemigos* enemigos;
	CorteVitales* corteVitales;
	Coins* coins;
	Rocas* rocas;

	Bitmap^ imgLobo;
	Bitmap^ imgPersonaje;
	Bitmap^ imgEnemigo;
	Bitmap^ imgProyectilCorteVital;
	Bitmap^ imgCoins;
	Bitmap^ imgRocas;
	Bitmap^ imgBarraVidaJugador;
	Bitmap^ imgBarraEstaminaJugador;
	Bitmap^ imgBarrasFondo;

	int coolcownAtaqueEnemigo;
	int tiempo;
	clock_t tiempoTransicionNivel3 = 0;
	bool listoParaTransicion = false;
	clock_t tiempoUltimoDanio = 0; // <-- NUEVO: para controlar el daño periódico

public:
	ClaseControladora2(int v, int E, int t) {
		imgLobo = gcnew Bitmap("img/powerPurple.png");
		imgPersonaje = gcnew Bitmap("img/LaySprite2.png");
		imgEnemigo = gcnew Bitmap("img/Robot2-90.png");
		imgProyectilCorteVital = gcnew Bitmap("img/powerLayCorteVital.png");
		imgCoins = gcnew Bitmap("img/coins3.png");
		imgRocas = gcnew Bitmap("img/Rocas.png");
		imgBarraVidaJugador = gcnew Bitmap("img/bar_hp.png");
		imgBarraEstaminaJugador = gcnew Bitmap("img/bar_stamina.png");
		imgBarrasFondo = gcnew Bitmap("img/bar_BG.png");

		jugador = new Jugador(imgPersonaje, v);
		obstaculos = new Obstaculos(5, jugador->area(), imgLobo);
		enemigos = new Enemigos(imgEnemigo, E);
		corteVitales = new CorteVitales();
		coolcownAtaqueEnemigo = 0;
		coins = new Coins(5, jugador->area(), imgCoins);
		rocas = new Rocas(6, jugador->area(), imgCoins);
		tiempo = t * 1000;
		tiempoUltimoDanio = 0;
	}
	~ClaseControladora2() {
		delete jugador;
		delete obstaculos;
		delete imgLobo;
		delete imgPersonaje;
		delete enemigos;
		delete imgEnemigo;
		delete corteVitales;
		delete imgProyectilCorteVital;
		delete imgCoins;
		delete coins;
		delete imgRocas;
		delete rocas;
		delete imgBarraVidaJugador;
		delete imgBarraEstaminaJugador;
		delete imgBarrasFondo;
	}
	void SumarVidaPorCoin()
	{
		int vidaMax = 40; // O usa jugador->GetVidaMax() si tienes ese método
		int fraccion = vidaMax / 8; // Suma 1/8 de la vida máxima por coin
		int nuevaVida = jugador->GetVida() + fraccion;
		if (nuevaVida > vidaMax) nuevaVida = vidaMax;
		jugador->SetVida(nuevaVida - jugador->GetVida()); // Suma solo la diferencia
	}
	bool DebePasarNivel() {
		// Verifica si todas las rocas han sido recolectadas
		bool todasRocasRecolectadas = (rocas->GetRocas().size() == 0);
		// Verifica si todos los enemigos están muertos
		bool todosEnemigosMuertos = true;
		auto& listaEnemigos = enemigos->GetEnemigos();
		for (int i = 0; i < listaEnemigos.size(); ++i) {
			if (!listaEnemigos[i]->EstaMuerto()) {
				todosEnemigosMuertos = false;
				break;
			}
		}
		return todasRocasRecolectadas && todosEnemigosMuertos;
	}

	void movimientoJugador(bool accion, Keys tecla)
	{
		int v = 13;
		if (accion == true)
		{
			if (tecla == Keys::Up)
			{
				jugador->SetDy(-v);
				if (jugador->GetAccion() == CaminarDerecha)
					jugador->SetAccion(CaminarDerecha);
				else {
					jugador->SetAccion(CaminarIzquierda);
				}
			}
			else if (tecla == Keys::Down)
			{
				jugador->SetDy(v);
				if (jugador->GetAccion() == CaminarIzquierda)
					jugador->SetAccion(CaminarIzquierda);
				else {
					jugador->SetAccion(CaminarDerecha);
				}
			}
			else if (tecla == Keys::Left)
			{
				jugador->SetAccion(CaminarIzquierda);
				jugador->SetDx(-v);
			}
			else if (tecla == Keys::Right)
			{
				jugador->SetAccion(CaminarDerecha);
				jugador->SetDx(v);
			}
			else if (tecla == Keys::X)
			{
				if (jugador->GetAccion() == CaminarDerecha)
					jugador->SetAccion(AtacarDerecha);
				else if (jugador->GetAccion() == CaminarIzquierda)
					jugador->SetAccion(AtacarIzquierda);
			}
		}
		else
		{
			if (tecla == Keys::Up)
				jugador->SetDy(0);
			else if (tecla == Keys::Down)
				jugador->SetDy(0);
			else if (tecla == Keys::Left)
				jugador->SetDx(0);
			else if (tecla == Keys::Right)
				jugador->SetDx(0);
		}
	}
	void DispararJugador(Keys tecla)
	{
		int v = 20;
		if (tecla == Keys::C)
		{
			if (jugador->GetAccion() == CaminarIzquierda || jugador->GetAccion() == AtacarIzquierda && jugador->GetiDx() == 7)
			{
				jugador->SetAccion(AtacarIzquierda);
				corteVitales->Agregar(jugador->GetX(), jugador->GetY() + jugador->GetAlto() / 4, -v, 0, imgProyectilCorteVital);
			}
			if (jugador->GetAccion() == CaminarDerecha || jugador->GetAccion() == AtacarDerecha && jugador->GetiDx() == 7)
			{
				jugador->SetAccion(AtacarDerecha);
				corteVitales->Agregar(jugador->GetX() + jugador->GetAncho(), jugador->GetY() + jugador->GetAlto() / 4, v, 0, imgProyectilCorteVital);
			}
		}
	}

	bool mover(Graphics^ g)
	{
		if (jugador->GetAccion() >= AtacarDerecha && jugador->GetAccion() <= AtacarIzquierda && jugador->GetiDx() == 7)
		{
			jugador->SetPuntos(obstaculos->Eliminar(jugador->area()));
		}

		if (jugador->GetVida() == 0)
			return false;

		if (coins->Colision(jugador->HitBox())) {
			jugador->SetPuntos(coins->Eliminar(jugador->HitBox()));
			SumarVidaPorCoin();

		}
		if (rocas->Colision(jugador->HitBox())) {
			jugador->SetPuntos(rocas->Eliminar(jugador->HitBox()));
		}

		// --- Daño por colisión con enemigos cada 1.5 segundos ---
		int idxColision = -1;
		if (enemigos->Colision(jugador->HitBox(), idxColision)) {
			clock_t ahora = clock();
			if (tiempoUltimoDanio == 0 || (ahora - tiempoUltimoDanio) >= 500) {
				jugador->SetVida(-1); // Fracción de daño (ajusta el valor según tu barra de vida)
				tiempoUltimoDanio = ahora;
			}
		}
		else {
			tiempoUltimoDanio = 0; // Reinicia el temporizador si no hay colisión
		}
		// --- Fin daño por colisión ---

		for (int i = 0; i < corteVitales->size(); ++i) {
			CorteVital* cv = corteVitales->Get(i);
			Rectangle area = cv->HitBox();
			bool hit = false;
			auto& listaEnemigos = enemigos->GetEnemigos();
			for (int j = 0; j < listaEnemigos.size(); ++j) {
				if (!listaEnemigos[j]->EstaMuerto() && area.IntersectsWith(listaEnemigos[j]->area())) {
					listaEnemigos[j]->RestarVida();
					hit = true;
					break;
				}
			}
			bool fueraPantalla = area.X < 0 || area.Y < 0 || area.Right > 1008 || area.Bottom > 729;
			if (hit || fueraPantalla) {
				corteVitales->Elminar(i);
				--i;
			}
		}

		jugador->mover(g);
		int jugadorCentroX = jugador->GetX() + jugador->GetAncho() / 2;
		int jugadorCentroY = jugador->GetY() + jugador->GetAlto() / 2;
		enemigos->mover(g, jugadorCentroX, jugadorCentroY);
		corteVitales->mover(g);
		return true;
	}
	void mostrar(Graphics^ g)
	{
		// Dibuja el fondo de las barras
		g->DrawImage(imgBarrasFondo, 0, 0);

		// --- Barra de Vida del Jugador (dividida en 10 partes) ---
		int vidaMax = 40;
		int vidaActual = jugador->GetVida();
		int anchoVida = imgBarraVidaJugador->Width * vidaActual / vidaMax;
		Rectangle srcVida = Rectangle(0, 0, anchoVida, imgBarraVidaJugador->Height);
		Rectangle destVida = Rectangle(0, 0, anchoVida, imgBarraVidaJugador->Height);
		g->DrawImage(imgBarraVidaJugador, destVida, srcVida, GraphicsUnit::Pixel);

		// --- Barra de Estamina del Jugador (dividida en 10 partes) ---
		int estaminaMax = 10;
		int estaminaActual = estaminaMax; // Reemplaza por jugador->GetEstamina() si tienes ese método
		int anchoEstamina = imgBarraEstaminaJugador->Width * estaminaActual / estaminaMax;
		Rectangle srcEstamina = Rectangle(0, 0, anchoEstamina, imgBarraEstaminaJugador->Height);
		Rectangle destEstamina = Rectangle(0, 0, anchoEstamina, imgBarraEstaminaJugador->Height);
		g->DrawImage(imgBarraEstaminaJugador, destEstamina, srcEstamina, GraphicsUnit::Pixel);

		// Resto del juego
		enemigos->mostrar(g, imgEnemigo);

		corteVitales->mostrar(g, imgProyectilCorteVital);
		coins->mostrar(g, imgCoins);
		rocas->mostrar(g, imgRocas);
		jugador->mostrar(g, imgPersonaje);
	}
};