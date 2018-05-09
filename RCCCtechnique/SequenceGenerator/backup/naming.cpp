#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

char * chstrswithf(char * a)
{
	char c='A';
	while(*a!='\0')
	{
		if(*a=='@'){
			*a=c;
			++c;
		}
		a++;
	}
return a;
}


int main(int argc, char *argv[])
{
	using std::string;
	using std::cout;
	using std::endl;
	using std::replace;
	ifstream in("new.txt");

	if(!in) {
		cout << "Cannot open input file.\n";
		return 1;
	}

	char str[255];
	string str1;
	while(in) {
		in.getline(str, 255);  // delim defaults to '\n'

		chstrswithf(str);
	    cout<< str << "\n";




}





in.close();


return 0;
}
