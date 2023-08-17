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

	// double	diff = (((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec - start.tv_usec) / 1000));
	printf("%f - %f\n", begin, end);
	printf("execution time%f\n", (end - begin));
	return (0);
}