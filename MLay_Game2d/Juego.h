#pragma once
#include "Jugador.h"
#include "Obstaculo.h"
#include "Enemigo.h"
#include "ProyectilCorteVital.h"
ref class ControladorJuego


{
private:
	Jugador* jugador;
	Obstaculos* obstaculos;
	Enemigos* enemigos;
	CorteVitales* corteVitales; 

	Bitmap^ imgLobo;
	Bitmap^ imgPersonaje;
	Bitmap^ imgEnemigo;

	int coolcownAtaqueEnemigo;
	int tiempo;
public:
	ControladorJuego(int v, int E,int t) {
		imgLobo = gcnew Bitmap("img/powerPurple.png");
		imgPersonaje = gcnew Bitmap("img/LaySprite2.png");
		imgEnemigo = gcnew Bitmap("img/MageSprite.png");

		jugador = new Jugador(imgPersonaje, v);
		obstaculos = new Obstaculos(5,jugador->area(),imgLobo);
		enemigos = new Enemigos(imgEnemigo, E);
		corteVitales = new CorteVitales();
		coolcownAtaqueEnemigo = 0;
		tiempo= t*1000;
	}
	~ControladorJuego() {
		delete jugador;
		delete obstaculos;
		delete imgLobo;
		delete imgPersonaje;
		delete enemigos;
		delete imgEnemigo;
		delete corteVitales;
	}

	void movimientoJugador(bool accion,  Keys tecla) 
	{
		int v = 4;
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
		if (tecla == Keys::C) 
		{
			if (jugador->GetAccion() == CaminarDerecha)
				jugador->SetAccion(AtacarDerecha);
			else if (jugador->GetAccion() == CaminarIzquierda)
				jugador->SetAccion(AtacarIzquierda);
		}
	}
	bool mover(Graphics^ g)
	{
		if (jugador->GetAccion()>=AtacarDerecha && jugador->GetAccion()<=AtacarIzquierda&& jugador->GetiDx()==7) 
		{
			jugador->SetPuntos(obstaculos->Eliminar(jugador->area()));
		}
		if (enemigos->Colision(jugador->area())&& clock() - coolcownAtaqueEnemigo>=2000) {
			jugador->SetVida(-1);
			coolcownAtaqueEnemigo = clock();

			if (jugador->GetVida() == 0)
				return false;
		}
		if (clock() >= tiempo)
			return false;
		
		if(obstaculos->Colision(jugador->NextHitBox())==false)
			jugador->mover(g);
		obstaculos->mover(g);
		corteVitales->mover(g);
		enemigos->mover(g);
		return true;
	}
	void mostrar(Graphics^ g)
	{
		g->DrawString("tiempo: "+ ((tiempo - clock()) / 1000), gcnew Font("arial", 12), Brushes::Black, 0, 20);

		obstaculos->mostrar(g, imgLobo);
		corteVitales->mostrar(g); 
		enemigos->mostrar(g, imgEnemigo);
		jugador->mostrar(g, imgPersonaje);

	}
};
