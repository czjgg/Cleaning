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
    static bool cmp(int a, int b) {
      return abs(a) > abs(b);
    }
private:
    
public:
    int dp[1005][2];

    int largestSumAfterKNegations(vector<int>& A, int K) {
        sort(A.begin(),A.end(),cmp);
        for(int i = 0; i < A.size() && K > 0; i++){
          if(A[i] < 0 ){
            A[i] = -A[i];
            K--;
          }
        }
        if(K % 2 == 1) A[A.size()-1] *= -1;
        int result = 0;
        for(int a : A){
          result += a;
        }
        return result;
    }
    int jump(vector<int>& nums) {
      int curDistance = 0;
      int ans = 0;
      int nextDistance = 0;
      for(int i = 0; i < nums.size() - 1; i++){
        nextDistance = max(nextDistance, i + nums[i]);
        if(i == curDistance){
          ans++;
          curDistance = nextDistance;
        }
      }
      return ans;
    }
    bool canJump(vector<int>& nums) {
      int cover = 0;
      for(int i = 0; i <= cover; i++){
        cover = max(cover, i + nums[i]);
        if(cover >= nums.size()-1) return true;
      }
      return false;
    }
    int maxProfit(vector<int>& prices) {
      int result = 0;
      for(int i = 1; i < prices.size(); i++){
        result += max(prices[i]-prices[i-1], 0);
      }
      return result;
    }
    int maxSubArray(vector<int>& nums) {
      int count = 0;
      int result = INT_MIN;
      for(int i = 0; i < nums.size(); i++){
        count += nums[i];
        if(count > result){
          result = count;
        }
        if(count < 0){
          count = 0;
        }
      }
      return result;
    }
    int wiggleMaxLength(vector<int>& nums) {
      // 贪心
      // if(nums.size() <= 1){
      //   return nums.size();
      // }
      // int curDiff = 0;
      // int preDiff = 0;
      // int result = 1;
      // for(int i = 0; i < nums.size() - 1; i++){
      //   curDiff = nums[i + 1] - nums[i];
      //   if((curDiff > 0 && preDiff <= 0) || (curDiff < 0 && preDiff >= 0)){
      //     result++; 
      //     preDiff = curDiff;
      //   }
      // }
      // return result;

      // 动态规划
      memset(dp, 0 ,sizeof dp);
      dp[0][0] = dp[0][1] = 1;
      
      for(int i = 1; i < nums.size(); i++){
        dp[i][0] = dp[i][1] =1;
        for( int j = 0; j < i; j++){
          if(nums[j] > nums[i]){
            dp[i][1] = max(dp[i][1], dp[j][0] + 1);
          }
        }
        for( int j = 0; j < i; j++){
          if(nums[j] < nums[i]){
            dp[i][0] = max(dp[i][0], dp[j][1] + 1);
          }
        }
      }
      return max(dp[nums.size()-1][0],dp[nums.size()-1][1]);
    }
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
  // for(vector<int> a:result){
  //   for(int b: a){
  //     cout<<b;
  //   }
  //   cout<<endl;
  // }
  getchar();
}