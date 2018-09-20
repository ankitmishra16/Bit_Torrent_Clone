#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<openssl/sha.h>
#include<sys/stat.h>
#include<vector>
#include<sstream>
#include <stdio.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string>
#include<map>
using namespace std;
#ifndef INC_GLOBAL_H//header fle for listing the directories
#define INC_GLOBAL_H

int sha1(string,string, string, string );
void bin2hex( unsigned char* , int , char* );

#endif 