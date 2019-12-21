#ifndef CONTROLS_H
#define CONTROLS_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define KEY 12345
#endif

union semun {
	Int val;		// Value for SETVAL
	Struct semid_ds *buf;		//Buffer for IPC_STAT, IPC_SET
	Unsigned short *array;	//Array for GETALL, SETALL
	Struct seminfo *__buf;	//Buffer for IPC_INFO (Linux-specific)
};

int control(char ** flag);
int write();
