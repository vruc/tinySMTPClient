#ifndef __SMTP_H__
#define __SMTP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int print_help(void);
int connect2server(int *,char *,char *);
int hello(int,char *);
int authenticate(int,char *,char *);
int send_email(int ,char *,char *,char *,char *);



int client_send(int,char *);
int get_response(int,char *,int);

#endif