#pragma once
#include "Entidad.h"
#include <vector>
enum SpriteEnemigo
{
	CaminarDerechaEnemigo,
	CaminarIzquierdaEnemigo,
};

class Enemigo : public Entidad {
private:
	SpriteEnemigo accion;
	int iDx;

public:
	Enemigo(Bitmap^ img)
	{
		x = rand() % 200;
		y = rand() % 200;
		iDx = 0;
		accion = CaminarDerechaEnemigo;

		if (rand() % 2 == 0) {
			dx = rand() % 11 - 5;
			if (dx == 0)
				dx = 5;
			dy = 0;
		}
		else {
			dy = rand() % 11 - 5;
			if (dy == 0)
				dy = 5;
			dx = 0;
		}

		ancho = img->Width / 8;
		alto = img->Height/2;

	}

	void Mover(Graphics^ g) {
		if (!(x + dx >= 0 && x + ancho + dx <= g->VisibleClipBounds.Width)) {
			dx *= -1;
		}
		if (!(y + dy >= 0 && y + alto + dy <= g->VisibleClipBounds.Height)) {
			dy *= -1;
		}
		x += dx;
		y += dy;
	}

	void mostrar(Graphics^ g, Bitmap^ img) {
		Rectangle corte = Rectangle(iDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, area(), corte, GraphicsUnit::Pixel);
		g->DrawRectangle(Pens::Black, area());

		if (accion == CaminarDerechaEnemigo) {
			iDx = (iDx + 1) % 4;
		}
		if (accion == CaminarIzquierdaEnemigo) {
			iDx = (iDx + 1) % 4;
		}
	}
};

class Enemigos {
private:
	std::vector<Enemigo*> enemigos;

public:
	Enemigos(Bitmap^ img, int cant)
	{
		for (int i = 0; i < cant; i++) {
			enemigos.push_back(new Enemigo(img));
		}
	}

	~Enemigos()
	{
		for (Enemigo* E : enemigos) {
			delete E;
		}
	}

	bool Colision(Rectangle obj)
	{
		for (Enemigo* E : enemigos) {
			if (E->area().IntersectsWith(obj))
				return true;
		}
		return false; 
	}

	void mover(Graphics^ g)
	{
		for (Enemigo* E : enemigos) {
			E->Mover(g);
		}
	}

	void mostrar(Graphics^ g, Bitmap^ img)
	{
		for (Enemigo* E : enemigos) {
			E->mostrar(g, img);
		}
	}
};
