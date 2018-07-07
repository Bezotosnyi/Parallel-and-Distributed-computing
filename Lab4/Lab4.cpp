/*
Задача 1. Модифікувати текст попередньої програми таким чином, щоб
а) в рамках першої групи виконувалася колективна операція MPI_MIN, і ре-
зультат містився в процес з найменшим рангом в глобальній (вихідної) групі і роздруковувався їм
б) в рамках другої групи виконувалася колективна операція MPI_MAX, і ре-
зультат містився в процес з найбільшим рангом в глобальній (вихідній) групі і роздруковувався ним.

Задача 2. 16 процесів об'єднуються в декартову топологію 4х4
*/

#include "stdafx.h"

#define TASK 1 // задаем номер задачи

#define SIZE 16
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

int main(int argc, char*argv[]) 
{
#if TASK == 1
	int numtasks;
	int rank, rank1, rank2;
	int dims[3] = { 2,2,4 }, periods[3] = { 1,1,1 }, reorder = 0, coords[3];
	int source, dest;
	MPI_Comm cartcomm, sub_cart;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (numtasks == SIZE) 
	{
		MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, reorder, &cartcomm);
		MPI_Comm_rank(cartcomm, &rank1);
		MPI_Cart_coords(cartcomm, rank, 3, coords);
		printf("rank %d has such coordinates: %d %d %d\n", rank1, coords[0], coords[1], coords[2]);
		int subdims[] = { 2,0,4 };
		int coords2[3];
		MPI_Cart_sub(cartcomm, subdims, &sub_cart);//создание подрешетки
		MPI_Comm_rank(sub_cart, &rank2);//присвоение новых рангов в sub_cart
		if (rank2 != MPI_UNDEFINED)
		{
			MPI_Cart_coords(sub_cart, rank2, 3, coords2);//определение координат
			printf("rank %d in sub_cart has such coordinates: %d %d %d\n", rank2, coords2[0], coords2[1], coords2[2]);
		}
	}
	else
		printf("Must specify %d processors. Terminating.\n", SIZE);
#else
	int numtasks, rank, source, dest, outbuf, i, tag = 1,
		inbuf[4] = { MPI_PROC_NULL,MPI_PROC_NULL,MPI_PROC_NULL,MPI_PROC_NULL, },
		nbrs[4], dims[2] = { 4,4 },
		periods[2] = { 0,0 }, reorder = 0, coords[2];
	MPI_Request reqs[8];
	MPI_Status stats[8];
	MPI_Comm cartcomm;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	if (numtasks == SIZE)
	{
		MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);
		MPI_Comm_rank(cartcomm, &rank);
		MPI_Cart_coords(cartcomm, rank, 2, coords);
		MPI_Cart_shift(cartcomm, 0, 1, &nbrs[UP], &nbrs[DOWN]);
		MPI_Cart_shift(cartcomm, 1, 1, &nbrs[LEFT], &nbrs[RIGHT]);
		outbuf = rank;
		for (i = 0; i < 4; i++) {
			dest = nbrs[i];
			source = nbrs[i];
			MPI_Isend(&outbuf, 1, MPI_INT, dest, tag,
				MPI_COMM_WORLD, &reqs[i]);
			MPI_Irecv(&inbuf[i], 1, MPI_INT, source, tag,
				MPI_COMM_WORLD, &reqs[i + 4]);
		}
		MPI_Waitall(8, reqs, stats);
		printf("rank= %d coords= %d %d  neighbors(u,d,l,r)= %d %d %d %d\n", rank, coords[0], coords[1], nbrs[UP], nbrs[DOWN], nbrs[LEFT], nbrs[RIGHT]);
		printf("rank= %d inbuf(u,d,l,r)= %d %d %d %d\n",
			rank, inbuf[UP], inbuf[DOWN], inbuf[LEFT], inbuf[RIGHT]);
	}
	else
		printf("Must specify %d processors. Terminating.\n", SIZE);
#endif // TASK

	MPI_Finalize();
	return 0;
}


