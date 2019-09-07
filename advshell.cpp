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
char cdpath[mx];
using namespace std;

void showPrompt(){
	char hostname[mx];
	cout<<getenv("USER")<<"@";
	gethostname(hostname,mx);
	cout<<hostname<<"$ ";
}

void changeDirectory(char *st[]){
		size_t sz = mx;
		char *bfr = (char *)malloc(mx*sizeof(char));
		if(st[1] == NULL || !strcmp(st[1],"~")){
			char *path=(char *)malloc(mx*sizeof(char));
			strcpy(path,getenv("HOME"));
			strcpy(cdpath,getcwd(bfr,sz));
			chdir(path);
			free(path);
		}
		else if(!strcmp(st[1],"-")){
			char *path=(char *)malloc(mx*sizeof(char));
			strcpy(path,getcwd(bfr,sz));
			chdir(cdpath);
			strcpy(cdpath,path);
			free(path);
		}
		else{
			strcpy(cdpath,getcwd(bfr,sz));
			chdir(st[1]);
		}
		free(bfr);
}

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
			execvp(arr[0],arr);
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

void piping(char *st[], int rflag,int pflag){
	int i=0, index = 0,temp,count = 1,pid;
	//int fd[2],pid,fd1[2];
	//pipe(fd);
	while(st[i]){
	    //cout<<"pipe "<<endl;
		//pipe(fd1);
		int fd[2];
		pipe(fd);
		printf("%s ",st[i]);
		if(!strcmp(st[i],"|")){
				st[i] = NULL;
				pid = fork();
				if(pid){
					wait(&pid);
					close(fd[1]);
					dup2(fd[0],0);
				}
				else{
					//cout<<"child index "<<index<<endl;
					//printf("cmd at index %s ",st[index]);
					close(fd[0]);
					dup2(fd[1],1);
					close(fd[1]);
					//execvp(st[index],st+index);
					//execvp(cmd[0],cmd);
					execvp(st[index],st+index);
					_exit(0);
				}
				//cout<<"before updating "<<index<<endl;
				index = i+1;
				//cout<<"after updating "<<index<<endl;
		}
		i++;
	}
	//close(fd[1]);
    //dup2(fd[0],0);
	if(rflag == 1){
		redirection(st+index,rflag,pflag);
		_exit(0);
	}
	else{
    	execvp(st[index],st+index);
		_exit(0);
	}
}

int main(){
	int i;
	strcpy(cdpath,getenv("PWD"));
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
			if(!strcmp(st[0],"cd")){
				changeDirectory(st);
			}
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
	    	    	execvp(st[0],st);
					exit(0);
				}
	    	}
		}
	}

}
