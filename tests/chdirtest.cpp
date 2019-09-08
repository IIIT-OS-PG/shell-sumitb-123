#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
#define _GNU_SOURCE
using namespace std;

int main(){
	char *st[]={"cd","/home/sumit",NULL};
	int pid = fork();
	while(1){
	if(pid){
		wait(&pid);
	}
	else{
		cout<<chdir(st[1])<<endl;
		exit(0);	
	}
	}
}
