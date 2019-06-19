/*
 *   HuffmanTree Class
 *   provides operations to build/rebuild the Huffman tree, to compute the code word of a given character, and to derive the character given a code word.
 * 
 *   This class is responsible for ensuring that the appropriate information (needed to rebuild the Huffman tree) is written to the compressed file (when compressing). 
 *   It is also responsible for gathering information necessary to rebuild the Huffman tree from the compressed file (when decompressing).
 * 
 *   Think carefully about what kind of information you will be using to reconstruct the Huffman tree. You must select information that requires a minimum amount of space.
 *   There is little point coming up with an elaborate compression scheme if the additional information written to the file (so that it can be decompressed) takes up an inordinate amount of space!
 *   The simplest approach is to write each character found in the original file along with its frequency count, i.e., the frequency table. This is enough information to allow you to re-construct the Huffman tree and determine the Huffman prefix code for each character.
 *   This is not necessarily the most efficient approach — feel free to investigate alternatives!
 * 
 *   Author: Duo Lu, Byeongguk Kwak
 *   Date: Mar 7th  
 */

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "PriorityQueue.h"
#include "FrequencyCounter.h"
#include "Character.h"
#include "HTNode.h"

#pragma once 

class HuffmanTree
{
private:

    // The root of the tree
    HTNode* root;

    // frequency_table
    FrequencyCounter frequency_table;

    // the size of encode_table is 256, but we use only what we need to use
    Character* encode_table;

    // the size of encode table, decide how the encode_table size
    int size_of_encode_table;

    int fileSize;

    // Desc: Using Deapth First Search to encode every character in the Character_array
    // This funtion is exactly decide like h-> 000 t-> 111 something like this
    // Pre: the tree is not empty
    // Pos: Each encodeinfo attributes has been filled
    void DFS_encode_char(HTNode* root, string encodeinfo);

    // Desc: Helper test funtion, travser the tree and display the information in every node
    // Character obj and HTNode has already been overloaded
    // pre: the tree is not empty
    // Pos: display the informaition of each node, Pre-order travser
    void display_tree(HTNode* root);

    // Desc: free the dynamic HTNode (new) in the heap
    // Pre: the tree is not empty
    // Pos: the dynamic memeory has been free
    void delete_tree(HTNode* root);

    // Desc: Allowcate a new Character array that has exactly same size as how many different characters in the source file
    // Pre: the tree is not empty
    // Pos: the encode table has been filled 
    void fill_encode_table(HTNode* root , int& i);

    // Desc: print the encode table 
    // Pre: the encode table is not empty
    // Pos: travser the encode table array and print the information 
    void display_encode_table(Character* encode_table);


public:

    // Desc: Constructor 
    // Pos: encode table has been filled  
    HuffmanTree();

    // Desc: Destructor 
    // Pos: use local private helper funtion to delete the HuffmanTree and free encode_table memory
    ~HuffmanTree();


    // Desc: The core step of the whole HuffmanTree class , it's actually use the priority_queue and built the class
    // get the file_name(the 3rd argument) and built the frequency table. Each time you get a character object, it will 
    // generate the HTNode and enqueue all the HTNode, and then do the Algorithm as Assignment show
    // Pre: the file_name is vaild and the priority_queue is empty
    // Pos: the HuffmanTree has been constructed, each HTNode include its Character obj and weight
    void enqueue_frequency_PQ(const string& file_name);

    // Use local private helper function DFS_encode_char()
    void encode() { this->DFS_encode_char(this->root , ""); }

    // Use local private helper funtion display_tree()
    void display() { this->display_tree(this->root); }

    // Use local private helper funtion fill_encode_table()
    void fill_encode_table() { this->fill_encode_table(this->root , size_of_encode_table); }

    // use local private helper funtion display_encode_table()
    void display_encode_table() { this->display_encode_table(this->encode_table); }

    // Desc: the core step for BitStream, search the encode_table and then get the encode information of Character object
    // like when you in your BitStream class, read h, this funtion is to search encode table, and then return object contain that
    // information, also Character obj has a attribute contain encodeinfo
    // Pre: the encode_table is not empty
    // Pos: return the Character object that contain the char c 
    Character search_encode_table(char c);

    // Desc: getter
    // Pos: return pointer to the Character_array
    Character* getFrequencyCounter() const;

    // setter
    void setRoot(HTNode* root) { this->root = root; }

    // getter
    HTNode* getRoot() const { return this->root; }

    // getter
    FrequencyCounter getFrequencyTable() const;

    // getter
    int getSizeEncodeTable() const;

    //getter
    Character* getEncodeTable() const;

    int getFileSize() const;

    void setFileSize(int i);

};

