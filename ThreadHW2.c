#include<stdio.h>
#include<pthread.h>
#define NUM_THREADS 4

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
}

main(int argc, char *argv[])
{
    pthread_t thread1, thread2, thread3, thread4;

    int count1 = atoi(argv[1]);
    int count2 = atoi(argv[2]);
    int count3 = atoi(argv[3]);
    int count4 = atoi(argv[4]);

    printf("Zach, ");
    pthread_create(&thread1, NULL, Fib, (void *)count1);
    sleep(10);
    printf("\n");
    printf("Shunk, ");
    pthread_create(&thread2, NULL, Fib, (void *)count2);
    sleep(10);
    printf("\n");
    printf("ESU, ");
    pthread_create(&thread3, NULL, Fib, (void *)count3);
    sleep(10);
    printf("\n");
    printf("CPSC, ");
    pthread_create(&thread4, NULL, Fib, (void *)count4);
    sleep(10);
    printf("\n");
    pthread_exit(NULL);
}
