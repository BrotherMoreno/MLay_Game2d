#pragma once
#include "Entidad.h"

enum SpriteJugador
{
	CaminarDerecha,
	CaminarIzquierda,
	SaltarMirandoDerecha,
	saltarMirandoIzquierda
};

class Jugador : public Entidad
{
private: 
	int vidas;
	SpriteJugador  accion;
public:
	Jugador(Bitmap^ img  ) {
		x = 60;
		y = 60;
		dx = dy = 0;
		ancho = img->Width/12;
		alto = img->Height/4;

		accion = CaminarDerecha;
	}
	void SetVida(int value) {
		vidas += value;
	}
	int GetVida() {
		return vidas;
	}
	
	void SetAccion(SpriteJugador value) {
		accion = value;
	}
	void mover(Graphics^ g) {
		if (x + dx >= 0 && x + ancho + dx <= g->VisibleClipBounds.Width) {
			x += dx;
		}
		if (y + dy >= 0 && y + alto + dy <= g->VisibleClipBounds.Height) {
			y += dy;
		}
	}
	void mostrar(Graphics^ g, Bitmap^img) {
		Rectangle corte = Rectangle(iDx*ancho, accion*alto, ancho, alto);
		g->DrawImage(img, area(), corte, GraphicsUnit::Pixel);
		g->DrawRectangle(Pens::Black, x+11, y+7, ancho-30, alto-7);
		if (dx != 0 || dy != 0) 
		{
			if(accion>=CaminarDerecha && accion<=CaminarIzquierda)
			{
				iDx = (iDx + 1) % 8;
			}
			else if (accion >= SaltarMirandoDerecha && accion <= saltarMirandoIzquierda) 
			{
				iDx = (iDx + 1) % 12;

			}
		}

	}
};