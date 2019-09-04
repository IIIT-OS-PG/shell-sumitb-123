#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
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
			if(rflag == 1){
            fdw = open(arr[len-1],O_WRONLY | O_CREAT | O_APPEND);
            /*while(read(fdr,bfr,20)){
                write(fdw,bfr,20);
            }*/
            //close(fdw);
            }
            if(rflag == 2){
            fdw = open(arr[len-1],O_WRONLY | O_CREAT);
            /*while(read(fdr,bfr,20)){
                write(fdw,bfr,20);
            }*/
            //close(fdw);
            }
			//close(1);
			dup2(fdw,1);
			arr[len-2] = NULL;
			execvp(arr[0],arr);
			/*if(rflag == 1){
			fdw = open(arr[len-1],O_WRONLY | O_CREAT | O_APPEND);
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
			}*/
			
		}

}


int main(){
	int i;
	while(1){
		i=0;	
		showPrompt();
		char *st[argl];
		int rflag = 0,pflag = 0;
		char c;// = getchar();
		string temp = "";
		struct termios termios_p;
		//int rtv = tcgetattr(0, termios_p);
		//cout<<rtv<<endl;
		do{ 
			c = getchar();

			if(c != ' ' && c != '\t' && c != '\n'){
				temp+=string(1,c);	
				//cout<<temp<<endl;
			}
			else if(c == ' '){
				//cout<<"space handle"<<endl;	
				char *cmd = (char *)malloc(temp.length()*sizeof(char));
				strcpy(cmd,temp.c_str());
				st[i] = cmd;
				//printf("%s \n",st[i]);
				temp = "";
				i++;
			}
			else if(c == '\n'){
				//cout<<"new line handle"<<endl;	
				if(temp.length() != 0){
					char *cmd = (char *)malloc(temp.length()*sizeof(char));
            	    strcpy(cmd,temp.c_str());
            	    st[i] = cmd;
				    //printf("%s \n",st[i]);
            	    temp = "";
            	    i++;
				}	
				break;
			}

			if(c == '>'){
				rflag = 1;
			}
			if(c == '|'){
				pflag = 1;
			}
		
		}while(1);

		if(i>0){
		
		st[i]=NULL;
		i = 0;
		while(st[i]) printf("%s ",st[i++]);
		cout<<endl;
		int pid = fork();
		if(pid){
			int wc = wait(&pid);
	    }
	    else{
			if(rflag == 1 && pflag == 1){
			}
			else if(rflag == 0 && pflag == 1){
			}
			else if(rflag == 1 && pflag == 0){
				redirection(st,rflag,pflag);
			}
			else{
	        	execvp(st[0],st);
				exit(0);
			}
	    }
		}
	}

}
