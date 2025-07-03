#pragma once
#include "Entidad.h"

enum SpriteJugador
{
	CaminarDerecha,
	CaminarIzquierda,
	SaltarMirandoDerecha,
	saltarMirandoIzquierda,
	AtacarDerecha,
	AtacarIzquierda,
	Desaparecer,
};

class Jugador : public Entidad
{
private:
	int vidas;
	int puntos;
	int materiales; 
	SpriteJugador  accion;
public:
	Jugador(Bitmap^ img, int v  ) {
		x = 60;
		y = 60;
		dx = dy = 0;
		ancho = img->Width/12;
		alto = img->Height/7;

		accion = CaminarDerecha;
		vidas = v;
		puntos = 0;
	}
	void SetVida(int value) {
		vidas += value;
	}
	int GetVida() {
		return vidas;
	}
	int GetiDx() {
		return iDx;
	}
	int GetPuntos() 
	{
		return puntos;
	}
	void SetPuntos(int value) 
	{
		puntos += value;
	}

	SpriteJugador GetAccion() 
	{
		return accion;
	}
	void SetAccion(SpriteJugador value) {
		if (accion != value) {
			iDx = 0;
		}
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
	void mostrar(Graphics^ g, Bitmap^ img) {
		g->DrawString("vidas: " + vidas, gcnew Font("arial", 12), Brushes::Black, 0, 0);
		g->DrawString("puntos: " + puntos, gcnew Font("arial", 12), Brushes::Black, 0, 40);
		Rectangle corte = Rectangle(iDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, area(), corte, GraphicsUnit::Pixel);
		//g->DrawRectangle(Pens::Black, area());
		g->DrawRectangle(Pens::Blue, HitBox());
		
		if(accion>=CaminarDerecha && accion<=CaminarIzquierda&&(dx!=0||dy!=0))
		{
			iDx = (iDx + 1) % 8;
		}
		else if (accion >= SaltarMirandoDerecha && accion <= saltarMirandoIzquierda) 
		{
			iDx = (iDx + 1) % 12;

		}
			
		else if (accion >= AtacarDerecha && accion <= AtacarIzquierda) 
		{
			iDx = (iDx + 1) % 8;
			if (iDx==0)
			{
				accion = (SpriteJugador)(accion - 4);
			}
		}
		else if (accion == Desaparecer) 
		{
			iDx = (iDx + 1) % 11;
		}
		

	}
};