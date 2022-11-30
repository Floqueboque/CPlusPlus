#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include "main.h"
using namespace std;

int main(int argc, char *argv[])
{
	Huffman *huffman_compr = new Huffman();
	vector<bool> cur_compression;
	bool *compr_bits = 0;
	int count_bits = 0;
	int selection;
	do
	{
		selection = print_menue();
		switch (selection)
		{
		case 1:
			compr_bits = compress_file(huffman_compr, compr_bits, &count_bits);
			save_compression(compr_bits, count_bits);
			break;
		case 2:
			save_decompression(huffman_compr);
			break;
		}

		cout << endl
			 << endl;
	} while (selection != 3);

	return 0;
}

/**
 * Fragt den User welche Funktion er verwenden moechte
 *
 * @return int 0 -> Komprimieren 1 -> dekomprimieren 3 -> Beenden
 */
int print_menue()
{
	int result;

	cout << "Bitte waehle eine Funktion:" << endl;
	cout << endl;
	cout << "[1] Datei komprimieren und speichern" << endl;
	cout << "[2] Datei dekomprimieren und speichern" << endl;
	cout << "[3] Beenden" << endl;
	cout << endl;

	cout << "Eingabe: ";
	cin >> result;
	cout << endl;

	return result;
}

/**
 *	Fragt nach einem Dateinamen, liest ihn ein und prueft, ob die
 *	Datei existiert (muss aber nicht existieren, siehe param exist)
 *
 *	@param exist False wenn die Datei nicht existieren muss
 *	@returns eingelesener Dateiname
 */
string read_filename(bool exist)
{
	string filename;
	do
	{
		cout << "Bitte geben Sie einen Dateinamen ein: ";
		cin >> filename;

		ifstream check_file(filename);
		if (exist && !check_file)
		{
			cout << "Diese Datei existiert nicht." << endl;
			filename = "";
		}
		else
		{
			filename = filename;
		}
	} while (filename == "" && exist);

	return filename;
}

/**
 * Komprimiert eine Datei mithilfe von Huffman
 *
 * @param huffman_compr Huffman Objekt was die Komprimierung durchfuehrt
 * @param compr_bits Zeiger auf bool, welches die kompremierte Datei spaeter beinhaltet
 * @param count Laenge der kompremmierten Datei
 * @return compr_bits
 */
bool *compress_file(Huffman *huffman_compr, bool *compr_bits, int *count)
{
	cout << "Zu komprimierende Datei:" << endl;
	string compr_file = read_filename(true);

	huffman_compr->build_tree(compr_file);
	compr_bits = huffman_compr->compress(compr_bits, count, compr_file);

	return compr_bits;
}

/**	Speichert die uebergebenen Bits in einer Datei.
 *
 *	@param compr_bits zu speichernde Bits
 *	@param length laenge von compr_bits
 */
void save_compression(bool *compr_bits, int length)
{
	cout << "Ausgabe-Datei:" << endl;
	char value = 0;
	int counter_bits = 0;
	fstream output_file;
	output_file.open(read_filename(false), ios::out);

	for (int i = 0; i < length; i++)
	{
		value |= compr_bits[i] << (7 - (counter_bits % 8)); // Bringt die Daten in dem char (8 Bit) an die richtige Position
		counter_bits++;
		if (counter_bits % 8 == 0)
		{
			output_file << value; // Sobald ein char (8 Bit) befuellt sind in datei schreiben
			value = 0;
		}
	}
	if (counter_bits % 8 != 0) // Falls die kompression nicht genau auf alle chars augeht
	{						   // werden die Restlichen noch reingeschrieben
		output_file << value;  // Hier kann es zum fehler kommen, da nicht klar ist mit was das char aufgefuellt wird
	}
	output_file.close();
	if (compr_bits != 0)
	{
		delete[] compr_bits;
		compr_bits = 0;
	}
}

/**
 *	Liest eine kompremmierte Datei ein und speichert diese wieder dekompriert ab
 *
 *	@param huffman_compr Zeiger auf das kompremierte Huffman-Objekt, da die Baumstruktur benoetigt wird
 */
void save_decompression(Huffman *huffman_compr)
{
	cout << "Einlese-Datei:" << endl;
	string filename = read_filename(true);
	cout << "Ausgabe-Datei:" << endl;
	huffman_compr->decompress(filename, read_filename(false));
}