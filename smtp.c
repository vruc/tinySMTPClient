#include "smtp.h"
#include "base64.h"


int print_help(void){
	printf("How to use it:\n");
	printf("    smtp host [port]\n");
	printf("    the default port is 25\n");
	return 0;
}
int connect2server(int *socket_p,char *host,char *port){
	char response[BUFSIZ] = "";
	struct addrinfo hint = {0},*res = NULL;
	int function_flag = -1;

	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	function_flag = getaddrinfo(host,"smtp",&hint,&res);
	if (function_flag != 0){
		return -1;
	}else{
		struct addrinfo *temp = res;
		while (temp){
			*socket_p = socket(temp->ai_family,SOCK_STREAM,temp->ai_protocol);
			if (*socket_p == -1){
				temp = temp->ai_next;
			}else{
				break;
			}
		}
		function_flag = connect(*socket_p,temp->ai_addr,temp->ai_addrlen);
		get_response(*socket_p,response,BUFSIZ);
		printf("%s\n",response);
		freeaddrinfo(res);
		return function_flag;
	}
}
int hello(int socket,char *hostname){
	char message[108] = "HELO ";
	strcat(message,hostname);
	client_send(socket,message);
	get_response(socket,message,108);
	printf("%s",message);
	return 0;
}
int authenticate(int socket,char *username,char *password){
	char username_encode[512] = "";
	char password_encode[512] = "";
	char response[BUFSIZ] = "";

	base64_encode(username,username_encode);
	base64_encode(password,password_encode);

	client_send(socket,"AUTH LOGIN");
	get_response(socket,response,BUFSIZ);
	client_send(socket,username_encode);
	get_response(socket,response,BUFSIZ);
	printf("%s\n",response);
	if (response[0] == '4'||
		response[0] == '5'){
		perror("Account Deny!");
		return -1;
	}

	client_send(socket,password_encode);
	get_response(socket,response,BUFSIZ);
	printf("%s",response);
	if (response[0] == '4'||
		response[0] == '5'){
		perror("Password Wrong!");
		return -1;
	}
	return 0;
}
int send_email(int socket,char *from,char *address,char *subject,char *content){
	char message[BUFSIZ] = "";
	char *content_encode = NULL;

	strcpy(message,"MAIL FROM: <");
	strcat(message,from);
	strcat(message,">");
	client_send(socket,message);
	get_response(socket,message,BUFSIZ);
	printf("%s\n",message);

	strcpy(message,"RCPT TO: <");
	strcat(message,address);
	strcat(message,">");
	client_send(socket,message);
	get_response(socket,message,BUFSIZ);
	printf("%s\n",message);

	client_send(socket,"DATA");
	get_response(socket,message,BUFSIZ);
	printf("%s\n",message);

	strcpy(message,"From: ");
	strcat(message,from);
	client_send(socket,message);

	strcpy(message,"To: ");
	strcat(message,address);
	client_send(socket,message);

	strcpy(message,"Subject:");
	strcat(message,subject);
	client_send(socket,message);

	client_send(socket,"MIME-Version:1.0");
	
	client_send(socket,"Content-Type:multipart/alternative;");
	client_send(socket,"boundary=----=smtp_demo");
	client_send(socket,"\r\n----=smtp_demo");


	client_send(socket,"Content-Type:text/plain;charset=utf-8");
	client_send(socket,"Content-Transfer-Encoding: 8bit\r\n");
	client_send(socket,content);
	client_send(socket,"\r\n----=smtp_demo");

	client_send(socket,"Content-Type:text/html;charset=utf-8");
	client_send(socket,"Content-Transfer-Encoding: 8bit\r\n");
	client_send(socket,content);
	client_send(socket,"\r\n----=smtp_demo");
	client_send(socket,".");
	memset(message,0,BUFSIZ);
	get_response(socket,message,BUFSIZ);
	printf("%s\n",message);
}

int client_send(int socket,char *message){
	char buff[512] = {'\0'};
	strcpy(buff,message);
	strcat(buff,"\r\n");
	printf("%s",buff);
	return write(socket,buff,strlen(buff));
}
int get_response(int socket,char *response,int response_length){
	int read_size = read(socket,response,response_length);
	if (read_size == -1){
		return -1;
	}else{
		response[read_size] = '\0';
		return 0;
	}
}
