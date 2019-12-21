#include "semaphone.h"

int main() {
  printf("trying to get in...\n");
  write();
  return 0;
}

int write() {
  sem_wait(&sem);
  char * data = shmat(shmd, 0, 0);
  // char previous[1024];
  int fd = open("story.txt", O_RDWR, 0666);
  int r = read(fd, data, sizeof(data));
  if (r < 0) {
    printf("READ errno: %d, error message: %s", errno, strerror(errno));
    return errno;
  }
  printf("Last addition: %s\n\n", previous);
  // char input[1024];
  printf("Your addition: ");
  fgets(input, sizeof(input) - 1, stdin);
  int w = write(fd, input, sizeof(input));
  if (w < 0) {
    printf("WRITE errno: %d, error message: %s", errno, strerror(errno));
    return errno;
  }
  r = read(fd, data, sizeof(data));
  if (r < 0) {
    printf("READ errno: %d, error message: %s", errno, strerror(errno));
    return errno;
  }
  shmdt(data);
  shmctl(shmd, IPC_RMID, 0);
  sem_post(&sem);
  return 0;
}
