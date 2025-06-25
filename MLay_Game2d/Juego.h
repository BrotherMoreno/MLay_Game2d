#pragma once
#include "Jugador.h"
#include "Obstaculo.h"
#include "Enemigo.h"
ref class ControladorJuego


{
private:
	Jugador* jugador;
	Obstaculos* obstaculos;
	Enemigos* enemigos;

	Bitmap^ imgLobo;
	Bitmap^ imgPersonaje;
	Bitmap^ imgEnemigo;
public:
	ControladorJuego(int E) {
		imgLobo = gcnew Bitmap("img/howl.png");
		imgPersonaje = gcnew Bitmap("img/LaySpriteUnic.png");
		imgEnemigo = gcnew Bitmap("img/MageSprite.png");

		jugador = new Jugador(imgPersonaje);
		obstaculos = new Obstaculos(5,jugador->area(),imgLobo);
		enemigos = new Enemigos(imgEnemigo, E);
	}
	~ControladorJuego() {
		delete jugador;
		delete obstaculos;
		delete imgLobo;
		delete imgPersonaje;
		delete enemigos;
		delete imgEnemigo;
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
	void mover(Graphics^ g)
	{
		if(obstaculos->Colision(jugador->NextArea())==false)
			jugador->mover(g);
		obstaculos->mover(g);
		enemigos->mover(g);
		
	}
	void mostrar(Graphics^ g)
	{
		jugador->mostrar(g, imgPersonaje);
		obstaculos->mostrar(g, imgLobo);
		enemigos->mostrar(g, imgEnemigo);

	}
};
