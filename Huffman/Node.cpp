//
// Created by tfs- on 17/05/17.
//



#include "Node.h"
#include <iostream>

#include <iomanip>

#include "Huffman.h"




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

void Node::incrementFrequency(int value) {
    this->frequency += value;
}

void Node::FillEncondedTable(std::map<char,std::string> *table,std::string bitsValue) {
    if(this->isLeaf()){
        table->insert(std::pair<char,std::string>(getSymbol(),bitsValue));
       // std::cout << getSymbol() << " " << bitsValue <<  " " << getFrequency() << std::endl;
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


void Node::showTree() {

    std::cout << "Character: " << this->character << " Frequency: " << this->frequency << std::endl;
    if(left != nullptr) {

        std::cout << "Left" << std::endl;
        left->showTree();
    }
    if(right != nullptr) {
        std::cout << "Right" << std::endl;
        right->showTree();
    }


}

//void serialize(Node *node, std::deque<char> *serialized) {
//    if(node != nullptr){
//
//        if(node->isLeaf()){
//            serialized->push_back('0');
//            serialized->push_back(node->getFrequency());
//            return;
//        }
//
//        if(node->left != nullptr){
//            serialized->push_back('1');
//            serialize(node->left,serialized);
//        }
//
//        if(node->right != nullptr){
//            serialized->push_back('1');
//            serialize(node->right,serialized);
//        }
//    }
//}



//void deserialize(Node *node, std::deque<char> *deserialized) {
//    if(!deserialized->empty()) {
//        if (deserialized->front() == '0') {
//            deserialized->pop_front();
//            node->setSymbol(deserialized->front());
//            deserialized->pop_front();
//            return;
//        }
//
//        std::cout << "Simbolos" << std::endl;
//        for(char c: *deserialized)
//            std::cout <<  c;
//        std::cout << std::endl;
//        if (deserialized->front() == '1') {
//            deserialized->pop_front();
//
//            node->setSymbol('+');
//            node->left = new Node(nullptr, nullptr);
//            node->right = new Node(nullptr, nullptr);
//
//            deserialize(node->getLeft(), deserialized);
//            deserialize(node->getRight(), deserialized);
//        }
//
//
//
//    }
//}





void Node::setSymbol(char c) {
    this->character = c;
}




////
//Node* deserialize(std::deque<int> frequencies, std::deque<char> symbols) {
//
//
//}
//





//std::string Node::serialize() {
//    std::string serialization = "";
//    if(isLeaf()){
//
//        serialization += "0"+getSymbol();
//        return serialization;
//    }
//
//    if(left != nullptr) {
//        left->serialize();
//    }
//    if(right!= nullptr){
//        right->serialize();
//    }
//
//
//}
