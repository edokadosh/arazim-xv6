#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    unsigned char buf;
    unsigned char prime;
    int p1[2], p2[2]; //reading from p1 writing to p2
    pipe(p2);
    int pid = fork();
    if(pid > 0){
    process:
        p1[0] = p2[0];
        p1[1] = p2[1];
        read(p1[0], &buf, 1);
        if (buf == 0) {
            exit(0);
        }
        prime = buf;
        printf("prime %d\n", prime);
        pipe(p2);
        int pid = fork();
        if(pid > 0){
            goto process;
        } else if(pid == 0){
            while (buf != 0) {
                read(p1[0], &buf, 1);
                if (buf%prime != 0) {
                    write(p2[1], &buf, 1);
                }
            }
            close(p1[0]);
            write(p2[1], &buf, 1);
            close(p2[1]);
        } else {
            printf("fork error\n");
        }
    } else if(pid == 0){
        for (int i = 2 ; i <= 35 ; i++) {
            buf = (char)i;
            write(p2[1], &buf, 1);
        }
        buf = (char)0;
        write(p2[1], &buf, 1);
        close(p2[1]);
    } else {
        printf("fork error\n");
    }
    exit(0);
}