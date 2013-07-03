#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "smtp.h"

int main(int argc,char *argv[]){
	char *smtp_host = NULL;
	char  smtp_port[32] = {'\0'};
	int   socket = -1;

	char *username = "";//Your account
	char *password = "";//Your password

	char *address  = "";//Target e-mail address
	char *subject  = "SMTP Client Demo";
	char *content  = "this is a test from smtp client written in C!";

	switch(argc){
		case 1:
			print_help();
			return;
			break;
		case 2:
			smtp_host = argv[1];
			sprintf(smtp_port,"%s","25");
			break;
		case 3:
			smtp_host = argv[1];
			strcpy(smtp_port,argv[2]);
			break;
	}

	connect2server(&socket,smtp_host,smtp_port);//Connect to the SMTP server
	hello(socket,"localhost");//Say hello
	authenticate(socket,username,password);//Check your authentication
	send_email(socket,username,address,subject,content);//Send an e-mail.
	return 0;
}