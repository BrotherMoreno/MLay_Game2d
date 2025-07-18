#pragma once
#include "MyJuego.h"
#include "Nivel2Form.h"
#include "Nivel3Formh.h"
#include "Instrucciones.h"
#include "Creditos.h"

// Agrega este using para el reproductor de sonido
using namespace System::Media;

namespace MLayGame2d {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyMenuForm
	/// </summary>
	public ref class MyMenuForm : public System::Windows::Forms::Form
	{
	public:
		MyMenuForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyMenuForm()
		{
			// Detener el sonido al cerrar el formulario
			if (menuSoundPlayer != nullptr) {
				menuSoundPlayer->Stop();
			}
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Jugar;
	private: System::Windows::Forms::Button^ instrucciones;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;

	// Agrega el reproductor de sonido como miembro privado
	private:
		SoundPlayer^ menuSoundPlayer;

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyMenuForm::typeid));
			this->Jugar = (gcnew System::Windows::Forms::Button());
			this->instrucciones = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Jugar
			// 
			this->Jugar->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Jugar.BackgroundImage")));
			this->Jugar->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Jugar->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Jugar->ForeColor = System::Drawing::Color::Fuchsia;
			this->Jugar->Location = System::Drawing::Point(70, 434);
			this->Jugar->Name = L"Jugar";
			this->Jugar->Size = System::Drawing::Size(159, 58);
			this->Jugar->TabIndex = 0;
			this->Jugar->Text = L"Jugar";
			this->Jugar->UseVisualStyleBackColor = true;
			this->Jugar->Click += gcnew System::EventHandler(this, &MyMenuForm::button1_Click);
			// 
			// instrucciones
			// 
			this->instrucciones->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"instrucciones.BackgroundImage")));
			this->instrucciones->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->instrucciones->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->instrucciones->ForeColor = System::Drawing::Color::Fuchsia;
			this->instrucciones->Location = System::Drawing::Point(265, 434);
			this->instrucciones->Name = L"instrucciones";
			this->instrucciones->Size = System::Drawing::Size(159, 58);
			this->instrucciones->TabIndex = 1;
			this->instrucciones->Text = L"instrucciones";
			this->instrucciones->UseVisualStyleBackColor = true;
			this->instrucciones->Click += gcnew System::EventHandler(this, &MyMenuForm::instrucciones_Click);
			// 
			// button1
			// 
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::Color::Fuchsia;
			this->button1->Location = System::Drawing::Point(455, 434);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(159, 58);
			this->button1->TabIndex = 2;
			this->button1->Text = L"creditos";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyMenuForm::button1_Click_1);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button2->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::Color::Fuchsia;
			this->button2->Location = System::Drawing::Point(643, 434);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(159, 58);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Salir ";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyMenuForm::button2_Click);
			// 
			// MyMenuForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(886, 540);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->instrucciones);
			this->Controls->Add(this->Jugar);
			this->DoubleBuffered = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyMenuForm";
			this->Text = L"MLay";
			this->Load += gcnew System::EventHandler(this, &MyMenuForm::MyMenuForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		// Detener el sonido del men� antes de abrir el juego
		if (menuSoundPlayer != nullptr) {
			menuSoundPlayer->Stop();
		}

		MLayGame2d::MyJuego^ myJuego = gcnew MLayGame2d::MyJuego();
		myJuego->Show();
		this->Hide();
	}

	private: System::Void instrucciones_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Hide();
		Instrucciones^ instrucciones = gcnew Instrucciones();
		instrucciones->ShowDialog();
		this->Show();
	}
	private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
		this->Hide();
		Creditos^ creditos = gcnew Creditos();
		creditos->ShowDialog();
		this->Show();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	private: System::Void MyMenuForm_Load(System::Object^ sender, System::EventArgs^ e) {
		// Reproduce el sonido del men� al cargar el formulario
		menuSoundPlayer = gcnew SoundPlayer("MenuJuegoSonido.wav");
		try {
			menuSoundPlayer->Load();
			menuSoundPlayer->PlayLooping();
		}
		catch (Exception^ ex) {
			MessageBox::Show("No se pudo reproducir el sonido del men�: " + ex->Message);
		}
	}
};
}