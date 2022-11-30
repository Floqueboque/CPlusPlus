/**	@file letter.cpp Verwalten von Buchstaben und deren Anzahlen

	@author		- Florian Glaser, Florian Herkommer
	@version	- 1.0
	@date		- 22.02.2022
*/

#include "letter.h"

/**	Erzeugt einen Buchstaben mit 0 als Wert und 0 als Vorkommens-Anzahl
 */
Letter::Letter()
{
	letter = 0;
	count = 0;
}

/**	Erzeugt einen Buchstaben mit 0 als Vorkommens-Anzahl

	@param cur_letter Dezimalwert des Buchstaben
*/
Letter::Letter(int cur_letter)
{
	letter = cur_letter;
	count = 0;
}

/**	Ueberladung des < Operator ermoeglicht den Vergleich von Buchstaben.
	Buchstaben mit geringerer Anzahl sind kleiner als Buchstaben mit
	groesserer Vorkommens-Anzahl.

	@param compare zu vergleichender Buchstabe
	@returns 0, wenn der aktuelle Buchstabe nicht kleiner ist, sonst ist er kleiner
*/
bool Letter::operator<(const Letter &compare) const
{
	return (count < compare.get_count());
}

/**	Liefert den aktuellen Buchstaben.

	@returns aktueller Buchstabe
*/
int Letter::get_letter() const
{
	return letter;
}

/**	Liefert die aktuelle Vorkommens-Anzahl.

	@returns Anzahl
*/
int Letter::get_count() const
{
	return count;
}

/**	Erhoeht die Vorkommens-Anzahl um 1.
 */
void Letter::add_count()
{
	count++;
}