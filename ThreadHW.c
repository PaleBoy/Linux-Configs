#include<stdio.h>
#include<pthread.h>
#define NUM_THREADS 1

void *Fib(void *arg)
{
    int a=0;
    int b =1;
    int c = 0;
    int n = (int)arg;

    printf("%d, %d, ", a, b);
    for (int i =0; i < n; i++)
    {
        c = a + b;
        printf("%d, ", c);
        a = b;
        b = c;
    }
    pthread_exit(NULL);
}

main()
{
    pthread_t thread1;

    int n = 15;

    printf("Zach, ");
    pthread_create(&thread1, NULL, Fib, (void *)n);

    pthread_exit(NULL);
}
