#include "semaphone.h"

int main() {
  int shmd, semd;
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1;
  printf("trying to get in...\n");
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
  int fd = open("story.txt", O_RDWR, 0666);
  char * data = shmat(shmd, 0, 0);
  printf("Last addition: %s\n\n", data);
  char input[1024];
  printf("Your addition: ");
  fgets(input, sizeof(input) - 1, stdin);
  int w = write(fd, input, sizeof(input));
  if (w < 0) {
    printf("ERROR: %d, error message: %s", errno, strerror(errno));
    return errno;
  }
  strcpy(data, input);
  shmdt(data);
  semop(semd, &sb, 1);
  sb.sem_op = 1;
  return 0;
}
