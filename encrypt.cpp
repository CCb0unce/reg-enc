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
        //·��Ϊ�Ҽ��˵���ֵ����Դ�ֵ
		char* filename = argv[1];
		//�˴�Ȩ�޵�ֵ,Ӧ���ò��Ե�һ������,����Ϊ��ǰ�û��Ƿ���Ȩ��(��Ȩ�޷���ֵΪ1)
		int root = 1;
		//ӦΪ���Դ������Կ
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
	char* targetfile = "temp.txt";//��ʱ�ļ�
	char buffer[21];
	int readCount;
    int  keyLen = strlen(secretKey);
    int i;
    //�˴�Ӧ�ֱ���ò��Եĺ���(���ļ�����·����Ϊ����,�õ��ķ���ֵ�ж��ļ�Ϊ��������δ���ܲŽ������´���,�����������
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
			buffer[i] ^= secretKey[i];      //�˴�Ӧ�����㷨��ļ��ܺ���.�������Ĵ�С����Կ���Ƚ��е���
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
	/*�޸��ļ�ͼ��*/

	/*�޸��ļ�ͷ*/
	
	
	
	return 1;
}
