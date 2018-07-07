#include "stdafx.h"
#include "ConsistentСomputing.h"

ConsistentСomputing::ConsistentСomputing(int m, int n, double **_matrix, double **_matrix2)
{
	M = m;
	N = n;
	matrix = _matrix;
	matrix2 = _matrix2;
	size = M * N;

	// создаем массив для приватных сум
	prefixSum = new double[size];

	// создаем матрицу для результата умножения
	resultMatrix = new double *[M];
	for (int i = 0; i < M; i++)
		resultMatrix[i] = new double[M];
}

ConsistentСomputing::~ConsistentСomputing()
{
	// очищаем память
	delete[] prefixSum;

	for (int i = 0; i < M; i++)
		delete[] resultMatrix[i];
	delete[] resultMatrix;
}

void ConsistentСomputing::CountPositiveNegativeZero()
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

double ConsistentСomputing::CascadeSums()
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			sum += matrix[i][j];
	return sum;
}

void ConsistentСomputing::PrefixSum()
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

void ConsistentСomputing::MatrixMultiplication()
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

double ConsistentСomputing::FindMinimum()
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

void ConsistentСomputing::BubbleSort()
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

void ConsistentСomputing::WriteToFile()
{
	ofstream file("Logger.txt", ios::app); // открываем файл для дозаписи
	file << "ПОСЛЕДОВАТЕЛЬНОЕ ВЫПОЛНЕНИЕ" << endl;
	file << "Количество положительных: " << positive << endl;
	file << "Количество отрицательных: " << negative << endl;
	file << "Количество нулевых: " << zero << endl;
	file << "Сума: " << sum << endl;
	file << "Приватные суммы:" << endl;
	for (int i = 0; i < size; i++)
		file << prefixSum[i] << "\t";
	file << endl;
	file << "Результат умножения матриц:" << endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
			file << resultMatrix[i][j] << "\t";
		file << endl;
	}
	file << "Минимальное значение: " << minimum << endl;
	file << "Отсортированиая матрица: " << endl;
	BubbleSort();
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			file << matrix[i][j] << "\t";
		file << endl;
	}
	file.close(); // закрываем файл
}

void ConsistentСomputing::WriteToConsole()
{
	setlocale(LC_ALL, "Russian"); // русский язык в консоле
	cout << "ПОСЛЕДОВАТЕЛЬНОЕ ВЫПОЛНЕНИЕ" << endl;
	cout << "Матрица 2 для умножения:" << endl;
	cout << "Количество положительных: " << positive << endl;
	cout << "Количество отрицательных: " << negative << endl;
	cout << "Количество нулевых: " << zero << endl;
	cout << "Сума: " << sum << endl;
	cout << "Приватные суммы:" << endl;
	for (int i = 0; i < size; i++)
		cout << prefixSum[i] << "\t";
	cout << endl;
	cout << "Результат умножения матриц:" << endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
			cout << resultMatrix[i][j] << "\t";
		cout << endl;
	}
	cout << "Минимальное значение: " << minimum << endl;
	cout << "Отсортированиая матрица: " << endl;
	//BubbleSort();
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			cout << matrix[i][j] << "\t";
		cout << endl;
	}
}