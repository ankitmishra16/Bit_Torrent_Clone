#include "global.h"

int main(int args, char const *argv[])
{
	string path,torent_filename,tr1, tr2,cmd,opcode, ip1,ip2,port1,pot2;
	vector<string> cmdchunks;
	int port_tracker_1,port_tracker_2;
	// path=argv[1];
	string client_socket(argv[1]);
	tr1=argv[2];
	tr2=argv[3];

	//****CONVERTING STRING TYPE PORT NUMBERS INTO INTEGERS**********************
	ip1=tr1.substr(0,tr1.find(":"));//getting IP and port of tracker1
    port_tracker_1=stoi(tr1.substr(tr1.find(":")+1,tr1.length()-1));

    ip2=tr2.substr(0,tr2.find(":"));//getting IP and port of tracker2
    port_tracker_2=stoi(tr2.substr(tr2.find(":")+1, tr2.length()-1));
    //CONVERTED STRING PORTS TO INTEGER PORTS*****************************

	getline(cin, cmd);
	istringstream ss(cmd); 
	while(ss>>opcode)
	{

		cmdchunks.push_back(opcode);
	}
	if(cmdchunks[0]=="share")
						{
							to_tracker_1(client_socket,cmdchunks[1],cmdchunks[2],ip1,port_tracker_1, ip2, port_tracker_2);//socket of client, name_of_file, mtorrent_file(with extension), IP of tracker_1, port of tracker_1, IP of tracker_2, port of tracker_2
						}
	return 0;
}