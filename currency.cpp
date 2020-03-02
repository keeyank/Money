#include "currency.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace Currency {
	Money::Money() { }
	Money::Money(long int c):
				total_cents{c}
	{
		if (c < 0)
			throw runtime_error("Money::Money: Invalid input (c < 0).");
	}
	Money::Money(long int d, int c)
	{
		if (d < 0 || c < 0)
			throw runtime_error("Money::Money: Invalid input (non-negative).");
		total_cents = to_cents(d, c);
	}

	ostream& operator<<(ostream& os, const Money& m) {
		int cents = m.get_cents() % 100;
		long int dollars = m.get_cents() / 100;
		return os << '$' << dollars << '.' << cents;
	}

	istream& operator>>(istream& is, Money& m) {
		char ch1, ch2;
		long int d;
		int c;

		is >> ch1 >> d >> ch2 >> c;
		if (!is) {return is;}
		if (ch1 != '$' || ch2 != '.') {
			is.clear(ios_base::failbit); // set fail bit
			return is;
		}

		m = Money(d, c);
		return is;
	}

	long int to_cents(long int d, int c) {
		// Assertion: d, c are non-negative

		long int total = d*100;

		while (c >= 1000) {
			c /= 10; // integer div (throw out remainder)
		}

		// Round c (4/5 rule)
		if (c >= 100) {
			int r = c % 10;
			if (r >= 5) {
				c += 10; // round UP 
			}
			// r <= 4, round down (div throws out remainder anyways)
			c /= 10;
		}

		total += c;
		return total;

	}
}

// TEST
using namespace Currency;
int main() {
	Money m;
	cout << ">";
	while (cin >> m) {
		cout << m << endl;
		cout << ">";
	}
	return 0;
}