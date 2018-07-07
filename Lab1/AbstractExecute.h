#pragma once

#include "stdafx.h"

ref class AbstractExecute abstract
{
public:
	virtual double MatrixMultiplicationByFactorAndSums() = 0; // умножение матрицы на заданный коэффициент и их суммирование
	virtual void SelectNonZeroElementsIntoArray() = 0; // выбор не нулевых элементов в массив
	virtual void SelectElementInRange() = 0; // выбор элементов в заданном диапазоне
	virtual int CountRowWhereIElementEqualZero() = 0; // количество рядков, где элемент = i
	virtual void AverageVector() = 0; // усреднение значений по вектору
	virtual void MatrixVectorMultiplication() = 0; // умножение матрицы на вектор
	virtual void WriteToFile() = 0; // запись в файл
	virtual void WriteToConsole() = 0; // вывод на консоль
	virtual void DivideByFactor() = 0; // деление матрицы на k
protected:
	int M;
	int N;
	int size;
	double factor;
	double **matrix;
	double *vector;
	double sum = 0;
	int index = 0;
	int countNonZeroElements = 0;
	double *nonZeroElementsArray;
	double a;
	double b;
	int countElementRange = 0;
	double *elementRangeArray;
	int iElement;
	int countRow = 0;
	int v = 0;
	double vect = 0;
	int lenVector;
	int avgVectorSize = 0;
	double *averageVectorArray;
	double *matrixVectorMultArray;
	int pEndl = 0;
};

