#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "iconv.h"

#pragma(lib,"iconv.lib")
#pragma(lib,"charset.lib")
#define OUTLEN 255

int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen);
int u2g(char *inbuf,int inlen,char *outbuf,int outlen);
int u2gbk(char *inbuf,int inlen,char *outbuf,int outlen);
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int gbk2ebcdic(char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int EbcdicToAscii(char *sIn, char *sOut);
unsigned short unCharToUnShort(unsigned char* pBuf);

int main(void)
{
	//iconv_t it = iconv_open ("utf-8", "gbk");
	//printf("%d",it);

	//char *in_utf8 = "姝ｅ?ㄥ??瑁?";
	char *in_utf8 = "Jack say: hello [axis2] Jack 璇达細鎮ㄥソ鍟奫axix2]";
    char *in_gb2312 = "Hi我来自IBM";
	//char *gbk = "囙囜団囥囦囧囨囩囪囬";
	char out[OUTLEN];
	//char *ebcdicStr = "趑篑@@@@@@@@@@";
	//char asciiStr[OUTLEN];

	//unsigned char *ch = "Hi我来自IBM"; //gbk
	//unsigned char *ch = "我";
	//wchar_t *wch = L"Hi我来自IBM";//uniconde
	//TCHAR *tch = TEXT("Hi我来自IBM");

	//unsigned short ushort;

	//puts(strlen(gbk));

	//unicode码转为gb2312码
	u2g(in_utf8,strlen(in_utf8),out,OUTLEN);
	printf("unicode-->gb2312 ");
	puts(out);
	
	//unicode码转为gbk码
	u2gbk(in_utf8,strlen(in_utf8),out,OUTLEN);
	printf("unicode-->gbk ");
	puts(out);

	//gb2312码转为unicode码
	//g2u(in_gb2312,strlen(in_gb2312),out,OUTLEN);
	//printf("gb2312-->unicode ");
	//puts(out);

	//puts(strlen(ch));
	/*
	while(*ch != '\0')
	{
		printf("%X ",*ch);
		ch++;
	}
	printf("\n");

	while(*wch != '\0')
	{
		printf("%X ",*wch);
		wch++;
	}
	printf("\n");

	while(*tch != '\0')
	{
		printf("%X ",*tch);
		tch++;
	}
	printf("\n");
    //printf("%X %X %X %X %X %X %X %X %X %X %X %X\n",ch[0],ch[1],ch[2],ch[3],ch[4],ch[5],ch[6],ch[7],ch[8],ch[9],ch[10],ch[11]);

	//rc = gbk2ebcdic(in_gb2312,strlen(in_gb2312),out,OUTLEN);
	//printf("gb2312-->ebcdic out=%s\n",out);

	//rc=EbcdicToAscii(ebcdicStr,out);

	ushort = unCharToUnShort(ch);
	printf("%d\n",ushort);*/
	
	return 0;
}

//代码转换:从一种编码转为另一种编码
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
{
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset,from_charset);

	if(cd == 0) 
		return -1;
	memset(outbuf,0,outlen);
	if (iconv(cd,pin,&inlen,pout,&outlen) == -1) 
		return -1;

	iconv_close(cd);

	return 0;
}

//UNICODE码转为GB2312码
int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
{
	return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
}

//UNICODE码转为GBK码
int u2gbk(char *inbuf,int inlen,char *outbuf,int outlen)
{
	return code_convert("utf-8","gbk",inbuf,inlen,outbuf,outlen);
}

//GB2312码转为UNICODE码
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	return code_convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
}

int gbk2ebcdic(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	return code_convert("gbk","IBM_935",inbuf,inlen,outbuf,outlen);
}

int EbcdicToAscii(char *sIn, char *sOut) 
 { 
    iconv_t cd; 
    size_t inBytesLeft = 0; 
    size_t outBytesLeft = 0; 
    char *inTemp = sIn; 
    char *outTemp = sOut; 
    char localCode[20], targetCode[20]; 

    inBytesLeft = strlen(sIn); 
    outBytesLeft = strlen(sIn) * 2; 
    memset(&localCode, 0x00, sizeof(localCode)); 
    //sprintf(localCode, "%s", "IBM-850");/*850 ASCII */ 
	sprintf(localCode, "%s", "IBM-850");

    memset(&targetCode, 0x00, sizeof(targetCode)); 
    sprintf(targetCode, "%s", "IBM-037"); /* 037 for EBCDIC */ 

    cd = iconv_open(localCode, targetCode); 
    
    if (iconv(cd, &inTemp, &inBytesLeft, &outTemp, &outBytesLeft) != 0) 
    { 
      printf("Error calling iconv\n"); 
      if (iconv_close(cd) == -1) 
      { 
         printf("Error calling iconv_Close\n"); 
         return 1; 
      } 
    } 

    if (iconv_close(cd) == -1) 
    { 
       printf("Error calling iconv_Close\n"); 
       return (1); 
    } 

    return 0; 
 } 

unsigned short unCharToUnShort(unsigned char* pBuf)
{
 unsigned short result = 0;
 result = (short)pBuf[0]*256;
 result += (short)pBuf[1];
 return result;
}