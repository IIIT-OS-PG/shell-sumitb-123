#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
#define _GNU_SOURCE
using namespace std;

int main(){

	char *st[6];//,*tt[3];
	st[0] = "ls";
	st[1] = "-ltr";
	st[2] = NULL;
	st[3] = "wc";
	st[4] = "-l";
	st[5] = NULL;
	int fd[2];
	pipe(fd);
	int pid = fork();
	if(pid){
		wait(&pid);
		close(fd[1]);
		dup2(fd[0],0);
		execvp(st[3],st+3);
		close(fd[0]);

	}
	else{
		close(fd[0]);
		dup2(fd[1],1);
		close(fd[1]);
		execvp(st[0],st);
		exit(0);
	
	}


}
