#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27

int main()
{
    int shmid;
    key_t key1, key2, key3;
    char *shm, *s, *r, *t, theString[10];

    //get segments
    key1 = 5678;
    key2 = 5679;
    key3 = 5680;

    //locate segment 1
    if ((shmid = shmget(key1, SHMSZ, 0666)) < 0) {
        perror("shmget");
        return 1;
    }

    //attach segment 1
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return 1;
    }

    //read segment 1
    printf("Text from shared memory: " );
   for (s = shm; *s != 0; s++)
       putchar(*s);
   putchar('\n');

    /* //locate segment 2
    if ((shmid = shmget(key2, SHMSZ, 0666)) < 0) {
        perror("shmget");
        return 1;
    }

    //attach segment 2
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return 1;
    }

    //read segment 2
    printf("Text from shared memory: " );
   for (r = shm; *r != 0; s++)
       putchar(*r);
   putchar('\n');

    //locate segment 3
    if ((shmid = shmget(key3, SHMSZ, 0666)) < 0) {
        perror("shmget");
        return 1;
    }

    /* //attach segment 3
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return 1;
    }

    //read segment 3
    printf("Text from shared memory: " );
   for (t = shm; *t != 0; s++)
       putchar(*t);
   putchar('\n');

    /* //print out the string
    printf("%s", theString); */


    return 0;
}
