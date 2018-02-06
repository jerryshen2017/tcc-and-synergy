#include <iostream>
using namespace std;

int add(int x, int y) {
return x+y;
}
int sub(int x, int y) {
return x-y;

}

int main()
{
  int(*fp)(int, int);
  fp = &add;
  cout << "The result is: "<<fp(6,3) << endl;
  fp = &sub;
  cout <<"The result is: " << fp(6,3) << endl;
  return 0;


}







