#include "stdafx.h"
#include "Consistent�omputing.h"

Consistent�omputing::Consistent�omputing(int m, int n, double **_matrix, double **_matrix2)
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

Consistent�omputing::~Consistent�omputing()
{
	// ������� ������
	delete[] prefixSum;

	for (int i = 0; i < M; i++)
		delete[] resultMatrix[i];
	delete[] resultMatrix;
}

void Consistent�omputing::CountPositiveNegativeZero()
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (matrix[i][j] > 0)
				positive++;
			if (matrix[i][j] < 0)
				negative++;
			if (matrix[i][j] == 0)
				zero++;
		}
	}
}

double Consistent�omputing::CascadeSums()
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			sum += matrix[i][j];
	return sum;
}

void Consistent�omputing::PrefixSum()
{
	int index = 0;
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

void Consistent�omputing::MatrixMultiplication()
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			resultMatrix[i][j] = 0;
			for (int p = 0; p < N; p++)
				resultMatrix[i][j] += matrix[i][p] * matrix2[p][j];
		}
	}
}

double Consistent�omputing::FindMinimum()
{
	minimum = matrix[0][0];
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

void Consistent�omputing::BubbleSort()
{
	double temp;
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

void Consistent�omputing::WriteToFile()
{
	ofstream file("Logger.txt", ios::app); // ��������� ���� ��� ��������
	file << "���������������� ����������" << endl;
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
	BubbleSort();
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			file << matrix[i][j] << "\t";
		file << endl;
	}
	file.close(); // ��������� ����
}

void Consistent�omputing::WriteToConsole()
{
	setlocale(LC_ALL, "Russian"); // ������� ���� � �������
	cout << "���������������� ����������" << endl;
	cout << "������� 2 ��� ���������:" << endl;
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
	//BubbleSort();
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			cout << matrix[i][j] << "\t";
		cout << endl;
	}
}