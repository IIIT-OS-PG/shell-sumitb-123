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
#define argl 1024
#define cmdl 100
#define mx 100
#define ml 1024
char cdpath[mx];
using namespace std;


/*void showPrompt(){
	char *cwd = (char *)malloc(mx*sizeof(char));
	char hostname[mx];
	cout<<getenv("USER")<<"@";
	gethostname(hostname,mx);
	cout<<hostname<<getcwd(cwd,mx)<<":~"<<getenv("PS1")<<"$ ";
}*/

int main(){
	int i,count=0;
	map<string,string> m;
	//setting the path for c - comand
	strcpy(cdpath,getenv("PWD"));
	//setitng the environment variables for my shell
	char* st[]={"myrc",NULL};
    bashrc(st);

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
			count = i;
			i = 0;
			//condition to exit from the shell
			if(!strcmp(st[0],"exit")){
                    cout<<"Bye !"<<endl;
                    exit(0);
			}
			if(!strcmp(st[0],"cd")){
				if(count>2){
					cout<<"too many arguments"<<endl;
				}
				else{
					changeDirectory(st);
				}
				//continue;
			}
			/*if(!strcmp(st[0],"alias"){
				char *cmd = srtok(st[1],"="); 
			}*/
			int pid = fork();
			if(pid){
				int wc = wait(&pid);
	    	}
	    	else{
				if(rflag == 1 && pflag == 1){
						piping(st,rflag,pflag);
				}
				else if(rflag == 0 && pflag == 1){
						piping(st,rflag,pflag);

				}
				else if(rflag == 1 && pflag == 0){
					redirection(st,rflag,pflag);
				}
				else{
	    	    	if(execvp(st[0],st)<0){
						cout<<"error: please check "<<endl;		
					}
					exit(0);
				}
	    	}
		}
	}

}
