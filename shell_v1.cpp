#include<iostream>
#include <unistd.h>
#include <string>

using namespace std;

int main(){
	string st = "ls -lrt";
	if(fork()){
		cout<<"hello from parent "<<endl;
	}
	else{
		char *ed[] = {NULL};	
		char *tk[]  =  {"/bin/ls","-ltr","../",NULL};	
        execve(tk[0],tk,ed);
        cout<<"hello from child "<<endl;
	}
    cout<<"hello from parent "<<endl;

}
