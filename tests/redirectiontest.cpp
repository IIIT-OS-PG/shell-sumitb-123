#include<iostream>
#include<string>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#define ds 10
#define ml 1024

using namespace std;

void redirection(char *arr[],int rflag, int pflag){
	
		int len = 0,i=0;
		while(arr[i]){
			len++;
			i++;
		}
		if(pflag == 0){
			char bfr[ml];
			int fdr,fdw;

			if(!strcmp(arr[len-2],">>")) rflag = 1;
			else if(!strcmp(arr[len-2],">"))	rflag = 2;

			close(1);
			dup2(1,fdr);
			arr[len-2] = NULL;
			execvp(arr[0],arr);
			if(rflag == 1){
			fdw = open(arr[len-1],O_WRONLY | O_APPEND);
			while(read(fdr,bfr,20)){
				write(fdw,bfr,20);
			}
			close(fdw);
			}
			if(rflag == 2){
			fdw = open(arr[len-1],O_WRONLY | O_CREAT);
			while(read(fdr,bfr,20)){
				write(fdw,bfr,20);
			}
			close(fdw);
			}
			
		}

}
