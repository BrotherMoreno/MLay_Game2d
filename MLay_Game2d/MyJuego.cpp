#include "MyJuego.h"
#include "Nivel3Formh.h"
#include "Nivel2Form.h"
#include "MyMenuForm.h"
#include <iostream>
using namespace System;
using namespace MLayGame2d;

void main() {
	Application::EnableVisualStyles();
	Application::Run(gcnew MyMenuForm());
}