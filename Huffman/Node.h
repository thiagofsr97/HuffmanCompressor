#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <map>
#include <vector>
#include <deque>

//! Node Class.
/*!
  Class responsible for representing a node of a tree. Its goal is to
  support creation of the Huffman Tree.
*/
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





};







#endif //HUFFMAN_NODE_H
