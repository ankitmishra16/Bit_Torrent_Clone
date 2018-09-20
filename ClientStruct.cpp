#include <stdio.h> 
#include<iostream>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string> 
#define PORT 8080 
using namespace std;
   
int main() 
{ 
    struct sockaddr_in address; //Declaration && Initialization
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char ch,buffer[1024] = {0}; 
    string hash, address_of_file, socket_of_client;

    cout<<"\n Creating Socket...";
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    do{
        cout<<"\n Enter hash : ";//taking input
        cin>>hash;
        cout<<"\n Enter address of file : ";
        cin>>address_of_file;
        cout<<"\n Enter the socket of client : ";
        cin>>socket_of_client;

        hash=hash+" ";//apending whole data                                            
        hash+=address_of_file;
        hash+=" ";
        hash+=socket_of_client;
        hash+=" ";
        hash+="000";


        send(sock , hash.c_str() , hash.length(), 0 );
        hash.clear();
        address_of_file.clear();
        socket_of_client.clear(); 
        printf("\n Message sent");
        cout<<"\n Want to share more files...(Y/N)"; 
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    
    return 0; 
} 