#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void bashrc(char *fp[]) {
    int i;
   	FILE *f;
	char c;
	char *st;
	char *tok;
	char *cmd[3];
	string s="";	
    f = fopen(fp[0],"r");
    c = fgetc(f);
	i=0;
	while(c!=EOF){
		if(c!='\n')
			s = s+string(1,c);
		else if(c == '\n'){
			st = (char*)malloc((s.length()+1)*sizeof(char));
			strcpy(st,s.c_str());
			tok = strtok(st,"=");
			cmd[0]=tok;
			//cout<<"cmd "<<cmd[0]<<endl;
			while(1){
				tok = strtok(NULL,"=");
				if(tok == NULL) break;
				else{
					cmd[1]=tok;
					cout<<"cmd "<<cmd[1]<<endl;
				}
			//free(st);	
			}
			cout<<cmd[0]<<" "<<cmd[1]<<endl;
			//setenv(cmd[0],cmd[1],1);
			s = "";
		}
		c= fgetc(f);
	}
	cmd[i]=NULL;
	cout<<endl;
}
int main(){
 char *fp[] = {"alias","ls=ls -lrt",NULL};
 bashrc(fp);

}
