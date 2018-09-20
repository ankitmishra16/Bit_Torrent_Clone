#include "global.h"

int main(int args, char const *argv[])
{
	string path,torent_filename,tr1, tr2,cmd,opcode;
	vector<string> cmdchunks;
	// path=argv[1];
	tr1=argv[1];
	tr2=argv[2];
	getline(cin, cmd);
	istringstream ss(cmd); 
	while(ss>>opcode)
	{

		cmdchunks.push_back(opcode);
	}
	if(cmdchunks[0]=="share")
						{
							// if(cmdchuncks.size()>3)//to handle spaces in between name space
							
							// {
							// 	for(int i=1;i<cmdchuncks.size()-2;++i)
							// }
							sha1(cmdchunks[1],cmdchunks[2],tr1,tr2);//name_of_file, mtorrent_file(with extension), socket_of_tracker1, socket_of_tracker2
						}
	return 0;
}