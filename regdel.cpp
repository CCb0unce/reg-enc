#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
    system("regedit /s delete.reg" );
    return 0;
}
