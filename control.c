#include "semaphone.h"

int shmd, semd;
union semun su;
struct sembuf sb;
int control(char * flag);

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
    shmd = shmget(KEY, sizeof(char *), IPC_CREAT | 0644);
    if(shmd < 0){
     printf("ERROR2: %s\n", strerror(errno));
     return 1;
    }
    printf("shared memory created\n");
    FILE * f = fopen("story", "w");
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
    shmd = shmget(KEY, sizeof(char *), 0);
    if(shmd < 0){
     printf("ERROR2: %s\n", strerror(errno));
     return 1;
    }
    char data[SIZE];
    FILE * f = fopen("story", "r");
    if (f == NULL){
        printf("ERROR: Story does not exist.\n");
        return 1;
    }
    printf("The story so far:\n");
    while (fgets(data, SIZE, f) != NULL) printf("%s", data);
    fclose(f);
    shmctl(shmd, IPC_RMID, 0);
    semctl(semd, IPC_RMID, 0);
    remove("story");
  }
  else if (strcmp(flag, "-v") == 0) {
    char data[SIZE];
    FILE * f = fopen("story", "r");
    if (f == NULL){
        printf("ERROR: Story does not exist.\n");
        return 1;
    }
    printf("The story so far:\n");
    while (fgets(data, SIZE, f) != NULL) printf("%s", data);
    fclose(f);
  }
  return 0;
}
