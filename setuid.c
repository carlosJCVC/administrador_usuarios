#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(){

//Declaring variables
int Uid, Gid, iUid, iGid;

printf("Content-type: text/html\n\n");

//Usar setuid

Uid = getuid();
Gid = getgid();

printf("<br>UID: %d\n", Uid);
printf("<br>GID: %d\n", Gid);

// Cambiar uid and gid
if((setuid(0)) < 0) printf("<br>setuid: operation not permitted");
if((setgid(0)) < 0) printf("<br>setgid: operation not permitted");
iUid = getuid();
iGid = getgid();

printf("<br>Nuevo UID: %d\n", iUid);
printf("<br>Nuevo GID: %d\n", iGid);

system("fdisk -l 1>salida.txt 2>error.txt");
printf("<br><br>...Fdisk!!!\n");

}

