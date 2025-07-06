#pragma once
#include "Jugador.h"
#include "Obstaculo.h"
#include "Enemigo.h"
#include "ProyectilCorteVital.h"
#include "Coins.h"
#include "HowlDtroy.h"
#include "MaterialesConstruccion.h"

using namespace System::Collections::Generic;

ref class ClaseControladorJuego3
{
private:
	Jugador* jugador;
	Obstaculos* obstaculos;
	MaterialesConstruccion* Materiales;
	MaterialConstruccion* Material;
	Bitmap^ imgLobo;
	Bitmap^ imgPersonaje;
	Bitmap^ imgEnemigo;
	Bitmap^ imgProyectilCorteVital;
	Bitmap^ imgCoins;
	Bitmap^ imgHowlDtroy;

	Bitmap^ Material0;
	Bitmap^ Material1;
	Bitmap^ Material2;
	Bitmap^ Material3;
	Bitmap^ Material4;
	Bitmap^ Material5;
	Bitmap^ Material6;
	Bitmap^ Material7;
	Bitmap^ Material8;
	Bitmap^ Material9;

	int tiempo;

	// Estado para materiales
	bool materialVisible = false;
	int materialActual = 0;

	// Variables de posición para el material
	int materialX = 100;
	int materialY = 100;
	int materialVel = 10; // Velocidad de movimiento de la imagen

	List<Bitmap^>^ imagenesMateriales;

	Bitmap^ getMaterialBitmap(int idx) {
		switch (idx) {
		case 0: return Material0;
		case 1: return Material1;
		case 2: return Material2;
		case 3: return Material3;
		case 4: return Material4;
		case 5: return Material5;
		case 6: return Material6;
		case 7: return Material7;
		case 8: return Material8;
		case 9: return Material9;
		default: return Material0;
		}
	}

public:
	ClaseControladorJuego3(int v, int E, int t) {
		imgLobo = gcnew Bitmap("img/powerPurple.png");
		imgPersonaje = gcnew Bitmap("img/LaySprite2.png");
		imgEnemigo = gcnew Bitmap("img/powerLayCorteVital.png");
		imgProyectilCorteVital = gcnew Bitmap("img/powerLayCorteVital.png");
		imgCoins = gcnew Bitmap("img/coins3.png");
		imgHowlDtroy = gcnew Bitmap("img/SpriteHowlDtroy7.png");

		//materiales pe sanasos ;V
		Material0 = gcnew Bitmap("img/arbol2.png");
		Material1 = gcnew Bitmap("img/tierra.png");
		Material2 = gcnew Bitmap("img/farolPartebaja.png");
		Material3 = gcnew Bitmap("img/farolParteMedio.png");
		Material4 = gcnew Bitmap("img/farolParteArriba.png");
		Material5 = gcnew Bitmap("img/pozo1.png");
		Material6 = gcnew Bitmap("img/pozo2.png");
		Material7 = gcnew Bitmap("img/pozo3.png");
		Material8 = gcnew Bitmap("img/pozo4.png");
		Material9 = gcnew Bitmap("img/SpriteHowlDtroy7.png");

		jugador = new Jugador(imgPersonaje, v);
		obstaculos = new Obstaculos(5, jugador->area(), imgLobo);
		Materiales = nullptr;
		tiempo = t * 1000;
		imagenesMateriales = gcnew List<Bitmap^>(); // Inicializa la lista
	}

	~ClaseControladorJuego3() {
		delete jugador;
		delete obstaculos;
		delete imgLobo;
		delete imgPersonaje;
		delete imgEnemigo;
		delete imgProyectilCorteVital;
		delete imgCoins;
		delete imgHowlDtroy;
		delete Materiales;
	}

	void moverMateriales(bool accion, Keys tecla)
	{
		if (accion) {
			if (tecla == Keys::Q) {
				materialVisible = true;
			}
			else if (tecla == Keys::D0) {
				materialActual = 0;
			}
			else if (tecla == Keys::D1) {
				materialActual = 1;
			}
			else if (tecla == Keys::D2) {
				materialActual = 2;
			}
			else if (tecla == Keys::D3) {
				materialActual = 3;
			}
			else if (tecla == Keys::D4) {
				materialActual = 4;
			}
			else if (tecla == Keys::D5) {
				materialActual = 5;
			}
			else if (tecla == Keys::D6) {
				materialActual = 6;
			}
			else if (tecla == Keys::D7) {
				materialActual = 7;
			}
			else if (tecla == Keys::D8) {
				materialActual = 8;
			}
			else if (tecla == Keys::D9) {
				materialActual = 9;
			}
			// Movimiento con WASD
			else if (tecla == Keys::W) {
				materialY -= materialVel;
			}
			else if (tecla == Keys::S) {
				materialY += materialVel;
			}
			else if (tecla == Keys::A) {
				materialX -= materialVel;
			}
			else if (tecla == Keys::D) {
				materialX += materialVel;
			}
			else if (tecla == Keys::Space) {
				// Si la colección aún no existe, créala
				if (Materiales == nullptr) {
					Materiales = new MaterialesConstruccion();
				}
				Bitmap^ imgActual = getMaterialBitmap(materialActual);
				Materiales->AgregarMaterial(imgActual, materialX, materialY);
				imagenesMateriales->Add(imgActual); // Usa Add en vez de push_back
			}
		}
	}

	// Llama esta función en tu método de renderizado
	void mostrarMaterial(Graphics^ g)
	{
		if (materialVisible) {
			Bitmap^ img = getMaterialBitmap(materialActual);
			g->DrawImage(img, materialX, materialY);
			g->DrawRectangle(Pens::Black, materialX, materialY, img->Width, img->Height);
		}
	}

	void movimientoJugador(bool accion, Keys tecla)
	{
		int v = 13;
		if (accion == true)
		{
			if (tecla == Keys::Up)
			{
				jugador->SetDy(-v);
				if (jugador->GetAccion() == CaminarDerecha)
					jugador->SetAccion(CaminarDerecha);
				else {
					jugador->SetAccion(CaminarIzquierda);
				}
			}
			else if (tecla == Keys::Down)
			{
				jugador->SetDy(v);
				if (jugador->GetAccion() == CaminarIzquierda)
					jugador->SetAccion(CaminarIzquierda);
				else {
					jugador->SetAccion(CaminarDerecha);
				}
			}
			else if (tecla == Keys::Left)
			{
				jugador->SetAccion(CaminarIzquierda);
				jugador->SetDx(-v);
			}
			else if (tecla == Keys::Right)
			{
				jugador->SetAccion(CaminarDerecha);
				jugador->SetDx(v);
			}
			else if (tecla == Keys::X)
			{
				if (jugador->GetAccion() == CaminarDerecha)
					jugador->SetAccion(AtacarDerecha);
				else if (jugador->GetAccion() == CaminarIzquierda)
					jugador->SetAccion(AtacarIzquierda);
			}
		}
		else
		{
			if (tecla == Keys::Up)
				jugador->SetDy(0);
			else if (tecla == Keys::Down)
				jugador->SetDy(0);
			else if (tecla == Keys::Left)
				jugador->SetDx(0);
			else if (tecla == Keys::Right)
				jugador->SetDx(0);
		}
	}

	bool mover(Graphics^ g)
	{
		
		jugador->mover(g);
		return true;
	}
	void mostrar(Graphics^ g)
	{
		

		// Mostrar cada material con la imagen que tenía al ser colocado
		if (Materiales != nullptr) {
			auto& vec = Materiales->obtenerVector();
			for (int i = 0; i < (int)vec.size(); ++i) {
				if (i < imagenesMateriales->Count) {
					vec[i]->mostrar(g, imagenesMateriales[i]);
				}
			}
		}

		mostrarMaterial(g); // Imagen flotante
		jugador->mostrar(g, imgPersonaje);
	}
};