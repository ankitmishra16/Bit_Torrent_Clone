#include "global.h" 
#define PORT 8080 
#define MAX_BUF_LEN (512*1000)
using namespace std;
   
int to_tracker_1(string name,string mtorrent_file, string tr1IP, string tr2IP) 
{ 
    struct sockaddr_in address; //Declaration && Initialization
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char ch,buffer[1024] = {0}; 
    string hash, address_of_file, socket_of_client,cmd;

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
    ch='n';

    do{

        //*********MODULE OF SHA***************
        string hash_o;
        FILE * pf,*trt;
        unsigned long size;
        unsigned char out[ SHA_DIGEST_LENGTH ];
        char hex[2*SHA_DIGEST_LENGTH];
        unsigned char buf[ MAX_BUF_LEN ];

        pf = fopen( name.c_str(), "rb" );

        struct stat stat_buf;//to get size of the file
        stat(name.c_str(), &stat_buf);
        size=stat_buf.st_size; 
        trt=fopen(mtorrent_file.c_str(), "w");

        string complete_path=realpath(name.c_str(),NULL);//to get real path of the file

        while(fread( buf, 1, MAX_BUF_LEN, pf )>0)//for creating SHA1 hash of  chunks of file
        {
            SHA1(buf,sizeof(buf),out);
            bin2hex(out,sizeof(out), hex);
            string temp(hex,20);
            hash_o=hash_o+temp;
        }

        cout<<"\n Hash before writing : "<<hash_o;
        fprintf(trt,"%s\n%s\n%s\n%lu\n%s",tr1IP.c_str(), tr2IP.c_str(), complete_path.c_str(),size,hash_o.c_str());
        cout<<"\n After writting in mtorrent_file";
        fclose(pf);
        fclose(trt);
        //**********UPTO HERE CODE IS OF SHA***************

        cout<<"\n Enter the socket of client : ";
        cin>>socket_of_client;
        hash=hash_o.substr(0,20);
        hash=hash+" ";//apending whole data                                            
        hash+=complete_path ;
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
        cout<<"\n Value of ch is : "<<ch;
        if(ch=='y'|| ch=='Y')
        {
            cout<<"\n Inside first if ";
            cmd.clear();
            cin.ignore();
            getline(cin, cmd);
            cout<<"\n After getline() ";
            stringstream ss(cmd);
            string temp;
            ss>>temp;
            if(temp!="share")
                break;
            else
            {
                ss>>temp;
                name=temp;
                temp.clear();
                ss>>temp;
                mtorrent_file=temp;
                temp.clear();
                ss>>temp;

            }
        }
    }while(ch=='y'||ch=='Y');
    
    return 0; 
} 