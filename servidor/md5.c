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
  memset(out,'\0',16);
  memset(buf,'\0',512);
  MD5_Init(&c);

  int tamano=0;
  while(read(dato,buf,512 )>0){
    tamano=strlen(buf)+tamano;
  }
  lseek (dato, 0, SEEK_SET );
  char bufT[tamano];
  memset(bufT,'\0',tamano);
  while(read(dato,bufT,tamano)>0){
    MD5_Update(&c,bufT,strlen(bufT));
    memset(bufT,'\0',tamano);
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
