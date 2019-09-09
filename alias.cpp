#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include<cstring>
#include<string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "header.h"

using namespace std;
extern map<string,string> ms;

void setAlias(char *fp[]) {
    int i;
   	FILE *f;
	char c;
	char *st;
	char *tok;
	char *cmd[3];
	//cout<<"cmd "<<fp[1]<<endl;
	/*i=0;
	while(fp[1][i]){
		cout<<fp[1][i]<<endl;
		i++;
	}*/
	//string m="ls=ls -ltr";	
    char *s=(char *)malloc(10*sizeof(char));
	strcpy(s,fp[1]);
	i=1;
	tok = strtok(s,"=");
	cmd[0]=tok;
	while(1){
		tok = strtok(NULL,"=");
		if(tok == NULL) break;
		else{
			cmd[1]=tok;
			ms.insert(pair<string,string>(cmd[0],cmd[1]));
			//cout<<"cmd in map "<<ms[cmd[0]]<<endl;
		}
	//free(st);	
	}
	//cout<<cmd[0]<<" "<<cmd[1]<<endl;
	//setenv(cmd[0],cmd[1],1);
	//cout<<endl;
}
char* findAlias(char *p[]){
	if(ms.find(p[0]) != ms.end()){
		//cout<<ms[p[0]]<<endl;
		char *val = (char*)malloc(ms[p[0]].size()*sizeof(char));
    	strcpy(val,ms[p[0]].c_str());
    	return val;	
	}
	else return p[0];
}
/*int main(){
 char *fp[] = {"alias","p=pwd",NULL};
 char *pw[] = {"p",NULL};
 setAlias(fp);
 pw[0]=findAlias(pw);
 cout<<pw[0]<<endl;
 int pid = fork();
 if(pid){
	wait(&pid);
 }else{
 	execvp(pw[0],pw);
	exit(0);
 }

}*/
