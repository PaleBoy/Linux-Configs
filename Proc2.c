#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27

int main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    //set memory segment
    key = 5678;

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

    while (*shm != '*')
        sleep(1);

    //put things into memory
    s = shm;
    char text[21] = {'i','s'};
    int i = 0;
    for (i = 0; i < 21; i++)
        *s++ = (int)text[i];
    *s = 0;

    //wait till it gets read by process 4
    while (*shm != '@')
        sleep(1);

    return 0;
}
