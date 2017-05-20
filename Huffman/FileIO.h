//
// Created by tfs- on 17/05/17.
//

#ifndef HUFFMAN_FILEIO_H
#define HUFFMAN_FILEIO_H

#include <string>
#include <deque>

class FileIO{
public:
    std::size_t getFileSize(std::string path);
    bool readFile(std::string path,char *bufferOut);
    bool writeFile(std::string content,std::string path,std::string fileExtension,std::deque<int> frequencies,std::deque<char> symbols,int offset);
    bool readerHeader(std::string path,std::deque<int> *frequencies, std::deque<char> *symbols,int *offset);
    bool readSymbols(std::string path,std::deque<char>*symbols);
    bool writeDecodedFile(std::string path,std::string content);

};

#endif //HUFFMAN_FILEIO_H
