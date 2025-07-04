#pragma once
#include "Entidad.h"

enum SpriteHowlDtroy
{
	HowlAnimStableIzquierda,
	HowlAnimStableDerecha,
	HowlCaminarIzquierda,
	HowlCaminarDerecha,
	HowlAturdidoIzquierda,
	HowlAturdidoDerecha,
	HowlAnimViolentIzquierda,
	HowlAnimViolentDerecha,
	HowlAtacarIzquierda,
	HOwlAtacarDerecha,
	HowlRasgaduraIzquierda,
	HowlRasgaduraDerecha,
	HowlMorirIzquierda,
	HowlMorirDerecha,
};

class HowlDtroy : public Entidad
{
private:
	int vidas;
	int puntos;
	int materiales;
	SpriteHowlDtroy  accion;

	bool pausadoIdle = false;
	clock_t tiempoPausaIdle = 0;
	const int duracionPausaIdleMs = 5000; 
	const int tiempoFrameMs = 100; 
	clock_t tiempoUltimoFrame = 0;

public:
	HowlDtroy(Bitmap^ img, int v) {
		x = 600;
		y = 150;
		dx = dy = 0;
		ancho = img->Width / 10;
		alto = img->Height / 14;

		accion = HowlAnimStableIzquierda;
		vidas = v;
		puntos = 0;
		tiempoUltimoFrame = clock();
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
	Rectangle HitBoxHowl() {
		return  Rectangle(x + ancho / 4, y + alto / 5, ancho / 2.2, alto * 4 / 5);
	}
	SpriteHowlDtroy GetAccion()
	{
		return accion;
	}
	void SetAccion(SpriteHowlDtroy value) {
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
		
		Rectangle corte = Rectangle(iDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, area(), corte, GraphicsUnit::Pixel);
		g->DrawRectangle(Pens::Black, area());
		g->DrawRectangle(Pens::Blue, HitBoxHowl());

		if (accion == HowlAnimStableIzquierda || accion == HowlAnimStableDerecha)
		{
			// Si está pausado, verificar si ya pasaron 5 segundos
			if (pausadoIdle)
			{
				if ((clock() - tiempoPausaIdle) >= duracionPausaIdleMs * CLOCKS_PER_SEC / 1000)
				{
					pausadoIdle = false;
					tiempoUltimoFrame = clock(); // reiniciar temporizador
				}
			}
			else
			{
				// Solo avanzar frame si pasó tiempo suficiente
				if ((clock() - tiempoUltimoFrame) >= tiempoFrameMs * CLOCKS_PER_SEC / 1000)
				{
					iDx++;

					if (iDx >= 6)
					{
						// Reinicia animación
						iDx = 0;
						pausadoIdle = true;
						tiempoPausaIdle = clock();
					}

					tiempoUltimoFrame = clock();
				}
			}
		}
		else if (accion >= HowlCaminarIzquierda && accion <= HowlCaminarDerecha && (dx != 0 || dy != 0))
		{
			iDx = (iDx + 1) % 4;

		}
		else if (accion >= HowlAturdidoIzquierda && accion <= HowlAturdidoDerecha)
		{
			iDx = (iDx + 1) % 1;

		}
		else if (accion >= HowlAnimViolentIzquierda && accion <= HowlAnimViolentDerecha)
		{
			iDx = (iDx + 1) % 8;

		}

		else if (accion >= HowlAtacarIzquierda && accion <= AtacarDerecha)
		{
			iDx = (iDx + 1) % 10;
			if (iDx == 0)
			{
				accion = (SpriteHowlDtroy)(accion - 8);
			}
		}
		else if (accion >= HowlRasgaduraIzquierda && accion <= HowlRasgaduraDerecha)
		{
			iDx = (iDx + 1) % 5;
		}
		else if (accion >= HowlMorirIzquierda && accion <= HowlMorirDerecha)
		{
			iDx = (iDx + 1) % 8;
		}


	}
};