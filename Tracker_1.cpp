#include "global.h"
using namespace std; 
#define PORT 8080 
map<string, vector<pair<string, string> > > seeder_list;
void seeder_update(int new_socket)
{
    char buffer[1024] = {0};
    string nxt,hash, address_file, socket_client; 
    while(read( new_socket , buffer, 1024))
    { 
        cout<<"\n Complete data recieved  ";
        stringstream ss(buffer);
        ss >> nxt;
        hash=nxt;
        cout<<"\nHash : "<<hash;
        nxt.clear();
        ss >> nxt;
        address_file=nxt;
        cout<<"\n Address of file : "<<address_file;
        nxt.clear();
        ss >> nxt;
        socket_client=nxt;
        cout<<"\nSocket : "<<socket_client<<"\n";
        nxt.clear();
        // seeder_list.insert({hash, make_pair(address_file, socket_client)});
        seeder_list[hash].push_back(make_pair(address_file, socket_client));
        map<string, vector<pair<string,string> > > :: iterator itr;
        cout<<"\n Printing Values in map ";
        for(itr= seeder_list.begin();itr!=seeder_list.end();itr++)
        {
            for(int i=0;i<seeder_list[itr->first].size();i++)
                cout<<itr->first<<" "<<itr->second[i].first<<" "<<itr->second[i].second<<"\n";
        }
    }
}
int main() 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0};
    string nxt,hash, address_file, socket_client;  
       
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
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
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
        // while(read( new_socket , buffer, 1024))
        // { 
        //     cout<<"\n Complete data recieved  ";
        //     stringstream ss(buffer);
        //     ss >> nxt;
        //     hash=nxt;
        //     cout<<"\nHash : "<<hash;
        //     nxt.clear();
        //     ss >> nxt;
        //     address_file=nxt;
        //     cout<<"\n Address of file : "<<address_file;
        //     nxt.clear();
        //     ss >> nxt;
        //     socket_client=nxt;
        //     cout<<"\nSocket : "<<socket_client<<"\n";
        //     nxt.clear();
        //     // seeder_list.insert({hash, make_pair(address_file, socket_client)});
        //     seeder_list[hash].push_back(make_pair(address_file, socket_client));
        //     map<string, vector<pair<string,string> > > :: iterator itr;
        //     cout<<"\n Printing Values in map ";
        //     for(itr= seeder_list.begin();itr!=seeder_list.end();itr++)
        //     {
        //         for(int i=0;i<seeder_list[itr->first].size();i++)
        //             cout<<itr->first<<" "<<itr->second[i].first<<" "<<itr->second[i].second<<"\n";
        //     }
        // }
    }
    close(new_socket);
    return 0; 
} 
















