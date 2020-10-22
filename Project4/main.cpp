#include "ExpandableHashMap.h"
#include <iostream>



int main()
{
	
	ExpandableHashMap<int,char> h;
	h.reset();
	char* l = h.find(7);
	h.associate(5, 'c');
	h.associate(6, 'd');
	char* g = h.find(6);
	
	h.associate(7, 'l');
	h.associate(8, 'b');
	char* k = h.find(8);
	char* a = h.find(6);
	 
	std::cerr << *a  << *k << h.size() << *g;
}