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
        parent->incrementFrequency(parent->getFrequency());


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

    size = file.getFileSize(inputFile);
    content = new char[size];
    std::cout << "Tamanho do arquivo: " << size * 8 << " bytes"<< std::endl;
    file.readFile(inputFile,content);

    //defining the root of the tree


    root = createBinaryTree(createFrequencyTable(content,size));

    std::map<char,std::string> encodedMap = createEncodedMap();
    std::string encondedText;

    std::deque<int> frequencies;
    std::deque<char> symbols;
    serialize(root,&frequencies,&symbols);
    //Enconding new compressed file
    for(int i = 0; i<size;i++){
        encondedText.append(encodedMap.at(content[i]));
    }
    file.writeFile(encondedText,outputFilePath,".tfs",frequencies,symbols,(encondedText.size() % 8));
    //Deallocating space used by chars


    delete content;


    return encondedText;
}

void HuffmanCompressor::destroyTree() {
    //deallocating entire tree

    delete this->root;
}

void HuffmanCompressor::serialize(Node *node, std::deque<int> *frequencies, std::deque<char> *symbols) {
    if(node != nullptr){
        if(node->isLeaf()){
            symbols->push_back(node->getSymbol());
            frequencies->push_back(node->getFrequency());
            return;
        }
        if(node->getLeft() != nullptr)
            serialize(node->getLeft(),frequencies,symbols);
        if(node->getRight()!= nullptr)
            serialize(node->getRight(),frequencies,symbols);
    }

}

Node *HuffmanCompressor::deserialize(std::deque<int> *frequencies, std::deque<char> *symbols) {
    FrequencyQueue queue;
    Node *aux;
    char c;
    int frequency;
    std::map<char,Node*> map;
    while(!frequencies->empty()){
        c = symbols->front();
        symbols->pop_front();
        frequency = frequencies->front();
        frequencies->pop_front();
        aux = new Node(c);
        aux->incrementFrequency(frequency);
        map.insert(std::pair<char,Node*>(c,aux));
    }

    for(auto const& pair:map)
        queue.push(pair.second);

    return createBinaryTree(queue);
}

std::string HuffmanCompressor::decodeFile(std::string inputFile, std::string outputFilePath) {
    Node *root,*current;
    FileIO file;
    int offset;
    std::deque<int> frequencies;
    std::deque<char> symbols;


    file.readerHeader(inputFile,&frequencies,&symbols,&offset);
    root = deserialize(&frequencies,&symbols);
    symbols.clear();
    file.readSymbols(inputFile,&symbols);
    std::string decoded = "";
    int count;
    char c;
    current = root;
   // std::cout << "Size" << symbols.size() << std::endl;
    for(int i = 0; i < symbols.size(); i++){
        c = symbols.at(i);
        if(i == symbols.size() - 1) {
            count = offset;
        }
        else
            count = 8;

        for(int j = 0; j<count; j++){
            if(((c >> j) & 0x01) == 0){
                current = current->getLeft();

                std::cout << 0;
            }
            else {
                current = current->getRight();
                std::cout << 1;
                }
                if(current->isLeaf()){

                decoded += current->getSymbol();

                current = root;
            }

        }
    }

    file.writeDecodedFile(outputFilePath,decoded);

    delete root;
    return decoded;

}

