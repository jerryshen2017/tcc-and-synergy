#include<iostream>
using namespace std;

int main(){
	char str[] = "This is a very long string" " and so I am assuming it won't fit it a line"
	"Oh but wait! It does?!!";

	cout<< str <<endl;

	cout<< "Size:" << sizeof(str) << endl;
	
	return 0;
}