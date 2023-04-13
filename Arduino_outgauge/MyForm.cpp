#include "MyForm.h"
#using <System.dll>

using namespace System;
using namespace System::Windows::Forms;




void main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Arduinooutgauge::MyForm form;
    Application::Run(% form);

    
}

inline System::Void Arduinooutgauge::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	Array^ ports = serialPort1->GetPortNames();
	if (ports->Length > 0) {
		for each (String ^ var in ports) {
			this->comboBox1->Items->Add(var);
		}
		this->comboBox1->SelectedIndex = 0;
	}
	this->ciroccoAdaper = gcnew CiroccoAdapter(serialPort1);
}

inline System::Void Arduinooutgauge::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ mesage = textBox1->Text->Trim();
	serialPort1->WriteLine(mesage);
	listBox1->Items->Add(">> " + mesage);
	textBox1->Text = "";
}

inline System::Void Arduinooutgauge::MyForm::timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	if (serialPort1->IsOpen) {
		listBox1->Items->Clear();
		while (serialPort1->BytesToRead > 0) {
			String^ mesage = serialPort1->ReadLine()->Trim();
			if (mesage != "") {
				if (mesage->StartsWith("FRAME:535;8;")) {
					this->ciroccoAdaper->setBrightnes(mesage->Substring(12, 1));
					listBox1->Items->Add("Brightnes: " + this->ciroccoAdaper->getBrightnes());
				}
				listBox1->Items->Add("<< " + mesage);
			}
		}
	}

}

inline System::Void Arduinooutgauge::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->reloadSerialPortsList();
}

inline System::Void Arduinooutgauge::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
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

inline System::Void Arduinooutgauge::MyForm::button4_Click(System::Object^ sender, System::EventArgs^ e) {

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
	else {
		this->outgauge->Disconnect();
		this->button4->Text = "Connect";
	}
}

inline void Arduinooutgauge::MyForm::reloadSerialPortsList() {
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

inline System::Void Arduinooutgauge::MyForm::trackBar1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	std::ostringstream b1;
	b1 << std::hex << trackBar1->Value;
	label2->Text = "Selected gear: " + gcnew String((b1.str()).c_str());
	this->ciroccoAdaper->setGear(b1.str()[0]);
}
