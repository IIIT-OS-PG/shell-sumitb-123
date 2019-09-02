#include<iostream>
#include <unistd.h>
#include <string.h>
#define argl 10
#define cmdl 10

using namespace std;

int main(){
	int i;
	while(1){
		i=0;	
		char *st[argl];
		char *cmd;
		char nc;

		do{
			cmd = new char[cmdl];
		    cin>>cmd;
			st[i]=cmd;
			//cout<<st[i]<<endl;
			if(getchar() == '\n') break;
			i++;

		}while(1);

		st[++i]=NULL;	

	if(fork()){
        cout<<"hello from parent "<<endl;
    }
    else{
        char *ed[] = {NULL};
		//cout<<"child "<<chk<<endl;
        execvp(st[0],st);
    }
	delete cmd;
	}

}
