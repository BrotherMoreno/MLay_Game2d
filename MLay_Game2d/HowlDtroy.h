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
	HowlAtacarDerecha,
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
	int xInicial;
	int yInicial;

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
		xInicial = x;
		yInicial = y;
		dx = 0;
		dy = 0;
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
	int GetXInicial() { return xInicial; }
	int GetYInicial() { return yInicial; }
	Point CentroRangoVision() {
		return Point(x + ancho / 2, y + alto / 2);
	}
	int RadioRangoVision() {
		return ancho ; // Ajusta aquí el tamaño del círculo (más pequeño que el ancho)
	}
	int RadioAtk() {
		return ancho*2/6 ; // Ajusta aquí el tamaño del círculo (más pequeño que el ancho)
	}
	Rectangle HitboxAtk() {
		return Rectangle(x+ ancho/6, y+alto/6, ancho *2/ 3, alto *2/ 3);

	}
	bool ActivaRangeVision(Rectangle rect)
	{
		return HitBoxHowlColision().IntersectsWith(rect);
	}
	Rectangle HitboxRangoVision()
	{
		int rangoAncho = ancho * 4;
		int rangoAlto = alto * 4/4;
		int offsetX = x - (rangoAncho - ancho) / 2;
		int offsetY = y - (rangoAlto - alto) / 2;
		return Rectangle(offsetX, offsetY, rangoAncho, rangoAlto);
	}
	Rectangle HitBoxHowlColision() {
		return  Rectangle(x + ancho * 2 / 6, y + alto * 1 / 4, ancho / 4, alto / 2);
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
	void moverHowl(Graphics^ g) {
		if (x + dx >= 0 && x + ancho + dx <= g->VisibleClipBounds.Width) {
			x += dx;
		}
		if (y + dy >= 0 && y + alto + dy <= g->VisibleClipBounds.Height) {
			y += dy;
		}
	}
	void mostrar(Graphics^ g, Bitmap^ img) {
		// Dibuja el círculo de rango de visión
		Point centro = CentroRangoVision();
		int radio = RadioRangoVision();
		int radioAtk = RadioAtk();
		g->DrawEllipse(Pens::Red, centro.X - radio, centro.Y - radio, radio * 2, radio * 2);
		//g->DrawEllipse(Pens::Black, centro.X - radioAtk, centro.Y - radioAtk, radioAtk * 2, radioAtk * 2);
		Rectangle corte = Rectangle(iDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, area(), corte, GraphicsUnit::Pixel);    
		g->DrawRectangle(Pens::Blue, HitBoxHowlColision());
		g->DrawRectangle(Pens::Black, HitboxAtk());
		g->DrawRectangle(Pens::Black, area());
		g->DrawRectangle(Pens::Red, HitboxRangoVision());

		if (accion == HowlAnimStableIzquierda || accion == HowlAnimStableDerecha)
		{
			if (pausadoIdle)
			{
				if ((clock() - tiempoPausaIdle) >= duracionPausaIdleMs * CLOCKS_PER_SEC / 1000)
				{
					pausadoIdle = false;
					tiempoUltimoFrame = clock();
				}
			}
			else
			{
				if ((clock() - tiempoUltimoFrame) >= tiempoFrameMs * CLOCKS_PER_SEC / 1000)
				{
					iDx++;

					if (iDx >= 6)
					{
						// Reinicia animación
						iDx = 0;
						pausadoIdle = true;
						tiempoPausaIdle = clock();

						// Alterna entre izquierda y derecha
						if (accion == HowlAnimStableIzquierda)
							accion = HowlAnimStableDerecha;
						else if (accion == HowlAnimStableDerecha)
							accion = HowlAnimStableIzquierda;
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

		else if (accion >= HowlAtacarIzquierda && accion <= HowlAtacarDerecha)
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