#pragma once
#include "Entidad.h"
#include <vector>
#include <cmath>

enum SpriteEnemigo
{
	accionDañoIzquierdaaEnemigo,
	CaminarDerechaEnemigo,
	CaminarIzquierdaEnemigo,
	accionDañoDerechaEnemigo

};

class Enemigo : public Entidad {
private:
	SpriteEnemigo accion;
	int iDx;
	int visionRadio = 120;
	int margen = 30;
	int vida = 5; // Vida máxima

public:
	// Nuevo constructor con posición explícita
	Enemigo(Bitmap^ img, int px, int py)
	{
		x = px;
		y = py;
		iDx = 0;
		accion = CaminarDerechaEnemigo;
		if (rand() % 2 == 0) {
			dx = rand() % 11 - 5;
			if (dx == 0) dx = 5;
			dy = 0;
		}
		else {
			dy = rand() % 11 - 5;
			if (dy == 0) dy = 5;
			dx = 0;
		}
		ancho = img->Width / 4;
		alto = img->Height / 4;
	}

	void RestarVida() { if (vida > 0) vida--; }
	int GetVida() { return vida; }
	bool EstaMuerto() { return vida <= 0; }

	// ... (resto igual)

	void Mover(Graphics^ g, int jugadorX, int jugadorY, const std::vector<Enemigo*>& todos) {
		int centroX = x + ancho / 2;
		int centroY = y + alto / 2;
		int dxJugador = jugadorX - centroX;
		int dyJugador = jugadorY - centroY;
		double distancia = std::sqrt(dxJugador * dxJugador + dyJugador * dyJugador);

		// --- Separación entre enemigos ---
		int minDist = ancho;
		double sepX = 0, sepY = 0;
		for (const auto& otro : todos) {
			if (otro == this || otro->EstaMuerto()) continue;
			int ox = otro->GetX() + otro->GetAncho() / 2;
			int oy = otro->GetY() + otro->GetAlto() / 2;
			double dist = std::sqrt((centroX - ox) * (centroX - ox) + (centroY - oy) * (centroY - oy));
			if (dist < minDist && dist > 0.1) {
				sepX += (centroX - ox) / dist;
				sepY += (centroY - oy) / dist;
			}
		}
		// --- Fin separación ---

		double movX = 0, movY = 0;
		const int velocidad = 5;

		if (distancia < visionRadio) {
			if (distancia > margen) {
				movX = dxJugador;
				movY = dyJugador;
			}
			// Si está muy cerca del jugador, solo separación
		}
		// Si está fuera de visión, patrulla en la dirección actual o aleatoria
		else {
			if (dx == 0 && dy == 0) {
				if (rand() % 2 == 0) {
					dx = rand() % 11 - 5;
					if (dx == 0) dx = 5;
					dy = 0;
				}
				else {
					dy = rand() % 11 - 5;
					if (dy == 0) dy = 5;
					dx = 0;
				}
			}
			movX = dx;
			movY = dy;
		}

		// Suma la separación
		movX += sepX * 2;
		movY += sepY * 2;

		// Normaliza el vector de movimiento para mantener velocidad constante
		double norm = std::sqrt(movX * movX + movY * movY);
		if (norm != 0) {
			dx = static_cast<int>(velocidad * movX / norm);
			dy = static_cast<int>(velocidad * movY / norm);
		}

		if (!(x + dx >= 0 && x + ancho + dx <= g->VisibleClipBounds.Width)) dx *= -1;
		if (!(y + dy >= 0 && y + alto + dy <= g->VisibleClipBounds.Height)) dy *= -1;
		if (dx < 0) accion = CaminarDerechaEnemigo;
		else if (dx > 0) accion = CaminarIzquierdaEnemigo;
		x += dx;
		y += dy;
	}
	void mostrar(Graphics^ g, Bitmap^ img) {
		// Dibuja círculo de visión
		int centroX = x + ancho / 2;
		int centroY = y + alto / 2;
		Pen^ penVision = gcnew Pen(Color::FromArgb(128, Color::Red), 1);
		/*g->DrawEllipse(penVision, centroX - visionRadio, centroY - visionRadio, visionRadio * 2, visionRadio * 2);
		delete penVision;*/

		// Dibuja barra de vida sobre el enemigo
		int barraAncho = ancho;
		int barraAlto = 8;
		int vidaMax = 5;
		int anchoVida = (int)((barraAncho - 2) * vida / (double)vidaMax);
		Rectangle fondoBarra(x, y - barraAlto - 2, barraAncho, barraAlto);
		Rectangle vidaBarra(x + 1, y - barraAlto - 1, anchoVida, barraAlto - 2);
		g->FillRectangle(Brushes::Gray, fondoBarra);
		g->FillRectangle(Brushes::LimeGreen, vidaBarra);
		g->DrawRectangle(Pens::Black, fondoBarra);

		Rectangle corte = Rectangle(iDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, area(), corte, GraphicsUnit::Pixel);
		//g->DrawRectangle(Pens::Black, area());

		if (accion == CaminarDerechaEnemigo) iDx = (iDx + 1) % 4;
		if (accion == CaminarIzquierdaEnemigo) iDx = (iDx + 1) % 4;
	}
};

class Enemigos {
private:
	std::vector<Enemigo*> enemigos;

	// Verifica si la posición está demasiado cerca de otro enemigo
	bool muyCerca(int x, int y, int ancho, int alto, int minDist) {
		for (auto* e : enemigos) {
			int ex = e->GetX() + e->GetAncho() / 2;
			int ey = e->GetY() + e->GetAlto() / 2;
			int cx = x + ancho / 2;
			int cy = y + alto / 2;
			double dist = std::sqrt((ex - cx) * (ex - cx) + (ey - cy) * (ey - cy));
			if (dist < minDist) return true;
		}
		return false;
	}

public:
	Enemigos(Bitmap^ img, int cant)
	{
		int minDist = 60; // Margen mínimo entre enemigos
		int ancho = img->Width / 10;
		int alto = img->Height / 8;
		int maxW = 700, maxH = 400;
		for (int i = 0; i < cant; i++) {
			int x, y, intentos = 0;
			do {
				x = rand() % (maxW - ancho);
				y = rand() % (maxH - alto);
				intentos++;
			} while (muyCerca(x, y, ancho, alto, minDist) && intentos < 100);
			enemigos.push_back(new Enemigo(img, x, y));
		}
	}

	~Enemigos()
	{
		for (Enemigo* E : enemigos) delete E;
	}

	bool Colision(Rectangle obj, int& idx)
	{
		for (int i = 0; i < enemigos.size(); ++i) {
			if (enemigos[i]->area().IntersectsWith(obj)) {
				idx = i;
				return true;
			}
		}
		return false;
	}

	void mover(Graphics^ g, int jugadorX, int jugadorY)
	{
		for (Enemigo* E : enemigos) {
			E->Mover(g, jugadorX, jugadorY, enemigos);
		}
	}

	void mostrar(Graphics^ g, Bitmap^ img)
	{
		for (auto it = enemigos.begin(); it != enemigos.end();) {
			if (!(*it)->EstaMuerto()) {
				(*it)->mostrar(g, img);
				++it;
			}
			else {
				delete* it;
				it = enemigos.erase(it);
			}
		}
	}

	// Permite acceso a los enemigos para lógica de daño
	std::vector<Enemigo*>& GetEnemigos() { return enemigos; }
};