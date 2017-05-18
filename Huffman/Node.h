//
// Created by tfs- on 17/05/17.
//

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <map>
#include <vector>
#include <deque>


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
    void setSymbol(char c);
    void incrementFrequency();
    void incrementFrequency(int value);
    void FillEncondedTable(std::map<char,std::string> *table,std::string bitsValue);
    void showTree();
    friend Node* deserialize(std::deque<int> *frequencies, std::deque<char> *symbols);

    friend void serialize(Node *node, std::deque<int> *frequencies, std::deque<char> *symbols );




};







#endif //HUFFMAN_NODE_H
