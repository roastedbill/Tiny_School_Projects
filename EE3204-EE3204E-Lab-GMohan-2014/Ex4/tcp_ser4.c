/**********************************
tcp_ser.c: the source file of the server in tcp transmission 
***********************************/


#include "headsock.h"

#define BACKLOG 10

void str_ser(int sockfd, int error_percentage);                                                        // transmitting and receiving function

int main(int argc, char **argv)
{
	int sockfd, con_fd, ret;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;
    int error_percentage;

//	char *buf;
	pid_t pid;
    
    if (argc != 2) {
        printf("Pleas input an Error Percentage following function name!\n");
        exit(1);
    }
    
    error_percentage = atoi(argv[1]);
    
    if (error_percentage > 99 || error_percentage < 0) {
        printf("The range of error percentage varies between 0 to 99! Please give a reasonable value!\n");
        exit(1);
    }
    

	sockfd = socket(AF_INET, SOCK_STREAM, 0);          //create socket
	if (sockfd <0)
	{
		printf("error in socket!");
		exit(1);
	}
	
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYTCP_PORT);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("172.0.0.1");
	bzero(&(my_addr.sin_zero), 8);
	ret = bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr));                //bind socket
	if (ret <0)
	{
		printf("error in binding");
		exit(1);
	}
	
	ret = listen(sockfd, BACKLOG);                              //listen
	if (ret <0) {
		printf("error in listening");
		exit(1);
	}

	while (1)
	{
		printf("waiting for data\n");
		sin_size = sizeof (struct sockaddr_in);
		con_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);            //accept the packet
		if (con_fd <0)
		{
			printf("error in accept\n");
			exit(1);
		}

		if ((pid = fork())==0)                                         // creat acception process
		{
			close(sockfd);
			str_ser(con_fd, error_percentage);                                          //receive packet and response
			close(con_fd);
			exit(0);
		}
		else close(con_fd);                                         //parent process
	}
	close(sockfd);
	exit(0);
}

void str_ser(int sockfd, int error_percentage)
{
	char buf[BUFSIZE];
	FILE *fp;
	char recvs[DATALEN];
	struct ack_so ack;
	int end = 0, n = 0;
	long lseek=0;
    int received = 0;
    uint8_t package_index = 1;
	
	printf("receiving data!\n");

	while(!end)
	{
		if ((n= recv(sockfd, &recvs, DATALEN, 0))==-1)                                   //receive the packet
		{
			printf("error when receiving\n");
			exit(1);
		}
		if (recvs[n-1] == '\0')								//if it is the end of the file
		{
			end = 1;
			n --;
		}
		memcpy((buf+lseek), recvs, n);
        if ((package_index%101) <= error_percentage) {
            ack.num = 0;
            ack.len = 0;
        } else {
            lseek += n;
            ack.num = package_index;
            ack.len = 0;
        }
        if ((received = send(sockfd, &ack, 2, 0)) == -1) {
            printf("send error!");
            exit(1);
        }
        
        if(package_index == 255)
            package_index = 1;
        else
            package_index++;
	}

	if ((fp = fopen ("myTCPreceive.txt","wt")) == NULL)
	{
		printf("File doesn't exit\n");
		exit(1);
	}
	fwrite (buf , 1 , lseek , fp);					//write data into file
	fclose(fp);
	printf("a file has been successfully received!\nthe total data received is %d bytes\n", (int)lseek);
}
