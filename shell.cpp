#include<iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define argl 1024
#define cmdl 100
#define mx 100

using namespace std;

void showPrompt(){
	char hostname[mx];
	cout<<getenv("USER")<<"@";
	gethostname(hostname,mx);
	cout<<hostname<<"$ ";
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
		if(rflag == 1){
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
