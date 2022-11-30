#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "huffman.h"
using namespace std;

int print_menue();
string read_filename(bool exist);
bool *compress_file(Huffman *huffman_compr, bool *compr_bits, int *count);
void save_compression(bool *compr_bits, int length);
void save_decompression(Huffman *huffman_compr);
void build_tree(Huffman *huffman_compr, string filename);

#endif