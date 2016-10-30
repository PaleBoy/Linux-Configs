#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     200

int main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *r;

    //set memory segment
    key = 5679;

    //create the segment
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return 1;
    }

    //attach segment to data space
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return 1;
    }

    //put things into memory
    r = shm;
    char text[21] = {'i','s'};
    int i = 0;
    for (i = 0; i < 21; i++)
        *r++ = (int)text[i];
    *r = 0;

    //wait till it gets read by process 4
    sleep(30);

    return 0;
}
