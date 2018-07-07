#pragma once
#include "stdafx.h"
#include "AbstractÑomputing.h"

ref class ConsistentÑomputing : public AbstractÑomputing
{
public:
	ConsistentÑomputing(int m, int n, double **_matrix, double **_matrix2);
	~ConsistentÑomputing();

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