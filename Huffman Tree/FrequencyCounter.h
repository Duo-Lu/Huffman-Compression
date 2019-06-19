/* 
 *   FrequencyCounter class 
 *   To build and manipulate a frequency table that stores the frequency with which a char appears in a file.
 * 
 *   In order to build the Huffman tree, you need to determine the frequency with which a char (8 bits) appears in the file to be compressed.
 *   There are a total of 256 possibilities. 
 * 
 *   Author: Duo Lu, Byeongguk Kwak
 *   Date: Mar 7th
 */

#include "Character.h"
#include "PriorityQueue.h"
#include "Character.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#pragma once

class FrequencyCounter
{
private:
    // Character_array to store Character obj
    Character* Character_array;
    int elementCounter;
    
public:


    // Decs: Defalut constructor
    // Pos: Initialize the Character_array with size 255
    FrequencyCounter();


    // Decs: copy constructor
    // Pos: this->FrequencyCounter is assigned by frequency
    FrequencyCounter(const FrequencyCounter& frequency);


    // Decs: Destructor
    // Pos: Delete the dynamic memory on the heap 
    ~FrequencyCounter();


    // Decs: read the input file, the file_name is the third argument from main function, and built the frequency table
    // Pre: file_name is a eligile file name 
    // Pos: character_array has been fill, built the frequency table 
    void read_Input_File(const string& file_name);


    // Decs: How many Character objects in the array?
    // Pre: the character_array is not empty
    // Pos: return how many Character objects in the array
    int getElementChar();
    

    // Decs: test cout function
    void display_character_frequency();


    // getter
    Character* get_Character_array() const;
};

