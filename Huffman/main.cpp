#include <iostream>
#include "Huffman.h"





int main(int argc, char* argv[]) {

    HuffmanCompressor compressor;

    std::string inputFile = "/home/tfs-/Hacking /HuffmanCompressor/Huffman/text1.txt";
    std::string outputFileName ="/home/tfs-/Hacking /HuffmanCompressor/Huffman/";


    //Printing the lenght of the encoded file.
    std::cout << compressor.encodeFile(inputFile,outputFileName).length() << " bytes";

    compressor.destroyTree();

    return 0;
}