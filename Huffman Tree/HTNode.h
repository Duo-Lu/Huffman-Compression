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

#include <iostream>
#include "Character.h"

using namespace std;

#pragma once 

class HTNode
{
public:
    Character data;

    HTNode* left;
    HTNode* right;

    // weight is actually the frequency of left child of right child 
    int weight;

    // Desc: Non-default Constructor
    HTNode(Character data , HTNode* left , HTNode* right, int weight);

    // Desc: Default Constructor
    HTNode();

    // Desc: Copy Constructor
    HTNode(const HTNode& node);

    // operator overload 
    bool operator < (const HTNode& n) const { return this->weight < n.weight; }
    bool operator > (const HTNode& n) const { return this->weight > n.weight; }
    bool operator <= (const HTNode& n) const { return this->weight <= n.weight; }
    bool operator >= (const HTNode& n) const { return this->weight >= n.weight; }

    // test for cout 
    friend ostream &operator << (ostream &output , const HTNode &n);

}; // HTNode

