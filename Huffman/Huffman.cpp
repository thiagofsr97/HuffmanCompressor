//
// Created by tfs- on 17/05/17.
//

#include "Huffman.h"
#include <iostream>
#include <cstring>


FrequencyQueue HuffmanCompressor::createFrequencyTable(char *character,int size) {

    //This map organize and increments frequencies of the characters, putting them in nodes, in order to
    //create the tree
    std::map<char,Node*> mapped;

    //Veryfing all the characters and counting how many times they appear in the file
    for(int i = 0; i < size; i++){
        if(mapped.count(character[i]) == 0) // if key is not present at the map, returns 0
            mapped.insert(std::pair<char, Node *>(character[i], new Node(character[i])));

        //if key already exits, increments its frequency by one
        mapped.at(character[i])->incrementFrequency();
    }

    std::cout << "Tamanho da tabela de frequencia: " << mapped.size() <<  std::endl;


    //Inserting the nodes in the Frequency Queue, which sort them automatically
    FrequencyQueue queue;

    std::cout << "Tabela de frequencia: " << std::endl;
    for(auto const& pair:mapped){
        queue.push(pair.second);
        std::cout << pair.second->getSymbol();
    }
    std::cout << std::endl;

    return queue;
}

Node* HuffmanCompressor::createBinaryTree(FrequencyQueue queue) {
    Node *first, *second;
    Node *parent;

    while(true){

        //Getting the two first nodes with lower frequencies and organizing them into a parent Node
        if(queue.empty())
            first = nullptr;
        else
            first = queue.top();

        if(!queue.empty()) queue.pop();

        if(queue.empty())
            second = nullptr;
        else
            second = queue.top();
        if(!queue.empty()) queue.pop();

        parent = new Node(first,second);

        //if the queue is empty, it means that the grouping has reached the end, leaving the two left
        //nodes to be put into the root node;
        if(queue.empty())
            return parent;

        queue.push(parent);
    }


}

std::map<char,std::string> HuffmanCompressor::createEncodedMap() {
    std::map<char,std::string> table;
    std::cout << "Simbolo e bytes associados: " <<std::endl;
    if(root!= nullptr)
        root->FillEncondedTable(&table,"");
    return table;
}

std::string HuffmanCompressor::encodeFile(std::string inputFile, std::string outputFilePath) {
    FileIO file;
    char* content;
    size_t size;
   // std::cout << size <<std::endl;
    size = file.getFileSize(inputFile);
    content = new char[size];
    std::cout << "Tamanho do arquivo: " << size * 8 << " bytes"<< std::endl;
    file.readFile(inputFile,content);


    //std::vector<char> letters = toChar(content,size);

    //defining the root of the tree


    root = createBinaryTree(createFrequencyTable(content,size));

    std::map<char,std::string> encodedMap = createEncodedMap();

    std::string encondedText;

    //Enconding new compressed file
    for(int i = 0; i<size;i++){
        encondedText.append(encodedMap.at(content[i]));
    }
    //std::cout << encondedText.size();

    file.writeFile(encondedText.c_str(),encondedText.size(),outputFilePath,"file.tfs");



    //Deallocating space used by char
    delete content;

    return encondedText;
}

void HuffmanCompressor::destroyTree() {
    //deallocating entire tree

    delete this->root;
}
