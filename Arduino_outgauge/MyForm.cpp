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
