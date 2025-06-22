#pragma once
#include "Jugador.h"
#include "Obstaculo.h"
ref class ControladorJuego


{
private:
	Jugador* jugador;
	Obstaculos* obstaculos;

	Bitmap^ imgLobo;
	Bitmap^ imgPersonaje;
public:
	ControladorJuego() {
		imgLobo = gcnew Bitmap("img/howl.png");
		imgPersonaje = gcnew Bitmap("img/LaySpriteUnic.png");

		jugador = new Jugador(imgPersonaje);
		obstaculos = new Obstaculos(5,jugador->area(),imgLobo);
	}
	~ControladorJuego() {
		delete jugador;
		delete obstaculos;
		delete imgLobo;
		delete imgPersonaje;
	}

	void movimientoJugador(bool accion,  Keys tecla) 
	{
		int v = 4;
		if (accion == true)
		{
			if (tecla == Keys::Up)
			{

				jugador->SetDy(-v);
				jugador->setAccion(CaminarDerecha);
			}
			else if (tecla == Keys::Down) 
			{
				jugador->setAccion(CaminarDerecha);

				jugador->SetDy(v);
			}
			else if (tecla == Keys::Left) 
			{
				jugador->setAccion(CaminarIzquierda);

				jugador->SetDx(-v);
			}
			else if (tecla == Keys::Right) 
			{
				jugador->setAccion(CaminarDerecha);

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
	}
	void mostrar(Graphics^ g, Bitmap^ img)
	{
		jugador->mostrar(g, imgPersonaje);
		obstaculos->mostrar(g, imgLobo);

	}
};
