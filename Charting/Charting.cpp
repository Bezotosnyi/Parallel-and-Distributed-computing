// ֳכאגםûי DLL-פאיכ.

#include "stdafx.h"
#include "Charting.h"
#include "MyForm.h"

Charting::MyGrafics::MyGrafics() { }

void Charting::MyGrafics::DrawGrafics(String^ title, String^ methodName, String^ fileName, bool saveFile)
{
	MyForm^ form = gcnew MyForm(title, methodName, fileName);
	form->ShowDialog();
	if (saveFile)
		form->SaveChartToFile(methodName + ".jpeg");
}

