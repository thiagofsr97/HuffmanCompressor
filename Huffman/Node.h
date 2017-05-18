//
// Created by tfs- on 17/05/17.
//

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <map>
class Node{

private:
    char character;
    int frequency;
    Node* left;
    Node* right;

public:
    Node(Node* left, Node* right);
    Node(char character);
    ~Node();
    bool isLeaf();
    int getFrequency();
    char getSymbol();
    Node* getLeft();
    Node* getRight();
    void incrementFrequency();
    void FillEncondedTable(std::map<char,std::string> *table,std::string bitsValue);

};







#endif //HUFFMAN_NODE_H
