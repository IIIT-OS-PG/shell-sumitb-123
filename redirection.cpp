#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include "header.h"
#define ds 10
#define argl 1024
#define cmdl 100
#define mx 100
#define ml 1024
using namespace std;

void redirection(char *arr[],int rflag, int pflag){

	int len = 0,i=0;
	char bfr[ml];
    int fdr,fdw;
	while(arr[i]){
		len++;
		i++;
	}
	if(pflag == 0){
		if(!strcmp(arr[len-2],">>")) rflag = 1;
		else if(!strcmp(arr[len-2],">"))	rflag = 2;
		if(rflag == 1){
        fdw = open(arr[len-1],O_WRONLY | O_CREAT | O_APPEND);
        }
        if(rflag == 2){
        fdw = open(arr[len-1],O_WRONLY | O_CREAT | O_TRUNC);
        }
		chmod(arr[len-1],S_IRUSR | S_IWUSR);
		dup2(fdw,1);
		arr[len-2] = NULL;
		//execvp(arr[0],arr);
		if(execvp(arr[0],arr)<0){
            cout<<"error: please check"<<endl;
        }
		close(fdw);
		
	}
	else if(pflag == 1){
        if(!strcmp(arr[len-2],">>")) rflag = 1;
        else if(!strcmp(arr[len-2],">"))    rflag = 2;
        if(rflag == 1){
        fdw = open(arr[len-1],O_WRONLY | O_CREAT | O_APPEND);
        }
        if(rflag == 2){
        fdw = open(arr[len-1],O_WRONLY | O_CREAT | O_TRUNC);
        }
        chmod(arr[len-1],S_IRUSR | S_IWUSR);
        dup2(fdw,1);
        arr[len-2] = NULL;
		//execvp(arr[0],arr);
        if(execvp(arr[0],arr)<0){
			cout<<"error: please check"<<endl;
		}
        close(fdw);
	}

}
