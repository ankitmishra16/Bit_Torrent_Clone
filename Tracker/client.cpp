#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<map>
#include<vector>
#include<utility>
#define port 4455
using namespace std;
int main()
{
	int client_socket,no_of_inp=0;
	FILE *fp;
	// struct sockaddr_in serverAddr;
	char buffer[1024],ch;
	string hash, address_of_file, socket_of_client;
	map<string, vector<pair<string, string>>> inp;

	// client_socket=socket(PF_INET, SOCK_STREAM,0);
	// memset(&serverAddr, '\0', sizeof(serverAddr));
	// serverAddr.sin_family=AF_INET;
	// serverAddr.sin_port=htons(port);
	// serverAddr.sin_addr.s_addr=INADDR_ANY;

	// connect(client_socket , (struct sockaddr*)&serverAddr, sizeof(serverAddr));//request to connect
	fp=fopen("structured.txt","w");
	do{
	cout<<"\n Enter the hash of the file : ";
	// getline(cin, hash);
	// fgets(buffer, 512, stdin);
	cin>>hash;
	// hash=buffer;
	// strcpy(hash,buffer);
	// memset(buffer,'\0', sizeof(buffer));
	cout<<"\n  Enter the address of file : ";
	// getline(cin, address_of_file);
	// cin>>obj->address_of_file;
	// fgets(buffer, 512, stdin);
	cin>>address_of_file;
	// strcpy(address_of_file,buffer);
	// address_of_file=buffer;
	// memset(buffer,'\0', sizeof(buffer));
	cout<<"\n Enter the socket of client ";
	// getline(cin, socket_of_client);
	// cin>>obj->socket_of_client;
	// fgets(buffer, 512, stdin);
	cin>>socket_of_client;
	// strcpy(socket_of_client,buffer);
	// socket_of_client=buffer;
	// memset(buffer,'\0', sizeof(buffer));

	//************Inserting in map of vector of pairs******************


	//**********Writinig to the file*****************
	
	inp[hash].push_back(make_pair(address_of_file,socket_of_client));
	no_of_inp++;
	cout<<"\n Want to enter more details...";
	cin>>ch;
	}while(ch=='y'|| ch=='Y');
	fwrite(&inp, sizeof(inp), 1, fp);
	fclose(fp);
	FILE *ff;
	ff=fopen("structured.txt","r");
	map<string, vector<pair<string, string> > > ii;
	map<string, vector<pair<string, string> > >::iterator itr;
	// itr=inp.begin();
	int m=0,i=0;
	fread(&ii, sizeof(ii),1, ff);
	fclose(ff);
	itr=ii.begin();
	cout<<"\n Size of array  is : "<<ii.size();
	// cout<<"\n Size of array  is : "<<itr.size();
	bool con=true;
	 while(itr!=ii.end())
	{
		// itr=ii.begin();
		cout<<"\nIteration Number : "<<m;
		for(int j=0;j<itr->second.size();j++)
			cout<<"\nHash is : "<<itr->first<<"\n File address : "<<itr->second[j].first<<"\n Port : "<<itr->second[j].second<<"\n";
		// i++;
		// if((++itr)!=ii.end())
		// {}
		// else
		// 	con=false;
		itr++;
		m++;
	}
	ii.clear();
	cout<<"\n Not here";
	// recv(clskt, buffer, 1024, 0);//recieve data

	// cout<<"\nMessage recieved : "<<buffer;
	// cout<<"\nClient :";
	// cin>>buff;
	// send(clskt,buff, sizeof(buff), 0);
	return 0;
}