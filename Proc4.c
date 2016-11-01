#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27
int shmid;
key_t key;
char *shm, *s;

void proc1()
{
    //get segments
    key = 5678;

    //locate segment
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        return 1;
    }

    //attach segment
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return 1;
    }

    //read segment process 1
    for (s = shm; *s != 0; s++)
        putchar(*s);
    putchar(' ');

    //indicate it was read
    s = shm;
     char text[20] = {'*','r','e','a','d'};
     int i = 0;
     for (i = 0; i < 20; i++)
         *s++ = (int)text[i];
     *s = 0;
}

void proc2()
{
    //locate segment
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        return 1;
    }

    //attach segment
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return 1;
    }

    //read segment process 2
    for (s = shm; *s != 0; s++)
        putchar(*s);
    putchar(' ');

   //indicate it was read
   s = shm;
    char text2[20] = {'@','r','e','a','d'};
    int j = 0;
    for (j = 0; j < 20; j++)
        *s++ = (int)text2[j];
    *s = 0;
}

void proc3()
{
    //locate segment
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        return 1;
    }

    //attach segment
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return 1;
    }

    //read segment process 3
    for (s = shm; *s != 0; s++)
        putchar(*s);
    putchar('\n');

   //indicate it was read
   s = shm;
    char text3[20] = {'$','r','e','a','d'};
    int k = 0;
    for (k = 0; k < 20; k++)
        *s++ = (int)text3[k];
    *s = 0;
}

int main()
{
    proc1();
    sleep(2);
    proc2();
    sleep(2);
    proc3();

    return 0;
}
