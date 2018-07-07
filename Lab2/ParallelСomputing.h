#pragma once
#include "stdafx.h"
#include "Abstract�omputing.h"

ref class Parallel�omputing : public Abstract�omputing
{
public:
	Parallel�omputing(int m, int n, double **_matrix, double **_matrix2);
	~Parallel�omputing();

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