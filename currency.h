#include <iostream>

namespace Currency {

class Money {
private:
	long int total_cents = 0;
public:
	Money();
	Money(long int c);
	Money(long int d, int c);
	long int get_cents() const {return total_cents;}
	//Money(float dollars); // TODO
};

std::ostream& operator<<(std::ostream& os, const Money& m);
std::istream& operator>>(std::istream& is, const Money& m);

// Returns the total number of cents in $d.c
long int to_cents(long int d, int c);
}