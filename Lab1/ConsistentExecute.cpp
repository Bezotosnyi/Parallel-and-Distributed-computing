#include "stdafx.h"
#include "ConsistentExecute.h"

ConsistentExecute::ConsistentExecute(int m, int n, double ** _matrix, double * _vector, double _factor, double _a, double _b, int _iElement, int _lenVector)
{
	M = m;
	N = n;
	matrix = _matrix;
	vector = _vector;
	factor = _factor;
	a = _a;
	b = _b;
	iElement = _iElement;
	lenVector = _lenVector;
	size = M * N;

	matrixVectorMultArray = new double[M];
}

ConsistentExecute::~ConsistentExecute()
{
	delete nonZeroElementsArray;
	delete elementRangeArray;
	delete averageVectorArray;
	delete matrixVectorMultArray;
}

double ConsistentExecute::MatrixMultiplicationByFactorAndSums()
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			matrix[i][j] *= factor;
			sum += matrix[i][j];
		}
	}

	return sum;
}

void ConsistentExecute::SelectNonZeroElementsIntoArray()
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (matrix[i][j] != 0)
				countNonZeroElements++;
		}
	}
	if (countNonZeroElements != 0)
	{
		nonZeroElementsArray = new double[countNonZeroElements];
		index = 0;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (matrix[i][j] != 0)
				{
					nonZeroElementsArray[index] = matrix[i][j];
					index++;
				}
			}
		}
	}
}

void ConsistentExecute::SelectElementInRange()
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (matrix[i][j] > a && matrix[i][j] < b)
			{
				countElementRange++;
			}
		}
	}
	if (countElementRange != 0)
	{
		elementRangeArray = new double[countElementRange];
		index = 0;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (matrix[i][j] > a && matrix[i][j] < b)
				{
					elementRangeArray[index] = matrix[i][j];
					index++;
				}
			}
		}
	}
}

int ConsistentExecute::CountRowWhereIElementEqualZero()
{
	if (iElement > N)
		return countRow;
	for (int i = 0; i < M; i++)
	{
		if (matrix[i][iElement] == 0)
			countRow++;
	}
	return countRow;
}

void ConsistentExecute::AverageVector()
{
	if (lenVector <= size)
	{
		avgVectorSize = ceil(static_cast<int>(size) / lenVector);
		averageVectorArray = new double[avgVectorSize];
		index = 0;
		v = 0;
		vect = 0;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				vect += matrix[i][j];
				v++;
				if (v == lenVector || (i == M - 1 && j == N - 1))
				{
					averageVectorArray[index] = vect / v;
					index++;
					vect = 0;
					v = 0;
				}
			}
		}
	}
}

void ConsistentExecute::MatrixVectorMultiplication()
{
	for (int i = 0; i < M; i++)
	{
		matrixVectorMultArray[i] = 0;
		for (int j = 0; j < N; j++)
			matrixVectorMultArray[i] += matrix[i][j] * vector[i];
	}
}

void ConsistentExecute::WriteToFile()
{
	ofstream file("Logger.txt", ios::app); // открываем файл для дозаписи
	file << "ПОСЛЕДОВАТЕЛЬНОЕ ВЫПОЛНЕНИЕ" << endl;
	file << "Матрица, умноженная на коэффициент " << factor << ":" << endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			file << matrix[i][j] << "\t";
		file << endl;
	}
	if(countNonZeroElements == 0)
		file << "В матрице все элементы 0!" << endl;
	else
	{
		file << "Не нулевые элементы матрицы:" << endl;
		pEndl = 0;
		for (int i = 0; i < countNonZeroElements; i++)
		{
			file << nonZeroElementsArray[i] << "\t";
			pEndl++;
			if (pEndl == N)
			{
				file << endl;
				pEndl = 0;
			}
		}
		file << endl;
	}
	if (countElementRange == 0)
		file << "Нет элементов матрицы в диапозоне " << a << " - " << b << "!" << endl;
	else
	{
		file << "Элементы матрицы в диапозоне " << a << " - " << b << "!" << endl;
		pEndl = 0;
		for (int i = 0; i < countElementRange; i++)
		{
			file << elementRangeArray[i] << "\t";
			pEndl++;
			if (pEndl == N)
			{
				file << endl;
				pEndl = 0;
			}
		}
		file << endl;
	}
	if (countRow == 0)
		file << "Нет строчек, где "<< iElement << "-ый элемент равен 0" << endl;
	else
		file << "Количество строчек, где " << iElement << "-ый элемент равен 0: " << countRow << endl;
	if (lenVector > size)
		file << "Длина вектора " << lenVector << " больше чем количество элементов в матрице!" << endl;
	else
	{
		file << "Усреденененные значения вектора длиной " << lenVector << ":" << endl;
		pEndl = 0;
		for (int i = 0; i < avgVectorSize; i++)
		{
			file << averageVectorArray[i] << "\t";
			pEndl++;
			if (pEndl == N)
			{
				file << endl;
				pEndl = 0;
			}
		}
		file << endl;
	}
	file << "Матрица, умноженная на вектор:" << endl;
	pEndl = 0;
	for (int i = 0; i < M; i++)
	{
		file << matrixVectorMultArray[i] << "\t";
		pEndl++;
		if (pEndl == N)
		{
			file << endl;
			pEndl = 0;
		}
	}
	
	file.close(); // закрываем файл
}

void ConsistentExecute::WriteToConsole()
{
	setlocale(LC_ALL, "Russian"); // русский язык в консоле
	cout << "ПОСЛЕДОВАТЕЛЬНОЕ ВЫПОЛНЕНИЕ" << endl;
	cout << "Матрица, умноженная на коэффициент " << factor << ":" << endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			cout << matrix[i][j] << "\t";
		cout << endl;
	}
	if (countNonZeroElements == 0)
		cout << "В матрице все элементы 0!" << endl;
	else
	{
		cout << "Не нулевые элементы массива:" << endl;
		pEndl = 0;
		for (int i = 0; i < countNonZeroElements; i++)
		{
			cout << nonZeroElementsArray[i] << "\t";
			pEndl++;
			if (pEndl == N)
			{
				cout << endl;
				pEndl = 0;
			}
		}
		cout << endl;
	}
	if (countElementRange == 0)
		cout << "Нет элементов матрицы в диапозоне " << a << " - " << b << "!" << endl;
	else
	{
		cout << "Элементы матрицы в диапозоне " << a << " - " << b << "!" << endl;
		pEndl = 0;
		for (int i = 0; i < countElementRange; i++)
		{
			cout << elementRangeArray[i] << "\t";
			pEndl++;
			if (pEndl == N)
			{
				cout << endl;
				pEndl = 0;
			}
		}
		cout << endl;
	}
	if (countRow == 0)
		cout << "Нет строчек, где " << iElement << "-ый элемент равен 0" << endl;
	else
		cout << "Количество строчек, где " << iElement << "-ый элемент равен 0: " << countRow << endl;
	if (lenVector > size)
		cout << "Длина вектора " << lenVector << " больше чем количество элементов в матрице!" << endl;
	else
	{
		cout << "Усреденененные значения вектора длиной " << lenVector << ":" << endl;
		pEndl = 0;
		for (int i = 0; i < avgVectorSize; i++)
		{
			cout << averageVectorArray[i] << "\t";
			pEndl++;
			if (pEndl == N)
			{
				cout << endl;
				pEndl = 0;
			}
		}
		cout << endl;
	}
	cout << "Матрица, умноженная на вектор:" << endl;
	pEndl = 0;
	for (int i = 0; i < M; i++)
	{
		cout << matrixVectorMultArray[i] << "\t";
		pEndl++;
		if (pEndl == N)
		{
			cout << endl;
			pEndl = 0;
		}
	}
	cout << endl;
}

void ConsistentExecute::DivideByFactor()
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			matrix[i][j] /= factor;
}

