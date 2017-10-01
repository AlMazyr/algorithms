#include <iostream>
#include <string>

int atoi(const char ch)
{
	return ch - '0';
}

char itoa(int i)
{
	return i + '0';
}

std::string sum(const std::string& num1, const std::string& num2)
{
	std::string res;
	int n1 = num1.size(), n2 = num2.size();
	int max_n = n1 > n2 ? n1 : n2;

	int carry = 0, i1, i2, part_sum, val = 0;

	res.reserve(max_n + 1);
	for (int i = 0; i < max_n; ++i)
	{
		i2 = n2 - i - 1;
		i1 = n1 - i - 1;
		if (i1 < 0) {
			part_sum = atoi(num2[i2]) + carry;
		} else if (i2 < 0) {
			part_sum = atoi(num1[i1]) + carry;
		} else {
			part_sum = atoi(num1[i1]) + atoi(num2[i2]) + carry;
		}
		val = part_sum % 10;
		carry = part_sum / 10;
		res.insert(res.begin(), 1, itoa(val));
	}
	if (carry)
		res.insert(res.begin(), 1, itoa(carry));

	return res;
}

std::string subtract(const std::string& num1, const std::string& num2)
{
	std::string res;
	int n1 = num1.size(), n2 = num2.size();
	int max_n = n1 > n2 ? n1 : n2;

	int loan = 0, i1, i2, val = 0;

	res.reserve(max_n);
	for (int i = 0; i < max_n; ++i)
	{
		i2 = n2 - i - 1;
		i1 = n1 - i - 1;

		val = atoi(num1[i1]) - loan;
		loan = 0;
		if (val < 0) {
			loan = 1;
			val += 10;
		}
		if (i2 >= 0) {
			if (val < atoi(num2[i2])) {
				loan = 1;
				val += 10;
			}
			val -= atoi(num2[i2]);
		}
		res.insert(res.begin(), 1, itoa(val));
	}

	return res;
}

std::string karatsuba_mult(const std::string& num1, const std::string& num2)
{
	int n = num1.size();

	if(n <= 2) {
		return std::to_string(std::stoi(num1) * std::stoi(num2));
	}

	std::string a(num1, 0, n / 2),
		b(num1, n / 2),
		c(num2, 0, n / 2),
		d(num2, n / 2);

	std::string first = karatsuba_mult(a, c);
	std::string second = karatsuba_mult(sum(a, b), sum(c, d));
	std::string third = karatsuba_mult(b, d);
	std::string forth = subtract(subtract(second, third), first);

	return sum(sum(first + std::string(n, '0'),
			forth + std::string(n / 2, '0')), third);
}

int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cerr << "Err arguments! Usage: " << argv[0] <<
			" <num1> <num2>" << std::endl;
		return -1;
	}

	std::string num1(argv[1]), num2(argv[2]), mult;
	
	if (num1.size() != num2.size()) {
		std::cerr << "Err arguments! numbers must be the same size!"
			<< std::endl;;
		return -1;
	}

	mult = karatsuba_mult(num1, num2);

	std::cout << mult << std::endl;
	return 0;
}
