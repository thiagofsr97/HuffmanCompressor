//
// Created by tfs- on 17/05/17.
//

#include "FileIO.h"
#include <fstream>


#include <iostream>
#include <cstring>


size_t FileIO::getFileSize(std::string path){
    std::ifstream file( path, std::ios::binary | std::ios::ate );
    if(!file.is_open())
        return 0;
    size_t fileSize = file.tellg();
    file.clear();
    file.close();

    return fileSize;
}

bool FileIO::readFile(std::string path,char bufferOut[]) {
    std::fstream myFile;

    size_t size = getFileSize(path);

    myFile.open (path, std::ios::in | std::ios::out | std::ios::binary);
    if(!myFile.is_open())
        return false;

    if(bufferOut != nullptr)
        if(!myFile.read(bufferOut,size))
            return false;

    myFile.clear();
    myFile.close();
    return true;

}
//
//bool FileIO::writeFile(const char *content,int size,std::string path, std::string fileExtension) {
//    std::fstream myFile;
//    myFile.open(path + fileExtension, std::ios::binary |std::ios::out);
//    if(!myFile.is_open())
//        return false;
//
//    if(!myFile.write(content,size))
//        return false;
//    myFile.close();
//
//    return true;
//
//}

bool FileIO::writeFile(std::string content, std::string path, std::string fileExtension) {

    std::fstream myFile;

    myFile.open(path + fileExtension, std::ios::binary | std::ios::out);
    if(!myFile.is_open())
        return false; //error opening file



    std::string fullStr = content;

    for (int i = 0; i < fullStr.length(); i+=8)
    {
        unsigned char byte = 0;
        std::string str8 = "";
        if (i + 8 < fullStr.length())
            str8 = fullStr.substr(i, i + 8);
        else
            str8 = fullStr.substr(i, fullStr.length());
        for (unsigned b = 0; b != 8; ++b)
        {
            if (b < str8.length())
                byte |= (str8[b] & 1) << b; // this line was wrong before
            else
                byte |= 1 << b;
        }
        myFile.put(byte);
    }
    //0int filelen = outf.tellp();

    myFile.close();



}