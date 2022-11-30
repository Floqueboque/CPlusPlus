#include "huffman.h"
/**
 * Konstruktor
 */
Huffman::Huffman()
{
    lookup_positions = 0;
    root = 0;
}

/**
 * Dekonstruktor
 */
Huffman::~Huffman()
{
}

/**
 *   Rekursive Tiefensuche. Durchsucht den Binaerbaum nach einem uebergebenen Blatt
 *   und speichert die Bits, die zum Erreichen notwendig waren.
 *
 *   @param search_node zu suchendes Blatt
 *   @param node aktuelles Blatt
 *   @param compr_buffer derzeit gespeicherte Bitfolge
 *   @returns 0, wenn Blatt nicht gefunden wurde, sonst wurde es gefunden
 */
bool Huffman::depth_search(char search_node, HuffmanElement *node, vector<bool> *compr_buffer)
{
    bool success = false;
    if (node->get_left() != 0 || node->get_right() != 0)
    {
        if (node->get_left() != 0)
        {
            compr_buffer->push_back(false);
            success = depth_search(search_node, node->get_left(), compr_buffer);
        }
        if (!success && node->get_right() != 0)
        {
            compr_buffer->push_back(true);
            success = depth_search(search_node, node->get_right(), compr_buffer);
        }
        if (!success)
        {
            if (compr_buffer->size() > 0)
            {
                compr_buffer->pop_back();
            }
        }
    }
    else
    {
        if (node->get_letter() == search_node)
        {
            success = true;
        }
        else
        {
            if (compr_buffer->size() > 0)
            {
                compr_buffer->pop_back();
            }
            success = false;
        }
    }

    return success;
}

/**
 * Komprimiert die Datei welche uebergeben wird
 *
 * @param compr_bits_ar speicherort der kompremierten Datei
 * @param count laenge von compr_bits
 * @param text Text welcher komprimiert werden soll
 * @return compr_bits_ar
 */
bool *Huffman::compress(bool *compr_bits_ar, int *count, string text)
{
    vector<bool> compr_bits;
    vector<bool> cur_compr_bits;
    vector<char> letters;

    read_file(text, &letters);
    for (unsigned int i = 0; i < letters.size(); i++)
    {
        cur_compr_bits.clear();
        depth_search(letters[i], root, &cur_compr_bits);
        compr_bits.insert(compr_bits.end(), cur_compr_bits.begin(), cur_compr_bits.end());
    }

    *count = compr_bits.size();

    compr_bits_ar = new bool[*count]();

    for (size_t i = 0; i < *count; i++)
    {
        compr_bits_ar[i] = compr_bits[i];
    }

    return compr_bits_ar;
}

/**
 *   Privat
 *   Dekomprimiert ein uebergebenes Bit-Array und speichert
 *   den dekomprimierten Text in eine Datei
 *
 *   @param compr_bits komprimierte Datei
 *   @param count Laenge von compr_bits
 *   @param filename wohin die dekomprimierte Datei gespeichert werden soll
 *   @returns dekomprimierter Text
 */
string Huffman::decompress(bool *compr_bits, int count, string filename)
{
    clock_t time_start = clock();
    stringstream decompr_string;
    HuffmanElement *node;
    int i = 0;
    while (i < count)
    {
        node = root;
        while (i < count && (node->get_left() != 0 || node->get_right() != 0))
        {
            if (!compr_bits[i])
            {
                if (node->get_left() != 0)
                {
                    node = node->get_left();
                }
            }
            else
            {
                if (node->get_right() != 0)
                {
                    node = node->get_right();
                }
            }
            i++;
        }

        decompr_string << node->get_letter();
    }

    ofstream file;
    file.open(filename);
    file << decompr_string.str();
    file.close();
    decompr_string.str("");

    return decompr_string.str();
}

/**
 * Public
 * Liest die Datei und versucht diese wieder zu dekomprimieren
 * Das Ergebnis wird in der Ausgabedatei gespeichert
 *
 * @param filename Eingabedatei
 * @param out_filenamne Speicherort der Ausgabedatei
 */
void Huffman::decompress(string filename, string out_filenamne)
{
    ifstream input_file(filename, ios::binary | ios::in);
    if (input_file)
    {
        char c;
        input_file.seekg(0, input_file.end);
        int length = input_file.tellg();
        input_file.seekg(0, input_file.beg);
        bool *compr_bits = new bool[length * 8]();
        int counter = 0;
        while (input_file.get(c))
        {

            for (int i = 7; i >= 0; i--)
            {
                char bit = ((c >> i) & 0x01);
                if (bit)
                {
                    compr_bits[counter] = 1;
                }
                else
                {
                    compr_bits[counter] = 0;
                }
                counter++;
            }
        }
        decompress(compr_bits, length * 8, out_filenamne);
    }
}

/**
 * Liest eine Datei ein und speichert jedes Byte / Chars in letters
 *
 * @param filename Eingabedatei
 * @param letters Array mit den enthaltenen Bytes / Chars der Datei
 */
void Huffman::read_file(string filename, vector<char> *letters)
{
    char byte = 0;

    ifstream input_file(filename);
    if (!input_file.is_open())
    {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
    }

    while (input_file.get(byte))
    {
        letters->push_back(byte);
    }

    input_file.close();
}

/**
 * Liest eine Datei ein und zaehlt wie viele Chars in der Datei vorkommen.
 * Dafuer muss letters bereits mit allen zu zaehlenden chars befuellt sein
 *
 * @param filename Eingabedatei
 * @param letters Vector von Letters die gezaehlt werden sollen
 */
void Huffman::read_file(string filename, vector<Letter> *letters)
{
    char byte = 0;

    ifstream input_file(filename);
    if (!input_file.is_open())
    {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
    }

    while (input_file.get(byte))
    {
        letters->at(byte).add_count();
    }

    input_file.close();
}

/**
 * Erzeugt einen Huffman-Binaer-Baum anhand einer Datei
 *
 * @param filename Dateiname
 */
void Huffman::build_tree(string filename)
{
    tree.clear();
    vector<HuffmanElement *> tmp_tree;
    vector<Letter> letters;
    // Make ASCII table
    for (unsigned int i = 0; i < ENCODING_MAX; i++)
    {
        letters.push_back(Letter(i));
    }

    read_file(filename, &letters);

    sort(letters.begin(), letters.end());
    lookup_positions = new int[ENCODING_MAX];
    for (unsigned int i = ENCODING_MAX - 1; i >= 0 && letters[i].get_count() > 0; i--)
    {
        tmp_tree.push_back(new HuffmanElement(letters[i].get_letter(), letters[i].get_count()));
        tree.push_back(tmp_tree[tmp_tree.size() - 1]);
        lookup_positions[letters[i].get_letter()] = tree.size() - 1;
    }
    while (tmp_tree.size() > 1)
    {
        tmp_tree.push_back(new HuffmanElement(tmp_tree[tmp_tree.size() - 1], tmp_tree[tmp_tree.size() - 2], tmp_tree[tmp_tree.size() - 1]->get_value() + tmp_tree[tmp_tree.size() - 2]->get_value()));
        root = tmp_tree[tmp_tree.size() - 1];
        tmp_tree[tmp_tree.size() - 2]->set_parent(root, false);
        tmp_tree[tmp_tree.size() - 3]->set_parent(root, true);
        tmp_tree.erase(remove(tmp_tree.begin(), tmp_tree.end(), tmp_tree[tmp_tree.size() - 2]), tmp_tree.end());
        tmp_tree.erase(remove(tmp_tree.begin(), tmp_tree.end(), tmp_tree[tmp_tree.size() - 2]), tmp_tree.end());
        sort(tmp_tree.begin(), tmp_tree.end(), compareCharacters());
    }
}