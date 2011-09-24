/*生成五个线程 并判断接收之后回收 然后退出 进程*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *foo(void *num)
{
	int t;
	t = *(int *)num;
	printf("I am child thread %d\n", t);	
	sleep(1);
}

int main(void)
{
	pthread_t ptd;
	int a, i;

	for (i = 0; i < 5; i++)
	{
		a = i;
		if (pthread_create(&ptd, NULL, foo, &a) != 0)
		{                           
			perror("pthread creat failed\n");
			exit(-1);
		}
		sleep(3);                 //若此处没有sleep 则会忽略0 线程 因为第一次执行完之后i++;
	}
	while (pthread_join(ptd, NULL) == 0);  //回收 成功返回是0， 错误是-1
	{
		printf("child thread over\n");
		pthread_exit(NULL);
	}
	return 0;

