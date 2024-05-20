#pragma once
#include "AirBattle.h"
#include<cstdlib>
namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			myBattlefield = gcnew Battlefield(pictureBox1);
			myBattlefield->Add(gcnew Enemy(rand() % 10 + 1, (rand() % 600 + 200) * -1, 2));
			myBattlefield->Add(gcnew Enemy(rand() % 200 + 20, (rand() % 600 + 200) * -1, 2));
			myBattlefield->Add(gcnew Enemy(rand() % 300 + 20, (rand() % 600 + 200) * -1, 2));
			myBattlefield->Add(gcnew Player(pictureBox1->Width/2-60, pictureBox1->Height - 100, 3));
			myBattlefield->Add(gcnew InterfaceMenu(label1, label2));
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: Battlefield^ myBattlefield;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;


	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(0, -1);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(778, 655);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MainForm::pictureBox1_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(795, -1);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(88, 66);
			this->label1->TabIndex = 1;
			this->label1->Text = L"0";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(784, 87);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(118, 173);
			this->label2->TabIndex = 2;
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->ClientSize = System::Drawing::Size(904, 652);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::MainForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::keyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::keyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
		timer1->Enabled = !timer1->Enabled;
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		myBattlefield->Tick();
		myBattlefield->gameOver();
		if (myBattlefield->getIsGameOver() == true) {
			timer1->Stop();
		}
		Invalidate();
	}

	private: Void MainForm_Paint(System::Object^ sender, PaintEventArgs^ e) {
		myBattlefield->Draw();
	}  

	private: System::Void keyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::A) {
			myBattlefield->getPlayer()->setGoLeft(true);
		}
		if (e->KeyCode == Keys::D) {
			myBattlefield->getPlayer()->setGoRight(true);
		}
		if (e->KeyCode == Keys::Space) {
			if(myBattlefield->getShooting() == true)
			myBattlefield->Add(gcnew Bullet(myBattlefield->getPlayer()->getX()+52, myBattlefield->getPlayer()->getY() - 30, 5));
			myBattlefield->setShooting(false);
		}
		if (e->KeyCode == Keys::Enter) {
			myBattlefield->restart();
			timer1->Start();
		}
	}

	private: System::Void keyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::A) {
			myBattlefield->getPlayer()->setGoLeft(false);
		}
		if (e->KeyCode == Keys::D) {
			myBattlefield->getPlayer()->setGoRight(false);
		}
		if (e->KeyCode == Keys::Space) {
			myBattlefield->setShooting(true);
		}
	}
    
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	
	};
}
