#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <sstream>
#include <algorithm> 

using namespace std;


long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}


long long get_maximum_value(string &exp) {
  vector <char> operations;
  vector <long long> digits;
  digits.push_back(0);
  operations.push_back('0');
  for(int i = 0; i < exp.size() ; i++){
  	if(exp[i] == '*' || exp[i] == '+' || exp[i] == '-'){
  		operations.push_back(exp[i]);
  		exp[i] = ' ';
	}
  }
  stringstream ss(exp);
  long long value;
  while(!ss.eof()){
  	ss >> value;
  	digits.push_back(value);
  }
  int n = digits.size();
  long long M[n][n];
  long long m[n][n];
  for(int i = 1; i < n; i++){
  	M[i][i] = digits[i];
  	m[i][i] = digits[i];
  	}
   for(int s = 1; s < n-1 ; s++){
   		for(int i = 1; i <= (n-1) - s; i++){
   			int j = i + s;
   			long long min_t = INFINITY;
   			long long max_t = -INFINITY;
   			long long a,b,c,d;
   			for(int k = i; k < j ; k++){
   				a = eval(M[i][k],M[k+1][j],operations[k]);
   				b = eval(M[i][k],m[k+1][j],operations[k]);
   				c = eval(m[i][k],M[k+1][j],operations[k]);
   				d = eval(m[i][k],m[k+1][j],operations[k]);
   				min_t = min(min_t,min(a,min(b,min(c,d))));
   				max_t = max(max_t,max(a,max(b,max(c,d))));
			   }
			   m[i][j] = min_t;
			   M[i][j] = max_t;
		}
   }
     	
   return M[1][n-1];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
