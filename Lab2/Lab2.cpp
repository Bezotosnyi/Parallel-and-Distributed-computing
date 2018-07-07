// Lab2.cpp: главный файл проекта.

#include "stdafx.h"

// класс, который позволяет делать вещественные числа с ,
class comma : public numpunct<char> {
public:
	comma() : numpunct<char>() {}
protected:
	char do_decimal_point() const {
		return ',';
	}
};

void CreateEachFileAndGrafics(double ***duration, int countElements);

void main()
{
	setlocale(LC_ALL, "Russian"); // русский язык в консоле
	srand(time(NULL)); // случайная генерация

	SYSTEMTIME st; // системное время

	int countElements = 12;
	int step = 10;
	int M = 0, N = 0;
	int _count;
	double **matrix;
	double **copyMatryx;
	double **matrix2;
	double element;
	int iIndex = 0;
	double totalDuration = 0;

	double ***duration2 = new double**[6]; // 3-x массив для длительности вычислений каждого метода отдельно
	for (int i = 0; i < 6; i++)
		duration2[i] = new double*[3];
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			duration2[i][j] = new double[countElements];

	double **duration = new double*[3]; // массив для длительности вычислений
	for (int i = 0; i < 3; i++)
		duration[i] = new double[countElements];

	Stopwatch^ timer = gcnew Diagnostics::Stopwatch; // класс CLI для подсчета тактов выполения кода

	ofstream fl("Logger.txt", ios::out | ios::trunc); // открываем файл для перезаписи
	GetLocalTime(&st);								  // получаем текущую дату и время, записываем ее в файл
	fl << "Дата и время запуска: " << st.wHour << ":" << st.wMinute << ":" << st.wSecond <<
		" " << st.wDay << "." << st.wMonth << "." << st.wYear << endl;
	fl.close();

	cout << "Начинаем вычисления..." << endl << endl;

	for (int index = 0; index < countElements; index++)
	{
		M += step;
		N += step;

		_count = M * N; // к-во элементов
		ofstream file("Logger.txt", ios::app); // открываем файл для дозаписи
		file << "Количество элементов: " << _count << endl;

		cout << "Вычисление над матрицей [" << M << "][" << N << "]" << endl;
		cout << "Заполение матриц и запись их в файл. ";
		timer->Start();

		// создаем матрицу
		matrix = new double *[M];
		for (int i = 0; i < M; i++)
			matrix[i] = new double[N];
		copyMatryx = new double *[M];
		for (int i = 0; i < M; i++)
			copyMatryx[i] = new double[N];

		// создаем вторую матрицу для умножения
		matrix2 = new double *[N];
		for (int i = 0; i < N; i++)
			matrix2[i] = new double[M];

		// заполняем массив и матрицу случайными числами
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				element = rand() % (2 * RANDOM + 1) - RANDOM;
				matrix[i][j] = element;
				copyMatryx[i][j] = element;
			}
		}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				matrix2[i][j] = rand() % (2 * RANDOM + 1) - RANDOM;

		// запись в файл матриц
		file << "Исходная матрица:" << endl;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
				file << matrix[i][j] << "\t";
			file << endl;
		}
		file << "Матрица 2 для умножения:" << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
				file << matrix2[i][j] << "\t";
			file << endl;
		}
		file.close();
		timer->Stop();
		cout << "Длительность " << (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency) << "с" << endl;
		timer->Reset();

		duration[0][index] = _count;

		cout << "Выполнение последовательных вычислений. ";
		ConsistentСomputing^ consistentСomputing = gcnew ConsistentСomputing(M, N, matrix, matrix2);
		timer->Start(); // старт
		consistentСomputing->CountPositiveNegativeZero();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		iIndex++;
		timer->Reset();
		timer->Start();
		consistentСomputing->CascadeSums();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistentСomputing->PrefixSum();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistentСomputing->MatrixMultiplication();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistentСomputing->FindMinimum();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistentСomputing->BubbleSort();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex = 0;
		totalDuration = 0;
		for (int i = 0; i < 6; i++)
			totalDuration += duration2[i][1][index];
		duration[1][index] = totalDuration;
		cout << "Длительность " << duration[1][index] << "с" << endl;

		cout << "Выполнение параллельных вычислений. ";
		ParallelСomputing^ parallelСomputing = gcnew ParallelСomputing(M, N, copyMatryx, matrix2);
		timer->Start();
		parallelСomputing->CountPositiveNegativeZero();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallelСomputing->CascadeSums();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallelСomputing->PrefixSum();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallelСomputing->MatrixMultiplication();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallelСomputing->FindMinimum();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallelСomputing->BubbleSort();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex = 0;
		totalDuration = 0;
		for (int i = 0; i < 6; i++)
			totalDuration += duration2[i][2][index];
		duration[2][index] = totalDuration;
		cout << "Длительность " << duration[2][index] << "с" << endl;

		cout << "Запись результатов в файл. ";
		timer->Start();
		//consistentСomputing->WriteToConsole();
		consistentСomputing->WriteToFile();
		//parallelСomputing->WriteToConsole();
		parallelСomputing->WriteToFile();
		timer->Stop();
		cout << "Длительность " << (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency) << "с" << endl << endl;
		timer->Reset();

		ofstream f("Logger.txt", ios::app); // открываем файл для дозаписи
		f << "Время последовательного выполнения: " << duration[1][index] << "с" << endl;
		f << "Время параллельного выполнения: " << duration[2][index] << "с" << endl;
		f << endl << "________________________________________________" << endl << endl;
		f.close(); // закрываем файл

		// очищаем память
		for (int i = 0; i < M; i++)
			delete[] matrix[i];
		delete[] matrix;
		for (int i = 0; i < M; i++)
			delete[] copyMatryx[i];
		delete[] copyMatryx;
		for (int i = 0; i < N; i++)
			delete[] matrix2[i];
		delete[] matrix2;
	}

	ofstream fil("Logger.txt", ios::app); // открываем файл для дозаписи
	fil << endl << endl << endl;
	fil.close();

	ofstream result("Results.txt", ios::out | ios::trunc); // открываем файл для записи результатов
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < countElements; j++)
			result << duration[i][j] << "\t";
		result << endl;
	}
	result.close();

	ofstream csv("ResultsXLS.csv", ios::out | ios::trunc); // открываем файл для записи результатов в csv файл
	locale loccomma(csv.getloc(), new comma);
	csv.imbue(loccomma);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < countElements; j++)
			csv << duration[i][j] << ";";
		csv << endl;
	}
	csv.close();


	// освобождаем память
	for (int i = 0; i < 3; i++)
		delete[] duration[i];
	delete[] duration;


	cout << "Готово! Пострение графиков..." << endl;
	Sleep(1000);

	// строим графики
	MyGrafics^ grafic = gcnew MyGrafics();
	grafic->DrawGrafics("Лабораторная работа №2", "Все методы одновременно", "Results.txt", true);
	CreateEachFileAndGrafics(duration2, countElements);

	// очистка 3-х масива
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			delete[] duration2[i][j];
	for (int i = 0; i < 6; i++)
		delete[] duration2[i];
	delete[] duration2;
}

void CreateEachFileAndGrafics(double ***duration, int countElements)
{
	cli::array< String^ >^ methodName = gcnew cli::array< String^ >(6) {
		"Количество положительных, отрицательных и нулевых элементов",
			"Каскадное суммирование",
			"Подсчет приватных сум",
			"Умножение матриц",
			"Поиск минимума",
			"Пузырьковая сортировка"
	};
	String^ newFileName = "*(result file).txt";
	cli::array< String^ >^ fileName = gcnew cli::array< String^ >(6);
	for (int k = 0; k < 6; k++)
	{
		fileName[k] = newFileName->Replace("*", methodName[k]);
		char* constCharFileName = (char*)Marshal::StringToHGlobalAnsi(fileName[k]).ToPointer();
		ofstream result(constCharFileName, ios::out | ios::trunc); // открываем файл для записи результатов
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < countElements; j++)
				result << duration[k][i][j] << "\t";
			result << endl;
		}
		result.close();
	}

	for (int i = 0; i < 6; i++)
	{
		MyGrafics^ grafics = gcnew MyGrafics();
		grafics->DrawGrafics("Лабораторная работа №2", methodName[i], fileName[i], true);
	}
}