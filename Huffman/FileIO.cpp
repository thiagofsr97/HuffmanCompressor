//
// Created by tfs- on 17/05/17.
//

#include "FileIO.h"
#include <fstream>


#include <iostream>
#include <cstring>
#include <deque>


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


void writeHeader(std::fstream *myFile,std::deque<int> frequencies,std::deque<char> symbols,int offset){
    int aux = frequencies.size();
    myFile->write(reinterpret_cast<char*>(&aux),sizeof(int));
    for(unsigned long i = 0; i <frequencies.size();i++){
        myFile->write(&(symbols.at(i)),sizeof(char));
        myFile->write(reinterpret_cast<char*>(&(frequencies.at(i))),sizeof(int));
    }

    //writing how many bits will not be considered at the end of the file
    myFile->write(reinterpret_cast<char*>(&offset),sizeof(int));
}

bool FileIO::readerHeader(std::string path,std::deque<int> *frequencies,std::deque<char> *symbols,int *offset){
    int size;
    int frequency;
    char symbol;
    std::fstream myFile;
    myFile.open(path, std::ios::binary | std::ios::in);
    myFile.read(reinterpret_cast<char*>(&size),sizeof(int));
    for(int i = 0; i < size; i ++){
        myFile.read(&symbol,sizeof(char));
        symbols->push_back(symbol);
        myFile.read(reinterpret_cast<char*>(&frequency),sizeof(int));
        frequencies->push_back(frequency);
    }

    myFile.read(reinterpret_cast<char*>(offset),sizeof(int));

    myFile.close();

}



void writeByte(std::fstream *myFile,std::string fullStr){

    for (int i = 0; i < fullStr.length(); i+=8)
    {
        unsigned char byte = 0;
        std::string str8 = "";
        if (i + 8 < fullStr.length()) {
            str8 = fullStr.substr(i, i + 8);
//            std::cout << str8 <<std::endl;

        }
        else
            str8 = fullStr.substr(i, fullStr.length());
        for (unsigned b = 0; b != 8; ++b)
        {
            if (b < str8.length())
                byte |= (str8[b] & 1) << b; // this line was wrong before
            else {
                byte |= 1 << b;
            }
        }
        myFile->put(byte);
        str8.clear();

    }
}

bool FileIO::writeFile(std::string content, std::string path, std::string fileExtension,std::deque<int> frequencies,std::deque<char> symbols,int offset) {

    std::fstream myFile;

    myFile.open(path + fileExtension, std::ios::binary | std::ios::out);
    if(!myFile.is_open())
        return false; //error opening file

    //writing header
    writeHeader(&myFile,frequencies,symbols,offset);

    //writing content to file
    writeByte(&myFile,content);
    myFile.close();
}

bool FileIO::readSymbols(std::string path, std::deque<char> *symbols) {
    std::fstream myFile;
    myFile.open(path,std::ios::binary|std::ios::in);
    if(!myFile.is_open())
        return false; //could not open the file

    int size;
    myFile.read(reinterpret_cast<char*>(&size),sizeof(int));
    for(int i = 0; i < size; i++){
        myFile.seekg(sizeof(char),std::ios::cur);
        myFile.seekg(sizeof(int),std::ios::cur);
    }

    myFile.seekg(sizeof(int),std::ios::cur);
    char c;


    while(!myFile.eof()){
        myFile.read(&c,sizeof(char));
        symbols->push_back(c);

    }

    // Needs to remove one char, refered to EOF.
    symbols->pop_back();
    myFile.close();

}

bool FileIO::writeDecodedFile(std::string path, std::string content) {
    std::fstream myFile;
    myFile.open(path,std::ios::binary|std::ios::out);

    if(!myFile.is_open())
        return false; //error opening file

    myFile.write(content.c_str(),sizeof(char) * content.size());

    myFile.close();

}
