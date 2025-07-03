
#pragma once
#include "Entidad.h"
class CorteVital : public Entidad
{
private:
	CorteVital(int x, int y, int dx, int dy ) 
	{
		this->x = x;
		this->y = y;
		this->dy = dy;
		this->dx = dx;

		ancho = alto = 7;
	}
public:
};

class CorteVitales
 
{
	std::vector<CorteVital* > corteVitales;
public:
	~CorteVitales()
	{
		for (int i;i < corteVitales.size();i++) 
			delete corteVitales.at(i);
		
	}

	void Agregar(CorteVital* corteVital) 
	{
		corteVitales.push_back(corteVital);
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
	void mostrar(Graphics^ g)
	{
		for (CorteVital* cv : corteVitales)
		{
			cv->mostrar(g, nullptr);
		}
	}
};