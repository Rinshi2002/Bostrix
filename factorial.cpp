#include<iostream>
using namespace std;
int main(){
  int a,fact,i;
  cout << "Enter a number: ";
  cin >> a;
  fact = 1;
  for( i = 1; i <= a; i++) {
    fact = fact * i;
    }
    cout << "factorial of " << a << " is: " << fact;
  return 0;
}
