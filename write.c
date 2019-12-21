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
  FILE * f = fopen("story", "a");
  char * data = shmat(shmd, 0, 0);
  printf("Last addition: %s\n\n", data);
  char input[SIZE];
  printf("Your addition: ");
  fgets(input, sizeof(input), stdin);
  for (int i = 0; i < sizeof(input); i++) {
    if (input[i] == '\n') {
      input[i] = '\0';
      break;
    }
  }
  fprintf(f, "%s\n", input);
  fclose(f);
  strcpy(data, input);
 if(shmdt(data) < 0){
    printf("ERROR! Couldn't detatch shared memory segment: %s\n", strerror(errno));
    return 1;
  }
  sb.sem_op = 1;
  semop(semd, &sb, 1);
  return 0;
}
