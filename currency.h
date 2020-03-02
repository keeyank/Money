#include <iostream>

namespace Currency {

class Money {
public:
	Money();
	Money(long int c);
	Money(double d); 

	friend std::ostream& operator<<(std::ostream& os, const Money& m);
	friend std::istream& operator>>(std::istream& is, Money& m);
private:
	long int total_cents = 0;
	static long int to_cents(double d);
};


}