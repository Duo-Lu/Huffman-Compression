/*      
 *      HTNode class
 *      The Node of HuffmanTree class
 *      
 *      It has 4 main attributs 
 *      Character data -> the object of Character 
 *      HTNode* left -> Binary tree pointer to the left
 *      HTNode* right -> Bianry tree pointer the right
 *      int weight -> the frequency of each Node, recursive defined that weight is frequency of left child and tight child 
 *
 *      Author: Duo Lu, Byeongguk Kwak
 *      Date: Mar 7th
 */

#include "HTNode.h"

// Desc: Default Constructor
HTNode::HTNode()
{
    Character();
    this->left = NULL;
    this->right = NULL;
    weight = 0;
}

// Desc: Non-default Constructor
HTNode::HTNode(Character data , HTNode* left , HTNode* right, int weight)
{
    this->data = data;
    this->left = left;
    this->right = right;
    this->weight = weight;
}

// Desc: Copy Constructor
HTNode::HTNode(const HTNode& node)
{
    this->data = node.data;
    this->left = node.left;
    this->right = node.right;
    this->weight = node.weight;
}

// test for cout 
ostream &operator << (ostream &output , const HTNode &n)
{
    output << n.data.getInputChar() << ":";
    output << n.data.getFrequency() << ":";
    output << n.weight << endl;
    return output;
}

