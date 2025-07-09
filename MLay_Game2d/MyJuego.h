#pragma once
#include "Juego.h"
#include "Nivel2Form.h"
using namespace System::Media;
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
			if (nivel1SoundPlayer != nullptr) {
				nivel1SoundPlayer->Stop();
			}
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ Clock;
	private: System::ComponentModel::IContainer^ components;

	private:
		bool esperandoTransicion = false;
		clock_t tiempoInicioTransicion = 0;
		Bitmap^ fondoRenderizado;
		SoundPlayer^ nivel1SoundPlayer;
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
			this->ClientSize = System::Drawing::Size(1008, 507);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyJuego";
			this->Text = L"MLAY";
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
			return;
		}
		juego->movimientoHowlDtroy();

		// --- TRANSICIÓN DE NIVEL ---
		if (!esperandoTransicion && juego->DebePasarNivel()) {
			esperandoTransicion = true;
			tiempoInicioTransicion = clock();
		}
		if (esperandoTransicion && (clock() - tiempoInicioTransicion) > 3000) { // 3 segundos
			this->Clock->Enabled = false; // Detén el timer para evitar doble ejecución
			MLayGame2d::Nivel2Form^ nivel2 = gcnew MLayGame2d::Nivel2Form();
			nivel2->Show();
			this->Hide(); // Oculta el formulario actual
			// Opcional: puedes usar this->Close(); si tu aplicación no termina al cerrar este form
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

		nivel1SoundPlayer = gcnew SoundPlayer("Nivel1Sonido.wav");
		try {
			nivel1SoundPlayer->Load();
			nivel1SoundPlayer->PlayLooping();
		}
		catch (Exception^ ex) {
			MessageBox::Show("No se pudo reproducir la música del nivel 1: " + ex->Message);
		}
	}
	};
	// este es el juego bien
}



