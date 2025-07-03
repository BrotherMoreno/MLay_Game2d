#pragma once
#include "Juego.h"
namespace MLayGame2d {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyJuego
	/// </summary>
	public ref class MyJuego : public System::Windows::Forms::Form
	{
		ControladorJuego^ juego;
	public:
		MyJuego(void)
		{
			InitializeComponent();
			juego = gcnew ControladorJuego(10,7,30);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyJuego()
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
		/// <summary>
		/// Required designer variable.
		/// </summary>
		 

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyJuego::typeid));
			this->Clock = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// Clock
			// 
			this->Clock->Enabled = true;
			this->Clock->Interval = 33;
			this->Clock->Tick += gcnew System::EventHandler(this, &MyJuego::Clock_Tick);
			// 
			// MyJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(830, 467);
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Name = L"MyJuego";
			this->Text = L"MyJuego";
			this->Load += gcnew System::EventHandler(this, &MyJuego::MyJuego_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyJuego::MyJuego_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyJuego::MyJuego_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Clock_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ bfc = BufferedGraphicsManager::Current;
		BufferedGraphics^ bf = bfc->Allocate(g, this->ClientRectangle);

		// Dibuja el fondo pre-renderizado (rápido)
		bf->Graphics->DrawImage(fondoRenderizado, 0, 0);

		// Luego el juego encima
		juego->mostrar(bf->Graphics);
		bf->Render(g);

		if (juego->mover(g) == false) {
			this->Close();
		}
	}
	private: System::Void MyJuego_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		juego->movimientoJugador(true, e->KeyCode);
	}
	private: System::Void MyJuego_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		juego->movimientoJugador(false, e->KeyCode);
		juego->DispararJugador(e->KeyCode);
	}
	private: System::Void MyJuego_Load(System::Object^ sender, System::EventArgs^ e) {
		fondoRenderizado = gcnew Bitmap(this->ClientSize.Width, this->ClientSize.Height);
		Graphics^ gFondo = Graphics::FromImage(fondoRenderizado);
		gFondo->DrawImage(this->BackgroundImage, 0, 0, this->ClientSize.Width, this->ClientSize.Height);
		delete gFondo;
	}
	};
	// este es el juego bien
}



