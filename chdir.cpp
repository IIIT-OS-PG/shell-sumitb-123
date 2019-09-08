#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include "header.h"
#define argl 1024
#define cmdl 100
#define mx 100
#define ml 1024

extern char cdpath[];
using namespace std;

void changeDirectory(char *st[]){
	size_t sz = mx;
	char *bfr = (char *)malloc(mx*sizeof(char));
	if(st[1] == NULL || !strcmp(st[1],"~")){
		char *path=(char *)malloc(mx*sizeof(char));
		strcpy(path,getenv("HOME"));
		strcpy(cdpath,getcwd(bfr,sz));
		chdir(path);
		setenv("PWD",path,1);
		free(path);
	}
	else if(!strcmp(st[1],"-")){
		char *path=(char *)malloc(mx*sizeof(char));
		strcpy(path,getcwd(bfr,sz));
		chdir(cdpath);
		setenv("PWD",cdpath,1);
		strcpy(cdpath,path);
		free(path);
	}
	else{
		strcpy(cdpath,getcwd(bfr,sz));
		chdir(st[1]);
		setenv("PWD",st[1],1);
	}
	free(bfr);
}

