#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
#include<unordered_set>
#include<cstring>
#include<math.h>
#include<algorithm>
using namespace std;

class Solution{
private:
    
public:
  int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(),g.end());
    sort(s.begin(),s.end());
    int result = 0;
    int index = s.size() - 1;
    for(int i = g.size()-1; i >= 0; i--){
      if(index > 0 && s[index] >= g[i]){
        result++;
        index--;
      }
    }
    return result;
  }
};

int main(){
  string s= "aabb", t = "abb";
  vector<int> a({-1, 0, 1, 2, -1, -4});
  vector<int> b({-2,-1});
  vector<int> c({-1,2});
  vector<int> d({0,2});
  Solution A;
  vector<vector<char>> e={{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};
  A.solveSudoku(e);
  // for(vector<int> a:result){
  //   for(int b: a){
  //     cout<<b;
  //   }
  //   cout<<endl;
  // }
  getchar();
}