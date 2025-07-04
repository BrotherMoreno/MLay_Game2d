#pragma once
#include "Jugador.h"
#include "Obstaculo.h"
#include "Enemigo.h"
#include "ProyectilCorteVital.h"
#include "Coins.h"
#include "HowlDtroy.h"
ref class ControladorJuego


{
private:
	Jugador* jugador;
	Obstaculos* obstaculos;
	Enemigos* enemigos;
	CorteVitales* corteVitales;
	Coins* coins;
	HowlDtroy* howlDtroy;

	Bitmap^ imgLobo;
	Bitmap^ imgPersonaje;
	Bitmap^ imgEnemigo;
	Bitmap^ imgProyectilCorteVital;
	Bitmap^ imgCoins;
	Bitmap^ imgHowlDtroy;

	int coolcownAtaqueEnemigo;
	int tiempo;
public:
	ControladorJuego(int v, int E, int t) {
		imgLobo = gcnew Bitmap("img/powerPurple.png");
		imgPersonaje = gcnew Bitmap("img/LaySprite2.png");
		imgEnemigo = gcnew Bitmap("img/powerLayCorteVital.png");
		imgProyectilCorteVital = gcnew Bitmap("img/powerLayCorteVital.png");
		imgCoins = gcnew Bitmap("img/coins3.png");
		imgHowlDtroy = gcnew Bitmap("img/SpriteHowlDtroy7.png");

		jugador = new Jugador(imgPersonaje, v);
		obstaculos = new Obstaculos(5, jugador->area(), imgLobo);
		enemigos = new Enemigos(imgEnemigo, E);
		corteVitales = new CorteVitales();
		howlDtroy = new HowlDtroy(imgHowlDtroy, 50);
		coolcownAtaqueEnemigo = 0;
		coins = new Coins(3, jugador->area(), imgCoins);
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
		int v = 6;
		if (accion == true)
		{
			if (tecla == Keys::Up)
			{

				jugador->SetDy(-v);
				jugador->SetAccion(CaminarDerecha);
			}
			else if (tecla == Keys::Down)
			{
				jugador->SetAccion(CaminarDerecha);

				jugador->SetDy(v);
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

		if (enemigos->Colision(jugador->area()) && clock() - coolcownAtaqueEnemigo >= 2000) {
			jugador->SetVida(-1);
			coolcownAtaqueEnemigo = clock();

			if (jugador->GetVida() == 0)
				return false;
		}
		if (clock() >= tiempo)
			return false;

		if (obstaculos->Colision(jugador->NextHitBox()) == false)
			jugador->mover(g);
		obstaculos->mover(g);
		howlDtroy->mover(g);
		corteVitales->mover(g);
		enemigos->mover(g);
		//coins->mover(g);
		return true;
	}
	void mostrar(Graphics^ g)
	{
		g->DrawString("tiempo: " + ((tiempo - clock()) / 1000), gcnew Font("arial", 12), Brushes::Black, 0, 20);
		
		obstaculos->mostrar(g, imgLobo);
		corteVitales->mostrar(g, imgProyectilCorteVital);
		enemigos->mostrar(g, imgEnemigo);
		howlDtroy->mostrar(g, imgHowlDtroy);
		coins->mostrar(g, imgCoins);
		jugador->mostrar(g, imgPersonaje);


	}
};
