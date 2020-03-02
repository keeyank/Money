#include <iostream>
#include <vector>

namespace Currency_lib {

enum class Currency {
	cad, usd, yen, eur
};

class Money {
public:
	Money();
	Money(long int c, Currency cr);
	Money(double d, Currency cr);

	friend std::ostream& operator<<(std::ostream& os, const Money& m);
	// Accept input of the form $[double] [currency]
	friend std::istream& operator>>(std::istream& is, Money& m);
	friend Money operator+(const Money& m1, const Money& m2);
	friend void operator+=(Money& m1, const Money& m2);
private:
	long int total_cents = 0;
	Currency currency = Currency::cad;
	static long int to_cents(double d);
	static std::string tostring(Currency cr);
};


}