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

#include <iostream>
#include <string>

using namespace std;

#pragma once


class Character
{
private:
    char inputChar;         // what char type it is 
    int frequency;          // Assocated frequency
    string encodeinfo;      // encode information when you have built Huffman Tree
public:
    // default constructor
    Character();

    // non-default constructor
    Character(char inputChar, int frequency);

    // copy constructor
    Character(const Character& obj);
    char getInputChar() const;          // getter
    void setInputChar(const char& c);   // setter
    int getFrequency() const;           // getter
    void setFrequency(const int& f);    // setter
    string getEncodeInfo() const;       // getter
    void setEnodeInfo(const string& s); // setter

    // operator overload
    bool operator < (const Character& cr) const { return this->frequency < cr.frequency; }
    bool operator > (const Character& cr) const { return this->frequency > cr.frequency; }
    bool operator <= (const Character& cr) const { return this->frequency <= cr.frequency; }
    bool operator >= (const Character& cr) const { return this->frequency >= cr.frequency; }

    // cout the Character object
    friend ostream &operator << (ostream &output , const Character &c);

};

