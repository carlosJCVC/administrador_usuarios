/*
* Ejemplo uso de la estructura passwd
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <pwd.h>

#define PASSWD_FILE "/etc/passwd"
#define TMPNAME "/etc/passwd.new"


int main()
{
    char usuario[80];
    char usrsys[80];
    char nuevoShell[80];
    int nuevogid;
    FILE *tmpf;
    struct passwd *pwd;        

    strcpy(usuario, "grover");    
    strcpy(nuevoShell, "/bin/sh");
    nuevogid = 1000;

   if (!(tmpf = fopen(TMPNAME, "w+"))) {
    		    perror("fopen()");
    		    return 1;
	}
    setpwent();
   
    while (pwd = getpwent())
    {
	strcpy(usrsys,pwd->pw_name);
	if (strcmp(usrsys, usuario))
	{
	    //recorrer
	    //printf("\nUsuario Sys: %s",usrsys);
	    //printf("  Buscando: %s", usuario);
	}
	else {
	
	    printf("\nUsuario: %s",usrsys);
	    printf(" UID: ");
	    printf("%d", pwd->pw_uid);
	    printf(" GID: ");
	    printf("%d", pwd->pw_gid);
	    printf(" SHELL: ");
	    printf("%s", pwd->pw_shell);
	    
	    //Cambiar Shell
	    pwd->pw_shell = nuevoShell;
	    pwd->pw_gid = nuevogid;
	        	    
	}
	putpwent(pwd, tmpf);
    }    
    
    endpwent();
    fclose(tmpf);
    printf("\n");
    return 0;
}
