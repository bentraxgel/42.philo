#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

// struct timeval
// {
// 	long	tv_sec;
// 	long	tv_usec;
// }

int	main()
{
	struct timeval	tv;
	double			begin, end;

	gettimeofday(&tv, NULL);
	begin = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;

	usleep(10000);

	gettimeofday(&tv, NULL);
	end = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;

	printf("execution time%f\n", (end - begin) / 1000);
	return (0);
}