// Lab1.cpp: главный файл проекта.

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

	double **matrix; 
	double *vector; 

	int countElements = 12;
	int step = 10;
	int M = 0, N = 0;
	int _count;
	double element;
	int iIndex = 0;
	double totalDuration = 0;

	double k;
	double a, b;
	int iElement; 
	int lenVector;

	cout << "Введите коэффициент k: ";
	cin >> k;

	cout << "Введите диапазон a и b:" << endl;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;

	cout << "Введите i-й рядок:" << endl;
	cout << "i = ";
	cin >> iElement;

	cout << "Введите длину вектора для усредения его елементов: ";
	cin >> lenVector;
	cout << endl;

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

		// создаем ветор
		vector = new double[M];

		// заполняем массив и вектор случайными числами
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				matrix[i][j] = rand() % RANDOM;

		for (int i = 0; i < M; i++)
			vector[i] = rand() % RANDOM;

		// запись в файл матриц
		file << "Матрица:" << endl;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
				file << matrix[i][j] << "\t";
			file << endl;
		}
		file << "Вектор:" << endl;
		for (int i = 0; i < M; i++)
			file << vector[i] << "\t";
		file << endl;
		file.close();

		timer->Stop();
		cout << "Длительность " << (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency) << "с" << endl;
		timer->Reset();

		duration[0][index] = _count;

		cout << "Выполнение последовательных вычислений. ";

		ConsistentExecute^ consistentExecute = gcnew ConsistentExecute(M, N, matrix, vector, k, a, b, iElement, lenVector);
		timer->Reset();
		timer->Start(); // старт
		consistentExecute->MatrixMultiplicationByFactorAndSums();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		iIndex++;
		timer->Reset();
		timer->Start();
		consistentExecute->SelectNonZeroElementsIntoArray();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistentExecute->SelectElementInRange();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistentExecute->CountRowWhereIElementEqualZero();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistentExecute->AverageVector();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistentExecute->MatrixVectorMultiplication();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex = 0;
		totalDuration = 0;
		consistentExecute->DivideByFactor();
		for (int i = 0; i < 6; i++)
			totalDuration += duration2[i][1][index];
		duration[1][index] = totalDuration;
		cout << "Длительность " << duration[1][index] << "с" << endl;

		cout << "Выполнение параллельных вычислений. ";
		ParallelExecute^ parallelExecute = gcnew ParallelExecute(M, N, matrix, vector, k, a, b, iElement, lenVector);
		timer->Reset();
		timer->Start();
		parallelExecute->MatrixMultiplicationByFactorAndSums();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallelExecute->SelectNonZeroElementsIntoArray();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallelExecute->SelectElementInRange();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallelExecute->CountRowWhereIElementEqualZero();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallelExecute->AverageVector();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallelExecute->MatrixVectorMultiplication();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex = 0;
		totalDuration = 0;
		parallelExecute->DivideByFactor();
		for (int i = 0; i < 6; i++)
			totalDuration += duration2[i][2][index];
		duration[2][index] = totalDuration;
		cout << "Длительность " << duration[2][index] << "с" << endl;

		cout << "Запись результатов в файл. ";
		timer->Start();		
		//consistentExecute->WriteToConsole();
		consistentExecute->WriteToFile();
		//parallelExecute->WriteToConsole();
		parallelExecute->WriteToFile();
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
		delete vector;
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
	grafic->DrawGrafics("Лабораторная работа №1", "Все методы одновременно", "Results.txt", true);
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
			"Умножение матрицы на коэффициент с дальнейшим суммированием элементов",
			"Выбор не нулевых элементов матрицы в новый массив",
			"Выбор элементов в заданном диапазоне",
			"Количество строчек, где i-ый элемент = 0",
			"Усреденение по вектору",
			"Умножение матрицы на вектор"
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
		grafics->DrawGrafics("Лабораторная работа №1", methodName[i], fileName[i], true);
	}
}
