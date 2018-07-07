// Lab2.cpp: ������� ���� �������.

#include "stdafx.h"

// �����, ������� ��������� ������ ������������ ����� � ,
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
	setlocale(LC_ALL, "Russian"); // ������� ���� � �������
	srand(time(NULL)); // ��������� ���������

	SYSTEMTIME st; // ��������� �����

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

	double ***duration2 = new double**[6]; // 3-x ������ ��� ������������ ���������� ������� ������ ��������
	for (int i = 0; i < 6; i++)
		duration2[i] = new double*[3];
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			duration2[i][j] = new double[countElements];

	double **duration = new double*[3]; // ������ ��� ������������ ����������
	for (int i = 0; i < 3; i++)
		duration[i] = new double[countElements];

	Stopwatch^ timer = gcnew Diagnostics::Stopwatch; // ����� CLI ��� �������� ������ ��������� ����

	ofstream fl("Logger.txt", ios::out | ios::trunc); // ��������� ���� ��� ����������
	GetLocalTime(&st);								  // �������� ������� ���� � �����, ���������� �� � ����
	fl << "���� � ����� �������: " << st.wHour << ":" << st.wMinute << ":" << st.wSecond <<
		" " << st.wDay << "." << st.wMonth << "." << st.wYear << endl;
	fl.close();

	cout << "�������� ����������..." << endl << endl;

	for (int index = 0; index < countElements; index++)
	{
		M += step;
		N += step;

		_count = M * N; // �-�� ���������
		ofstream file("Logger.txt", ios::app); // ��������� ���� ��� ��������
		file << "���������� ���������: " << _count << endl;

		cout << "���������� ��� �������� [" << M << "][" << N << "]" << endl;
		cout << "��������� ������ � ������ �� � ����. ";
		timer->Start();

		// ������� �������
		matrix = new double *[M];
		for (int i = 0; i < M; i++)
			matrix[i] = new double[N];
		copyMatryx = new double *[M];
		for (int i = 0; i < M; i++)
			copyMatryx[i] = new double[N];

		// ������� ������ ������� ��� ���������
		matrix2 = new double *[N];
		for (int i = 0; i < N; i++)
			matrix2[i] = new double[M];

		// ��������� ������ � ������� ���������� �������
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

		// ������ � ���� ������
		file << "�������� �������:" << endl;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
				file << matrix[i][j] << "\t";
			file << endl;
		}
		file << "������� 2 ��� ���������:" << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
				file << matrix2[i][j] << "\t";
			file << endl;
		}
		file.close();
		timer->Stop();
		cout << "������������ " << (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency) << "�" << endl;
		timer->Reset();

		duration[0][index] = _count;

		cout << "���������� ���������������� ����������. ";
		Consistent�omputing^ consistent�omputing = gcnew Consistent�omputing(M, N, matrix, matrix2);
		timer->Start(); // �����
		consistent�omputing->CountPositiveNegativeZero();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		iIndex++;
		timer->Reset();
		timer->Start();
		consistent�omputing->CascadeSums();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistent�omputing->PrefixSum();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistent�omputing->MatrixMultiplication();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistent�omputing->FindMinimum();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		consistent�omputing->BubbleSort();
		timer->Stop();
		duration2[iIndex][0][index] = _count;
		duration2[iIndex][1][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex = 0;
		totalDuration = 0;
		for (int i = 0; i < 6; i++)
			totalDuration += duration2[i][1][index];
		duration[1][index] = totalDuration;
		cout << "������������ " << duration[1][index] << "�" << endl;

		cout << "���������� ������������ ����������. ";
		Parallel�omputing^ parallel�omputing = gcnew Parallel�omputing(M, N, copyMatryx, matrix2);
		timer->Start();
		parallel�omputing->CountPositiveNegativeZero();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallel�omputing->CascadeSums();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallel�omputing->PrefixSum();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallel�omputing->MatrixMultiplication();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallel�omputing->FindMinimum();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex++;
		timer->Start();
		parallel�omputing->BubbleSort();
		timer->Stop();
		duration2[iIndex][2][index] = (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency);
		timer->Reset();
		iIndex = 0;
		totalDuration = 0;
		for (int i = 0; i < 6; i++)
			totalDuration += duration2[i][2][index];
		duration[2][index] = totalDuration;
		cout << "������������ " << duration[2][index] << "�" << endl;

		cout << "������ ����������� � ����. ";
		timer->Start();
		//consistent�omputing->WriteToConsole();
		consistent�omputing->WriteToFile();
		//parallel�omputing->WriteToConsole();
		parallel�omputing->WriteToFile();
		timer->Stop();
		cout << "������������ " << (static_cast<double>(timer->ElapsedTicks) / Stopwatch::Frequency) << "�" << endl << endl;
		timer->Reset();

		ofstream f("Logger.txt", ios::app); // ��������� ���� ��� ��������
		f << "����� ����������������� ����������: " << duration[1][index] << "�" << endl;
		f << "����� ������������� ����������: " << duration[2][index] << "�" << endl;
		f << endl << "________________________________________________" << endl << endl;
		f.close(); // ��������� ����

		// ������� ������
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

	ofstream fil("Logger.txt", ios::app); // ��������� ���� ��� ��������
	fil << endl << endl << endl;
	fil.close();

	ofstream result("Results.txt", ios::out | ios::trunc); // ��������� ���� ��� ������ �����������
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < countElements; j++)
			result << duration[i][j] << "\t";
		result << endl;
	}
	result.close();

	ofstream csv("ResultsXLS.csv", ios::out | ios::trunc); // ��������� ���� ��� ������ ����������� � csv ����
	locale loccomma(csv.getloc(), new comma);
	csv.imbue(loccomma);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < countElements; j++)
			csv << duration[i][j] << ";";
		csv << endl;
	}
	csv.close();


	// ����������� ������
	for (int i = 0; i < 3; i++)
		delete[] duration[i];
	delete[] duration;


	cout << "������! ��������� ��������..." << endl;
	Sleep(1000);

	// ������ �������
	MyGrafics^ grafic = gcnew MyGrafics();
	grafic->DrawGrafics("������������ ������ �2", "��� ������ ������������", "Results.txt", true);
	CreateEachFileAndGrafics(duration2, countElements);

	// ������� 3-� ������
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
		"���������� �������������, ������������� � ������� ���������",
			"��������� ������������",
			"������� ��������� ���",
			"��������� ������",
			"����� ��������",
			"����������� ����������"
	};
	String^ newFileName = "*(result file).txt";
	cli::array< String^ >^ fileName = gcnew cli::array< String^ >(6);
	for (int k = 0; k < 6; k++)
	{
		fileName[k] = newFileName->Replace("*", methodName[k]);
		char* constCharFileName = (char*)Marshal::StringToHGlobalAnsi(fileName[k]).ToPointer();
		ofstream result(constCharFileName, ios::out | ios::trunc); // ��������� ���� ��� ������ �����������
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
		grafics->DrawGrafics("������������ ������ �2", methodName[i], fileName[i], true);
	}
}