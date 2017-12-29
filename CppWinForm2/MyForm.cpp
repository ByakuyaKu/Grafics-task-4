#include <fstream>
#include <sstream>
#include "Transform.h"
#include "Clip.h"
#include "PClip.h"
#include "MyForm.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace CppWinForm2;


/*[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CppWinForm2::MyForm form;
	Application::Run(%form);
}*/
[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Create the main window and run it
	Application::Run(gcnew MyForm());
	return 0;
}
