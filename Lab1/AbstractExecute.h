#pragma once

#include "stdafx.h"

ref class AbstractExecute abstract
{
public:
	virtual double MatrixMultiplicationByFactorAndSums() = 0; // ��������� ������� �� �������� ����������� � �� ������������
	virtual void SelectNonZeroElementsIntoArray() = 0; // ����� �� ������� ��������� � ������
	virtual void SelectElementInRange() = 0; // ����� ��������� � �������� ���������
	virtual int CountRowWhereIElementEqualZero() = 0; // ���������� ������, ��� ������� = i
	virtual void AverageVector() = 0; // ���������� �������� �� �������
	virtual void MatrixVectorMultiplication() = 0; // ��������� ������� �� ������
	virtual void WriteToFile() = 0; // ������ � ����
	virtual void WriteToConsole() = 0; // ����� �� �������
	virtual void DivideByFactor() = 0; // ������� ������� �� k
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

