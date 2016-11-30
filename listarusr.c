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

int main()
{

    char usrsys[80];
    struct passwd *pwd;        

    setpwent();
   
    while (pwd = getpwent())
    {
	// Mostrar datos de usuario
	strcpy(usrsys,pwd->pw_name);
	printf("\nUsuario: %s",usrsys);
	printf(" UID: ");
	printf("%d", pwd->pw_uid);
	printf(" GID: ");
	printf("%d", pwd->pw_gid);
	printf(" SHELL: ");
	printf("%s", pwd->pw_shell);
	        	    
    }    
    
    endpwent();
    printf("\n");
    return 0;
}
