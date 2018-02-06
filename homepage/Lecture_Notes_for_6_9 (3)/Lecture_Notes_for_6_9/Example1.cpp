#include<iostream>
using namespace std;

int main(){
	const size_t s = 5;
	int A[s];
	int B[5] = {1,2,3,4,5};
	int C[] = {1,2,3,4,5};
	
	for(size_t i = 0; i<s; i++){
		A[i] = i*i;
		B[i] += A[i];
		C[i] += B[i];
	}
	
	for(size_t i = 0; i < s; i++){
		cout<< C[i] << ' ';
	}
	
	cout<<endl;
	return 0;
	
}