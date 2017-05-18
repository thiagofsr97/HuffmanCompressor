//
// Created by tfs- on 17/05/17.
//

#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

#include "Node.h"
#include <string>
#include <queue>
#include <map>
#include <vector>
#include "FileIO.h"


//Struct used to work as a comparator function to Node objects, comparing
//their frequencies.
struct node_cmp
{
    bool operator()(Node* a, Node* b ) const
    {
        return a->getFrequency() >= b->getFrequency();
    }
};

//Defining a Frequency Queue of Nodes
typedef std::priority_queue<Node*,std::vector<Node*>,node_cmp> FrequencyQueue;

class HuffmanCompressor{

private:
    Node *root;
    FrequencyQueue createFrequencyTable(char *content,int size);

    std::map<char,std::string> createEncodedMap();

public:
    Node* createBinaryTree(FrequencyQueue queue);
    std::string encodeFile(std::string inputFile,std::string outputFilePath);
    //std::string decodeFile(std::string inputFile,std::string outputFilePath);

    void destroyTree();
};



#endif //HUFFMAN_HUFFMAN_H
