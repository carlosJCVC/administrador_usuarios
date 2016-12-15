#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <regex.h> 
#include <dirent.h>

void cambiar( uid_t user , gid_t grupo , char archivo[] ) {
    int fd ;
    uid_t owner = user;
    gid_t group = grupo;
    if( ( fd = open( archivo , O_RDONLY ) ) < 0 ) {
		perror( "archivo" );
		exit( EXIT_FAILURE );
    }
   
   	if( ( fchown( fd , user , grupo ) ) < 0 ) {
		perror( "fchown" );
		exit( EXIT_FAILURE );
    }
}

/*
		[usuarios]
		root:x:0:0:root:/root:/bin/bash
		ubaldino:x:1000:100::/home/ubaldino:/bin/bash
		
			uid=1000(ubaldino)
			gid=100(users)
			grupos=100(users)
		
		http:x:33:33:http:/srv/http:/bin/false
		
		[grupos]
		root:x:0:root
		mail:x:12:
		audio:x:92:ubaldino,mpd
		users:x:100:ubaldino

	*/
int parsearUsuariosGrupos( int tipo  , char *gid ){
	regex_t retmp;
	regmatch_t mtmp;
	int res = -1;
	FILE *archivo;
	char linea[100];
	int tamanio;
	char uidUsuario[128];
	char uidGrupo[128];
	char lineaUsuario[100];
	
	char patron1[128]="\0";
	char patron2[128]="\0";
	char aux[128]="\0";
	bool band=true; //pocoya

	
	
	//  busca (id) de usuario
	if ( tipo == 1 ) {

		sprintf( patron1 , "%s.*" ,  gid );
		archivo = fopen( "/etc/passwd" , "r" );
		bool band = true;
		while ( fgets( linea , 100 , archivo ) != NULL  &&  band==true ) {
			// compara patron
			res = regcomp( &retmp , patron1 , REG_EXTENDED ) ;
			res = regexec( &retmp , linea , (size_t) 1 , &mtmp , 0 );
			if ( res == 0 ) {
				strncpy( lineaUsuario , linea+mtmp.rm_so , mtmp.rm_eo-mtmp.rm_so );
				band = false;
			}
		}

		sprintf( patron2 , "x:[0-9]+" );
		res = regcomp( &retmp , patron2 , REG_EXTENDED ) ;
		res = regexec( &retmp , lineaUsuario , (size_t) 1 , &mtmp , 0 );
		if ( res == 0 ) {
			strncpy( uidUsuario , lineaUsuario+mtmp.rm_so , mtmp.rm_eo-mtmp.rm_so );
		}

		res = regcomp( &retmp , "[0-9]+" , REG_EXTENDED ) ;
		res = regexec( &retmp , uidUsuario , (size_t) 1 , &mtmp , 0 );
		if ( res == 0 ) {
			strncpy( aux , uidUsuario+mtmp.rm_so , mtmp.rm_eo-mtmp.rm_so );
		}

		res = atoi( aux ); 	
		
	}

	if ( tipo == 2 ) {

		sprintf( patron1 , "%s.*" ,  gid );
		archivo = fopen( "/etc/group" , "r" );
		bool band = true;
		while ( fgets( linea , 100 , archivo ) != NULL && band == true) {
			// compara patron
			res = regcomp( &retmp , patron1 , REG_EXTENDED ) ;
			res = regexec( &retmp , linea , (size_t) 1 , &mtmp , 0 );
			if ( res == 0 ) {
				strncpy( lineaUsuario , linea+mtmp.rm_so , mtmp.rm_eo-mtmp.rm_so );
				band = false;
			}
		}

		sprintf( patron2 , "x:[0-9]+" );
		res = regcomp( &retmp , patron2 , REG_EXTENDED ) ;
		res = regexec( &retmp , lineaUsuario , (size_t) 1 , &mtmp , 0 );
		if ( res == 0 ) {
			strncpy( uidGrupo , lineaUsuario+mtmp.rm_so , mtmp.rm_eo-mtmp.rm_so );
		}

		res = regcomp( &retmp , "[10-9]+" , REG_EXTENDED ) ;
		res = regexec( &retmp , uidGrupo , (size_t) 1 , &mtmp , 0 );
		if ( res == 0 ) {
			strncpy( aux , uidGrupo+mtmp.rm_so , mtmp.rm_eo-mtmp.rm_so );
		}

		res = atoi( aux ); 	
	}

	return res;
}



int main( int argc , char *argv[] ){

    int file = 0;
	
	if( argc < 2 ) {
		printf( "ingrese argumentos \n" );
        return 1;
	}



	if ( argc == 2 && strcmp( argv[1] , "--ayuda" ) == 0 ) {
		printf( "Texto ayuda \n" );
	}



	/*
		./cambiar –u user01 –g red archivo   (5)
		./cambiar –u 1002 –g 100 archivo (5)
		./cambiar –u usr01 –g red *   (5)
	*/
	
	//  archivo unico
	if ( argc == 6 && strcmp( argv[5] , "*" ) != 0 ) {

		if ( strcmp( argv[1] , "-u" ) == 0 &&  strcmp( argv[3] , "-g" ) == 0 ) {
			//printf( "./cambiar –u user01 –g red archivo \n" );
			//printf( "./cambiar –u 1002 –g 100 archivo \n" );
			int usuario = parsearUsuariosGrupos( 1 , argv[2] );	
			int grupo 	= parsearUsuariosGrupos( 2 , argv[4] );	
		 
			cambiar( usuario , grupo , argv[5] );
		}

	}

	//  todos los archivos
	if( argc == 6 && strcmp( argv[5] , "*" ) == 0 ){
		int usuario = parsearUsuariosGrupos( 1 , argv[2] );	
		int grupo 	= parsearUsuariosGrupos( 2 , argv[4] );	


		


		DIR *d;
		struct dirent *dir;
		d = opendir(".");
		if ( d ) {
			while ( ( dir = readdir( d ) ) != NULL ) {
				if ( strcmp( dir->d_name , ".." ) != 0 && strcmp( dir->d_name , "." ) != 0 ) {
					cambiar( usuario , grupo , dir->d_name );
				}
			}

			closedir(d);
		}

		return 0;


		//printf( "./cambiar –u usr01 –g red * \n" );
	}




	/*
		./cambiar –u 1002 archivo       (3)
		./cambiar –u user02 archivo     (3)
		---------------------------------------
		./cambiar –g red archivo    (3)
		./cambiar –g 100 archivo    (3)
	*/
	if ( argc == 4 ) {
		if ( ( strcmp( argv[1] , "-u" ) ) == 0 ) {
			int usuario = parsearUsuariosGrupos( 1 , argv[2] );	
			//int grupo 	= parsearUsuariosGrupos( 2 , argv[2] );	
			//   uid_t user , gid_t grupo , char archivo[] 

			if( ( file = open( argv[3] , O_RDONLY ) ) < -1 )
            	return 1;
 
		    struct stat fileStat;
		    if( fstat( file , &fileStat) < 0 )    
		        return 1;
		 
			cambiar( usuario , fileStat.st_gid , argv[3] );
			
		}

		if ( strcmp( argv[1] , "-g" ) == 0 ) {
			//printf( "./cambiar –g red archivo \n" );
			//printf( "./cambiar –g 100 archivo \n" );

			int grupo 	= parsearUsuariosGrupos( 2 , argv[2] );	
			//   uid_t user , gid_t grupo , char archivo[]
			if( ( file = open( argv[3] , O_RDONLY ) ) < -1 )
            	return 1;
 
		    struct stat fileStat;
		    if( fstat( file , &fileStat) < 0 )    
		        return 1;
		 
			cambiar( fileStat.st_uid , grupo , argv[3] );
			
		}
	}

	return 0;
}
