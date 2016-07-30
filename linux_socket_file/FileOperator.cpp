#include "FileOperator.h"
#include <sys/sendfile.h>
#include <memory.h>
#include <iostream>

const  int  MAX_BUFFERLENGTH = 512;

using namespace std;

FileOperator::FileOperator():filePtr(NULL)
{
    //
}
FileOperator::~FileOperator()
{
    Close();
}

bool FileOperator::Open(const char *fileName,const char *option)
{
    filePtr = fopen(fileName,option);
    return filePtr!=NULL;
}

int FileOperator::WriteToFile(const std::string& buffer)
{
    int writeBytes = ::fwrite(buffer.c_str(),sizeof(char),buffer.size(),filePtr);
    if(writeBytes < 0){
        std::cout << "fwrite error\n";
        return -1;
    }else if(writeBytes == 0) {
         return 0;
    }else{
         return writeBytes;
    }
}

int FileOperator::ReadFromFile(std::string& buffer)
{
    char bufferArray[MAX_BUFFERLENGTH+1];
    memset(bufferArray,0x00,MAX_BUFFERLENGTH);

    int numberRead =  fread(bufferArray,sizeof(char),MAX_BUFFERLENGTH+1,filePtr);
    if(numberRead == -1){
        std::cout << "fread failed\n";
        return -1;
    }else if(numberRead == 0){
        return 0;
    }else{
        buffer = bufferArray;
        return numberRead;
    }

}

void FileOperator::Close()
{
    if(filePtr != NULL){
        fclose(filePtr);
    }
}























