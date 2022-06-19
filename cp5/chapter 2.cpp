#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
};
int main(){
  const int i = 42;
  auto j = i; const auto &k = i; auto *p = &i; 
  const auto j2 = i, &k2 = i;
  p = &j;

  // 3.26
  int a = 3, b = 4;
  int *e = &a;
  decltype(a + e) c = &a;
  decltype((b)) d = a;
  ++c;
  ++d;
  Solution A;
  //for(auto c:b)
  getchar();
}