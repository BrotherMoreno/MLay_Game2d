#pragma once
#include "Entidad.h"

enum SpriteRoca {
	animRoca,
};

class Roca : public Entidad
{
	SpriteRoca accion;
	int iDx;
public:
	Roca(Bitmap^ img) {
		x = rand() % 700;
		y = rand() % 700;
		ancho = img->Width;
		alto = img->Height;
		accion = animRoca;
		iDx = 0;
	}
	void mostrar(Graphics^ g, Bitmap^ img)
	{
		Rectangle corte = Rectangle(iDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, area(), corte, GraphicsUnit::Pixel);

	}
};

class Rocas
{
private:
	std::vector<Roca*> rocas;
public:
	Rocas(int n, Rectangle obj, Bitmap^ img)
	{
		for (int i = 0; i < n; i++)
		{
			Roca* obs = new Roca(img);
			if (obs->area().IntersectsWith(obj) == false && Colision(obs->area()) == false)
				rocas.push_back(obs);
			else {
				delete obs;
				i--;
			}
		}
	}
	~Rocas()
	{
		for (int i = 0; i < rocas.size(); i++) {
			delete rocas.at(i);
		}
	}

	int Eliminar(Rectangle rect) {
		int cant = 0;
		for (int i = 0; i < rocas.size(); i++) {
			if (rocas[i]->area().IntersectsWith(rect)) {
				delete rocas[i];
				rocas.erase(rocas.begin() + i--);
				cant++;
			}
		}
		return cant;
	}
	bool Colision(Rectangle obj) {
		for (Roca* obs : rocas) {
			if (obs->area().IntersectsWith(obj))
			{
				return true;
			}
		}
		return false;
	}
	void mover(Graphics^ g)
	{
		for (Roca* obs : rocas) {
			obs->mover(g);
		}
	}
	void mostrar(Graphics^ g, Bitmap^ img)
	{
		for (Roca* obs : rocas)
		{
			obs->mostrar(g, img);
		}
	}
	std::vector<Roca*>& GetRocas() { return rocas; }

};