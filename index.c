#include <stdio.h>
#include <string.h>

header(char *MIME_Type)
{
	printf("Content-type:%s\n\n", MIME_Type);
	return 0;
}

main(int argc, char **argv) 
{
	header("text/html");
	const char *redirect_page_format =
		"<head>\n"
		"<meta http-equiv=\"REFRESH\"\n"
		"content=\"0;url=/cgi-bin/listFiles.cgi?dirname=/home\">\n"
		"</head><body></body>\n"
		"</html>\n";
	printf(redirect_page_format);
}
