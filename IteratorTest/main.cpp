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

#ifdef INPUT_ITERATOR_TYPE
	for_each(vec2.begin(), vec2.end(), [](char &c) { cout << c; });
#endif

#ifdef FORWARD_ITERATOR_TYPE
	for_each(vec2.begin(), vec2.end(), [](char &c) { cout << c; });
#endif

#ifdef BIDIRECTIONAL_ITERATOR_TYPE
	for (auto i = vec2.rbegin(); i != vec2.rend(); i--)
		cout << *i;
	for_each(vec2.begin(), vec2.end(), [](char &c) { cout << c; });
#endif

#ifdef RANDOM_ITERATOR_TYPE
	for (auto i = vec2.rbegin(); i != vec2.rend(); i--)
		cout << *i;
	cout << "\n";
	for_each(vec2.begin(), vec2.end(), [](char &c) { cout << c; });
	cout << "\n";
	auto it = vec2.begin();
	cout << "It = " << *it << "\n";
	it += 3;
	cout << "It + 3" << " = " << *it << "\n";
	it -= 2;
	cout << "It - 2" << " = " << *it << "\n";
#endif

	return 0;
}