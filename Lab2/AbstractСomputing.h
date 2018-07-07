#pragma once

#include "stdafx.h"

ref class AbstractСomputing abstract
{
public:
	virtual void CountPositiveNegativeZero() = 0; // количество положительных, отрицательных и нулевых элементов
	virtual double CascadeSums() = 0; // каскадное суммирование
	virtual void PrefixSum() = 0; // подсчет приватных сум
	virtual void MatrixMultiplication() = 0; // умножение матриц
	virtual double FindMinimum() = 0; // поиск минимума
	virtual void BubbleSort() = 0; // пузырьковая сортировка
	virtual void WriteToFile() = 0; // запись в файл
	virtual void WriteToConsole() = 0; // вывод на консоль
protected:
	int M;
	int N;
	int size;
	double **matrix;
	int positive = 0;
	int negative = 0;
	int zero = 0;
	double sum = 0;
	double *prefixSum;
	double **matrix2;
	double **resultMatrix;
	double minimum;
};