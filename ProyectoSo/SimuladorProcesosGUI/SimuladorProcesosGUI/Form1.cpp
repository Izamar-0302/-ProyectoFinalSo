#include "Form1.h"
#include "Form1.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    SimuladorProcesosGUI::Form1 form;
    Application::Run(% form);
}

