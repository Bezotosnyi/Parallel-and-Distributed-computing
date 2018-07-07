#include "stdafx.h"
#include "Parallel�omputing.h"

Parallel�omputing::Parallel�omputing(int m, int n, double **_matrix, double **_matrix2)
{
	M = m;
	N = n;
	matrix = _matrix;
	matrix2 = _matrix2;
	size = M * N;

	// ������� ������ ��� ��������� ���
	prefixSum = new double[size];

	// ������� ������� ��� ���������� ���������
	resultMatrix = new double *[M];
	for (int i = 0; i < M; i++)
		resultMatrix[i] = new double[M];
}

Parallel�omputing::~Parallel�omputing()
{
	// ������� ������
	delete[] prefixSum;

	for (int i = 0; i < M; i++)
		delete[] resultMatrix[i];
	delete[] resultMatrix;
}

void Parallel�omputing::CountPositiveNegativeZero()
{
#pragma omp parallel for
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (matrix[i][j] > 0)
#pragma omp critical(critical1)
					positive++;

				else if (matrix[i][j] < 0)
#pragma omp critical(critical2)
					negative++;

				else
#pragma omp critical(critical3)
					zero++;
			}
		}
	}
}

double Parallel�omputing::CascadeSums()
{
#pragma omp for schedule(static, 1000) reduction(+:sum)
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			sum += matrix[i][j];
	return sum;
}

void Parallel�omputing::PrefixSum()
{
	int index = 0;
#pragma omp for schedule(dynamic, 100) 
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (index == 0)
				prefixSum[index] = matrix[i][j];
			else
				prefixSum[index] = prefixSum[index - 1] + matrix[i][j];
			index++;
		}
	}
}

void Parallel�omputing::MatrixMultiplication()
{
	int i, j, p;
#pragma omp parallel for shared(matrix, matrix2, resultMatrix, M, N) private(i, j, p)
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < M; j++)
		{
			resultMatrix[i][j] = 0;
			for (p = 0; p < N; p++)
				resultMatrix[i][j] += matrix[i][p] * matrix2[p][j];
		}
	}
}

double Parallel�omputing::FindMinimum()
{
	minimum = matrix[0][0];
#pragma omp for schedule(guided, 100) 
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (matrix[i][j] < minimum)
				minimum = matrix[i][j];
		}
	}
	return minimum;
}

void Parallel�omputing::BubbleSort()
{
	double temp;
#pragma omp parallel for
	for (int k = 0; k < M; k++)
	{
		for (int l = 0; l < N; l++)
		{
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (j + 1 == N)
					{
						if (i + 1 < M && matrix[i][j] > matrix[i + 1][0])
						{
							temp = matrix[i][j];
							matrix[i][j] = matrix[i + 1][0];
							matrix[i + 1][0] = temp;
						}
					}
					else
					{
						if (matrix[i][j] > matrix[i][j + 1])
						{
							temp = matrix[i][j];
							matrix[i][j] = matrix[i][j + 1];
							matrix[i][j + 1] = temp;
						}
					}
				}
			}
		}
	}
}

void Parallel�omputing::WriteToFile()
{
	ofstream file("Logger.txt", ios::app); // ��������� ���� ��� ��������
	file << endl << "������������ ����������" << endl;
	file << "���������� �������������: " << positive << endl;
	file << "���������� �������������: " << negative << endl;
	file << "���������� �������: " << zero << endl;
	file << "����: " << sum << endl;
	file << "��������� �����:" << endl;
	for (int i = 0; i < size; i++)
		file << prefixSum[i] << "\t";
	file << endl;
	file << "��������� ��������� ������:" << endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
			file << resultMatrix[i][j] << "\t";
		file << endl;
	}
	file << "����������� ��������: " << minimum << endl;
	file << "��������������� �������: " << endl;
	//BubbleSort();
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			file << matrix[i][j] << "\t";
		file << endl;
	}
	file.close(); // ��������� ����
}

void Parallel�omputing::WriteToConsole()
{
	setlocale(LC_ALL, "Russian"); // ������� ���� � �������
	cout << endl << "������������ ����������" << endl;
	cout << "���������� �������������: " << positive << endl;
	cout << "���������� �������������: " << negative << endl;
	cout << "���������� �������: " << zero << endl;
	cout << "����: " << sum << endl;
	cout << "��������� �����:" << endl;
	for (int i = 0; i < size; i++)
		cout << prefixSum[i] << "\t";
	cout << endl;
	cout << "��������� ��������� ������:" << endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
			cout << resultMatrix[i][j] << "\t";
		cout << endl;
	}
	cout << "����������� ��������: " << minimum << endl;
	cout << "��������������� �������: " << endl;
	BubbleSort();
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			cout << matrix[i][j] << "\t";
		cout << endl;
	}
}