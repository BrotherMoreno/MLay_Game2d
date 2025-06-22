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
	void setAccion(SpriteJugador value) {
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
		if (dx != 0 || dy != 0) {

			iDx = (iDx + 1) % 8;
		}

	}
};