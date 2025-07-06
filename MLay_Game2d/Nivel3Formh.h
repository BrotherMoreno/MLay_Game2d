#pragma once
#include "Nivel3.h"

namespace MLayGame2d {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Nivel3Formh : public System::Windows::Forms::Form
	{
		ClaseControladorJuego3^ juego;
	public:
		Nivel3Formh(void)
		{
			InitializeComponent();
			juego = gcnew ClaseControladorJuego3(10, 7, 30);
		}

	protected:
		~Nivel3Formh()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ Clock;
	private: System::ComponentModel::IContainer^ components;
	private:
		Bitmap^ fondoRenderizado;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Nivel3Formh::typeid));
			this->Clock = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// Clock
			// 
			this->Clock->Enabled = true;
			this->Clock->Interval = 33;
			this->Clock->Tick += gcnew System::EventHandler(this, &Nivel3Formh::Clock_Tick);
			// 
			// Nivel3Formh
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1008, 507);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Name = L"Nivel3Formh";
			this->Text = L"MLAY";
			this->Load += gcnew System::EventHandler(this, &Nivel3Formh::Nivel3Formh_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Nivel3Formh::Nivel3Formh_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Nivel3Formh::Nivel3Formh_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Clock_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ bfc = BufferedGraphicsManager::Current;
		BufferedGraphics^ bf = bfc->Allocate(g, this->ClientRectangle);

		// Dibuja el fondo pre-renderizado (rápido)
		if (fondoRenderizado != nullptr)
			bf->Graphics->DrawImage(fondoRenderizado, 0, 0);

		// Luego el juego encima
		juego->mostrar(bf->Graphics);
		bf->Render(g);

		if (juego->mover(g) == false) {
			this->Close();
		}

		delete bf;
		delete g;
	}
	private: System::Void Nivel3Formh_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		juego->movimientoJugador(true, e->KeyCode);
		juego->moverMateriales(true, e->KeyCode);
		
	}
	private: System::Void Nivel3Formh_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		juego->movimientoJugador(false, e->KeyCode);
	}
	private: System::Void Nivel3Formh_Load(System::Object^ sender, System::EventArgs^ e) {
		fondoRenderizado = gcnew Bitmap(this->ClientSize.Width, this->ClientSize.Height);
		Graphics^ gFondo = Graphics::FromImage(fondoRenderizado);
		if (this->BackgroundImage != nullptr)
			gFondo->DrawImage(this->BackgroundImage, 0, 0, this->ClientSize.Width, this->ClientSize.Height);
		delete gFondo;
	}
	};
}