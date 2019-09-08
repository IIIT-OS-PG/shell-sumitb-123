#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include "header.h"

using namespace std;

void piping(char *st[], int rflag,int pflag){
	int i=0, index = 0,temp,count = 1,pid;
	//int fd[2],pid,fd1[2];
	//pipe(fd);
	while(st[i]){
	    //cout<<"pipe "<<endl;
		//pipe(fd1);
		int fd[2];
		pipe(fd);
		printf("%s ",st[i]);
		if(!strcmp(st[i],"|")){
			st[i] = NULL;
			pid = fork();
			if(pid){
				wait(&pid);
				close(fd[1]);
				dup2(fd[0],0);
			}
			else{
				//cout<<"child index "<<index<<endl;
				//printf("cmd at index %s ",st[index]);
				close(fd[0]);
				dup2(fd[1],1);
				close(fd[1]);
				//execvp(st[index],st+index);
				//execvp(cmd[0],cmd);
				execvp(st[index],st+index);
				_exit(0);
			}
			//cout<<"before updating "<<index<<endl;
			index = i+1;
			//cout<<"after updating "<<index<<endl;
		}
		i++;
	}
	//close(fd[1]);
    //dup2(fd[0],0);
	if(rflag == 1){
		redirection(st+index,rflag,pflag);
		_exit(0);
	}
	else{
    	execvp(st[index],st+index);
		_exit(0);
	}
}

