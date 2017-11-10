#pragma once

namespace task5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
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
		float left, right, top, bottom;
		float Wcx, Wcy, Wx, Wy;
		float Vcx, Vcy, Vx, Vy;
		bool drawNames;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;



	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
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
			this->openFileDialog->FileName = L"openFileDialog1";
			this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(12, 12);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(66, 24);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Открыть";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &MyForm::btnOpen_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(304, 282);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(200, 200);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		left = 30;
		right = 40;
		top = 50;
		bottom = 20;
		Wcx = left;
		Wcy = Form::ClientRectangle.Height - bottom;
		Wx = Form::ClientRectangle.Width - left - right;
		Wy = Form::ClientRectangle.Height - top - bottom;
		drawNames = true;
		unit(T);
		lines.Clear();
	}
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Graphics^ g = e->Graphics;
		Rectangle rect = Form::ClientRectangle;
		g->Clear(Color::White);
		Pen^ rectPen = gcnew Pen(Color::Pink);
		rectPen->Width = 2;
		g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);
		Pen^ blackPen = gcnew Pen(Color::Black);
		blackPen->Width = 3;
		point Pmin, Pmax;
		Pmin.x = Wcx; Pmin.y = Wcy - Wy;
		Pmax.x = Wcx + Wx; Pmax.y = Wcy;

		for (int i = 0; i < lines.Count; i++) {
			vec A, B;
			point2vec(lines[i].start, A);
			point2vec(lines[i].end, B);
			vec A1, B1;
			timesMatVec(T, A, A1);
			timesMatVec(T, B, B1);
			point a, b;
			vec2point(A1, a);
			vec2point(B1, b);
			System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);
			SolidBrush^ drawBrush = gcnew SolidBrush(Color::Green);
			if (Clip(a, b, Pmin, Pmax))
			{
				g->DrawLine(blackPen, a.x, a.y, b.x, b.y);
				if (drawNames)
					g->DrawString(lines[i].name, drawFont, drawBrush, (a.x + b.x) / 2, (a.y + b.y) / 2);
			}

		}
	}
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	}
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->openFileDialog->ShowDialog() ==
			System::Windows::Forms::DialogResult::OK) {
			wchar_t fileName[1024];
			for (int i = 0; i < openFileDialog->FileName->Length; i++)
				fileName[i] = openFileDialog->FileName[i];
			fileName[openFileDialog->FileName->Length] = '\0';
			std::ifstream in;
			in.open(fileName);
			if (in.is_open()) {
				lines.Clear();
				std::string str;
				getline(in, str);
				std::stringstream s(str);
				line l;
				s >> l.start.x >> l.start.y >> l.end.x >> l.end.y;

				Vx = l.start.x;
				Vy = l.start.y;
				Vcx = l.end.x;
				Vcy = l.end.y;

				frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
				getline(in, str);
				while (in)
				{
					if ((str.find_first_not_of(" \t\r\n") != std::string::npos)
						&& (str[0] != '#'))
					{
						std::stringstream s(str);
						line l;
						s >> l.start.x >> l.start.y >> l.end.x >> l.end.y;
						std::string linename;
						s >> linename;
						l.name = gcnew String(linename.c_str());
						lines.Add(l);
					}
					getline(in, str);
				}
			}
			this->Refresh();
		}
	}
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		mat R, T1;
		Rectangle rect = Form::ClientRectangle;
		switch (e->KeyCode) {
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
			move(-Wcx, -Wcy + Wy, R);
			times(R, T, T1);
			set(T1, T);
			rotate(0.05, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx, Wcy - Wy, R);
			break;
		case Keys::X:
			move(-Wcx, -Wcy + Wy, R);
			times(R, T, T1);
			set(T1, T);
			scale(1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx, Wcy - Wy, R);
			break;
		case Keys::T:
			move(0, -20, R);
			break;
		case Keys::F:
			move(-20, 0, R);
			break;
		case Keys::G:
			move(0, 20, R);
			break;
		case Keys::H:
			move(20, 0, R);
			break;

		case Keys::Q:
			move(-Wcx, -Wcy + Wy, R);
			times(R, T, T1);
			set(T1, T);
			rotate(-0.05, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx, Wcy - Wy, R);
			break;
		case Keys::Z:
			move(-Wcx, -Wcy + Wy, R);
			times(R, T, T1);
			set(T1, T);
			scale(1 / 1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx, Wcy - Wy, R);
			break;

		case Keys::U:
			move(-Wcx - Wx / 2, -Wcy + Wy / 2, R);
			times(R, T, T1);
			set(T1, T);
			mirx(R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx + Wx / 2, Wcy - Wy / 2, R);
			break;

		case Keys::J:
			move(-Wcx - Wx / 2, -Wcy + Wy / 2, R);
			times(R, T, T1);
			set(T1, T);
			miry(R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx + Wx / 2, Wcy - Wy / 2, R);
			break;

		case Keys::R:
			move(-Wcx - Wx / 2, -Wcy + Wy / 2, R);
			times(R, T, T1);
			set(T1, T);
			rotate(-0.05, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx + Wx / 2, Wcy - Wy / 2, R);
			break;

		case Keys::Y:
			move(-Wcx - Wx / 2, -Wcy + Wy / 2, R);
			times(R, T, T1);
			set(T1, T);
			rotate(0.05, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx + Wx / 2, Wcy - Wy / 2, R);
			break;

		case Keys::C:
			move(-Wcx - Wx / 2, -Wcy + Wy / 2, R);
			times(R, T, T1);
			set(T1, T);
			scale(1 / 1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx + Wx / 2, Wcy - Wy / 2, R);
			break;

		case Keys::V:
			move(-Wcx - Wx / 2, -Wcy + Wy / 2, R);
			times(R, T, T1);
			set(T1, T);
			scale(1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx + Wx / 2, Wcy - Wy / 2, R);
			break;

		case Keys::I:
			move(-Wcx - Wx / 2, -Wcy + Wy / 2, R);
			times(R, T, T1);
			set(T1, T);
			s1(1 / 1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx + Wx / 2, Wcy - Wy / 2, R);
			break;

		case Keys::O:
			move(-Wcx - Wx / 2, -Wcy + Wy / 2, R);
			times(R, T, T1);
			set(T1, T);
			s1(1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx + Wx / 2, Wcy - Wy / 2, R);
			break;

		case Keys::K:
			move(-Wcx - Wx / 2, -Wcy + Wy / 2, R);
			times(R, T, T1);
			set(T1, T);
			s2(1 / 1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx + Wx / 2, Wcy - Wy / 2, R);
			break;

		case Keys::L:
			move(-Wcx - Wx / 2, -Wcy + Wy / 2, R);
			times(R, T, T1);
			set(T1, T);
			s2(1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(Wcx + Wx / 2, Wcy - Wy / 2, R);
			break;

		case Keys::Escape:
			frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
			unit(R);
			break;
		case Keys::P:
			unit(R);
			if (drawNames) drawNames = false;
			else drawNames = true;
			break;
		default:
			unit(R);
		}
		times(R, T, T1);
		set(T1, T);
		this->Refresh();
	}
	private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {
		float oldWx = Wx, oldWy = Wy;
		Wcx = left;
		Wcy = Form::ClientRectangle.Height - bottom;
		Wx = Form::ClientRectangle.Width - left - right;
		Wy = Form::ClientRectangle.Height - top - bottom;
		mat R, T1;
		unit(R);
		unit(T1);
		move(-Wcx, -top, R);
		times(R, T, T1);
		set(T1, T);
		s1(Wx / oldWx, R);
		times(R, T, T1);
		set(T1, T);
		s2(Wy / oldWy, R);
		times(R, T, T1);
		set(T1, T);
		move(Wcx, top, R);
		times(R, T, T1);
		set(T1, T);
		this->Refresh();
	}
	};
}