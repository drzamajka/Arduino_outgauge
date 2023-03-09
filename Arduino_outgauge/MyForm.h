#pragma once
#include "CiroccoAdapter.cpp"
#include <iostream>
#include <string>
#include <sstream>

#using <InSimDotNet.dll>
#using <System.dll>

namespace Arduinooutgauge {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;

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
			serialPort1->Close();
			timer1->Stop();
		}

	private: CiroccoAdapter^ ciroccoAdaper;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::IO::Ports::SerialPort^ serialPort1;
	private: InSimDotNet::Out::OutGauge^ outgauge;





	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::GroupBox^ groupBox3;


	protected:
	private: System::ComponentModel::IContainer^ components;


	private:
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// button1
			// 
			this->button1->Enabled = false;
			this->button1->Location = System::Drawing::Point(9, 56);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(339, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Send serial mesage";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 31);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(62, 17);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Mesage:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(74, 28);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(274, 22);
			this->textBox1->TabIndex = 2;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(6, 85);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(342, 116);
			this->listBox1->TabIndex = 3;
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(6, 21);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 24);
			this->comboBox1->TabIndex = 5;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(133, 22);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Refresh";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(273, 22);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Connect";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(273, 24);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 8;
			this->button4->Text = L"Connect";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(360, 62);
			this->groupBox1->TabIndex = 10;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Arduino";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->textBox2);
			this->groupBox2->Controls->Add(this->button4);
			this->groupBox2->Location = System::Drawing::Point(12, 80);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(360, 100);
			this->groupBox2->TabIndex = 11;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"OutGauge";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 57);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(38, 17);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Port:";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(50, 54);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 22);
			this->textBox3->TabIndex = 11;
			this->textBox3->Text = L"5555";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(21, 27);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(23, 17);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Ip:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(50, 24);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 22);
			this->textBox2->TabIndex = 9;
			this->textBox2->Text = L"127.0.0.1";
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label1);
			this->groupBox3->Controls->Add(this->textBox1);
			this->groupBox3->Controls->Add(this->button1);
			this->groupBox3->Controls->Add(this->listBox1);
			this->groupBox3->Location = System::Drawing::Point(12, 186);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(360, 220);
			this->groupBox3->TabIndex = 12;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Serial terminal";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(380, 418);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Arduino OutGauge";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		//Init COM ports list
		Array^ ports = serialPort1->GetPortNames();
		if (ports->Length > 0) {
			for each (String ^ var in ports) {
				this->comboBox1->Items->Add(var);
			}
			this->comboBox1->SelectedIndex = 0;
		}
		this->ciroccoAdaper = gcnew CiroccoAdapter(serialPort1);
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ mesage = textBox1->Text->Trim();
		serialPort1->WriteLine(mesage);
		listBox1->Items->Add(">> " + mesage);
		textBox1->Text = "";
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		
		if (serialPort1->IsOpen && serialPort1->BytesToRead>0) {
			String^ mesage = serialPort1->ReadLine()->Trim();
			if (mesage != "") {
				listBox1->Items->Add("<< " + mesage);
			}
		}

	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->reloadSerialPortsList();
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		if (button3->Text == "Connect") {
			try {
				serialPort1->PortName = this->comboBox1->SelectedItem->ToString();
				serialPort1->BaudRate = 115200;
				serialPort1->Open();
				timer1->Start();
				button3->Text = "Disconnect";
				button2->Enabled = false;
				button1->Enabled = true;
				comboBox1->Enabled = false;
			}
			catch (Exception^ e) {
				MessageBox::Show(L"Arduino  connection error!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				this->reloadSerialPortsList();
			}
		}
		else {
			serialPort1->Close();
			timer1->Stop();
			button3->Text = "Connect";
			button2->Enabled = true;
			button1->Enabled = false;
			comboBox1->Enabled = true;
		}
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
			
		if (button4->Text == "Connect") {
			try {
				this->outgauge = (gcnew InSimDotNet::Out::OutGauge());
				this->outgauge->PacketReceived += gcnew System::EventHandler<InSimDotNet::Out::OutGaugeEventArgs^>(this, &Arduinooutgauge::MyForm::OnPacketReceived);
				this->outgauge->Connect(this->textBox2->Text, int::Parse(this->textBox3->Text));
				this->button4->Text = "Disconnect";
			}
			catch (Exception^ e) {
				MessageBox::Show(L"OutGauge connection error!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		else{
			this->outgauge->Disconnect();
			this->button4->Text = "Connect";
		}
	}
	void Arduinooutgauge::MyForm::OnPacketReceived(System::Object^ sender, InSimDotNet::Out::OutGaugeEventArgs^ e)
	{
		this->ciroccoAdaper->RPM = e->RPM;
		this->ciroccoAdaper->Speed = e->Speed*3.6;
		this->ciroccoAdaper->TCoolant = e->EngTemp;
	}

	void reloadSerialPortsList()
	{
		this->comboBox1->Items->Clear();
		//refresh COM ports list
		Array^ ports = serialPort1->GetPortNames();
		if (ports->Length > 0) {
			for each (String ^ var in ports) {
				this->comboBox1->Items->Add(var);
			}
			this->comboBox1->SelectedIndex = 0;
		}
	}

};
}



