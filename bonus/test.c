#include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
//	int i = -23;
//	int j = 56;
////	printf("%d", 1256 | 124 | 124);
//	printf("%d %d\n", i, j);
//	i = i ^ j;
//	j = i ^ j;
//	i = i ^ j;
//	printf("%d %d\n", i, j);
//	int i = -2;
//
//	i <<= 6;
//	i >>= 1;
	int val;

//	printf("%d", (-1 & -1 & -1 & -1 & 0));
//	printf("%d", (-1 | -1 | -2 | -2));
//	printf("%d", (-1 ^ -1 ^ -1 ^ -1));
	sem_t	*forks_sem;
	forks_sem = sem_open("/sem_1", O_CREAT, 0666, 6); //посмотреть как O_EXCL работает
	if (forks_sem == SEM_FAILED)
	{
		printf("blya\n");
		return (0);
	}
	sem_getvalue(forks_sem, &val);
	printf("%d\n", val);
}
