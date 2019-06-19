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

#include "FrequencyCounter.h"


// Decs: Defalut constructor
// Pos: Initialize the Character_array with size 256
FrequencyCounter::FrequencyCounter()
{
    this->Character_array = new Character[256];
    for (int i = 0; i < 256; i++)
        Character_array[i] = Character(NULL , 0);
    this->elementCounter = 0;
}


// Decs: Destructor
// Pos: Delete the dynamic memory on the heap 
FrequencyCounter::~FrequencyCounter()
{
    delete []Character_array;
}

// Decs: copy constructor
// Pos: this->FrequencyCounter is assigned by frequency
FrequencyCounter::FrequencyCounter(const FrequencyCounter& frequency)
{
    Character* new_arr = new Character[256];
    for (int i = 0; i < 256; i++)
        new_arr[i] = frequency.Character_array[i];
    this->elementCounter = frequency.elementCounter;

    delete [] this->Character_array;

    this->Character_array = new_arr;
}


// Decs: read the input file, the file_name is the third argument from main function, and built the frequency table
// Pre: file_name is a eligile file name 
// Pos: character_array has been fill, built the frequency table 
void FrequencyCounter::read_Input_File(const string& file_name)
{
    // ifstream to open the file 
    string str;
    str = file_name;
    ifstream is(str);

    // When open file fails
    if (!is.is_open())
        cout << "Error opening file";
    // Read the input file, character by character
    else
    {
        char c;
        while(is.get(c) && !is.eof())
        {
            // increase the elementCounter
            elementCounter++;
            // diplay the character, remove after testing 

            int put_position = c + 128;
            if (this->Character_array[put_position].getFrequency() == 0) 
            {
                Character singleReadChar(c , 1);
                this->Character_array[put_position] = singleReadChar;
            }// first time to put new obj with frequency 1
            else
            {
                int temp = Character_array[put_position].getFrequency();
                this->Character_array[put_position].setFrequency(++temp);
            }// if Character is already in, frequency++
            
        }
    }
    
}


// Decs: How many Character objects in the array?
// Pre: the character_array is not empty
// Pos: return how many Character objects in the array
int FrequencyCounter::getElementChar()
{   
    int index = 0;
    for (int i = 0; i < 256; i++)
        if (Character_array[i].getFrequency() != 0)
            index++;
    return index;
}


// getter
Character* FrequencyCounter::get_Character_array() const
{
    return this->Character_array;
}


// Decs: test cout function
void FrequencyCounter::display_character_frequency()
{
    for (int i = 0; i <= 255; i++)
    {
        if (this->Character_array[i].getFrequency() != 0)
        {
            cout << this->Character_array[i].getInputChar() << " ";
            cout << this->Character_array[i].getFrequency() << " ";
            cout << this->Character_array[i].getEncodeInfo() << " ";
            cout << endl;
        }
    }
    cout << this->elementCounter << endl;
}

