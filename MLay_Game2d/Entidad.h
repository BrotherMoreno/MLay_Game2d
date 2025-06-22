#pragma once
#include "Dependencias.h"	
class Entidad
{
protected:

	int x, y;
	int dx, dy;
	int ancho, alto;
	int iDx;//identificador inicial para animar sprites xd
public:

	Entidad() {
		x = y = 0;
		dx = dy = 0;
		ancho, alto = 0;
		iDx = 0;
	}
	void SetDx(int value)
	{
		dx = value;
	}
	void SetDy(int value)
	{
		dy = value;
	}
	Rectangle area() {
		return Rectangle(x, y, ancho, alto);
	}
	Rectangle NextArea() {
		return Rectangle(x + dx, y + dy, ancho, alto);
	}
	virtual void mover(Graphics^ g) {
		y += dy;
		x += dx;
	}
	virtual void mostrar(Graphics^ g) {
		g->FillRectangle(Brushes::Black, area());
	}

};

