#pragma once
#pragma once
#include "Nivel2.h"
#include "Nivel3Formh.h"
namespace MLayGame2d {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Nivel2Form
	/// </summary>
	public ref class Nivel2Form : public System::Windows::Forms::Form
	{
		ClaseControladora2^ controladora2;
	public:
		Nivel2Form(void)
		{
			InitializeComponent();
			controladora2 = gcnew ClaseControladora2(40, 7, 30);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Nivel2Form()
		{
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Nivel2Form::typeid));
			this->Clock = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// Clock
			// 
			this->Clock->Enabled = true;
			this->Clock->Interval = 33;
			this->Clock->Tick += gcnew System::EventHandler(this, &Nivel2Form::Clock_Tick);
			// 
			// Nivel2Form
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
			this->Name = L"Nivel2Form";
			this->Text = L"MLAY";
			this->Load += gcnew System::EventHandler(this, &Nivel2Form::Nivel2Form_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Nivel2Form::Nivel2Form_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Nivel2Form::Nivel2Form_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Clock_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ bfc = BufferedGraphicsManager::Current;
		BufferedGraphics^ bf = bfc->Allocate(g, this->ClientRectangle);

		bf->Graphics->DrawImage(fondoRenderizado, 0, 0);
		controladora2->mostrar(bf->Graphics);
		bf->Render(g);

		if (controladora2->mover(g) == false) {
			this->Close();
			return;
		}

		// --- TRANSICIÓN DE NIVEL ---
		if (!esperandoTransicion && controladora2->DebePasarNivel()) {
			esperandoTransicion = true;
			tiempoInicioTransicion = clock();
		}
		if (esperandoTransicion && (clock() - tiempoInicioTransicion) > 3000) { // 3 segundos
			this->Clock->Enabled = false; // Detén el timer para evitar doble ejecución
			MLayGame2d::Nivel3Formh^ nivel3 = gcnew MLayGame2d::Nivel3Formh();
			nivel3->Show();
			this->Hide(); // Oculta el formulario actual en vez de cerrarlo inmediatamente
			// Opcional: puedes usar this->Close(); si tu aplicación no termina al cerrar este form
		}
	}
	private: System::Void Nivel2Form_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		controladora2->movimientoJugador(true, e->KeyCode);
	}
	private: System::Void Nivel2Form_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		controladora2->movimientoJugador(false, e->KeyCode);
		controladora2->DispararJugador(e->KeyCode);
	}
	private: System::Void Nivel2Form_Load(System::Object^ sender, System::EventArgs^ e) {
		fondoRenderizado = gcnew Bitmap(this->ClientSize.Width, this->ClientSize.Height);
		Graphics^ gFondo = Graphics::FromImage(fondoRenderizado);
		gFondo->DrawImage(this->BackgroundImage, 0, 0, this->ClientSize.Width, this->ClientSize.Height);
		delete gFondo;
	}
	};
	// este es el juego bien
}