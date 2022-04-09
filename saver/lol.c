#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
typedef struct timeval t_time;

void ft_sleep(long ms)
{
	t_time a;
	long	start;

	gettimeofday(&a, NULL);
	start = a.tv_sec * 1000000 + a.tv_usec;
	while (1)
	{
		gettimeofday(&a, NULL);
		if (a.tv_sec * 1000000 + a.tv_usec - start > 1000 * ms)
			break;
	}
}

int main()
{
	t_time a;
	t_time b;
	int q;

	gettimeofday(&a, NULL);
//	if (31)
//	usleep(1000);
	ft_sleep(1);
//	usleep(1000);
//	printf("lollollollollollollollollollollollollollollollollollollollollollollollol\n");
	gettimeofday(&b, NULL);
	printf("%ld", (b.tv_sec * 1000000 + b.tv_usec - (a.tv_sec * 1000000 + a.tv_usec)));
}


