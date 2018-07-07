#include "stdafx.h"
#include "ParallelСomputing.h"

ParallelСomputing::ParallelСomputing(int m, int n, double **_matrix, double **_matrix2)
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

ParallelСomputing::~ParallelСomputing()
{
	// очищаем память
	delete[] prefixSum;

	for (int i = 0; i < M; i++)
		delete[] resultMatrix[i];
	delete[] resultMatrix;
}

void ParallelСomputing::CountPositiveNegativeZero()
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

double ParallelСomputing::CascadeSums()
{
#pragma omp for schedule(static, 1000) reduction(+:sum)
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			sum += matrix[i][j];
	return sum;
}

void ParallelСomputing::PrefixSum()
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

void ParallelСomputing::MatrixMultiplication()
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

double ParallelСomputing::FindMinimum()
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

void ParallelСomputing::BubbleSort()
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

void ParallelСomputing::WriteToFile()
{
	ofstream file("Logger.txt", ios::app); // открываем файл для дозаписи
	file << endl << "ПАРАЛЛЕЛЬНОЕ ВЫПОЛНЕНИЕ" << endl;
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
	//BubbleSort();
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			file << matrix[i][j] << "\t";
		file << endl;
	}
	file.close(); // закрываем файл
}

void ParallelСomputing::WriteToConsole()
{
	setlocale(LC_ALL, "Russian"); // русский язык в консоле
	cout << endl << "ПАРАЛЛЕЛЬНОЕ ВЫПОЛНЕНИЕ" << endl;
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
	BubbleSort();
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			cout << matrix[i][j] << "\t";
		cout << endl;
	}
}