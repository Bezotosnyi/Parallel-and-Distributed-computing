#pragma once
#include "stdafx.h"
#include "Abstract�omputing.h"

ref class Consistent�omputing : public Abstract�omputing
{
public:
	Consistent�omputing(int m, int n, double **_matrix, double **_matrix2);
	~Consistent�omputing();

	// ������������ ����� Abstract�omputing
	virtual void CountPositiveNegativeZero() override;
	virtual double CascadeSums() override;
	virtual void PrefixSum() override;
	virtual void MatrixMultiplication() override;
	virtual double FindMinimum() override;
	virtual void BubbleSort() override;
	virtual void WriteToFile() override;
	virtual void WriteToConsole() override;
};