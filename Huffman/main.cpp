#include <iostream>
#include "Huffman.h"

/**
    Universidade Federal da Paraíba - UFPB
    Data Structure Discipline - Professor: Tiago Maritan
    Huffman Compressor Project
    Colaborators Students:
     - Thiago Filipe Soares da Rocha
     - João Vinícius Gomes de Lima
     - Fernando Alves Maximo
     - João Vitor Oliveira dos Anjos
     - Deborah de Jesus P. Viana

    @version 1.0 5/25/17
*/

int main(int argc, char* argv[]) {

    if(argc != 4){
        std::cout << "Wrong arguments, please try again..." << std::endl;
        exit(0);
    }
    HuffmanCompressor compressor;
    std::string command = argv[1];

    if(command == "-c")
        compressor.encodeFile(argv[2],argv[3]);
    else if(command == "-e")
        compressor.decodeFile(argv[2],argv[3]);
    else {
        std::cout << "Wrong arguments, please try again." << std::endl;
        exit(0);
    }
    return 0;
}