#include <stdio.h>
#include <unistd.h>
int main(){
    int ret = fork();
    if (ret == 0){
        printf("Child\n");
    }else{
        printf("Parent\n");
    }
}