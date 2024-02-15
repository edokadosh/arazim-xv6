#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p1[2], p2[2];
    char buf;
    pipe(p1);
    pipe(p2);
    int pid = fork();
    if(pid > 0){
        
        read(p1[0], &buf, 1);
        printf("%d: received ping\n", pid);
        write(p2[1], "a", 1);
    } else if(pid == 0){
        write(p1[1], "a", 1);
        read(p2[0], &buf, 1);
        sleep(1);
        printf("%d: received pong\n", pid);
    } else {
        printf("fork error\n");
    }
    exit(0);
}
