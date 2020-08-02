#include <iostream>
#include "vector.h"
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
	Vector<char> vec{ 'd','s','1','b','y' };
	char *data = vec.rawData();
	size_t size = vec.size();

	Vector<char> vec1(std::move(vec));
	data = vec1.rawData();
	size = vec1.size();

	Vector<char> vec2(vec1);
	data = vec2.rawData();
	size = vec2.size();
	auto it = vec2.begin();
	auto val = *it;
	++it;
	val = *it;
	++it;
	val = *it;
	for_each(vec2.begin(), vec2.end(), [](char &c) { cout << c; });
	return 0;
}