#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<cstring>
#include<math.h>
#include<algorithm>
using namespace std;
class Solution {
public:
  int minCostClimbingStairs(vector<int>& cost) {
    vector<int> dp(cost.size());
    dp[0]= cost[0];
    dp[1]= cost[1];
    const int n = cost.size();
    for(int i = 2; i < n; i++){
      dp[i] = min(dp[i - 2] , dp[i - 1]) + cost[i];
    }
    return min(dp[n - 1], dp[n - 2]);
  }
  int climbStairs(int n) {
    if(n <= 1){
      return n;
    }
    vector<int> dp(n + 1);
    dp[1] = 1; dp[2] =2;
    for(int i = 3; i <= n; i++){
      dp[i] = dp[i-1] + dp[i - 2];
    }
    return dp[n];
  }
  int fib(int n) {
    if(n < 1) return n;
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for(int i = 2; i <= n; i++){
      dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
  }
};
int main(){
  string s= "aabb", t = "abb";
  vector<int> a({-1, 0, 1, 2, -1, -4});
  vector<int> b({-2,-1});
  vector<int> c({-1,2});
  vector<int> d({0,2});
  Solution A;
  //cout<<A.isAnagram(s,t)<<endl;
  vector<vector<int>> result;
  for(vector<int> a:result){
      for(int j:a){
        cout<<j<<' ';
      }
      cout<<endl;
  }
  //cout<<A.fourSumCount(a,b,c,d)<<endl;
  getchar();
}