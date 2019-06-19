/*
 *      BitStream Class or (InBitStream and OutBitStream classes)
 *      provides operations necessary to read a bit from a file and to write a bit or sequence of bits to a file.
 *
 *      When you compress a file, you read each character in the file, determine its Huffman code (prefix code) and write this code to the compressed file. With reference to the example presented in the Huffman Compression/Decompression Scheme section above,
 *      if the first character in the file to be compressed is a 't', then you want to write the following sequence of bits to the compressed file: 000. 
 *      Similarly when decompressing a file, you want to read successive bits from the compressed file (e.g., 000) and determine the corresponding character, (e.g., 't').
 *
 *      In C++, there is no direct mechanism for reading and writing single bits. Therefore create two new objects: one to write bits to an output file stream and one to read bits from an input file stream.
 *      This class should encapsulate the operations necessary to read or write a bit or sequence of bits to/from a file stream.
 *
 *      Author: Duo Lu, Byeongguk Kwak
 *      Date: Mar 7th  
 * 
 */

#include "PriorityQueue.h"
#include "FrequencyCounter.h"
#include "Character.h"
#include "HTNode.h"
#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <errno.h>
#include <stdlib.h>

using namespace std;

#pragma once 

class BitStream
{
private:
    HuffmanTree tree;
public:
    // Desc: the core function for Compressing file, read the file again , construct a temporary string_file that contain the long string that
    // like that -> 1110001011111, (use the search_encode_table core funtion to get encode information), and then open the binay file, Use core char buffer
    // and something about bit shift to make 8 bits char get encode information. like 1110001011111 the first one char could contain 11100010 and put it in 
    // binary file. That's the way file get compress. Temporary string file will get deleted
    // Pre: the file_name and dest_file_name is valid
    // Pos: We get the compress file that named dest_file_name and also have the information about frequency table to reconstruct the tree
    void CompressFile(const string& file_name, const string& dest_file_name);


    // Desc: start function for Decompress, basically just read the file named source_file_name and get the frequency table 
    // and then open a temporary file named "decompress_string_file.txt" to store the binary string 
    // Pre: the source_file_name is vaild
    // Pos: return a frequency table that from decompressed file and put binary string into temporary file 
    Character* DecompressFile(const string& source_file_name);


    // Desc: we get already get frequency table from the compressed file, and then rebuilt the tree
    // Pre: the frequency table is vaild
    // Pos: the same HuffmanTree is constructed as we constructed before 
    HuffmanTree* read_build_tree(Character* frequency_table);


    // Desc: the core step to reconstruct the characters, actually we get the reconstructed HuffmanTree from rebuilt_tree
    // and then we need to travser the tree and convert BitStream to real characters like 111000 -> th
    // Pre: the HuffmanTress and dest_file_name is vaild
    // Pos: the dest_file_name has been filled, it contains same information as source file 
    void output_decompress(HuffmanTree* tree , const string& dest_file_name);
};

