#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
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
            }
            if(rflag == 2){
            fdw = open(arr[len-1],O_WRONLY | O_CREAT | O_TRUNC);
            }
			chmod(arr[len-1],S_IRUSR | S_IWUSR);
			dup2(fdw,1);
			arr[len-2] = NULL;
			execvp(arr[0],arr);
			close(fdw);
			
		}

}

/*char *[] chararr(vector<string> &v){
	int l = v.size()+1;
	char *cmds[l];
	int i = 0;
	for(string s: v){
		char *p = (char *)malloc(s.length()*sizeof(char));
		cmds[i] = p;
		i++;
	}
	cmds[i] = NULL;
	return cmds;
}*/

/*void piping(char *st[]){
	int i=0, index = -1,fd;
	int fd[2],pid;
	pipe(fd);
	while(st[i]){
		if(!strcmp(st[i],"|")){
			if(index == -1){
				st[i] = NULL;
				pid = fork();
				if(pid){
					wait(&pid);

				}
				else{
					close(fd[0]);
					dup2(fd[1],1);

				}
				execvp(st[++index],st+index);
				index = i;
			}
		}
	}

}*/

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
			//condition to exit from the shell
			if(!strcmp(st[0],"exit")){
                    cout<<"Bye !"<<endl;
                    exit(0);
			}
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
