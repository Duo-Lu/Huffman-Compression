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

#include "HuffmanTree.h"

// Desc: Constructor 
// Pos: encode table has been filled  
HuffmanTree::HuffmanTree()
{
    this->size_of_encode_table = 0;
    this->encode_table = new Character[256];
    this->root = NULL;
    int fileSize = 0;
}


// Desc: Destructor 
// Pos: use local private helper funtion to delete the HuffmanTree and free encode_table memory
HuffmanTree::~HuffmanTree()
{
    delete [] encode_table;
    this->delete_tree(this->root);
}


// Desc: getter
// Pos: return pointer to the Character_array
Character* HuffmanTree::getFrequencyCounter() const
{
    return this->frequency_table.get_Character_array();
}


// Desc: free the dynamic HTNode (new) in the heap
// Pre: the tree is not empty
// Pos: the dynamic memeory has been free
void HuffmanTree::delete_tree(HTNode* root)
{
    if (root == NULL)   return;

    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}


// Desc: The core step of the whole HuffmanTree class , it's actually use the priority_queue and built the class
// get the file_name(the 3rd argument) and built the frequency table. Each time you get a character object, it will 
// generate the HTNode and enqueue all the HTNode, and then do the Algorithm as Assignment show
// Pre: the file_name is vaild and the priority_queue is empty
// Pos: the HuffmanTree has been constructed, each HTNode include its Character obj and weight
void HuffmanTree::enqueue_frequency_PQ(const string& file_name)
{
    // PriorityQueue 
    PriorityQueue<HTNode> priority_queue;

    // get frequency_table
    frequency_table.read_Input_File(file_name);

    int elementChar = frequency_table.getElementChar();


    for (int i = 0; i < 256; i++)
    {
        int weight_of_character = frequency_table.get_Character_array()[i].getFrequency();
        HTNode* newNode = new HTNode(frequency_table.get_Character_array()[i] , NULL , NULL, weight_of_character);

        if ( weight_of_character != 0 )
        {
            // enqueue all the node
            priority_queue.enqueue(*newNode);
        }
    }

    
    while(!priority_queue.isEmpty())
    {
        HTNode* newNode = new HTNode;
        HTNode* leftNode = new HTNode(priority_queue.peek().data , priority_queue.peek().left, priority_queue.peek().right , priority_queue.peek().weight);
        newNode->weight += priority_queue.peek().weight;
        newNode->left = leftNode;
        this->root = newNode;

        priority_queue.dequeue();

        // check if the priority_queue is empty, and then the last node you dequeue is the root
        // but actually this->root = node you just dequeue, no need to set the root 
        if (priority_queue.isEmpty())
            return;

        HTNode* rightNode = new HTNode(priority_queue.peek().data , priority_queue.peek().left, priority_queue.peek().right , priority_queue.peek().weight);
        newNode->weight += priority_queue.peek().weight;
        newNode->right = rightNode;
        this->root = newNode;

        priority_queue.dequeue();

        // every time you dequeue, you should check 
        if (priority_queue.isEmpty())
            return;

        // enqueue the new node has the new weight    
        priority_queue.enqueue(*newNode);
    }
    return;
}


// Desc: Using Deapth First Search to encode every character in the Character_array
// This funtion is exactly decide like h-> 000 t-> 111 something like this
// Pre: the tree is not empty
// Pos: Each encodeinfo attributes has been filled
void HuffmanTree::DFS_encode_char(HTNode* root, string encodeinfo)
{
    if (root->left == NULL && root->right == NULL)  
    {
        root->data.setEnodeInfo(encodeinfo);
        return;
    }

    if (root->left)
        DFS_encode_char(root->left , encodeinfo + "0");

    if (root->right)
        DFS_encode_char(root->right , encodeinfo + "1");
}


// Desc: print the encode table 
// Pre: the encode table is not empty
// Pos: travser the encode table array and print the information 
void HuffmanTree::display_tree(HTNode* root)
{
    if (root == NULL)   return;

    if (root->data.getFrequency() != 0)
        cout << root->data << endl;
    display_tree(root->left);
    display_tree(root->right);
}


// Desc: Allowcate a new Character array that has exactly same size as how many different characters in the source file
// Pre: the tree is not empty
// Pos: the encode table has been filled 
void HuffmanTree::fill_encode_table(HTNode* root , int& i)
{
    if (root == NULL)   return;

    if (root->data.getFrequency() != 0)
    {
        this->encode_table[i] = root->data;
        i++;
    }

    fill_encode_table(root->left , i);
    fill_encode_table(root->right, i);
}


// Desc: print the encode table 
// Pre: the encode table is not empty
// Pos: travser the encode table array and print the information 
void HuffmanTree::display_encode_table(Character* encode_table)
{
    cout << endl;
    for (int i = 0; i < size_of_encode_table; i++)
        cout << this->encode_table[i] << endl;
}


// Desc: the core step for BitStream, search the encode_table and then get the encode information of Character object
// like when you in your BitStream class, read h, this funtion is to search encode table, and then return object contain that
// information, also Character obj has a attribute contain encodeinfo
// Pre: the encode_table is not empty
// Pos: return the Character object that contain the char c 
Character HuffmanTree::search_encode_table(char c)
{
    for (int i = 0; i < size_of_encode_table; i++)
    {
        if (this->encode_table[i].getInputChar() == c)
            return this->encode_table[i];
    }
    return Character();
}

// getter
FrequencyCounter HuffmanTree::getFrequencyTable() const
{
    return this->frequency_table;
}

// getter
int HuffmanTree::getSizeEncodeTable() const
{
    return this->size_of_encode_table;
}

// getter
Character* HuffmanTree::getEncodeTable() const
{
    return this->encode_table;
}

int HuffmanTree::getFileSize() const {
    return fileSize;
}

void HuffmanTree::setFileSize(int i) {
    fileSize = i;
}
