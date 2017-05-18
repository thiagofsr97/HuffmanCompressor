//
// Created by tfs- on 17/05/17.
//

#ifndef HUFFMAN_FILEIO_H
#define HUFFMAN_FILEIO_H

#include <string>

class FileIO{
public:
    std::size_t getFileSize(std::string path);
    bool readFile(std::string path,char *bufferOut);
    bool writeFile(std::string content,std::string path,std::string fileExtension);






};

#endif //HUFFMAN_FILEIO_H
