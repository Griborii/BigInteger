#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

using namespace std;

class BigInt {
	public:
		BigInt();
		BigInt(long long b);
	    BigInt(const BigInt& copied);
		BigInt& operator=(const BigInt& copied);
		BigInt& operator=(const long long);
	    ~BigInt(){};
		friend ostream& operator<<(ostream&, BigInt);
		friend BigInt Module(BigInt);
		bool operator!=(const BigInt&) const;
		bool operator==(const BigInt&) const;
		BigInt operator+(const BigInt&) const;
		BigInt operator-(const BigInt&) const;
		BigInt operator-() const;
		BigInt operator*(const BigInt&) const;
		bool operator>(const BigInt&) const;
		BigInt operator/(const BigInt&) const;
		bool operator<(const BigInt&) const;
		bool operator<=(const BigInt&) const;
		bool operator>=(const BigInt&) const;
		BigInt operator%(const BigInt&) const;
	private:
	    bool Znak;
		vector<int> Maks;
		void Rever();
		BigInt Moszhuhin(int, int);
};
BigInt::BigInt() {
    while (Maks.size() != 0) {
    	Maks.pop_back();
	}
	Znak = true;
	Maks.push_back(0);
}
BigInt::BigInt(long long n1) {
    long long n = n1;
    Znak = (n >= 0);
    if (n < 0) {
        n = -n;
    }
    if (n == 0) {
    	Maks.push_back(0);
	}
    while (n > 0) {
        Maks.push_back (n % 10);
        n = n / 10;
    }
}
BigInt::BigInt(const BigInt& copied) {
    while (Maks.size() > 0) {
        Maks.pop_back();
    }
    for (int i = 0; i < copied.Maks.size(); ++i) {
        Maks.push_back(copied.Maks[i]);
    }
    Znak = copied.Znak;
}
BigInt& BigInt::operator=(const BigInt& copied){
    while (Maks.size() > 0) {
        Maks.pop_back();
    }
	for (int i = 0; i < copied.Maks.size(); ++i) {
		Maks.push_back(copied.Maks[i]);
	}
	Znak = copied.Znak;
    return (*this);
}
BigInt& BigInt::operator=(long long n){
    Maks.clear();
	if (n >= 0) {
		Znak = true;
	}
	else {
		Znak = false;
		n = -n;
	}
	if (n == 0) {
		Maks.push_back(0);
	}
    while (n > 0) {
    	Maks.push_back(n % 10);
    	n = n / 10;
	}
	return (*this);
}
ostream& operator<<(ostream& Out, BigInt x) {
    if (x.Znak == false) {
        Out << "-";
    }
	for (int i = x.Maks.size() - 1; i >= 0; --i) {
		Out << x.Maks[i];
	}
	return Out;
}
BigInt Module (BigInt b1) {
	BigInt Answer = b1;
	Answer.Znak = true;
	return Answer;
}
bool BigInt::operator==(const BigInt& b1) const{
	BigInt b2 = (*this);
	if (b2.Maks.size() == 0 && b1.Maks.size() == 0) {
        return true;
	}
	if (b1.Maks.size() != b2.Maks.size()) {
		return false;
	}
	for (int i = 0; i < b1.Maks.size(); ++i) {
		if (b1.Maks[i] != b2.Maks[i]) {
			return false;
		}
	}
	return true;
}
bool BigInt::operator<(const BigInt& b1) const{
	BigInt b2 = (*this);
	if (b2 == b1) {
        return false;
	}
	if (b1.Znak == 0 && b2.Znak == 1) {
		return false;
	}
	if (b1.Znak == 1 && b2.Znak == 0) {
		return true;
	}
    bool k = (b1.Znak ^ true);
	if (b1.Maks.size() < b2.Maks.size()) {
		return (k ^ false);
	}
	if (b1.Maks.size() > b2.Maks.size()) {
		return (k ^ true);
	}
	for (int i = 0; i < b1.Maks.size(); ++i) {
		if (b1.Maks[i] < b2.Maks[i]) {
			return (k ^ false);
		}
		if (b1.Maks[i] > b2.Maks[i]) {
			return (k ^ true);
		}
	}
	return false;
}
void BigInt::Rever() {
	vector<int> v(0);
	for (int i = 0; i < Maks.size(); ++i) {
		v.push_back(Maks[i]);
	}
	for (int i = 0; i < Maks.size(); ++i) {
		Maks[i] = v[Maks.size() - i - 1];
	}
}
BigInt BigInt::Moszhuhin(int n2, int n1) {
	vector<int> v(0);
	for (int i = 0; i < n2; ++i) {
		long long j = Maks.size() + i - n1 - n2;
		v.push_back(Maks[Maks.size() + i - n1 - n2]);
	}
	BigInt Answer;
	Answer.Maks.pop_back();
	for (int i = 0; i < v.size(); ++i) {
		Answer.Maks.push_back(v[i]);
	}
	return Answer; 
}
bool BigInt::operator<=(const BigInt& b1) const{
	if (b1 == (*this)) {
		return true;
	}
	return ((*this) < b1);
}
bool BigInt::operator>=(const BigInt& b1) const{
	if (b1 == (*this)) {
		return true;
	}
	return (b1 < (*this));
}
bool BigInt::operator>(const BigInt& b1) const{
    if (b1 == (*this)) {
        return false;
    }
	return (b1 < (*this));
}
bool BigInt::operator!=(const BigInt& b1) const{
	BigInt b2 = (*this);
	if (b1.Maks.size() != b2.Maks.size()) {
		return true;
	}
	for (int i = 0; i < b1.Maks.size(); ++i) {
		if (b1.Maks[i] != b2.Maks[i]) {
			return true;
		}
	}
	return false;
}
bool Sravnenie(vector<int> b1, vector<int> b2) {
	if (b1.size() > b2.size()) {
		return true;
	}
	if (b1.size() < b2.size()) {
		return false;
	}
	for (int i = b1.size() - 1; i >= 0; --i) {
		if (b1[i] > b2[i]) {
			return true;
		}
		if (b1[i] < b2[i]) {
			return false;
		}
	}
	return false;
}
BigInt BigInt::operator-() const{
	BigInt Answer = (*this);
	if (Answer.Znak == true) {
		Answer.Znak = false;
	}
	else {
		Answer.Znak = true;
	}
	if (Answer.Maks.size() == 1 && Answer.Maks[0] == 0) {
		Answer.Znak = true;
	}
	return Answer;
}
BigInt BigInt::operator+(const BigInt& other) const{
    BigInt Answer1 = (*this);
    BigInt Answer;
    Answer.Maks.pop_back();
    bool b, u = false;
    if (Answer1.Znak == other.Znak) {

    	b = 0;
        for (int i = 0; i < min(Answer1.Maks.size(), other.Maks.size()); ++i) {
            Answer.Maks.push_back((b + Answer1.Maks[i] + other.Maks[i]) % 10);
            b = ((b + Answer1.Maks[i] + other.Maks[i]) >= 10);
        }
        if (Answer1.Maks.size() < other.Maks.size()) {
            for (int i = Answer1.Maks.size(); i < other.Maks.size(); ++i) {
                Answer.Maks.push_back((other.Maks[i] + b) % 10);
                b = (other.Maks[i] + b >= 10);
            }
        }
		if (Answer1.Maks.size() > other.Maks.size()) {
			
            for (int i = other.Maks.size(); i < Answer1.Maks.size(); ++i) {
                Answer.Maks.push_back((Answer1.Maks[i] + b) % 10);
                b = (Answer1.Maks[i] + b >= 10);
            }
        }
        if (b == 1) {
            Answer.Maks.push_back(1);
        }
        u = Answer1.Znak;
    }
    else {
    	b = 0;
    	BigInt other1 = other;
		if (Sravnenie(Answer1.Maks, other1.Maks)) {
			u = (other.Znak ^ true);
			for (int i = 0; i < other1.Maks.size(); ++i) {
	            Answer.Maks.push_back((-b + Answer1.Maks[i] - other1.Maks[i] + 10) % 10);
    	        b = ((-b + Answer1.Maks[i] - other1.Maks[i]) < 0);
        	}
        	int Q = other1.Maks.size();
        	while (b == 1 || Q < Answer1.Maks.size()) {
        		Answer.Maks.push_back((-b + Answer1.Maks[Q] + 10) % 10);
    	        b = ((-b + Answer1.Maks[Q]) < 0);
    	        ++Q;
			}
			Answer.Znak = false;
		}
		else {
    		other1 = Answer1;
    		Answer1 = other;
			u = other.Znak;
			for (int i = 0; i < other1.Maks.size(); ++i) {
	            Answer.Maks.push_back((-b + Answer1.Maks[i] - other1.Maks[i] + 10) % 10);
    	        b = ((-b + Answer1.Maks[i] - other1.Maks[i]) < 0);
        	}
        	int Q = other1.Maks.size();
        	while (b == 1 || Q < Answer1.Maks.size()) {
        		Answer.Maks.push_back((-b + Answer1.Maks[Q] + 10) % 10);
    	        b = ((-b + Answer1.Maks[Q]) < 0);
    	        ++Q;
			}
			Answer.Znak  = true;
		}
    }
    while (Answer.Maks.size() > 0) {
    	if (Answer.Maks[Answer.Maks.size() - 1] == 0) {
    		Answer.Maks.pop_back();
		}
    	else {
    		break;
		}
	}
	Answer.Znak = u;
	if(Answer.Maks.size() == 0) {
		Answer.Znak = true;
		Answer.Maks.push_back(0);
	}
	
    return Answer;
}
BigInt BigInt::operator-(const BigInt& other) const{
    BigInt Answer1 = (*this);    
    Answer1.Znak = (Answer1.Znak ^ true);
    return -(Answer1 + other);
}
BigInt BigInt::operator*(const BigInt& b1) const{
	BigInt b2 = (*this), Answer = 0;
	if (b2 == 0 || b1 == 0) {
		return 0;
	}
	vector<int> v(b1.Maks.size() + b2.Maks.size() + 1, 0);
	for (int i = 0; i < b2.Maks.size(); ++i) {
		BigInt s = 0;
		for (int j = 0; j < b2.Maks[i]; ++j) {
			s = (s + b1);
		}
		for (int j = i; j < i + s.Maks.size(); ++j) {
			v[j] = v[j] + s.Maks[j - i];
		}
		for (int i = 0; i < v.size() - 1; ++i) {
			if (v[i] > 9) {
				v[i + 1] = v[i + 1] + v[i] / 10;
				v[i] = v[i] % 10;
			}
		}
	}
	while (v[v.size() - 1] == 0) {
		v.pop_back();
	}
	Answer.Maks.pop_back();
	for (int i = 0; i < v.size(); ++i) {
		Answer.Maks.push_back(v[i]);
	}
	Answer.Znak = (b1.Znak ^ b2.Znak);
	return Answer;
}
BigInt BigInt::operator/(const BigInt& b0) const{
	BigInt b1 = b0;
	BigInt b2 = (*this);
	BigInt Answer;
	for (int i = 0; i <= b2.Maks.size() - b1.Maks.size(); ++i) {
		BigInt Dima = b2.Moszhuhin(b1.Maks.size(), i);
		int k = 0;
		while (Dima >=  Module(b1)) {
			++k;
			Dima = Dima - Module(b1);
		}

		Answer.Maks.push_back(k);
	}
	Answer.Rever();
	while (Answer.Maks[Answer.Maks.size() - 1] == 0) {
		Answer.Maks.pop_back();
	}
	Answer.Znak = (b1.Znak ^ b1.Znak);
	if (Answer.Maks.size() == 0) {
		return 0;
	}
	return Answer;
}
BigInt BigInt::operator%(const BigInt& b1) const{
	return 0;
}
std::string toString(const BigInt& value)
{
    std::stringstream buf;
    buf << value;
    return buf.str();
}

void check(long long x, long long y)
{
    const BigInt bigX = x;
    const BigInt bigY = y;

    if ((bigX + bigY) != BigInt(x + y))
    {
        std::cout << x << " + " << y << " == " << x + y << " got " << bigX + bigY << '\n';
    }

    if (bigX - bigY != BigInt(x - y))
    {
        std::cout << x << " - " << y << " == " << x - y << " got " << bigX - bigY << '\n';
    }

    if (bigX * bigY != BigInt(x * y))
    {
        std::cout << x << " * " << y << " == " << x * y << " got " << bigX * bigY << '\n';
    }
    if (x != 0 && y != 0)
    {
        if (bigX / bigY != BigInt(x / y))
        {
            std::cout << x << " / " << y << " != " << x / y << " got " << bigX / bigY << '\n';
        }
        
    }
}
void doCheckEqual(const BigInt& actual, const char* expected, size_t line)
{
    const std::string str = toString(actual);
    if (str != expected)
    {
        std::cout << "at line " << line << ": " << str << " != " << expected << '\n';
    }
}

#define checkEqual(x, y) do { doCheckEqual((x), (y), __LINE__); } while(0)
#define checkTrue(cond) do { if (!(cond)) std::cout << "at line " << __LINE__ << ": " << #cond << '\n'; } while(0)

int main()
{
    BigInt x = 3;
    checkEqual(x, "3");
    BigInt y = x;
    checkEqual(y, "3");
    BigInt z;
    checkEqual(z, "0");
    checkEqual(BigInt(-10), "-10");
    checkTrue(x == y);
    checkTrue(y == x);
    checkTrue(x != z);
    checkTrue(z != x);
    z = y;
    checkEqual(z, "3");

    x = 100;
    checkEqual(x, "100");
    checkTrue(!(x < x));
    checkTrue(x < 200);
    checkTrue(BigInt(50) < x);
    checkTrue(BigInt(-500) < x);
    checkTrue(BigInt(-500) < BigInt(-200));
    checkTrue(!(x > x));
    checkTrue(BigInt(200) > x);
    checkTrue(x > BigInt(50));
    checkTrue(x > BigInt(-500));
    checkTrue(BigInt(-200) > BigInt(-500));
    checkTrue(x <= x);
    checkTrue(x <= 200);
    checkTrue(BigInt(50) <= x);
    checkTrue(BigInt(-500) <= x);
    checkTrue(BigInt(-500) <= BigInt(-200));
    checkTrue(x >= x);
    checkTrue(BigInt(200) >= x);
    checkTrue(x >= BigInt(50));
    checkTrue(x >= BigInt(-500));
    checkTrue(BigInt(-200) >= BigInt(-500));
    BigInt z1(0);
    BigInt z2 = -z1;
    checkTrue(BigInt(0) == -BigInt(0));
    checkEqual(BigInt(10) + BigInt(10), "20");
    checkEqual(BigInt(-10) + BigInt(10), "0");
    checkEqual(BigInt(10) + BigInt(-10), "0");
    checkEqual(BigInt(-10) + BigInt(-10), "-20");
    checkEqual(BigInt(10) - BigInt(10), "0");
    checkEqual(BigInt(-10) - BigInt(10), "-20");
    checkEqual(BigInt(10) - BigInt(-10), "20");
    checkEqual(BigInt(-10) - BigInt(-10), "0");
    checkEqual(BigInt(0) + BigInt(-1), "-1");
    checkEqual(BigInt(0) - BigInt(1), "-1");
    checkEqual(BigInt(100) - BigInt(100), "0");
    checkEqual(BigInt(99) - BigInt(100), "-1");
    checkEqual(BigInt(10) - BigInt(11), "-1");
    checkEqual(BigInt(20) - BigInt(19), "1");
    for (int i = -21; i <= 21; ++i)
    {
        for (int j = -21; j <= 21; ++j)
        {
            check(i, j);
        }
    }
    const long long step = std::numeric_limits<unsigned long long>::max() / 99;
    const long long lower = std::numeric_limits<unsigned long long>::min() + step;
    const long long upper = std::numeric_limits<unsigned long long>::max() - step;

    for (long long i = lower; i < upper; i += step)
    {
        for (long long j = -99; j < 99; ++j)
        {
            check(i, j);
        }
    }

    const BigInt big1 = std::numeric_limits<long long>::max();
    checkEqual(big1, "9223372036854775807");

    const BigInt big2 = big1 * big1;
    std::cout << "9223372036854775807 * 9223372036854775807\n";
    checkEqual(big2, "85070591730234615847396907784232501249");

    const BigInt big3 = big2 * big2;
    std::cout << "85070591730234615847396907784232501249 * 85070591730234615847396907784232501249\n";
    checkEqual(big3, "7237005577332262210834635695349653859421902880380109739573089701262786560001");

    std::cout << "done\n";

    return 0;
}
