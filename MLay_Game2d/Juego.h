#pragma once
#include "Jugador.h"
#include "Obstaculo.h"
#include "Enemigo.h"
#include "ProyectilCorteVital.h"
#include "Coins.h"
#include "HowlDtroy.h"
#include "Roca.h"
ref class ControladorJuego

{
private:
	Jugador* jugador;
	Obstaculos* obstaculos;
	Enemigos* enemigos;
	CorteVitales* corteVitales;
	Coins* coins;
	HowlDtroy* howlDtroy;
	Rocas* rocas;

	Bitmap^ imgLobo;
	Bitmap^ imgPersonaje;
	Bitmap^ imgEnemigo;
	Bitmap^ imgProyectilCorteVital;
	Bitmap^ imgCoins;
	Bitmap^ imgRocas;
	Bitmap^ imgHowlDtroy;
	Bitmap^ imgBarraVidaJugador;
	Bitmap^ imgBarraEstaminaJugador;
	Bitmap^ imgBarrasFondo;
	Bitmap^ imgBarraVidaHowl;


	int coolcownAtaqueEnemigo;
	int tiempo;

	// --- Control de aturdimiento de Howl ---
	int golpesHowl = 0;
	bool howlAturdido = false;
	clock_t tiempoAturdido = 0;
	// ----------------------------------------

public:
	ControladorJuego(int v, int E, int t) {
		imgLobo = gcnew Bitmap("img/powerPurple.png");
		imgPersonaje = gcnew Bitmap("img/LaySprite2.png");
		imgEnemigo = gcnew Bitmap("img/powerLayCorteVital.png");
		imgProyectilCorteVital = gcnew Bitmap("img/powerLayCorteVital.png");
		imgCoins = gcnew Bitmap("img/coins3.png");
		imgHowlDtroy = gcnew Bitmap("img/SpriteHowlDtroy7.png");
		imgRocas = gcnew Bitmap("img/Rocas.png");
		imgBarraVidaJugador = gcnew Bitmap("img/bar_hp.png");
		imgBarraVidaHowl = gcnew Bitmap("img/bar_hpHowl.png");
		imgBarraEstaminaJugador = gcnew Bitmap("img/bar_stamina.png");
		imgBarrasFondo = gcnew Bitmap("img/bar_BG.png");
		
		jugador = new Jugador(imgPersonaje, v);
		obstaculos = new Obstaculos(5, jugador->area(), imgLobo);
		enemigos = new Enemigos(imgEnemigo, E);
		corteVitales = new CorteVitales();
		howlDtroy = new HowlDtroy(imgHowlDtroy, 20);
		coolcownAtaqueEnemigo = 0;
		coins = new Coins(5, jugador->area(), imgCoins);
		rocas = new Rocas(6, jugador->area(), imgCoins);
		tiempo = t * 1000;
	}
	~ControladorJuego() {
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
		delete imgHowlDtroy;
		delete howlDtroy;
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
	// MLay_Game2d/Juego.h
	void movimientoHowlDtroy()
	{
		// Si está aturdido, no se mueve ni cambia de animación
		if (howlAturdido) return;

		int velocidad = 8;
		int margen = 5;

		Point centroVision = howlDtroy->CentroRangoVision();
		int radioVision = howlDtroy->RadioRangoVision();

		Point centroJugador = Point(jugador->GetX() + jugador->GetAncho() / 2, jugador->GetY() + jugador->GetAlto() / 2);

		int dx = centroVision.X - centroJugador.X;
		int dy = centroVision.Y - centroJugador.Y;
		int distancia2 = dx * dx + dy * dy;

		Rectangle areaAtaque = howlDtroy->HitboxAtk();
		Rectangle hitboxLobo = howlDtroy->HitBox();
		Rectangle hitboxJugador = jugador->HitBox();

		if (areaAtaque.IntersectsWith(jugador->HitBox()))
		{
			howlDtroy->SetDx(0);
			howlDtroy->SetDy(0);

			int centroAtkX = areaAtaque.X + areaAtaque.Width / 2;
			int centroJugadorX = jugador->GetX() + jugador->GetAncho() / 2;

			if (centroJugadorX >= centroAtkX)
				howlDtroy->SetAccion(HowlAtacarDerecha);
			else
				howlDtroy->SetAccion(HowlAtacarIzquierda);

			if (clock() - coolcownAtaqueEnemigo >= 500)
			{
				jugador->SetVida(-1);
				coolcownAtaqueEnemigo = clock();
			}
		}
		else if (distancia2 <= radioVision * radioVision)
		{
			int posLoboX = howlDtroy->GetX();
			int posLoboY = howlDtroy->GetY();
			int posJugadorX = jugador->GetX();
			int posJugadorY = jugador->GetY();

			if (posLoboX < posJugadorX) {
				howlDtroy->SetDx(velocidad);
				howlDtroy->SetAccion(HowlCaminarDerecha);
			}
			else if (posLoboX > posJugadorX) {
				howlDtroy->SetDx(-velocidad);
				howlDtroy->SetAccion(HowlCaminarIzquierda);
			}
			else {
				howlDtroy->SetDx(0);
			}

			if (posLoboY < posJugadorY) {
				howlDtroy->SetDy(velocidad);
			}
			else if (posLoboY > posJugadorY) {
				howlDtroy->SetDy(-velocidad);
			}
			else {
				howlDtroy->SetDy(0);
			}
		}
		else
		{
			int posLoboX = howlDtroy->GetX();
			int posLoboY = howlDtroy->GetY();
			int xInicial = howlDtroy->GetXInicial();
			int yInicial = howlDtroy->GetYInicial();

			if (posLoboX < xInicial - margen) {
				howlDtroy->SetDx(velocidad);
				howlDtroy->SetAccion(HowlCaminarDerecha);
			}
			else if (posLoboX > xInicial + margen) {
				howlDtroy->SetDx(-velocidad);
				howlDtroy->SetAccion(HowlCaminarIzquierda);
			}
			else {
				howlDtroy->SetDx(0);
			}

			if (posLoboY < yInicial - margen)
				howlDtroy->SetDy(velocidad);
			else if (posLoboY > yInicial + margen)
				howlDtroy->SetDy(-velocidad);
			else
				howlDtroy->SetDy(0);

			if (abs(posLoboX - xInicial) <= margen && abs(posLoboY - yInicial) <= margen) {
				howlDtroy->SetDx(0);
				howlDtroy->SetDy(0);
				if (howlDtroy->GetAccion() == HowlCaminarDerecha)
					howlDtroy->SetAccion(HowlAnimStableDerecha);
				if (howlDtroy->GetAccion() == HowlCaminarIzquierda)
					howlDtroy->SetAccion(HowlAnimStableIzquierda);
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
		}
		if (rocas->Colision(jugador->HitBox())) {
			jugador->SetPuntos(rocas->Eliminar(jugador->HitBox()));
		}

		// --- CorteVitales colisión con Howl y límites de pantalla + aturdimiento ---
		for (int i = 0; i < corteVitales->size(); ++i) {
			CorteVital* cv = corteVitales->Get(i);
			Rectangle area = cv->HitBox();
			bool fueraPantalla = area.X < 0 || area.Y < 0 || area.Right > 1008 || area.Bottom > 729;
			bool colisionHowl = area.IntersectsWith(howlDtroy->HitBoxHowlColision());
			if (fueraPantalla || colisionHowl) {
				if (colisionHowl && !howlAturdido) {
					golpesHowl++;
					howlDtroy->SetVida(-0.5); // Baja medio espacio por cada CorteVital
					if (golpesHowl >= 3) {
						howlAturdido = true;
						tiempoAturdido = clock();
						howlDtroy->SetDx(0);
						howlDtroy->SetDy(0);
						howlDtroy->SetVida(-2.5); // Completa el daño a 3 espacios al aturdirse
						if (howlDtroy->GetAccion() == HowlCaminarDerecha || howlDtroy->GetAccion() == HowlAnimStableDerecha)
							howlDtroy->SetAccion(HowlAturdidoDerecha);
						else {
							howlDtroy->SetAccion(HowlAturdidoIzquierda);
						}
					}
				}
				corteVitales->Elminar(i);
				--i;
			}
		}
		// --- Fin CorteVitales colisión y aturdimiento ---

		// Control de aturdimiento: 2 segundos sin moverse ni cambiar animación
		if (howlAturdido) {
			if ((clock() - tiempoAturdido) >= 2000) {
				howlAturdido = false;
				golpesHowl = 0;
				howlDtroy->SetAccion(HowlAnimStableDerecha);// O la animación idle que corresponda
			}
			else {
				howlDtroy->SetDx(0);
				howlDtroy->SetDy(0);
			}
		}

		jugador->mover(g);
		howlDtroy->moverHowl(g);
		corteVitales->mover(g);
		return true;
	}
	void mostrar(Graphics^ g)
	{
		// Dibuja el fondo de las barras
		g->DrawImage(imgBarrasFondo, 0, 0);
		g->DrawImage(imgBarrasFondo, 1008 - 256, 0);

		// --- Barra de Vida del Jugador (dividida en 10 partes) ---
		int vidaMax = 10;
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

		// --- Barra de Vida de HowlDtroy (dividida en 20 partes, acepta decimales) ---
		// Calcula el ancho de la barra
		int vidaHowlMax = 20;
		double vidaHowlActual = howlDtroy->GetVida();
		int anchoVidaHowl = static_cast<int>(imgBarraVidaHowl->Width * vidaHowlActual / vidaHowlMax);

		// El recorte de la imagen fuente empieza desde la derecha
		Rectangle srcVidaHowl = Rectangle(imgBarraVidaHowl->Width - anchoVidaHowl, 0, anchoVidaHowl, imgBarraVidaHowl->Height);

		// El destino también se ajusta para que el lado derecho quede fijo
		Rectangle destVidaHowl = Rectangle(1008 - 256 + (imgBarraVidaHowl->Width - anchoVidaHowl), 0, anchoVidaHowl, imgBarraVidaHowl->Height);

		g->DrawImage(imgBarraVidaHowl, destVidaHowl, srcVidaHowl, GraphicsUnit::Pixel);
		// Resto del juego
		corteVitales->mostrar(g, imgProyectilCorteVital);
		coins->mostrar(g, imgCoins);
		rocas->mostrar(g, imgRocas);
		jugador->mostrar(g, imgPersonaje);
		howlDtroy->mostrar(g, imgHowlDtroy);
	}
};