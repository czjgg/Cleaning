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

  int rob2(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    if(nums.size() == 1) return nums[0];
    int result1 = robRange(nums, 0, nums.size() - 2); // 情况二
    int result2 = robRange(nums, 1, nums.size() - 1); // 情况三
    return max(result1, result2);
  }
  int robRange(vector<int>& nums, int start, int end) {
    if(start == end) return nums[start];
    vector<int> dp(nums.size(), 0);
    dp[start] = nums[start];
    dp[start + 1] = max(nums[start], nums[start + 1]);
    for(int i = start + 2; i <= end; i++){
      dp[i]= max(dp[i - 1], dp[i - 2] + nums[i]);
    }
    return dp[end];
  }
  int rob(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    if(nums.size() == 1) return nums[0];
    vector<int> dp(nums.size(), 0);
    dp[0] = nums[0];dp[1] = max(dp[0],nums[1]);
    for(int i = 2; i <= nums.size(); i++){
      dp[i]= max(dp[i - 1], dp[i - 2] + nums[i]);
    }
    return dp[nums.size()];
  }  
  bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> word(wordDict.begin(),wordDict.end());
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;
    for(int i = 1; i <= s.size(); i++){
      for(int j = 0; j <= i; j++){
        string temp = s.substr(j, i - j);
        if(word.find(temp) != word.end() && dp[j] == true){
          dp[i] = true;
        }
      }
    }
    return dp[s.size()];
  }
  bool canPartition(vector<int>& nums) {
    int sum = 0;
    vector<int> dp(10001, 0);
    int numsSize = nums.size();
    for(int i = 0; i < numsSize; i++){
      sum += nums[i];
    }
    if(sum % 2 == 1) return false;
    sum /= 2;
    for(int i = 0; i < numsSize; i++){
      for(int j = sum; j >= nums[i]; j--){
        dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
      }
    }
    return dp[sum] == sum; 
  }
  int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for(int i = 1; i*i < n;i++){
      for(int j = i*i; j <= n; j++){
        dp[j] = min(dp[j], dp[j - i*i] + 1);
      }
    }
    return dp[n];
  }
  int coinChange(vector<int>& coins, int amount) {
    if(amount == 0) return 0;
    vector<int> dp(amount + 1,INT_MAX);
    dp[0] = 0;
    for(int i = 1; i <= amount; i++){
      for(int j = 0; j < coins.size(); j++){
        if(i >= coins[j]){
          dp[i] = min(dp[i],dp[i - coins[j]] + 1);
        }
      }
    }
    return dp[amount];
  }
  int combinationSum4(vector<int>& nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    for(int j = 0; j <= target; j++){
      for(int i = 0; i < nums.size(); i++){
        if(j - nums[i] >= 0 && dp[i] < INT_MAX - dp[j - nums[i]]){
          dp[j] += dp[j - nums[i]];
        }
      }
    }
    return dp[target];
  }
  int change(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for(int i = 0; i < coins.size(); i++){
      for(int j = coins[i]; j <= amount; j++){
        dp[j] = max(dp[j], dp[j - coins[i]] + 1);
      }
    }
    return dp[amount];
  }
  int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int oneSum,zeroSum;
    for(string str: strs){
      oneSum = 0; zeroSum = 0;
      for(char c : str){
        if(c == '0') zeroSum++;
        else oneSum++;
      }
      for(int i = m; i >= zeroSum; i--){
        for(int j = n; j >= oneSum; j--){
          dp[i][j] = max(dp[i][j], dp[i - zeroSum][j - oneSum] + 1);
        }
      }
    }
    return dp[m][n];
  }
  int findTargetSumWays(vector<int>& nums, int target) {
    int sum =0;
    int numsSize = nums.size();
    for(int i = 0; i < numsSize; i++){
      sum += nums[i];
    }
    if((sum + target)% 2 == 1) return 0;
    if(abs(target) > sum) return 0;
    int numsLen = (sum + target) / 2;
    vector<int> dp(numsLen + 1, 0);
    dp[0] = 1;
    for(int i = 0; i < numsSize; i++){
      for(int j = numsLen; j >= nums[i]; j--){
        dp[j] += dp[j - nums[i]];
      }
    }
    return dp[numsLen];      
  }
  int lastStoneWeightII(vector<int>& stones) {
    int sum = 0;
    for(int i = 0; i < stones.size(); i++){
      sum += stones[i];
    }
    int target = sum/2;
    vector<int> dp(target + 1, 0);
    for(int i = 0; i < stones.size(); i++){
      for(int j = target; j >= stones[i]; j--){
        dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
      }
    }
    // for( auto a : dp){
    //   cout<< a<<endl;
    // }
    return sum - 2 * dp[target];
  }
  int backBag(vector<int>& weight, vector<int>& value,int bagWeight){
    // 二维数组法
    // vector<vector<int>> dp(weight.size(), vector<int>(bagWeight + 1, 0));
    // for(int j = weight[0]; i < bagWeight; i++){
    //   dp[0][j] = value[0];
    // }
    // for(int i = 1; i < weight.size(); i++){
    //   for(int j = 0; j <= bagWeight; j++){
    //     if(j < weight[i]) dp[i][j] = dp[i-1][j];
    //     else dp[i][j] = max(dp[i-1][j], dp[i - 1][j - weight[i]] + value[i]);
    //   }
    // }
    // return dp[weight.size() - 1][bagWeight];

    // 一维数组
    vector<int> dp(bagWeight + 1,0);
    for(int i = 0; i < weight.size(); i++){
      for(int j = bagWeight; j >= weight[i]; j--){
        dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
      }
    }
    return dp[bagWeight];
  }

  int numTrees(int n) {
    vector<int> dp(n + 1);
    dp[0] = 1;
    for(int i = 1; i <= n; i++){
      for(int j = 1; j <= i; j++){
        dp[i] += dp[j - 1] * dp[i - j];
      }
    }
    return dp[n];
  }
  int integerBreak(int n) {
    vector<int> dp(n + 1);
    dp[2]= 1;
    for(int i = 3; i <= n; i++){
      for(int j = 1; j < i-1; j++){
        dp[i] = max(dp[i], max(dp[i-j] * j, (i - j) * j));
      }
    }
    return dp[n];
  }
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