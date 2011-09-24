#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NLOOP 5

int counter;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
/*使用全局变量 宏定义的 方法 创建锁*/

void *doit(void *);

int main(void)
{
	pthread_t tidA, tidB;

	pthread_create(&tidA, NULL, doit, NULL);   /*创建线程*/
	pthread_create(&tidB, NULL, doit, NULL);

	pthread_join(tidA, NULL);                /*等待子线程结束　（阻塞函数）*/
	pthread_join(tidB, NULL);

	return 0;
}

void *doit(void *vptr)
{
	int i, val;

	for (i = 0; i < NLOOP; i++)
	{
		pthread_mutex_lock(&counter_mutex);	　/*获得锁　（阻塞函数）*/
　　　　　　　　　　　　　　　　　　　　　　　　　　　　　/*获得锁的非阻塞函数pthread_mutex_unlock*/　　　
		val = counter;
		printf("%x: %d\n", (unsigned int)pthread_self(), val+1);
		counter = val + 1;             /* 获得本线程的线程号*/

		pthread_mutex_unlock(&counter_mutex); /*释放锁　即为　解锁*/
	}
	
	return NULL;
}
