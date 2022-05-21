#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
#include<unordered_set>
#include<cstring>
#include<math.h>
#include<list>
#include<algorithm>
using namespace std;

class Solution{
    // 按绝对值排序
    // static bool cmp(int a, int b) {
    //   return abs(a) > abs(b);
    // }

    // 从大到小，相同的从小到大
    // static bool cmp(const vector<int>& a, const vector<int>& b) {
    //   if(a[0] == b[0]) return a[1] < b[1];
    //   return a[0] > b[0];
    // }

    // 从小到大,按照第一个元素排序
    // static bool cmp(const vector<int>& a, const vector<int>& b) {
    //     return a[0] < b[0];
    // }
    // 按照区间右边界排序
    static bool cmp (const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    }
private:
    
public:
    int dp[1005][2];
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
      if(intervals.size() == 0) return 0;
      sort(intervals.begin(), intervals.end(), cmp);
      int result = 1;
      for(int i = 1; i < intervals.size(); i++){
        if(intervals[i][0] >= intervals[i-1][1]){
          result++;
        }else{
          intervals[i][1] = min(intervals[i][1],intervals[i-1][1]);
        }
      }
      return intervals.size() - result;
    }
    int findMinArrowShots(vector<vector<int>>& points) {
      if(points.size() == 0) return 0;
      sort(points.begin(),points.end(),cmp);
      int result = 1;
      for(int i = 1; i < points.size(); i++){
        if(points[i - 1][1] < points[i][0]){
          result++;
        }else{
          points[i][1] = min(points[i][1], points[i-1][1]);
        }
      }
      return result;
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
      sort(people.begin(),people.end(),cmp);
      list<vector<int>> que;
      for(int i = 0; i < people.size(); i++){
        int position = people[i][1]; // 插入到下标为position的位置
        std::list<vector<int>>::iterator it = que.begin();
        while (position--) { // 寻找在插入位置
          it++;
        }
        que.insert(it, people[i]);
      }
      return vector<vector<int>>(que.begin(), que.end());
    }
    bool lemonadeChange(vector<int>& bills) {
      int five = 0, ten = 0;
      for(int i = 0; i < bills.size(); i++){
        if(bills[i] == 5){
          five++;
        }
        if(bills[i] == 10){
          if(five == 0) return false;
          five--;
          ten++;
        }
        if(bills[i] == 20){
          if(five > 0 && ten > 0){
            five--;
            ten--;
          }else if(five > 2){
            five -=3;
          }else return false;
        }
      }
      return true;
    }
    int candy(vector<int>& ratings) {
      vector<int> candyVec(ratings.size(),1);
      for(int i = 0; i < ratings.size()-1; i++){
        if(ratings[i+1] > ratings[i]){
          candyVec[i+1] = candyVec [i] + 1;
        }
      }
      for(int i = ratings.size() - 1; i > 0; i--){
        if(ratings[i - 1] > ratings[i]){
          candyVec[i - 1] = max(candyVec[i - 1], candyVec[i] + 1);
        }
      }
      int result = 0;
      for(int i : candyVec){
        result += i;
      }
      return result;
    }
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
      int curSum = 0;
      int totalSum = 0;
      int start = 0;
      for(int i = 0; i < gas.size(); i++){
        curSum += gas[i] - cost[i];
        totalSum += gas[i] - cost[i];
        if(curSum < 0){
          curSum = 0;
          start = i + 1;
        } 
      }
      if(totalSum < 0) return -1;
      return start;
    }
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