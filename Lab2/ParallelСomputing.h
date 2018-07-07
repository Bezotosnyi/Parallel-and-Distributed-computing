#pragma once
#include "stdafx.h"
#include "AbstractÑomputing.h"

ref class ParallelÑomputing : public AbstractÑomputing
{
public:
	ParallelÑomputing(int m, int n, double **_matrix, double **_matrix2);
	~ParallelÑomputing();

	// Óíàñëåäîâàíî ÷åğåç AbstractÑomputing
	virtual void CountPositiveNegativeZero() override;
	virtual double CascadeSums() override;
	virtual void PrefixSum() override;
	virtual void MatrixMultiplication() override;
	virtual double FindMinimum() override;
	virtual void BubbleSort() override;
	virtual void WriteToFile() override;
	virtual void WriteToConsole() override;
};