#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <thread>

void error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

void* does_not(void *a)
{
	int i = 0;
	for(i = 0; i < 5; i++)
	{
		sleep(1);
		puts("А вот и нет!");
	}
	return NULL;
}

void* does_too(void *a)
{
	int i = 0;
	for(i = 0; i < 5; i++)
	{
		sleep(1);
		puts("А вот и да!");
	}
	return NULL;
}

int main ()
{
	pthread_t t0;
	pthread_t t1;

	if(pthread_create(&t0, NULL, does_not, NULL) == -1)
		error("Не могу создать поток t0");
	if(pthread_create(&t1, NULL, does_too, NULL) == -1)
		error("Не могу создать поток t1");

	void* result;
	if (pthread_join(t0, &result) == -1)
		error("Can't join thread t0");
	if (pthread_join(t1, &result) == -1)
		error("Can't join thread t1");
	

}
