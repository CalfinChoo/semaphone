#include "semaphone.h"

int main(int argc, char *argv[]) {
  if (arg == 1) {
    printf("ERROR: You need to include a flag.");
    return 0;
  }
  else return control(argv[1]);
}

int control(char ** flag) {
  if (strcmp(flag, "-c") == 0) {
    shmd = shmget(KEY, sizeof(char), IPC_CREAT | 0640);
    sem_init(&sem, 1, 1);
    FILE * f = fopen("story.txt", "r");
    fclose(f);
  }
  else if (strcmp(flag, "-r") == 0) {
    sem_wait(&sem);
    char * data;
    int fd = open("story.txt", O_RDWR, 0666);
    int r = read(fd, data, sizeof(data));
    printf("The story so far:\n %s", data);
    shmd = -1;
    sem_destroy(&sem);
  }
  else if (strcmp(flag, "-v") == 0) {
    char * data;
    int fd = open("story.txt", O_RDWR, 0666);
    int r = read(fd, data, sizeof(data));
    printf("The story so far:\n %s", data);
  }
  return 0;
}
