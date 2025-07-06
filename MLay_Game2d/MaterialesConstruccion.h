#pragma once
#include <vector>
#include "Entidad.h"
using namespace System;
using namespace System::Drawing;

class MaterialConstruccion : public Entidad
{
public:
    MaterialConstruccion(Bitmap^ img, int px, int py) {
        x = px; // Correct assignment
        y = py;
        ancho = img->Width;
        alto = img->Height;
    }
    void mostrar(Graphics^ g, Bitmap^ img)
    {
        g->DrawImage(img, x, y);
        
    }
};

class MaterialesConstruccion
{
private:
    std::vector<MaterialConstruccion*> Materiales;
public:
    // Default constructor
    MaterialesConstruccion() {}

    // Optional: Constructor que recibe una imagen y posición inicial
    MaterialesConstruccion(Bitmap^ img, int valueX, int valueY) {
        Materiales.push_back(new MaterialConstruccion(img, valueX, valueY));
    }

    ~MaterialesConstruccion()
    {
        for (size_t i = 0; i < Materiales.size(); i++) {
            delete Materiales[i];
        }
        Materiales.clear();
    }

    // Método para agregar un material dinámicamente
    void AgregarMaterial(Bitmap^ img, int x, int y) {
        Materiales.push_back(new MaterialConstruccion(img, x, y));
    }

    std::vector<MaterialConstruccion*>& obtenerVector() {
        return Materiales;
    }

    int Eliminar(Rectangle rect) {
        int cant = 0;
        for (size_t i = 0; i < Materiales.size(); ) {
            if (Materiales[i]->area().IntersectsWith(rect)) {
                delete Materiales[i];
                Materiales.erase(Materiales.begin() + i);
                cant++;
            }
            else {
                i++;
            }
        }
        return cant;
    }
    bool Colision(Rectangle obj) {
        for (MaterialConstruccion* obs : Materiales) {
            if (obs->area().IntersectsWith(obj))
            {
                return true;
            }
        }
        return false;
    }
    void mover(Graphics^ g)
    {
        for (MaterialConstruccion* obs : Materiales) {
            obs->mover(g);
        }
    }
    void mostrar(Graphics^ g, Bitmap^ img)
    {
        for (MaterialConstruccion* obs : Materiales)
        {
            obs->mostrar(g, img);
        }
    }
};