#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>


time_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + (current_time.tv_usec / 1000));
}

void	ft_sleep(time_t amount)
{
	time_t	start;
    time_t  time;

	start = get_time();
    time = get_time() - start;
	while (time < amount)
	{
        printf("time = %ld\n", time);
        usleep(100);
        time = get_time() - start;
    }	
}

typedef struct test
{
    int  g;
    char *ptr;
    int f;
} test;

int main(int ac, char **av)
{

    printf("size of struct is : %zu\n", sizeof(test));
    // sem_t   *sem = sem_open("/forks", O_CREAT, 0666, 1);
    // if (sem == SEM_FAILED)
    //     exit (1);
    // sem_post(sem);
    exit (0);

}
