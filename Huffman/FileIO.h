#ifndef HUFFMAN_FILEIO_H
#define HUFFMAN_FILEIO_H

#include <string>
#include <deque>
#include <fstream>
#include <iostream>
#include <cstring>

//! FileIO Class.
/*!
  Class responsible for all the processes related to reading and writing into a file,
  supporting the compressing and decompressing processes.
*/

class FileIO{
public:
    bool readFile(std::string path,char **bufferOut, size_t *sizeOfFile);
    bool writeEncodedFile(std::string path,std::string fileExtension,std::deque<int> frequencies,std::deque<char> symbols,int padding);
    void writeEncodedByte(const char bits[],unsigned long bufferSize);
    bool readerHeader(std::string path,std::deque<int> *frequencies, std::deque<char> *symbols,int *padding);
    void readSymbols(std::deque<char>*symbols);
    bool writeDecodedFile(std::string path);
    void writeDecodedByte( const char bits);
    void closeFile();

private:
    std::size_t getFileSize(std::string path);
    std::fstream stream;

};

#endif //HUFFMAN_FILEIO_H
