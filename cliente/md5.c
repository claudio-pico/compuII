#include <openssl/md5.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void md5(int dato,char* outMd5){
  int n;
  MD5_CTX c;
  unsigned char out[16];
  char buf[512];
  memset(out,'\0',sizeof out);
  memset(buf,'\0',sizeof buf);
  MD5_Init(&c);
 int lee=0;
  while((lee=read(dato,buf,sizeof buf))>0){
    MD5_Update(&c,buf,lee);
    memset(buf,'\0',sizeof buf);
  }
  memset(outMd5,'\0',64);
  MD5_Final(out, &c);
  char aux[8];
  for(n=0; n<16; n++){
    sprintf(aux,"%02x",out[n]);
    strcat(outMd5,aux);
  }
  return;
   
}
