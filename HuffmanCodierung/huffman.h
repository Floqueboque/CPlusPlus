#ifndef HUFFMAN_HEADER
#define HUFFMAN_HEADER

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include "huffmanElement.h"
#include "letter.h"
#include <bitset>
#include <stdlib.h>

using namespace std;

class Huffman
{
private:
	/**
		Anzahl an maximalen Buchstaben des Binaer-Baums
		(ASCII Zeichen)
	*/
	static const int ENCODING_MAX = 127;
	/**
		Blaetter des Baums
	*/
	vector<HuffmanElement *> tree;
	/**
		Oberster Knoten des Binaerbaums
	*/
	HuffmanElement *root;
	/**
		Look-Up-Struktur zum Speichern und Lesen von Blatt-Positionen
	*/
	int *lookup_positions;

public:
	Huffman();
	virtual ~Huffman();
	virtual void build_tree(string text);
	virtual bool *compress(bool *compr_bits_ar, int *count, string text);
	virtual void decompress(string filename, string out_filename);

private:
	string decompress(bool *compr_bits, int count, string filename);
	bool depth_search(char search_node, HuffmanElement *node, vector<bool> *compr_buffer);
	void read_file(string filename, vector<char> *letters);
	void read_file(string filename, vector<Letter> *letters);
};

#endif