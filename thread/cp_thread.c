#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
int fd, dp;
int allsize = 0;
int counter = 0;
int temp = 0;

void *thread_copy(void *arg)
{
	int len;
	int buf = (int)arg; 
	int str[4096];

	pthread_mutex_lock(&counter_mutex);
	allsize = counter;
	lseek(fd, allsize, SEEK_SET);
	lseek(dp, allsize, SEEK_SET);
	len = read(fd, str, buf);
	write(dp, str, len);
	counter += buf;
	printf("进度： %d\n", counter);
	pthread_mutex_unlock(&counter_mutex);
	
	return NULL;
}
int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("error input\n");
		exit(-1);
	}
	struct stat buf;
	int i;
	int num = atoi(argv[3]);
	pthread_t array[num];
	fd = open(argv[1], O_RDWR);
	if (fd < 0)
	{
		perror("open failed");
		exit(-1);
	}
	fstat(fd, &buf);
	dp = open(argv[2], O_RDWR | O_CREAT, 0777);
	if (dp < 0)
	{
		perror("open dp failed");
		exit(-1);
	}
	for (i = 0; i < num; i++)
	{
		pthread_create(&array[i], NULL, thread_copy, (void *)(buf.st_size/num));
	}
	for (i = 0; i < num; i++)
	{
		pthread_join(array[i], NULL);
	}
	close(dp);
	close(fd);

	return 0;

}
