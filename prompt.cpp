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
using namespace std;

void showPrompt(){
    char *cwd = (char *)malloc(mx*sizeof(char));
    char hostname[mx];
    cout<<getenv("USER")<<"@";
    gethostname(hostname,mx);
    cout<<hostname<<getcwd(cwd,mx)<<":~"<<getenv("PS1")<<"$ ";
}

