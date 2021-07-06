#include <stdio.h>
#include <unistd.h>
int main(){
    int ret = fork();
    if (ret == 0){
        printf("prog: Child\n");
    }else{
        printf("prog: Parent %d\n", ret);
    }
}