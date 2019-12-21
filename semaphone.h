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

int shmd = -1;
sem_t sem;

int control(char ** flag);
int write();
