#include<iostream>
#include<string>
#include<string.h>
#include<unistd.h>

using namespace std;
#define ds 10
//string redirection(string source, string destination)

string pipeoperator(string source){

	int i = 0, k = 0, g;
    char c;
    char *cmds[ds];
	string temp = "";
    while(source[i]){
        c = source[i];
        if(c!= ' ' && c != '|'){
            temp += string(1,c);
        }
		else if(c == ' '){
			char *cmd = (char *) malloc(temp.length()*sizeof(char));
			strcpy(cmd,temp.c_str());
			//cout<<"cmd "<<cmd<<endl;
			cmds[k++] = cmd;
			g = k - 1;
			cout<<"cmds "<<cmds[g]<<endl;
			temp = "";
			free(cmd);
		}
		else if(c == '|'){
			
		}
		i++;
    }   
	return "pipe is found";
}

int main(){
	string st = "ls -l | grep file";
	cout<<pipeoperator(st)<<endl;	
}
