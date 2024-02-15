#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXLINE 30

void fork_and_exec(char** _argv){
  int pid = fork();
  if(pid > 0){
    pid = wait((int *) 0);
  }else if (pid==0){
    exec(_argv[0], _argv);
    printf("exec failed\n");
    exit(0);
  } else {
    printf("fork error\n");
  }
}

int
main(int argc, char *argv[])
{
  char line[MAXLINE] = {0};
  char* _argv[MAXARG] = {0};
  int l = 0;
  if (argc < 2){
    printf("not enough arguments\n");
    exit(0);
  }

  for (int i = 0 ; i < argc-1 ; i++){
    _argv[i] = argv[i+1];
  }
  _argv[argc-1] = line;

  while(read(0, &line[l], 1) > 0) {
    l++;
    if (line[l-1] == '\n') {
      line[l-1] = 0;
      fork_and_exec(_argv);

      l = 0;
      memset(line, 0, sizeof(line));
    }
  }
  if (line[0]) {
      fork_and_exec(_argv);
  }

  exit(0);
}
