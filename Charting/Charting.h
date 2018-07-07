// Charting.h

#pragma once

using namespace System;

namespace Charting {

	public ref class MyGrafics
	{
	public:
		/// <summary>
		/// Конструктор, который инициализирует новый объект класса MyGrafics для построения графиков.
		/// </summary>
		MyGrafics();

		/// <summary>
		/// Этот метод выводит окно с графиком.
		/// </summary>
		/// <param name="methodName">Имя метода</param>
		/// <param name="fileName">Имя файла с точками</param>
		/// <param name="saveFile">Сохранять ли изображение графика в файл</param>
		/// <returns></returns>
		void DrawGrafics(String^ title, String^ methodName, String^ fileName, bool saveFile);
	};
}
