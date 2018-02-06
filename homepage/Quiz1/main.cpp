#include <iostream>
#include<string>
using namespace std;

void swap(int, int);

int main()
{
   int a = 1;
   int b = 2;
   swap(a,b);







   return 0;
}

void swap(int a, int b) {
int temp;
temp = a;
 a= b;
 b = temp;

cout << "After the swapping a is : " << a<< "B is: " <<b<<endl;



}



