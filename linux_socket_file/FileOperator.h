#ifndef  FILEOPERATOR_H
#define  FILEOPERATOR_H

#include <stdio.h>
#include <string.h>
#include <string>


#define  WRITE_CREATE_MODE  "a+b"

class FileOperator
{
    public:
        FileOperator();
        ~FileOperator();
        bool Open(const char *fileName,const char *option);
        int WriteToFile(const std::string& buffer);
        int ReadFromFile(std::string& buffer);
        void Close();
    private:
        FILE *filePtr;

};



#endif
