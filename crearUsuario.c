#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1024


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <pwd.h>

void separar(char *cadena, char *linea, char separador)
{
    int x, y;				//separa datos 
    
    x = 0; y = 0;
    
    while ((linea[x]) && (linea[x] != separador))
    {
	cadena[x] = linea[x];
	x = x + 1;
    }
    cadena[x] = '\0';
    if (linea[x]) ++x;
    
    y = 0;
    
    while (linea[y] = linea[x])
    {
	linea[y] = linea[x];
	y++;
	x++;
    }

}

int main(void)
{
    setuid(0);
    setgid(0);
    int israel = getuid();
    char *lenstr;
    char inputBuffer[MAXLEN];
    int contentLength;
    int i;
    char x;
    char mensaje[80];
    char usuario[80];
    char clave[80];
    char shell[80];
    char shell1[80];
    char shell11[80];
    char shell2[80];
    char shell21[80]="BY IOAN";
    char res[80];
    char respass[80];
    char ruta[80] = "useradd ";
    char m[80] = " -m ";
    char echo[80]="echo -e ";
    char pipe[80]="| passwd ";
    char resdos[80];

    printf ("Content-type:text/html\n\n");
    printf("<html><TITLE>Response</TITLE>\n");
    printf("<body>\n");
    lenstr = getenv("CONTENT_LENGTH");
    if (lenstr!= NULL)
    {
	contentLength = atoi(lenstr);   
    }
    else contentLength = 0;

    printf("Content Length: %d", contentLength,"<br>");
    i = 0;

    while (i < contentLength){

	x = fgetc(stdin);
	if (x==EOF) break;
	inputBuffer[i] = x;
	i++;
    }

    inputBuffer[i] = '\0';
    contentLength = i;
    
    
    printf("<br>FORMULARIO CON DATOS: %s\n", inputBuffer);
    printf("<br>TAMANIO: %d\n",contentLength);

    separar(usuario, inputBuffer, '=');
    separar(usuario, inputBuffer, '&');
    separar(clave, inputBuffer, '=');
    separar(clave, inputBuffer, '&');
    separar(shell, inputBuffer, '=');
    separar(shell, inputBuffer, '&');
//    separar(shell11, shell1, '2');
//    separar(shell2, shell1, '%');
//    separar(shell21, shell2, '2');
//    reemplazar(shell21,shell, '%', '2');

    sprintf(res,"%s %s %s",ruta, m, usuario);
    printf("\n<p> PROBANDO:%s",shell1);
    sprintf(respass,"/bin/echo -e \"%s\\n%s\" | passwd %s",clave,clave,usuario);
    printf("\n<p> MENSAJE PASSWORD: %s ",respass);
    printf("\n<p> OTRO MENSAJE: %s ",ruta);
    printf("\n<p> USUARIO %s", usuario);
    printf("\n<p> CLAVE: %s",clave);
    printf("\n<p> SHELL: %s",shell);
    printf("\n</body></html>");
    system(res);
    system(respass);
    return 0;
}



