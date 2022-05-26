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
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size();
    int n = obstacleGrid.size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for(int i = 0; i < m; i++){
      if(obstacleGrid[i][0] == 1){
        break;
      }
      dp[i][0] = 1;
    }
    for(int j = 0; j < n; j++){
      if(obstacleGrid[0][j] == 1){
        break;
      }
      dp[0][j] = 1;
    }
    for(int i = 1; i < m; i++){
      for(int j = 1; j < n; j++){
        if(obstacleGrid[i][j] == 1){
          continue;
        }else{
          dp[i][j] = dp[i - 1][j] + dp [i][j - 1];
        }
      }
    }
    return dp[m - 1][n - 1];
  }
  int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for(int i = 0; i < m; i++) dp[i][0] = 1;
    for(int j = 0; j < n; j++) dp[0][j] = 1;
    for(int i = 1; i < m; i++){
      for(int j = 1; j < n; j++){
        dp[i][j] = dp[i - 1][j] + dp [i][j - 1];
      }
    }
    return dp[m - 1][n - 1];
  }
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