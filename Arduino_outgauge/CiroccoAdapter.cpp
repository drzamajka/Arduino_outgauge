#include <iostream>
#include <string>
#include <sstream>

namespace Arduinooutgauge {

	using namespace System;

	ref class CiroccoAdapter
	{
	public: float RPM;
	public: float Speed;
	public: float TCoolant;
	public: bool LeftI, RightI;
	public: bool Ignition;
	public: int Odometer;

	private: System::IO::Ports::SerialPort^ serialPort;
	private: System::Windows::Forms::Timer^ timer50;
	private: System::Windows::Forms::Timer^ timer500;


	public:	CiroccoAdapter(System::IO::Ports::SerialPort^ serialPort)
	{
		this->serialPort = serialPort;
		this->timer50 = (gcnew System::Windows::Forms::Timer());
		this->timer50->Interval = 50;
		this->timer50->Tick += gcnew System::EventHandler(this, &CiroccoAdapter::timer50_Tick);
		this->timer500 = (gcnew System::Windows::Forms::Timer());
		this->timer500->Interval = 1000;
		this->timer500->Tick += gcnew System::EventHandler(this, &CiroccoAdapter::timer500_Tick);
		this->RPM = 0;
		this->Speed = 0;
		this->TCoolant = 0;
		this->LeftI = this->RightI = false;
		this->Ignition = false;
		this->Odometer = 0;
		this->timer50->Start();
		this->timer500->Start();

	}

	protected:	~CiroccoAdapter()
	{
		this->serialPort->Close();
		this->timer50->Stop();
		this->timer500->Stop();
	}


	private: System::Void timer50_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (serialPort->IsOpen) {
			array<String^>^ rpm = getRPMHex(RPM);
			array<String^>^ speed = getSpeedHex(Speed);
			
			System::String^ mesage = "id:0B6;l:8;D:" + rpm[0]+  ":" + rpm[1] + ":" + speed[0] + ":" + speed[1] + ":00:FF:0D:D0\n";

			this->serialPort->WriteLine(mesage);
		}
	}

	private: System::Void timer500_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (serialPort->IsOpen) {
			String^ TCoolantHex = getTCoolantHex(this->TCoolant);
			System::String^ mesage1 = "id:036;l:8;D:0E:00:00:27:01:00:00:A0";
			System::String^ mesage2 = "id:128;l:8;D:00:B0:00:00:00:00:04:00";
			System::String^ mesage3 = "id:0F6;l:8;D:8E:"+ TCoolantHex +":00:FF:FF:8F:00:00";
			System::String^ mesage4 = "id:168;l:8;D:00:00:00:00:00:00:00:00";

			this->serialPort->WriteLine(mesage1);
			this->serialPort->WriteLine(mesage2);
			this->serialPort->WriteLine(mesage3);
			this->serialPort->WriteLine(mesage4);
		}
	}


	private: array<String^>^ getRPMHex(Int16 RPM) {
		RPM = RPM * 0.925;
		array<String^>^ RPMArray = gcnew array<String^>(2);

		std::string r = "";
		if (this->RPM > 50) {
			while (RPM > 0) {
				r = (RPM % 2 == 0 ? "0" : "1") + r;
				RPM /= 2;
			}
			r += "000";
			for (int i = r.length(); i < 16; i++) {
				r = "0" + r;
			}
		}
		else {
			RPMArray[0] = gcnew String("00");
			RPMArray[1] = gcnew String("00");
			return RPMArray;
		}

		std::ostringstream s1;
		std::ostringstream s2;
		s1 << std::hex << std::stoi(r.substr(0, 8), 0, 2);
		s2 << std::hex << std::stoi(r.substr(9), 0, 2);

		RPMArray[0] = gcnew String((s1.str()).c_str());
		RPMArray[1] = gcnew String((s2.str()).c_str());

		if (RPMArray[0]->Length != 2) {
			while (RPMArray[0]->Length < 2)
				RPMArray[0] = "0" + RPMArray[0];
		}
		if (RPMArray[1]->Length != 2) {
			while (RPMArray[1]->Length < 2)
				RPMArray[1] = "0" + RPMArray[1];
		}

		return RPMArray;
	}

	private: array<String^>^ getSpeedHex(Int16 Speed) {
		Speed = Speed * 100;
		array<String^>^ SpeedArray = gcnew array<String^>(2);

		std::string b = "";
		if(Speed>100){
			while (Speed > 0) { 
				b = (Speed % 2 == 0 ? "0" : "1") + b;
				Speed /= 2; 
			}
			for (int i = b.length(); i < 16; i++) {
				b = "0" + b;
			}
		}
		else {
			SpeedArray[0] = gcnew String("00");
			SpeedArray[1] = gcnew String("00");
			return SpeedArray;
		}

		std::ostringstream b1;
		std::ostringstream b2;
		b1 << std::hex << std::stoi(b.substr(0, 8), 0, 2);
		b2 << std::hex << std::stoi(b.substr(9, 16), 0, 2);

		SpeedArray[0] = gcnew String((b1.str()).c_str());
		SpeedArray[1] = gcnew String((b2.str()).c_str());

		if (SpeedArray[0]->Length != 2) {
			while(SpeedArray[0]->Length<2)
				SpeedArray[0] = "0" + SpeedArray[0];
		}
		if (SpeedArray[1]->Length != 2) {
			while (SpeedArray[1]->Length < 2)
				SpeedArray[1] = "0" + SpeedArray[1];
		}

		return SpeedArray;
	}

	private: String^ getTCoolantHex(Int16 TCoolant) {
		TCoolant = TCoolant + 39;

		std::string b = "";
		if (TCoolant > 100) {
			while (TCoolant > 0) {
				b = (TCoolant % 2 == 0 ? "0" : "1") + b;
				TCoolant /= 2;
			}
			for (int i = b.length(); i < 8; i++) {
				b = "0" + b;
			}
		}
		else {
			return gcnew String("00");
		}

		std::ostringstream b1;
		b1 << std::hex << std::stoi(b, 0, 2);

		String^ TCoolantHex = gcnew String((b1.str()).c_str());

		if (TCoolantHex->Length != 2) {
			while (TCoolantHex->Length < 2)
				TCoolantHex = "0" + TCoolantHex;
		}

		return TCoolantHex;
	}

	};
}