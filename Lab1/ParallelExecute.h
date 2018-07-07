#pragma once
ref class ParallelExecute : public AbstractExecute
{
public:
	ParallelExecute(int m, int n, double ** _matrix, double * _vector, double _factor, double _a, double _b, int _iElement, int _lenVector);
	~ParallelExecute();

	// Унаследовано через AbstractExecute
	virtual double MatrixMultiplicationByFactorAndSums() override;
	virtual void SelectNonZeroElementsIntoArray() override;
	virtual void SelectElementInRange() override;
	virtual int CountRowWhereIElementEqualZero() override;
	virtual void AverageVector() override;
	virtual void MatrixVectorMultiplication() override;
	virtual void WriteToFile() override;
	virtual void WriteToConsole() override;
	virtual void DivideByFactor() override;
};

