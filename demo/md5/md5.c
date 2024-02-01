#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 void get_Md5(char* filename,unsigned char outmd[])
{
    MD5_CTX ctx;
    char buff[1024];
    int len=0;
    FILE* fp=NULL;
    memset(buff,0,sizeof(buff));
    fp=fopen(filename,"rb");
    if(fp==NULL)
    {
        printf("Can't open file\n");
        return;
    }
  
    MD5_Init(&ctx);
    while((len=fread(buff,1,1024,fp))>0)
    {
        MD5_Update(&ctx,buff,len);
        memset(buff,0,sizeof(buff));
    }
    MD5_Final(outmd,&ctx);
  }

  int main()
  {

  }