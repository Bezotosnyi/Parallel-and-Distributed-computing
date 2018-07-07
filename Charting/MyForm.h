#pragma once

namespace Charting {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	private ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		MyForm(String^ title, String^ methodName, String^ fileName)
		{
			InitializeComponent();
			//
			this->StartPosition = FormStartPosition::CenterScreen;
			this->Text = title;
			this->title1->Text = methodName;
			CreateGrafics(fileName);
			//
		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
		System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
		System::Windows::Forms::DataVisualization::Charting::Title^  title1;
		array<String^>^ countElements;
		array<String^>^ posledov;
		array<String^>^ parallel;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(0, 0);
			this->chart1->Name = L"chart1";
			series1->BorderWidth = 3;
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Последовательно";
			series1->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series1->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series2->BorderWidth = 3;
			series2->ChartArea = L"ChartArea1";
			series2->Legend = L"Legend1";
			series2->Name = L"Параллельно";
			series2->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series2->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(754, 402);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			title1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14, System::Drawing::FontStyle::Bold));
			title1->Name = L"Title1";
			title1->Text = L"Заголовок";
			this->chart1->Titles->Add(title1);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(754, 402);
			this->Controls->Add(this->chart1);
			this->Name = L"MyForm";
			this->Text = L"Графики вычислений";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: void CreateGrafics(String^ fileName)
		{
			try
			{
				// считываем из файла результаты длительности вычислений и заносим в массив
				StreamReader^ read = gcnew StreamReader(fileName);
				countElements = read->ReadLine()->Split('\t');
				posledov = read->ReadLine()->Split('\t');
				parallel = read->ReadLine()->Split('\t');
				read->Close();

				// построение графика
				for (int i = 0; i < countElements->Length - 1; i++)
				{
					this->chart1->Series[0]->Points->AddXY(countElements[i], posledov[i]);
					this->chart1->Series[1]->Points->AddXY(countElements[i], parallel[i]);
				}
			}
			catch (Exception^ ex)
			{
				this->Text = "Ошибка: " + ex->Message->ToLower();
				this->title1->Text = "График по умолчанию";
				for (int i = 1; i < 6; i++)
				{
					this->chart1->Series[0]->Points->AddXY(i, i + 1);
					this->chart1->Series[1]->Points->AddXY(i, i);
				}
			}
		}

	public: void SaveChartToFile(String^ imageName)
	{
		this->chart1->SaveImage(imageName, System::Drawing::Imaging::ImageFormat::Jpeg);
	}
	};
}