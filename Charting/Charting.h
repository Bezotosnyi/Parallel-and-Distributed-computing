// Charting.h

#pragma once

using namespace System;

namespace Charting {

	public ref class MyGrafics
	{
	public:
		/// <summary>
		/// �����������, ������� �������������� ����� ������ ������ MyGrafics ��� ���������� ��������.
		/// </summary>
		MyGrafics();

		/// <summary>
		/// ���� ����� ������� ���� � ��������.
		/// </summary>
		/// <param name="methodName">��� ������</param>
		/// <param name="fileName">��� ����� � �������</param>
		/// <param name="saveFile">��������� �� ����������� ������� � ����</param>
		/// <returns></returns>
		void DrawGrafics(String^ title, String^ methodName, String^ fileName, bool saveFile);
	};
}
