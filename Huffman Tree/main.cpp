/*
 *   The mainline program of encoding and decoding
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
#include "HuffmanTree.h"
#include "BitStream.h"

using namespace std;


// Desc: Caculate the file size
// Pre: the file can be successfully open
// Pos: return the size of file
int size_measure(const string& file_name)
{
    streampos begin,end;
    ifstream myfile (file_name, ios::binary);
    begin = myfile.tellg();
    myfile.seekg (0, ios::end);
    end = myfile.tellg();
    myfile.close();
    return (end-begin);
}


int main(int argc , char* argv[])
{
    if (argc != 4)
    {
        cout << "Please enter the vaild number of parameters! " << endl;
        return 0;
    }

    string argument2_compress_decompress = argv[1];
    string argument3_SourceFile_name = argv[2];
    string argument4_destFile_name = argv[3];

    // corner case test
    ifstream infile_source (argument3_SourceFile_name , std::ifstream::binary);
    
    if (!infile_source.is_open())
    {
        cout << "Error opening file!" << endl;
        return 0;
    }

    // Empty file
    if (infile_source.peek() == ifstream::traits_type::eof())
    {
        cout << "Empty File" << endl;
        return 0;
    }
    infile_source.close();


    BitStream Compress;

    if (argument2_compress_decompress == "-c") 
    {
        Compress.CompressFile(argument3_SourceFile_name , argument4_destFile_name);
        int source_size = size_measure(argument3_SourceFile_name);
        cout << argument3_SourceFile_name << " -> ";
        cout << source_size << " bytes" << endl;

        int dest_size = size_measure(argument4_destFile_name);
        cout << argument4_destFile_name << " -> ";
        cout << dest_size << " bytes" << endl;

        if (source_size < dest_size) 
        {
            cout << "*** Size of compressed file > size of source file ***" << endl;
        }
    }
    else if (argument2_compress_decompress == "-d")
    {
        ifstream infile_dest (argument3_SourceFile_name , std::ifstream::binary);
        if (!infile_dest.is_open())
        {
            cout << "Error opening file!" << endl;
            return 0;
        }
    
        Compress.output_decompress(Compress.read_build_tree(Compress.DecompressFile(argument3_SourceFile_name)) , argument4_destFile_name);
        infile_dest.close();
    } 
    else
    {
        cout << "Please enter the vaild command! " << endl;
        return 0;
    }  
}

