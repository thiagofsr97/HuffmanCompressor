#include <iostream>
#include "Huffman.h"





int main(int argc, char* argv[]) {

    HuffmanCompressor compressor;

    std::string inputFile = "/home/tfs-/Hacking/ED Project/HuffmanCompressor/Huffman/text.txt";
    std::string outputFileName ="/home/tfs-/Hacking/ED Project/HuffmanCompressor/Huffman/";


    compressor.encodeFile(inputFile,outputFileName + "Convict");
    compressor.decodeFile(outputFileName + "Convict.tfs",outputFileName + "extracted.txt");

    compressor.destroyTree();

    return 0;
}