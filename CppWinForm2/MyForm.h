#pragma once
/*#include "Transform.h"
#include "Clip.h"
#include "PClip.h"*/
namespace CppWinForm2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Collections::Generic::List<line> lines;
	private: System::Collections::Generic::List<polygon^> polygons;
	float left, right, top, bottom;
	float Wcx, Wcy, Wx, Wy;
	float Vcx, Vcy, Vx, Vy;
	bool drawNames;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;

	private: System::Windows::Forms::Button^  btnOpen;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"txt";
			this->openFileDialog->FileName = L"openFileDialog";
			this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			// 
			// btnOpen
			// 
			this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnOpen->Location = System::Drawing::Point(697, 12);
			this->btnOpen->MaximumSize = System::Drawing::Size(200, 100);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Окрыть";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &MyForm::btnOpen_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(220, 150);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}

#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		Rectangle rect = Form::ClientRectangle;
		lines.Clear();
		polygons.Clear();
		unit(T);
		left = 50;
		right = 50;
		top = 50;
		bottom = 50;
		Wcx = left;
		Wcy = Form::ClientRectangle.Height - bottom;
		Wx = Form::ClientRectangle.Width - left - right;
		Wy = Form::ClientRectangle.Height - top - bottom;
		drawNames = false;
	}

	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		Graphics^ g = e->Graphics;
		g->Clear(Color::White);


		Rectangle rect = Form::ClientRectangle;
		Rectangle smallRect;

		Pen^ blackPen = gcnew Pen(Color::Black);
		Pen^ rectPen = gcnew Pen(Color::Red);
		g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);
		blackPen->Width = 2;
		rectPen->Width = 4;
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 12);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Red);


		point Pmin, Pmax;
		Pmin.x = Wcx;
		Pmin.y = Wcy - Wy;
		Pmax.x = Wcx + Wx;
		Pmax.y = Wcy;

		for (int i = 0; i < polygons.Count; i++)
		{
			polygon^ p = polygons[i];
			polygon^ p2 = gcnew polygon(0);
			point a, b, c;
			vec A, B, A1, B1;
			point2vec(p[p->Count - 1], A);
			timesMatVec(T, A, A1);
			vec2point(A1, a);
			p2->Add(a);

			for (int j = 0; j < p->Count; j++)
			{
				point2vec(p[j], B);
				timesMatVec(T, B, B1);
				vec2point(B1, b);
				p2->Add(b);
			}
			p = PClip(p2, Pmin, Pmax);
			for (int j = 0; j < p->Count - 1; j++)
			{
				g->DrawLine(blackPen, p[j].x, p[j].y, p[j + 1].x, p[j + 1].y);
			}
		}
		/*Graphics^ g;
		g = e->Graphics;
		Pen^ blackPen = gcnew Pen(Color::Black);
		Pen^ rectPen = gcnew Pen(Color::Red);
		rectPen->Width = 2;
		g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);
		blackPen->Width = 1;
		point Pmin, Pmax;
		Pmin.x = Wcx;
		Pmin.y = Wcy - Wy;
		Pmax.x = Wcx + Wx;
		Pmax.y = Wcy;
		point centre;
		for (int i = 0; i < polygons.Count; i++) {
			polygon^ p = polygons[i];
			polygon^ temp = gcnew polygon(0);
			point a, b, c;
			vec A, B, A1, B1;
			for (int j = 0; j < p->Count; j++)
			{
				point2vec(p[j], B);
				timesMatVec(T, B, B1);
				vec2point(B1, b);
				temp->Add(b);
			}
			temp = PClip(temp, Pmin, Pmax);
			if (temp->Count != 0)
			{
				a = temp[temp->Count - 1];
				for (int j = 0; j < temp->Count; j++)
				{
					b = temp[j];
					g->DrawLine(blackPen, a.x, a.y, b.x, b.y);
					a = b;
				}
			}
		}*/
	}

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->openFileDialog->ShowDialog() ==
			System::Windows::Forms::DialogResult::OK)
		{
			wchar_t fileName[1024];
			for (int i = 0; i < openFileDialog->FileName->Length; i++)
				fileName[i] = openFileDialog->FileName[i];
			fileName[openFileDialog->FileName->Length] = '\0';
			std::ifstream in;
			in.open(fileName);
			if (in.is_open())
			{
				lines.Clear();
				unit(T);
				std::string str;
				getline(in, str);

				while (in)
				{
					if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {

						std::stringstream s(str);
						std::string cmd;
						s >> cmd;
						if (cmd == "frame")
						{
							float newVcx, newVcy, newVx, newVy;
							s >> newVcx >> newVcy >> newVx >> newVy;
							Vcx = newVcx;
							Vcy = newVcy;
							Vx = newVx;
							Vy = newVy;
							frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
						}
						if (cmd == "polygon")
						{
							int numpoint;
							s >> numpoint;
							polygon^ P = gcnew polygon(0);
							for (int i = 0; i<numpoint; i++) {
								point p;
								s >> p.x >> p.y;
								P->Add(p);
							}
							polygons.Add(P);
						}
					}
					getline(in, str);
				}
			}
			this->Refresh();
		}
		/*point A, B;

		if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			wchar_t fileName[1024];
			for (int i = 0; i < openFileDialog->FileName->Length; i++)
			{
				fileName[i] = openFileDialog->FileName[i];
			}
			fileName[openFileDialog->FileName->Length] = '\0';
			std::ifstream in;
			in.open(fileName);

			if (in.is_open())
			{
				lines.Clear();
				std::string str;
				getline(in, str);

				while (in)
				{
					if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#'))
					{
						std::stringstream s(str);
						std::string cmd;
						s >> cmd;
						if (cmd == "frame") {
							float Vcx1, Vcy1, Vx1, Vy1;
							s >> Vcx1 >> Vcy1 >> Vx1 >> Vy1;
							Vcx = Vcx1;
							Vcy = Vcy1;
							Vx = Vx1;
							Vy = Vy1;
							frame(Vx1, Vy1, Vcx1, Vcy1, Wx, Wy, Wcx, Wcy, T);
						}
						else if (cmd == "polygon") {
							int numpoint;
							s >> numpoint;
							polygon^ P = gcnew polygon(0);
							for (int i = 0; i < numpoint; i++) {
								point p;
								s >> p.x >> p.y;
								P->Add(p);
							}
							polygons.Add(P);
						}
					}
					getline(in, str);
				}
			}
			this->Refresh();
		}*/
	}
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
	{
		mat R, T1, R1, R2, R3, R4;
		Rectangle rect = Rectangle(Wcx, top, Wx, Wy);
		switch (e->KeyCode)
		{
		case Keys::W:
			move(0, -1, R);
			break;
		case Keys::S:
			move(0, 1, R);
			break;
		case Keys::A:
			move(-1, 0, R);
			break;
		case Keys::D:
			move(1, 0, R);
			break;
		case Keys::E:
			rotate(0.05, R);
			break;
		case Keys::X:
			move(-50, -50, R1);
			scale(1 / 1.1, R2);
			move(50, 50, R3);
			times(R2, R1, R4);
			times(R3, R4, R);
			break;
		case Keys::Z:
			rotate(-0.05, R);
			break;
		case Keys::Q:
			move(- 50, - 50, R1);
			scale(1.1, R2);
			move(50, 50, R3);
			times(R2, R1, R4);
			times(R3, R4, R);
			break;
		case Keys::I:
			move(0, 10, R);
			break;
		case Keys::O:
			move(0, -10, R);
			break;
		case Keys::K:
			move(-10, 0, R);
			break;
		case Keys::L:
			move(10, 0, R);
			break;
		case Keys::U:
			move(rect.Width+100, 0, R);
			R[0][0] = -1;
			break;
		case Keys::J:
			move(0, rect.Height+100, R);
			R[1][1] = -1;
			break;
		case Keys::C:
			rotate_centre(rect.Width / 2+50, rect.Height / 2+50, -0.05, R);
			break;
		case Keys::V:
			rotate_centre(rect.Width / 2+50, rect.Height / 2+50, 0.05, R);
			break;
		case Keys::R:
			move(-rect.Width / 2-50, -rect.Height / 2-50, R1);
			scale(1/1.1, R2);
			move(rect.Width / 2+50, rect.Height / 2+50, R3);
			times(R2, R1, R4);
			times(R3, R4, R);
			break;
		case Keys::Y:
			move(-rect.Width / 2-50, -rect.Height / 2-50, R1);
			scale (1.1, R2);
			move(rect.Width / 2+50, rect.Height / 2+50, R3);
			times(R2, R1, R4);
			times(R3, R4, R);
			break;
		case Keys::T:
			move((rect.Width / 2 + 50) * (1 - 1 / 1.1), 0, R);
			R[0][0] = 1/1.1;
			break;
		case Keys::G:
			move((rect.Width / 2 + 50) * (1 - 1.1), 0, R);
			R[0][0] = 1.1;
			break;
		case Keys::F:
			move(0, (rect.Height / 2 + 50) * (1 - 1 / 1.1), R);
			R[1][1] = 1/1.1;
			break;
		case Keys::H:
			move(0, (rect.Height / 2 + 50) * (1 - 1.1), R);
			R[1][1] = 1.1;
			break;
		case Keys::P:
			unit(R);
			if (drawNames)
				drawNames = false;
			else
				drawNames = true;
			break;
		case Keys::Escape:
			unit(R);
			frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
			break;
		default:
			unit(R);
		}
		times(R, T, T1);
		set(T1, T);
		this->Refresh();
	}

private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {
	Rectangle rect = Form::ClientRectangle;
	mat R, R1, Z, T1;
	float oldWx = Wx, oldWy = Wy;
	unit(R); unit(R1); unit(Z); unit(T1);
	Wcx = left;
	Wcy = Form::ClientRectangle.Height - bottom;
	Wx = Form::ClientRectangle.Width - left - right;
	Wy = Form::ClientRectangle.Height - top - bottom;
	move(Wcx, top, R);
	scale2(Wx / oldWx, Wy / oldWy, Z);
	times(R, Z, R1);
	set(R1, R);
	move(-Wcx, -top, Z);
	times(R, Z, R1);
	set(R1, R);
	times(R, T, T1);
	set(T1, T);
	this->Refresh();
}
};
}