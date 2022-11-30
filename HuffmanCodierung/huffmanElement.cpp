/**	@file huffmanElement.cpp Verwalten von Huffman-Knoten und -Blaettern

	@author		- Florian Glaser, Florian Herkommer
	@version	- 1.0
	@date		- 22.02.2022
*/

#include "huffmanElement.h"

int HuffmanElement::count_nodes = 1;
int HuffmanElement::longest_code = 0;

/**	Erzeugt einen leeren Knoten.
 *	Reserviert Speicher fuer 30 Lookup-Bits.
 */
HuffmanElement::HuffmanElement()
{
	left = 0;
	right = 0;
	parent = 0;
	name = 0;
	letter = -1;
	value = 0;
	is_right = false;
	lookup_code = new bool[30];
	lookup_code_length = 0;
}

/**	Erzeugt ein Blatt mit Buchstaben und deren Anzahl.
 *	Reserviert Speicher fuer 30 Lookup-Bits.
 *
 *   @param cur_letter Buchstabe
 *	@param cur_value Anzahl
 */
HuffmanElement::HuffmanElement(char cur_letter, int cur_value) : letter(cur_letter), value(cur_value)
{
	left = 0;
	right = 0;
	name = 0;
	is_right = false;
	parent = 0;
	lookup_code = new bool[30];
	lookup_code_length = 0;
}

/**	Erzeugt einen Knoten mit linkem und rechtem Nachfolger, sowie einem Wert,
 *	der die Wertigkeit des aktuellen Asts angibt.
 *	Reserviert Speicher fuer 30 Lookup-Bits.
 *
 *   @param cur_left linker Nachfolger
 *	@param cur_right rechter Nachfolger
 *	@param cur_value Wert des Asts
 */
HuffmanElement::HuffmanElement(HuffmanElement *cur_left, HuffmanElement *cur_right, int cur_value) : left(cur_left), right(cur_right), value(cur_value)
{
	letter = -1;
	name = count_nodes;
	count_nodes++;
	is_right = false;
	parent = 0;
	lookup_code = new bool[30];
	lookup_code_length = 0;
}

/**	Gibt alle Speicherbereiche des Knotens/Blatt frei.
 */
HuffmanElement::~HuffmanElement()
{
	delete_huffman_element();
}

/**	Zuweisungsoperator zum Kopieren/Zuweisen eines Knotens/Blatts.
 *
 *   @param original zuzuweisender Knoten/Blatt
 *   @returns Referenz auf den neuen Knoten/Blatt
 */
HuffmanElement &HuffmanElement::operator=(const HuffmanElement &original)
{
	copy_huffman_element(original);
	return *this;
}

/**	ueberladung des > Operator ermoeglicht den Vergleich von Knoten/Blaettern.
 *	Knoten/Blaetter mit großem Wert sind groesser als Knoten/Blaettern mit
 *	kleinem Wert.
 *
 *   @param compare zu vergleichender Knoten
 *   @returns 0, wenn der aktuelle Knoten nicht groesser ist, sonst ist er groesser
 */
bool HuffmanElement::operator>(const HuffmanElement &compare) const
{
	return (value > compare.get_value());
}

/**	Liefert den aktuellen Buchstaben.
 *
 *   @returns Buchstabe
 */
char HuffmanElement::get_letter() const
{
	return letter;
}

/**	Liefert den aktuellen Wert (Wertigkeit des aktuellen Asts)
 *
 *   @returns Wertigkeit
 */
int HuffmanElement::get_value() const
{
	return value;
}

/**	Liefert den Namen des Knotens (Nummer)
 *
 *   @returns Namens-ID
 */
int HuffmanElement::get_name() const
{
	return name;
}

/**	Gibt an, ob der aktuelle Knoten/Blatt ein
 *	rechter oder linker Nachfolger ist.
 *
 *   @returns 0, wenn es ein linker Nachfolger ist, sonst ist es ein rechter Nachfolger
 */
bool HuffmanElement::get_is_right() const
{
	return is_right;
}

/**	Liefert den uebergeordneten Knoten.
 *
 *   @returns uebergeordneter Knoten
 */
HuffmanElement *HuffmanElement::get_parent()
{
	return parent;
}

/**	Liefert den linken Nachfolger.
 *
 *   @returns linker Nachfolger
 */
HuffmanElement *HuffmanElement::get_left()
{
	return left;
}

/**	Liefert den rechten Nachfolger.
 *
 *   @returns rechter Nachfolger
 */
HuffmanElement *HuffmanElement::get_right()
{
	return right;
}

/**	Liefert den Lookup-Code des aktuellen Blatts.
 *
 *    @returns Lookup-Bit-Code
 */
bool *HuffmanElement::get_lookup_code()
{
	return lookup_code;
}

/**	Liefert die Laenge des Lookup-Codes des aktuellen Blatts.
 *
 *	@returns Laenge des Lookup-Bit-Codes
 */
unsigned int HuffmanElement::get_lookup_code_length() const
{
	return lookup_code_length;
}

/**	Legt den uebergeordneten Knoten fest und bestimmt, ob der aktuelle Knoten/Blatt
 *	ein linker oder rechter ist.
 *
 *	@param cur_parent uebergeordneter Knoten
 *	@param cur_is_right 0, wenn es ein linker Nachfolger ist, sonst ist es ein rechter Nachfolger
 */
void HuffmanElement::set_parent(HuffmanElement *cur_parent, bool cur_is_right)
{
	parent = cur_parent;
	is_right = cur_is_right;
	add_lookup_code(cur_is_right);
}

/**	Fuegt ein uebergebenes Bit zum eigenen Lookup-Code hinzu und macht
 *	dies auch fuer alle Nachfolger des aktuellen Knotens.
 *
 *	@param code hinzuzufuegendes Bit
 */
void HuffmanElement::add_lookup_code(bool code)
{
	lookup_code[lookup_code_length] = code;
	++lookup_code_length;
	if (longest_code < lookup_code_length)
	{
		longest_code = lookup_code_length;
	}

	if (left != 0)
	{
		left->add_lookup_code(code);
	}
	if (right != 0)
	{
		right->add_lookup_code(code);
	}
}

/**	Liefert die Laenge des laengsten Lookup-Codes.
 *
 *	@returns Anzahl an Stellen des laengsten Lookup-Codes
 */
int HuffmanElement::get_longest_code()
{
	return longest_code;
}

/**	Kopiert einen Knoten/Blatt.
 *
 *	@param original zu kopierender Knoten/Blatt
 */
void HuffmanElement::copy_huffman_element(const HuffmanElement &original)
{
	if (this != &original)
	{
		delete_huffman_element();

		left = original.left;
		right = original.right;
		parent = original.parent;
		name = original.name;
		letter = original.letter;
		value = original.value;
		is_right = original.is_right;
		lookup_code = original.lookup_code;
	}
}

/**	Gibt alle Speicherbereiche des aktuellen Knotens frei.
 */
void HuffmanElement::delete_huffman_element()
{
	if (left != 0)
	{
		delete left;
	}
	if (right != 0)
	{
		delete right;
	}
	if (lookup_code != 0)
	{
		delete[] lookup_code;
	}
}