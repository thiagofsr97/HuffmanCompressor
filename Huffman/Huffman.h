#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

#include "Node.h"
#include <string>
#include <queue>
#include <map>
#include <vector>
#include "FileIO.h"


//! Structure
/*! This structure is a component of the priority queue collection, defining
 * how the collection will compare its elements. The comparison is made according
 * to the node frequencies, sorting them from the lowest to the highest frequency */

struct node_cmp
{
    bool operator()(Node* a, Node* b ) const
    {
        return a->getFrequency() >= b->getFrequency();
    }
};

//! Typedef Collection.
/*! Definition of a new type of priority queue called FrequencyQueue, which is composed by a vector
 * of Nodes and a comparison function */
typedef std::priority_queue<Node*,std::vector<Node*>,node_cmp> FrequencyQueue;

//!  HuffmanCompressor.
/*!
  Class responsible for all the processes of enconding and compressing a file,
  as well as decoding and decompressing a file.
*/
class HuffmanCompressor{

private:
    Node *root;
    FrequencyQueue createFrequencyTable(char *content,int size);
    void serialize(Node *node, std::deque<int> *frequencies, std::deque<char> *symbols );
    Node* deserialize(std::deque<int> *frequencies, std::deque<char> *symbols);
    Node* createBinaryTree(FrequencyQueue queue);
    std::map<char,std::string> createEncodedMap();

public:
    bool encodeFile(std::string inputFile,std::string outputFilePath);
    bool decodeFile(std::string inputFile,std::string outputFilePath);

};



#endif //HUFFMAN_HUFFMAN_H
