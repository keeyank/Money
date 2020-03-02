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
			throw runtime_error("Money::Money: Invalid input (non-negative).");
	}

	Money::Money(double d) {
		if (d < 0)
			throw runtime_error("Money::Money: Invalid input (non-negative).");
		total_cents = to_cents(d);
	}

	long int Money::to_cents(double d) {
		long int total = (int)(d*1000);
		int r = total%10;
		if (r >= 5) {
			total += 10;
		}
		total /= 10;
		return total;
	}

	ostream& operator<<(ostream& os, const Money& m) {
		int cents = m.total_cents % 100;
		long int dollars = m.total_cents / 100;
		return os << '$' << dollars << '.' << cents;
	}

	istream& operator>>(istream& is, Money& m) {
		char ch1;
		double d;

		is >> ch1 >> d;
		if (!is) {return is;}
		if (ch1 != '$') {
			is.clear(ios_base::failbit); // set fail bit
			return is;
		}

		m = Money(d);
		return is;
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