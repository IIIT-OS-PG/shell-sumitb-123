#include<iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#define argl 1024
#define cmdl 100
#define mx 100
#define ml 1024


using namespace std;

void showPrompt(){
	char hostname[mx];
	cout<<getenv("USER")<<"@";
	gethostname(hostname,mx);
	cout<<hostname<<"$ ";
}

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


int main(){
	int i;
	while(1){
		i=0;	
		showPrompt();
		char *st[argl];
		char *cmd;
		char nc;
		int rflag = 0;

		do{
			cmd = new char[cmdl];
		    cin>>cmd;
			st[i]=cmd;

			/*if(!strcmp(cmd,"cat") || !strcmp(cmd,"echo") || !strcmp(cmd,"cd") || !strcmp(cmd,"grep")){
				
			}	
			if(!strcmp(st[i],">>")) rflag = 1;
			else if(!strcmp(st[i],">")) rflag = 2;*/

			if(getchar() == '\n') break;
			i++;

		}while(1);

		st[++i]=NULL;	
	int pid = fork();
	if(pid){
		int wc = wait(&pid);
    }
    else{
		if(rflag == 0 && pflag == 1){
			cout<<""<<endl;	
		}
		else if(rflag == 2){
			cout<<""<<endl;
		}
		else{
        		execvp(st[0],st);
				exit(0);
		}
    }
	delete cmd;
	}

}
