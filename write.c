#include "semaphone.h"

int writ();
int shmd, semd;
struct sembuf sb;


int main() {
  sb.sem_num = 0;
  sb.sem_op = -1;
  printf("trying to get in...\n");
  writ();
  return 0;
}

int writ() {
  semd = semget(KEY, 1, 0);
  semop(semd, &sb, 1);
  shmd = shmget(KEY, sizeof(char *), 0);
  int fd = open("story.txt", O_RDWR, 0666);
  char * data = shmat(shmd, 0, 0);
  printf("Last addition: %s\n\n", data);
  char input[1024];
  printf("Your addition: ");
  fgets(input, sizeof(input) - 1, stdin);
  int w = write(fd, input, sizeof(input));
  if (w < 0) {
    printf("WRITE errno: %d, error message: %s", errno, strerror(errno));
    return errno;
  }
  strcpy(data, input);
  shmdt(data);
  semop(semd, &sb, 1);
  sb.sem_op = 1;
  return 0;
}
