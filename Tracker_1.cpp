#include "global.h"
using namespace std; 
#define PORT 8080 
map<string, vector<pair<string, string> > > seeder_list;
void seeder_update(int new_socket)
{
    FILE* sdl;
    char buffer[1024] = {0};
    string nxt,hash, address_file, socket_client; 
    while(read( new_socket , buffer, 1024))
    { 
        // read( new_socket , buffer, 1024);
        // cout<<"\n Complete data recieved  ";
        stringstream ss(buffer);
        ss >> nxt;
        hash=nxt;
        // cout<<"\nHash : "<<hash;
        nxt.clear();
        ss >> nxt;
        address_file=nxt;
        // cout<<"\n Address of file : "<<address_file;
        nxt.clear();
        ss >> nxt;
        socket_client=nxt;
        // cout<<"\nSocket : "<<socket_client<<"\n";
        nxt.clear();
        seeder_list[hash].push_back(make_pair(address_file, socket_client));//to Update Map Seeder_List

        //**********************UPDATING SEEDER_LIST*************
        // cout<<"\n Going to create file ";
        sdl=fopen("Seeder_List.txt","app");//Opening file in append mode 
        fprintf(sdl,"\n%s\n%s\n%s",hash.c_str(), address_file.c_str(), socket_client.c_str());//Format is hash \n address_of_file \n socket_client
        // cout<<"\n Entery updated in Seeder_List.txt";
        fclose(sdl);
        //*******UPTO HERE UPDATING SEEDER_LIST******************

        map<string, vector<pair<string,string> > > :: iterator itr;
        cout<<"\n Printing Values in map \n";
        for(itr= seeder_list.begin();itr!=seeder_list.end();itr++)
        {
            for(int i=0;i<seeder_list[itr->first].size();i++)
                cout<<itr->first<<" "<<itr->second[i].first<<" "<<itr->second[i].second<<"\n";
        }
    }
}
int main(int args, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int self_port,other_port,opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0};
    string nxt,hash, address_file, socket_client,ip1, ip2, self_ip, other_ip;  
    // FILE *upd;//To update the map

    cout<<"\n Reading input from command line ";
    ip1=argv[1];//taking arguments in variables
    ip2=argv[2];
    cout<<"\n Command red";

    cout<<"\n Converting passed arguments to appropriate types";
    self_ip=ip1.substr(0,ip1.find(":"));//Fetching out ip and port from ccommand line argument for tracker_1
    self_port=stoi(ip1.substr(ip1.find(":")+1,ip1.length()-1));

    cout<<"\n Conversion of tracker 2";
    other_ip=ip2.substr(0,ip2.find(":"));//Fetching out ip and port from ccommand line argument for tracker_1
    other_port=stoi(ip2.substr(ip2.find(":")+1,ip2.length()-1));

    ifstream upd;
    upd.open("Seeder_List.txt");

    // upd=fopen("Seeder_List.txt","r");
    getline(upd,hash);
    hash.clear();
    while(getline(upd, hash))//Because if there is hash then there will be next two entries too
    {
        getline(upd,address_file);
        getline(upd, socket_client);
        seeder_list[hash].push_back(make_pair(address_file, socket_client));
        cout<<"\nEntery Updated ";
    }
    upd.close();
    // fclose(upd);
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = inet_addr(self_ip.c_str()); 
    address.sin_port = htons( self_port ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 50) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    while(1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 
        thread  th(seeder_update, new_socket);
        th.detach();
    }
    close(new_socket);
    return 0; 
} 
















