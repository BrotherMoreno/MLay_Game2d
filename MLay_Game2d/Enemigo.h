#pragma once
#include"Entidad.h"

class Enemigo :public Entidad { 
public:
	Enemigo(Bitmap^ img) 
	{
		x = rand() % 200;
		y = rand() % 200;

		ancho = img->Width;
		alto = img->Height;

	}
	void mostrar(Graphics^ g, Bitmap^ img) {

	}
private:

};