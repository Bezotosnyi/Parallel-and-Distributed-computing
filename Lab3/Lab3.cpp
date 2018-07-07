/*
Задача 1. Написати і відлагодити MPI - програму, в якій кореневої процес(процес з рангом 0) видає на консоль 
кількість запущених процесів, а також повідомлення
"Root process: Hello, world",
а всі інші процеси видають повідомлення
"Slave process: my rank is xxxx",
де xxx є ранг відповідного процесу.

Задача 2. Написати програму, в якій процес з номером 0 пінгує всі процеси в групі(крім самого себе),
посилаючи їм однобайтові повідомлення і приймаючи від них такі ж відповідь повідомлення.

Задача 3. Реалізувати програму підсумовування елементів вектора на заданому числі процесів (задається через аргументи):
майстер-процес посилає дочірнім частини вектора, дочірні повертають суми частин, після чого майстер-процес
їх підсумовує і виводить результат, час виконання. Порівняти з послідовним варіантом підсумовування
для 5000, 10000, 50000 елементів.
*/


#include "stdafx.h"

#define TASK 1 // задаем номер задачи

int main(int argc, char * argv[]) 
{
#if TASK == 1
	int numtasks, rank, rc;
	rc = MPI_Init(&argc, &argv);
	if (rc != MPI_SUCCESS)
	{
		printf("Error starting MPI program. Terminating. \ n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		Console::WriteLine("Count process: {0}", numtasks);
		Console::WriteLine("Root process: Hello, world");
	}
	else
		Console::WriteLine("Slave process: my rank is {0}", rank);

#elif TASK == 2
	int numtasks, rank, dest, source, rc, count, tag = 0;
	char inmsg, outmsg = 'x';
	srand(time(NULL));
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status Stat;
	if (rank == 0)
	{
		for (int i = 1; i < numtasks; i++)
		{
			dest = i;
			source = i;
			rc = MPI_Sendrecv(&outmsg, 1, MPI_CHAR, dest, 0,
				&inmsg, 1, MPI_CHAR, source, tag,
				MPI_COMM_WORLD, &Stat);
			Console::WriteLine("Task {0}: Received {1} char(s) from task {2} with tag {3} \n",
				rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);
		}
	}
	else
	{
		dest = 0;
		source = 0;
		rc = MPI_Sendrecv(&outmsg, 1, MPI_CHAR, dest, 0,
			&inmsg, 1, MPI_CHAR, source, tag,
			MPI_COMM_WORLD, &Stat);
	}

#else 
	srand(time(NULL));
	int numtasks, rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	int size;
	int sizeProcess;
	float localSum = 0, globalSum = 0;
	float *vectorArray;
	Random^ random = gcnew Random();

	for (int index = 0; index < 3; index++)
	{
		switch (index)
		{
		case 0: size = 5000;
			break;
		case 1: size = 10000;
			break;
		case 2: size = 50000;
			break;
		}
		sizeProcess = size / numtasks;
		localSum = 0;
		globalSum = 0;

		vectorArray = new float[sizeProcess];

		for (int i = 0; i < sizeProcess; i++)
			vectorArray[i] = random->Next(rank + 10);

		for (int i = 0; i < sizeProcess; i++)
			localSum += vectorArray[i];

		printf("%d.Local sum for process %d - %f\n", index, rank, localSum);

		MPI_Reduce(&localSum, &globalSum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

		if (rank == 0)
		{
			printf("%d.Total sum = %f\n", index, globalSum);
		}

		delete[] vectorArray;
	}
#endif // TASK 
	
	MPI_Finalize();
	return 0;
}

