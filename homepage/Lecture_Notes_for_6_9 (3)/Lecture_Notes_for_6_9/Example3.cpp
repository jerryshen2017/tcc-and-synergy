#include<iostream>
using namespace std;

int main(){
	char sa[] = "Only upto here\0 The rest can also be printed";
	
	cout<< sa << endl;
	
	for(int i = 0; i < sizeof(sa); i++){
		if(sa[i] != '\0') cout<< sa[i];
		else cout<< "[NULL CHAR]";
	}
	
	cout<< endl;
	
	string str_obj = sa;
	cout<<str_obj;
	
	return 0;
}