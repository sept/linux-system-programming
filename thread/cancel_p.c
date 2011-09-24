/*三个线程采用不同的接收方式并打印出 最后一个使用pthread_cancle 即在线程外杀死此线程*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thr_fn1(void *arg)
{
	printf("thread 1 returning\n");
	return (void *)1;
}
void *thr_fn2(void *arg)
{
	printf("thread 2 returning\n");
	pthread_exit((void *)2);
}
void *thr_fn3(void *arg)
{
	while (1)
	{
		printf("thread 4 writing\n");
		sleep(1);
	}
}

int main(void)
{
	pthread_t tid;
	void *tret;

	pthread_create(&tid, NULL, thr_fn1, NULL);
	pthread_join(tid, &tret);
	printf("thread 1 exit code %d\n", (int)tret);

	pthread_create(&tid, NULL, thr_fn2, NULL);
	pthread_join(tid, &tret);
	printf("thread 2 exit code %d\n", (int)tret);

	pthread_create(&tid, NULL, thr_fn3, NULL);
	sleep(3);
	pthread_cancel(tid);
	pthread_join(tid, &tret);
	printf("thread 3 exit code %d\n", (int)tret);

	return 0;
}
