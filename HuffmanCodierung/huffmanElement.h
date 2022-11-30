#ifndef HUFFMAN_ELEMENT_HEADER
#define HUFFMAN_ELEMENT_HEADER

#include <list>

using namespace std;

/**
	Klasse zum Verwalten von Huffman-Knoten und -Blaettern
*/
class HuffmanElement
{
private:
	/**
		Anzahl der Gesamtknoten
	*/
	static int count_nodes;
	/**
		Groesse des laengsten Lookup-Codes
	*/
	static int longest_code;
	/**
		Name des Knotens
	*/
	int name;
	/**
		Buchstabe des Blatts
	*/
	char letter;
	/**
		Linker Ast
	*/
	HuffmanElement *left;
	/**
		Rechter Ast
	*/
	HuffmanElement *right;
	/**
		Wert des Asts
	*/
	int value;
	/**
		Uebergeordneter Knoten
	*/
	HuffmanElement *parent;
	/**
		true -> rechter Ast, false -> linker Ast
	*/
	bool is_right;
	/**
		Binaer-Code des Knotens/Blatts
	*/
	bool *lookup_code;
	/**
		Laenge des Binaer-Codes des Knotens/Blatts
	*/
	unsigned int lookup_code_length;

public:
	HuffmanElement();
	HuffmanElement(char cur_letter, int cur_value);
	HuffmanElement(HuffmanElement *cur_left, HuffmanElement *cur_right, int cur_value);
	virtual ~HuffmanElement();
	virtual HuffmanElement &operator=(const HuffmanElement &original);
	virtual bool operator>(const HuffmanElement &compare) const;
	virtual char get_letter() const;
	virtual int get_value() const;
	virtual int get_name() const;
	virtual bool get_is_right() const;
	virtual HuffmanElement *get_parent();
	virtual HuffmanElement *get_left();
	virtual HuffmanElement *get_right();
	virtual bool *get_lookup_code();
	virtual unsigned int get_lookup_code_length() const;
	virtual void set_parent(HuffmanElement *cur_parent, bool cur_is_right);
	virtual void add_lookup_code(bool code);
	virtual int get_longest_code();

private:
	void copy_huffman_element(const HuffmanElement &original);
	void delete_huffman_element();
};

/**
	Comparator zum Vergleichen von Knoten/Blaettern
*/
struct compareCharacters
{
	bool operator()(HuffmanElement *left, HuffmanElement *right)
	{
		return *left > *right;
	}
};

#endif