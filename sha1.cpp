#include "global.h"
#define MAX_BUF_LEN (512*1000)

int sha1(string name,string mtorrent_file, string tr1IP, string tr2IP) 
{
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

    fprintf(trt,"%s\n%s\n%s\n%lu\n%s",tr1IP.c_str(), tr2IP.c_str(), complete_path.c_str(),size,hash_o.c_str());
    fclose(pf);

    return 0;
}