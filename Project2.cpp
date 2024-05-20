#include "pch.h"
#include "MainForm.h"
using namespace System::Windows::Forms;
using namespace System;

int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Project2::MainForm form;
	Application::Run(% form);
}
