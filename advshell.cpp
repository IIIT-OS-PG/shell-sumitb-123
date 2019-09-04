#include<iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
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
		int rflag = 0;
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

			if(c == '|' || c == '>'){
				rflag = 1;
			}
		
		}while(1);

		if(i>0){
		st[i]=NULL;
		i = 0;
		int pid = fork();
		if(pid){
			int wc = wait(&pid);
	    }
	    else{
			if(rflag == 1){
				cout<<" flag is there "<<endl;	
			}
			else{
	        		execvp(st[0],st);
					exit(0);
			}
	    }
		}
	}

}
