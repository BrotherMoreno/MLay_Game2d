#pragma once
#include "Entidad.h"

class Obstaculo : public Entidad
{
public:
	Obstaculo(Bitmap^ img) {
		x = rand() % 500;
		y = rand() % 500;
		ancho = img->Width;
		alto = img->Height;
	}
	void mostrar(Graphics^ g, Bitmap^ img)
	{
		g->DrawImage(img, area());
		g->DrawRectangle(Pens::Black, area());
	}
};

class Obstaculos
{
private:
	std::vector<Obstaculo*> obstaculos;
public:
	Obstaculos(int n, Rectangle obj, Bitmap^ img)
	{
		for (int i = 0;i < n;i++)
		{
			Obstaculo* obs = new Obstaculo(img);
			if (obs->area().IntersectsWith(obj) == false&& Colision(obs->area())==false)
				obstaculos.push_back(obs);
			else {
				delete obs;
				i--;
			}

		}
	}
	~Obstaculos()
	{
		for (int i;i < obstaculos.size();i++) {
			delete obstaculos.at(i);
		}
	}


	bool Colision(Rectangle obj) {
		for (Obstaculo* obs : obstaculos) {
			if (obs->area().IntersectsWith(obj))
			{
				return true;
			}
		}
		return false;
	}
	void mover(Graphics^ g)
	{
		for (Obstaculo* obs : obstaculos) {
			obs->mover(g);
		}
	}
	void mostrar(Graphics^ g, Bitmap^img)
	{
		for (Obstaculo* obs : obstaculos)
		{
			obs->mostrar(g, img);
		}
	}
};
