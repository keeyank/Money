#include "currency.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*


Make A SINGLETON VECTOR FUNCTION THINGY
FOR THE CONVERSION RATE
IT JUST RETURNS A CONVERSION BASED ON INDEX
AND USES A STATIC VECTOR THAT IT MAKES A CONST STATIC VECTOR
 WITH ALL OF THE CONVERSIONS IN TI CORRESPONDING TO ENUMS
*/
namespace Currency_lib {
	Money::Money() { }

	Money::Money(long int c, Currency cr):
				total_cents{c}, currency{cr}
	{
		if (c < 0)
			throw runtime_error("Money::Money: Invalid input (non-negative).");
		if (cr < Currency::cad || cr > Currency::eur)
			throw runtime_error("Money::Money: Invalid input (bad currency).");
	}

	Money::Money(double d, Currency cr):
				currency{cr}
	{
		if (d < 0)
			throw runtime_error("Money::Money: Invalid input (non-negative).");
		if (cr < Currency::cad || cr > Currency::eur)
			throw runtime_error("Money::Money: Invalid input (bad currency).");
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

		// Ensure 1, 2, ..., 9 cents printed properly
		string zero = "";
		if (cents < 10) {
			zero = "0";
		}
		return os << '$' << dollars << '.' << zero << cents << 
				' ' << Money::tostring(m.currency);
	}

	string Money::tostring(Currency cr) {
		static const vector<string> cr_map {"cad", "usd", "yen", "eur"};
		// Assert: cr is a valid value
		return cr_map[(int)cr];
	}

	istream& operator>>(istream& is, Money& m) {
		char ch;
		double d;
		string s;

		is >> ch >> d >> s;
		if (!is) {return is;}
		if (ch != '$') {
			is.clear(ios_base::failbit); // set fail bit
			return is;
		}

		Currency cr;
		if (s == "cad") {cr = Currency::cad;}
		else if (s == "usd") {cr = Currency::usd;}
		else if (s == "yen") {cr = Currency::yen;}
		else if (s == "eur") {cr = Currency::eur;}
		else {
			is.clear(ios_base::failbit); // set fail bit
			return is;
		}

		m = Money{d, cr};
		return is;
	}

	Money operator+(const Money& m1, const Money& m2) {
		if (m1.currency != m2.currency)
			throw runtime_error("operator+: Mismatched currency.");
		return Money{m1.total_cents + m2.total_cents, m1.currency};
	}

	void operator+=(Money& m1, const Money& m2) {
		if (m1.currency != m2.currency)
			throw runtime_error("operator+=: Mismatched currency.");
		m1 = Money{m1.total_cents + m2.total_cents, m1.currency};
	}


}

// TEST
using namespace Currency_lib;
int main() {
	Money prev{(long int)0, Currency::usd}; // long int to get past ambiguity of constructors
	Money next;
	cout << ">";
	while (cin >> next) {
		next += prev;
		cout << next << endl;
		prev = next;
		cout << ">";
	}
	return 0;
}