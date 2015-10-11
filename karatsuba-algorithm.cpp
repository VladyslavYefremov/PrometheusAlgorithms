#include "stdafx.h"
#include "testStatic.h"
#include <cstdlib>
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

#define max(a,b) ((a)>(b) ? (a):(b))
#define min(a,b) ((a)<(b) ? (a):(b))

/*
	Program gets FIRST * SECOND = ...
*/
#define FIRST "1685287499328328297814655639278583667919355849391453456921116729"
#define SECOND "7114192848577754587969744626558571536728983167954552999895348492"

//#define FIRST "49823261"
//#define SECOND "44269423"

#define THIRD 105

typedef vector<char> container;


class BigData {
public:
	container data;
	
	BigData(unsigned char exponent){
		data.reserve(exponent);
		for (unsigned char i = 0; i < exponent; i++)
			data.push_back(0);
		data.push_back(1);
	}
	
	BigData(container buffer){
		data = buffer;
	}
	
	BigData(const BigData & object){
		this->data = object.data;
	}
	
	BigData(){}

	BigData & operator = (BigData & right)
	{
		if (this == &right)
			return *this;

		this->data = right.data;
		return *this;
	}

	friend bool operator ==(const BigData & left, const BigData & right);
	friend bool operator >(const BigData & left, const BigData & right);
	friend BigData operator+(BigData & left, BigData & right);
	friend BigData operator-(BigData & left, BigData & right);
	friend BigData operator*(BigData & left, BigData & right);
	friend BigData valueToContainer(char value);
	friend BigData multPow(unsigned int value, container B);

	friend ostream &operator<<(ostream & stream, const BigData & Obj);
	friend void correctData(BigData &, BigData &);

	BigData getRightPart(){
		char halfSize = data.size() / 2;

		container buffer;
		for (char i = 0; i < halfSize; i++)
			buffer.push_back(data[i]);

		return BigData(buffer);
	}

	BigData getLeftPart(){
		char halfSize = data.size() / 2;
		
		container buffer;

		container test = data;
		
		while (test.size() > 1 && test[test.size() - 1] == 0) {
			test.pop_back();
		}

		if (test.size() > 1) {
			for (char i = 0; i < halfSize; i++)
				buffer.push_back(data[i + halfSize]);
		}

		if (!buffer.size())
			buffer.push_back(0);

		return BigData(buffer);
	}
};

ostream &operator<<(ostream & stream, const BigData & Obj) {
	auto size = Obj.data.size();
	for (auto i = size; i > 0; i--)
		stream << (int)Obj.data[i - 1];

	return stream;
}

bool operator ==(const BigData & left, const BigData & right) {
	BigData l(left);
	BigData r(right);

	correctData(l, r);

	auto ls = l.data.size();
	auto rs = r.data.size();

	if (ls != rs)
	{
		auto n = max(ls, rs);
		auto s = min(ls, rs);
		for (int i = 0; i < (n - s); i++) {
			if (ls > rs)
				r.data.push_back(0);
			else
				l.data.push_back(0);
		}
	}

	auto size = l.data.size();
	for (auto i = 0; i < size; i++) {
		if (l.data[i] != r.data[i])
			return false;
	}

	return true;
}

bool operator >(const BigData & left, const BigData & right) {
	BigData l(left);
	BigData r(right);

	correctData(l, r);

	auto ls = l.data.size();
	auto rs = r.data.size();

	if (ls != rs)
	{
		auto n = max(ls, rs);
		auto s = min(ls, rs);
		for (int i = 0; i < (n - s); i++) {
			if (ls > rs)
				r.data.push_back(0);
			else
				l.data.push_back(0);
		}
	}

	auto size = l.data.size();
	for (auto i = 0; i < size; i++) {
		if (l.data[size - i - 1] > r.data[size - i - 1])
			return true;
		if (l.data[size - i - 1] < r.data[size - i - 1])
			return false;
	}

	return true;
}

void trim(BigData & object) {
	while (object.data.size() > 1 && object.data[object.data.size() - 1] == 0){
		object.data.pop_back();
	}
}

void exponent(BigData & object){
	int exp = 1;
	int n = object.data.size();

	while (pow(2, exp) < n)
		exp++;

	for (auto i = 0; i < (pow(2, exp) - n); i++) {
		object.data.push_back(0);
	}
}

void correctData(BigData & left, BigData & right) {
	trim(left);
	trim(right);

	auto ls = left.data.size();
	auto rs = right.data.size();

	if (ls < 2 && rs < 2)
		return;

	if (ls != rs) {
		if (ls > rs) {
			for (int i = 0; i < (ls - rs); i++)
				right.data.push_back(0);
		}
		else if (rs > ls) {
			for (int i = 0; i < (rs - ls); i++)
				left.data.push_back(0);
		}
	}

	exponent(left);
	exponent(right);
}

BigData valueToContainer(char value){
	container result;

	if (value <= 0) {
		result.push_back(0);
		return BigData(result);
	}

	while (value > 0) {
		result.push_back(value % 10);
		value /= 10;
	}
	return BigData(result);
}

BigData multPow(unsigned int value, container B) {
	container buf = B;

	for (unsigned int i = 0; i < value; i++)
		buf.insert(buf.begin(), 0);

	return BigData(buf);
}

BigData operator*(BigData & left, BigData & right) {
	correctData(left, right);

	container left_value = left.data;
	container right_value = right.data;

	if (left_value.size() < 1 || right_value.size() < 1)
		return BigData(valueToContainer(0));

	char n = left_value.size();

	if (left_value.size() == 1 || right_value.size() == 1) {

		if (left_value.size() == 1 && right_value.size() == 2) {
			left_value.push_back(0);
		}else if(left_value.size() == 2 && right_value.size() == 1) {
			right_value.push_back(0);
		}
		
		return BigData(valueToContainer(left_value[0] * right_value[0]));
	}
	else {
		BigData a(left.getLeftPart());
		BigData b(left.getRightPart());

		BigData c(right.getLeftPart());
		BigData d(right.getRightPart());

		static int firstCounter = 0;

		BigData ac = a*c;

		BigData ac_(multPow(n, ac.data));
		BigData bd = b*d;
		BigData a_plus_b(a + b);
		BigData c_plus_d(c + d);
		BigData adbc0(a_plus_b*c_plus_d);
		BigData adbc1(adbc0 - ac);
		BigData adbc(adbc1 - bd);
		BigData adbc_(multPow(n / 2, adbc.data));

		if (BigData(adbc) == BigData(valueToContainer(THIRD))){
			firstCounter++;
			cout << firstCounter << endl;
		}

		return BigData(ac_ + adbc_ + bd);
	}
}

BigData operator+(BigData & left, BigData & right) {
	correctData(left, right);

	auto ls = left.data.size();
	auto rs = right.data.size();

	if (!ls || !rs)
		return BigData(1);

	container smaller = rs >= ls ? left.data : right.data;
	container bigger = ls > rs ? left.data : right.data;

	container result(smaller.size() + 1);

	while (smaller.size() < bigger.size()) {
		smaller.push_back(0);
	}

	for (auto i = 0; i < max(ls, rs); i++) {
		char sum = smaller[i] + bigger[i] + result[i];

		if (sum / 10) {
			result[i] = sum % 10;
			result[i + 1] = sum / 10;
		}
		else {
			result[i] = sum;
		}
	}

	return (BigData(result));
}

BigData operator-(BigData & left, BigData & right) {
	correctData(left, right);

	if (left == right)
	{
		return BigData(container(left.data.size()));
	}

	auto ls = left.data.size();
	auto rs = right.data.size();

	if (!ls || !rs)
		return BigData(1);

	container smaller = (right > left) ? left.data : right.data;
	container bigger = (left > right) ? left.data : right.data;

	container result(smaller.size() + 1);

	while (smaller.size() < bigger.size()) {
		smaller.push_back(0);
	}

	for (auto i = 0; i < max(ls, rs); i++) {
		char res = 0;

		if (bigger[i] < smaller[i])
		{
			bigger[i] += 10;
			bigger[i + 1]--;
		}
		result[i] = bigger[i] - smaller[i];
	}

	auto it = result.end();
	while (!(*(it - 1))) {
		result.pop_back();
		it = result.end();
	}

	return (BigData(result));
}

container stringToVector(char str[]){
	container buffer;
	for (auto i = strlen(str); i > 0; i--){
		char * symbol = new char(str[i-1]);
		buffer.push_back((char)atoi(symbol));
		delete symbol;
	}
	return buffer;
}


int main()
{
	container lol1(stringToVector(FIRST));
	container lol2(stringToVector(SECOND));
	
	BigData A(lol1);
	BigData B(lol2);

	cout << A << " * " << B << " = " << "" << A*B << endl;

	return system("pause");
}
