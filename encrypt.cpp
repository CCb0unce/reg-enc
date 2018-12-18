#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include<windows.h>
#include <dirent.h>

using namespace std;

vector<string> files;
void encryfunct(char* ,char* ,int );
int encfolder(char* ,char* );
int encryptFile(char *, char *);
int main(int argc,char* argv[]) {
        //路径为右键菜单传值或策略传值
		char* filename = argv[1];
		//此处权限的值,应调用策略的一个函数,返回为当前用户是否有权限(有权限返回值为1)
		int root = 1;
		//应为策略传输的密钥
		char* secretKey = "jsdgaflscbkuyqoruycxh";
		encryfunct(filename,secretKey,root);

       }
void encryfunct(char* filename,char* secretKey,int root=1){

        struct stat buf;
		int result = 0;
		result = stat(filename,&buf);
        //root or not
        if(root==1) {
		//folder or file
		if(_S_IFDIR & buf.st_mode) {
			if(encfolder(filename,secretKey)==1)
                printf("success\n");
		} else if(_S_IFREG & buf.st_mode) {
			if(encryptFile(filename,secretKey)==1)
               printf("success\n");
		}
	}
	else if(root==0)printf("Permission denied");
	system("pause");
	//return 0;
}
int encfolder(char* path,char* secretKey){
    char file_path[2048] = {0};
  //  char file[512] = {0};
    DIR *dir = NULL;
    struct dirent *ptr = NULL;
    struct stat buf;
    int i, j;
    if ((dir = opendir(path)) == NULL) {
        perror("opendir failed!");
        return -1;
    }
    while((ptr = readdir(dir)) != NULL) {
        if (ptr->d_name[0] != '.') {
            strcpy(file_path, path);
            if (path[strlen(path) - 1] != '/')
                strcat(file_path, "/");
            strcat(file_path, ptr->d_name);  
            printf("%s",file_path);
            encryfunct(file_path,secretKey);
           // continue;
            }}return 1;
}

int encryptFile(char *sourcefile, char *secretKey) {
	FILE *fpSource,*fpTarget;
	char* targetfile = "temp.txt";//临时文件
	char buffer[21];
	int readCount;
    int  keyLen = strlen(secretKey);
    int i;
    //此处应分别调用策略的函数(将文件完整路径作为参数,得到的返回值判断文件为白名单且未加密才进行以下代码,否则结束程序
	fpSource = fopen(sourcefile, "rb");
	if(fpSource==NULL) {
		return 0;
	}
    fpTarget = fopen(targetfile, "wb");
	if(fpTarget==NULL) {
		return 0;
	}

	while( (readCount=fread(buffer, 1, keyLen, fpSource)) > 0 ) {
		for(i=0; i<readCount; i++) {
			buffer[i] ^= secretKey[i];      //此处应调用算法组的加密函数.缓冲区的大小随密钥长度进行调整
			//printf("buffer=%s\n",buffer);
		}
		fwrite(buffer, 1, readCount, fpTarget);
		//fseek(fpSource,21L,1);
	}
	fclose(fpSource);
	fclose(fpTarget);
	remove(sourcefile);
	rename(targetfile,sourcefile);
	
	//TO BE CONTINUE
	/*修改文件图标*/

	/*修改文件头*/
	
	
	
	return 1;
}
