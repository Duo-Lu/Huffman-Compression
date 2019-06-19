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

#include "BitStream.h"


// Desc: the core function for Compressing file, read the file again , construct a temporary string_file that contain the long string that
// like that -> 1110001011111, (use the search_encode_table core funtion to get encode information), and then open the binay file, Use core char buffer
// and something about bit shift to make 8 bits char get encode information. like 1110001011111 the first one char could contain 11100010 and put it in 
// binary file. That's the way file get compress. Temporary string file will get deleted
// Pre: the file_name and dest_file_name is valid
// Pos: We get the compress file that named dest_file_name and also have the information about frequency table to reconstruct the tree
void BitStream::CompressFile(const string& file_name , const string& dest_file_name)
{
    this->tree.enqueue_frequency_PQ(file_name);
    this->tree.encode();
    this->tree.fill_encode_table();

    // source file name 
    string str;
    str = file_name;
    ifstream is(str);

    ofstream string_file("string_file.txt" , std::ofstream::binary);

    if (!string_file.is_open())
        cout << "Error opening file";

    if (!is.is_open())
        cout << "Error opening file";
    else
    {
        // read the file again, get encode information and write them to a string file
        char readChar;
        while(is.get(readChar) && !is.eof())
        {
            Character get_c = tree.search_encode_table(readChar);
            string get_codeinfo = get_c.getEncodeInfo();

            string_file << get_codeinfo;
        }
    }

    // close the file 
    is.close();
    string_file.close();
    

    // compress the frequency table into the file, but need to new array that contain what exactly frequency table we want
    int size_of_table = this->tree.getSizeEncodeTable();
    Character* temp_frequency_table = new Character[size_of_table + 1];
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        if (this->tree.getFrequencyCounter()[i].getFrequency() != 0)
        {
            temp_frequency_table[j++] = this->tree.getFrequencyCounter()[i];
        }
    }

    ofstream frequency_file(dest_file_name, std::ofstream::binary);
    
    // put the frequency table into file 
    frequency_file.put(size_of_table);
    frequency_file.write((char*)temp_frequency_table , sizeof(Character) * size_of_table);
    
    ifstream infile ("string_file.txt", std::ifstream::binary);
    
    // corner case 
    if (!infile.is_open())
    {
        cout << "Error opening file";
        return;
    }
    if (!frequency_file.is_open())
    {
        cout << "Error opening file";
        return;
    }

    // convert the string file to binary file 
    char buffer;
    buffer ^= buffer;
    char read_Char;
    int i = 7;
    while(infile.get(read_Char))
    {
        if (read_Char == '1')
            buffer = buffer | (1 << i);
        i--;    
        if (i == -1)
        {
            frequency_file.put(buffer);
            buffer ^= buffer;
            i = 7;
        }
    }
    if (i != -1)
        frequency_file.put(buffer);

    // close the file 
    infile.close();
    frequency_file.close();

    // remove temporary string_file 
    remove ("string_file.txt");
}



// Desc: start function for Decompress, basically just read the file named source_file_name and get the frequency table 
// and then open a temporary file named "decompress_string_file.txt" to store the binary string 
// Pre: the source_file_name is vaild
// Pos: return a frequency table that from decompressed file and put binary string into temporary file 
Character* BitStream::DecompressFile(const string& source_file_name)
{
    ifstream read_frequency_file(source_file_name , std::ifstream::binary);

    if (!read_frequency_file.is_open())
    {
        cout << "Error opening file";
    }

    int size_of_table = 0;
    char c;
    read_frequency_file.get(c);
    size_of_table = c;

    // if frequency is 256, char would be overflow  
    if (size_of_table == 0) 
        size_of_table = 256;
    
    Character* read_Frequency_Table = new Character[size_of_table + 1];   
    
    read_frequency_file.read((char*)read_Frequency_Table , sizeof(Character) * size_of_table);

    string open_file_name = source_file_name;
   
    ofstream outfile ("decompress_string_file.txt", std::ofstream::binary);

    char buffer;
    buffer ^= buffer;

    while(read_frequency_file.get(buffer))
    {
        for (int i = 7; i >= 0 ; i--)
        {
            bool bit = (buffer >> i) & 1;
            if (bit == 0)
                outfile.put('0');
            else
                outfile.put('1');
        }
    }
    outfile.close();
    read_frequency_file.close();


    // return frequency table that size 256
    Character* copy_read_frequency_table = new Character[256];
    int j = 0;
    for (int i = 0; i < size_of_table; i++)
    {
        if (read_Frequency_Table[i].getFrequency() != 0)
        {
            copy_read_frequency_table[j] = read_Frequency_Table[i];
            j++;
        }
    }
    return copy_read_frequency_table;
}


// Desc: we get already get frequency table from the compressed file, and then rebuilt the tree
// Pre: the frequency table is vaild
// Pos: the same HuffmanTree is constructed as we constructed before 
HuffmanTree* BitStream::read_build_tree(Character* frequency_table)
{
    HuffmanTree* rebuilt_tree = new HuffmanTree;
    // PriorityQueue 
    PriorityQueue<HTNode> priority_queue;

    int total = 0;
    for (int i = 0; i < 256; i++)
    {
        if (frequency_table[i].getFrequency() != 0)
            total += frequency_table[i].getFrequency(); 
    }
    
    rebuilt_tree->setFileSize(total); 


    for (int i = 0; i < 256; i++)
    {
        int weight_of_character = frequency_table[i].getFrequency();
        HTNode* newNode = new HTNode(frequency_table[i] , NULL , NULL, weight_of_character);

        if (weight_of_character != 0)
        {
            priority_queue.enqueue(*newNode);
        }
    }

    while(!priority_queue.isEmpty())
    {
        HTNode* newNode = new HTNode;
        HTNode* leftNode = new HTNode(priority_queue.peek().data , priority_queue.peek().left, priority_queue.peek().right , priority_queue.peek().weight);
        newNode->weight += priority_queue.peek().weight;
        newNode->left = leftNode;
        rebuilt_tree->setRoot(newNode);

        priority_queue.dequeue();

        if (priority_queue.isEmpty())
            break;

        HTNode* rightNode = new HTNode(priority_queue.peek().data , priority_queue.peek().left, priority_queue.peek().right , priority_queue.peek().weight);
        newNode->weight += priority_queue.peek().weight;
        newNode->right = rightNode;
        rebuilt_tree->setRoot(newNode);

        priority_queue.dequeue();

        if (priority_queue.isEmpty())
            break;
            
        priority_queue.enqueue(*newNode);
    }
    rebuilt_tree->encode();
    rebuilt_tree->fill_encode_table();

    return rebuilt_tree;
}


// Desc: the core step to reconstruct the characters, actually we get the reconstructed HuffmanTree from rebuilt_tree
// and then we need to travser the tree and convert BitStream to real characters like 111000 -> th
// Pre: the HuffmanTress and dest_file_name is vaild
// Pos: the dest_file_name has been filled, it contains same information as source file 
void BitStream::output_decompress(HuffmanTree* tree , const string& dest_file_name)
{
    ifstream infile ("decompress_string_file.txt" , std::ifstream::binary);
    ofstream outfile (dest_file_name , std::ofstream::binary);

    int file_size = tree->getFileSize();

    if (!infile.is_open())
    {
        cout << "Error opening file" << endl;
    }
    if(!outfile.is_open()) {
        cout << "efe" << endl;
    }
    char c;
    char input_char;
    HTNode* temp_root = tree->getRoot();
    while (infile.get(c) && file_size != 0)
    {
        if (c == '0')
        {
            temp_root = temp_root->left;
            if (temp_root->data.getFrequency() != 0)
            {
                input_char = temp_root->data.getInputChar();
                outfile.put(input_char);
                file_size--;
                temp_root = tree->getRoot();
            }
        }
        else if (c == '1')
        {
            temp_root = temp_root->right;
            if (temp_root->data.getFrequency() != 0)
            {
                input_char = temp_root->data.getInputChar();
                outfile.put(input_char);
                file_size--;
                temp_root = tree->getRoot();
            }
        }
    }

    infile.close();
    outfile.close();

    // "decompress_string_file.txt" is just temporary file for decompress, when decompress done
    // remove the temporary file
    remove("decompress_string_file.txt");
}