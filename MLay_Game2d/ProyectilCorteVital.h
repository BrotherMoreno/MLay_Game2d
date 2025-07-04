
#pragma once
#include "Entidad.h"

enum SpriteProyectilLay {
	giroIzquierda,
	giroDerecha
};
class CorteVital : public Entidad
{
	SpriteProyectilLay accion;
	int iDx = 0;
public:
	CorteVital(int x, int y, int dx, int dy, Bitmap^ img ) 
	{
		this->x = x;
		this->y = y;
		this->dx = dx;
		this->dy = dy;

		ancho = img->Width/6;
		alto = img->Height/2;
		accion = giroIzquierda;

	}
	void mover(Graphics^ g) override {
		x += dx;
		y += dy;
	}
	void mostrar(Graphics^ g, Bitmap^ img) {
		Rectangle corte = Rectangle(iDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, area(), corte, GraphicsUnit::Pixel);	

		if (accion == giroDerecha) {
			iDx = (iDx + 1) % 6;

		}
		if (accion == giroIzquierda) {
			iDx = (iDx + 1) % 6;


		}
	}
public:
};

class CorteVitales
 
{
	std::vector<CorteVital* > corteVitales;
public:
	~CorteVitales()
	{
		for (CorteVital* cv : corteVitales) {
			delete cv;
		}
		
	}

	void Agregar(int x, int y, int dx,int dy, Bitmap ^img) 
	{
		corteVitales.push_back(new CorteVital(x,y,dx,dy,img));
	}
	void Elminar(int pos) 
	{
		corteVitales.erase(corteVitales.begin() + pos);
	}

	int size() 
	{
		return corteVitales.size();
	}
	CorteVital* Get(int pos) 
	{
		return corteVitales[pos];
	}

	bool Colision(Rectangle obj) 
	{
		for (CorteVital* cv : corteVitales) {
			if (cv->NextArea().IntersectsWith(obj))
			{
				return true;
			}
		}
		return false;
	}
	void mover(Graphics^ g)
	{
		for (CorteVital* cv : corteVitales) {
			cv->mover(g);
		}
	}
	void mostrar(Graphics^ g, Bitmap ^img)
	{
		for (CorteVital* cv : corteVitales)
		{
			cv->mostrar(g, img);
		}
	}
};