#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<cstring>
#include<math.h>
#include<algorithm>
using namespace std;

class Solution{
private:
    vector<vector<int>> result; // 存放符合条件结果的集合
    vector<int> path; // 用来存放符合条件结果

    void backtrackingSum3(int targetSum, int k, int sum, int startIndex) {
      if(path.size() == k){
        if(sum == targetSum){
          result.push_back(path);
        }
        return;
      }
      for(int i = startIndex; i <= 9 - (k - path.size()) + 1; i++){
        path.push_back(i);
        sum+=i;
        if(sum>targetSum){
          path.pop_back();
          sum-=i;
          continue;
        }
        backtrackingSum3(targetSum, k, sum, i+1);
        path.pop_back();
        sum-=i;
      }
    }

    void backtracking(int n, int k, int startIndex) {
      if(path.size()==k){
        result.push_back(path);
        return;
      }
      for(int i=startIndex;i <= n - (k - path.size()) + 1;i++){
        path.push_back(i);
        backtracking(n,k,i+1);
        path.pop_back();
      }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
      result.clear();
      path.clear();
      backtrackingSum3(n,k,0,1);
      return result;
    }
    vector<vector<int>> combine(int n, int k) {
      result.clear();
      path.clear();
      backtracking(n,k,1);
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
  vector<vector<int>> result=A.combine(4,2);
  for(vector<int> a:result){
    for(int b: a){
      cout<<b;
    }
    cout<<endl;
  }
  getchar();
}