//
// Created by tfs- on 17/05/17.
//



#include "Node.h"
#include <iostream>


Node::Node(char character) {
    this->left = nullptr;
    this->right = nullptr;
    this->character = character;
    this->frequency = 0;
}



Node::Node(Node *left, Node *right) {
    this->left = left;
    this->right = right;
    this->character = '+';
    this->frequency = 0;

}

Node::~Node() {
    delete this->left;
    delete this->right;
}

int Node::getFrequency(){
    if(this->isLeaf())
        return this->frequency;

    return this->left->getFrequency() + this->right->getFrequency();

}

bool Node::isLeaf() {
    return (this->right == nullptr && this->left == nullptr);
}

Node* Node::getLeft() {
    return this->left;
}

Node* Node::getRight() {
    return this->right;
}

void Node::incrementFrequency() {
    this->frequency++;
}

void Node::FillEncondedTable(std::map<char,std::string> *table,std::string bitsValue) {
    if(this->isLeaf()){
        table->insert(std::pair<char,std::string>(getSymbol(),bitsValue));
        std::cout << getSymbol() << " " << bitsValue <<  " " << getFrequency() << std::endl;
        return;
    }

    if(left != nullptr);
        left->FillEncondedTable(table,bitsValue + "0");

    if(right!= nullptr)
        right->FillEncondedTable(table,bitsValue + "1");

}

char Node::getSymbol() {
    return this->character;
}
