#pragma once
#pragma once
#include "Entidad.h"
enum SpriteCoins {
	animCoins,
};

class Coin : public Entidad
{
	SpriteCoins accion;
	int iDx;
public:
	Coin(Bitmap^ img) {
		x = rand() % 500;
		y = rand() % 400;
		ancho = img->Width/8;
		alto = img->Height;
		accion = animCoins;
	}
	void mostrar(Graphics^ g, Bitmap^ img)
	{
		Rectangle corte = Rectangle(iDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, area(), corte, GraphicsUnit::Pixel);
		g->DrawRectangle(Pens::Black, area());

		if (accion == animCoins) {
			iDx = (iDx + 1) % 8;

		}
	}
};

class Coins
{
private:
	std::vector<Coin*> coins;
public:
	Coins(int n, Rectangle obj, Bitmap^ img)
	{
		for (int i = 0;i < n;i++)
		{
			Coin* obs = new Coin(img);
			if (obs->area().IntersectsWith(obj) == false && Colision(obs->area()) == false)
				coins.push_back(obs);
			else {
				delete obs;
				i--;
			}
		}
	}
	~Coins()
	{
		for (int i;i < coins.size();i++) {
			delete coins.at(i);
		}
	}

	int Eliminar(Rectangle rect) {
		int cant = 0;
		for (int i = 0;i < coins.size();i++) {
			if (coins[i]->area().IntersectsWith(rect)) {
				coins.erase(coins.begin() + i--);
				cant++;
			}
		}
		return cant;
	}
	bool Colision(Rectangle obj) {
		for (Coin* obs : coins) {
			if (obs->area().IntersectsWith(obj))
			{
				return true;
			}
		}
		return false;
	}
	void mover(Graphics^ g)
	{
		for (Coin* obs : coins) {
			obs->mover(g);
		}
	}
	void mostrar(Graphics^ g, Bitmap^ img)
	{
		for (Coin* obs : coins)
		{
			obs->mostrar(g, img);
		}
	}
};
