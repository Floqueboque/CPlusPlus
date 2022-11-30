#ifndef LETTER_HEADER
#define LETTER_HEADER

/**
	Klasse zum Verwalten von Buchstaben und deren Anzahlen
*/
class Letter
{
private:
	/**
		Buchstabe
	*/
	int letter;
	/**
		Anzahl an Vorkommnissen des Buchstabens
	*/
	int count;

public:
	Letter();
	Letter(int cur_letter);
	virtual bool operator<(const Letter &compare) const;
	virtual int get_letter() const;
	virtual int get_count() const;
	virtual void add_count();

private:
};

#endif