/*
 *   Character class
 *
 *   Basically , there are three attributes in one Character
 *   -> char inputChar
 *   -> int frequency
 *   -> string encodeinfo
 *
 *   inputChar decide the what the character it is 
 *   frequency is associated frequency with the character, how many time inputChar show in the file
 *   encodeinfo is when you complete HuffmanTree, do the DFS Algoritms, and decided encode information 
 *
 *   Author: Duo Lu, Byeongguk Kwak
 *   Date: Mar 7th
 */

#include "Character.h"

// default constructor
Character::Character()
{
    this->inputChar = ' ';
    this->frequency = 0;
    this->encodeinfo = "";
}

// non-default constructor
Character::Character(char inputChar, int frequency)
{
    this->inputChar = inputChar;
    this->frequency = frequency;
}

// copy constructor
Character::Character(const Character& obj)
{
    this->inputChar = obj.inputChar;
    this->frequency = obj.frequency;
    this->encodeinfo = obj.encodeinfo;
}

// getter
char Character::getInputChar() const
{
    return this->inputChar;
}

// setter
void Character::setInputChar(const char& c)
{
    this->inputChar = c;
}

// getter
int Character::getFrequency() const
{
    return this->frequency;
}

// setter
void Character::setFrequency(const int& f)
{
    this->frequency = f;
}

// getter
string Character::getEncodeInfo() const
{
    return this->encodeinfo;
}

// setter
void Character::setEnodeInfo(const string& s)
{
    this->encodeinfo = s;
}

// cout the Character object
ostream &operator << (ostream &output , const Character &c)
{
    output << c.getInputChar() << " ";
    output << c.getFrequency() << " ";
    output << c.getEncodeInfo() << endl;
    return output; 
}

