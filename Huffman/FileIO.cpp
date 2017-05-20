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



void FileIO::writeEncodedByte(const char bits[8]){
    unsigned char byte = 0;
    for (int i = 0; i != 8; ++i)
    {
        byte |= (bits[i] & 1) << i; // this line was wrong before

    } stream.put(byte);

}


bool FileIO::writeFile(std::string path, std::string fileExtension,std::deque<int> frequencies,std::deque<char> symbols,int offset) {

   // std::fstream myFile;

    stream.open(path + fileExtension, std::ios::binary | std::ios::out);
    if(!stream.is_open())
        return false; //error opening file

    //writing header
    writeHeader(&stream,frequencies,symbols,offset);

    //writing content to file
    //writeByte(&myFile,content);
    //myFile.close();
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

bool FileIO::writeDecodedFile(std::string path) {
    std::fstream myFile;
    stream.open(path,std::ios::binary|std::ios::out);

    if(!stream.is_open())
        return false; //error opening file

//    myFile.write(content.c_str(),sizeof(char) * content.size());
//
//    myFile.close();

}

void FileIO::writeDecodedByte(const char bits) {

    stream.put(bits);

}

void FileIO::closeFile() {
    stream.close();
}
