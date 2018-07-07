#pragma once

#include "stdafx.h"

ref class Abstract�omputing abstract
{
public:
	virtual void CountPositiveNegativeZero() = 0; // ���������� �������������, ������������� � ������� ���������
	virtual double CascadeSums() = 0; // ��������� ������������
	virtual void PrefixSum() = 0; // ������� ��������� ���
	virtual void MatrixMultiplication() = 0; // ��������� ������
	virtual double FindMinimum() = 0; // ����� ��������
	virtual void BubbleSort() = 0; // ����������� ����������
	virtual void WriteToFile() = 0; // ������ � ����
	virtual void WriteToConsole() = 0; // ����� �� �������
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