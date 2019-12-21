#include "semaphone.h"

int shmd, semd;
union semun su;
struct sembuf sb;

int main(int argc, char *argv[]) {
  su.val = 1;
  sb.sem_num = 0;
  sb.sem_op = -1;
  if (argc == 1) {
    printf("ERROR: You need to include a flag.\n");
    return 0;
  }
  else control(argv[1]);
  return 0;
}

int control(char * flag) {
  if (strcmp(flag, "-c") == 0) {
    semd = semget(KEY, 1, IPC_CREAT | 0644);
    if(semd < 0){
     printf("ERROR1: %s\n", strerror(errno));
     return 1;
    }
    printf("semaphore created\n");
    semctl(semd, 0, SETVAL, su);
    shmd = shmget(KEY, SIZE, IPC_CREAT | 0644);
    if(shmd < 0){
     printf("ERROR2: %s\n", strerror(errno));
     return 1;
    }
    printf("shared memory created\n");
    FILE * f = fopen("story.txt", "w");
    printf("file created\n");
    fclose(f);
  }
  else if (strcmp(flag, "-r") == 0) {
    semd = semget(KEY, 1, 0);
    if(semd < 0){
     printf("ERROR1: %s\n", strerror(errno));
     return 1;
    }
    semop(semd, &sb, 1);
    shmd = shmget(KEY, SIZE, 0);
    if(shmd < 0){
     printf("ERROR2: %s\n", strerror(errno));
     return 1;
    }
    char * data = calloc(1000, sizeof(char));
    int fd = open("story.txt", O_RDWR, 0666);
    int r = read(fd, data, sizeof(data));
    printf("The story so far:\n %s", data);
    shmctl(shmd, IPC_RMID, 0);
    semctl(semd, IPC_RMID, 0);
    remove("story.txt");
  }
  else if (strcmp(flag, "-v") == 0) {
    char * data = calloc(1000, sizeof(char));
    int fd = open("story.txt", O_RDONLY, 0666);
    int r = read(fd, data, sizeof(data));
    printf("The story so far:\n%s", data);
    free(data);
  }
  return 0;
}
