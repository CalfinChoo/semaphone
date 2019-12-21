#include "semaphone.h"

int main(int argc, char *argv[]) {
  int shmd, semd;
  union semun su;
  struct sembuf sb;
  su.val = 1;
  sb.sem_num = 0;
  sb.sem_op = -1;
  if (argc == 1) {
    printf("ERROR: You need to include a flag.\n");
    return 0;
  }
  char * flag = argv[1];
  if (strcmp(flag, "-c") == 0) {
    semd = semget(KEY, 1, IPC_CREAT | 0644);
    if(semd < 0){
     printf("ERROR: %s\n", strerror(errno));
     return 1;
    }
    printf("semaphore created\n");
    shmd = shmget(IPC_PRIVATE, sizeof(char *), IPC_CREAT | 0644);
    if(shmd < 0){
     printf("ERROR: %s\n", strerror(errno));
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
     printf("ERROR: %s\n", strerror(errno));
     return 1;
    }
    semop(semd, &sb, 1);
    shmd = shmget(KEY, sizeof(char *), 0);
    if(shmd < 0){
     printf("ERROR: %s\n", strerror(errno));
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
