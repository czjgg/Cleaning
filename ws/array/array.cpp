#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
  vector<int> searchRange(vector<int>& nums, int target) {
    if(nums.size() == 0||target < nums[0] || target > nums[nums.size() - 1]) return {-1, -1};
    int leftBorder,rightBorder;
    int left = 0, right = nums.size();
    int index = 0;
    while(left < right){
      index = (left + right) / 2;
      if(nums[index] == target){
        break;
      }else if(nums[index] < target){
        left = index + 1;
      }else{
        right = index;
      }
    }
    if(left >= right) return {-1, -1};
    int temp = index;
    while(index >=0 && nums[index] == target){
      leftBorder = index;
      --index;
    }
    index = temp;
    while(index < nums.size()&& nums[index] == target){
      rightBorder = index;
      ++index;
    }
    return {leftBorder, rightBorder};
  }
  int pivotIndex(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) sum += num; // 求和
        int leftSum = 0;    // 中心索引左半和
        int rightSum = 0;   // 中心索引右半和
        for (int i = 0; i < nums.size(); i++) {
            leftSum += nums[i];
            rightSum = sum - leftSum + nums[i];
            if (leftSum == rightSum) return i;
        }
        return -1;
  }
  void reverse(vector<int>& nums, int head, int last){
    int size = last - head;
    for(int i = head; i < head + size / 2; i++){
      int temp = nums[i];
      nums[i] = nums[last- (i - head) - 1];
      nums[last - (i - head) - 1] = temp;
    }
    return ;
  }
  void rotate(vector<int>& nums, int k) {
    k = k % nums.size();
    reverse(nums, 0, nums.size());
    reverse(nums, 0, k);
    reverse(nums, k, nums.size());
    return;
  }
  void moveZeroes(vector<int>& nums) {
    int slow = 0;
    for(int fast = 0; fast < nums.size();fast++){
      if(nums[fast] == 0){
        continue;
      }else{
        nums[slow] = nums[fast];
        slow++;
      }
    }
    for(;slow < nums.size(); slow++){
      nums[slow] = 0;
    }
  }
  bool uniqueOccurrences(vector<int>& arr) {
    int count[2002]={0};
    for(int i = 0; i < arr.size(); i++){
      ++count[arr[i] + 1000];
    }
    bool fre[2002] = {false};
    for(int i = 0; i < 2002; i++){
      if(count[i]){
        if(fre[count[i]] == false){
          fre[count[i]] = true;
        }else {
          return true;
        }
      }
    }
    return false;
  }
  bool validMountainArray(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    if(right < 2) return false;
    for(int i = 0; i < arr.size() - 1; i++){
      if(arr[i + 1] > arr[i]){
        ++left;
      }else{
        break;
      }
    }
    for(int i = arr.size() - 1; i > 0; i--){
      if(arr[i - 1] > arr[i]){
        --right;
      }else{
        break;
      }
    }
    if(left == arr.size() - 1 || right == 0) return false;
    if(left == right) return true;
    return false;
  }
  vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    vector<int> vec = nums;
    sort(vec.begin(),vec.end());
    int hash[101];
    for(int i = vec.size() - 1; i >= 0; i--){
      hash[vec[i]] = i;
    }
    for(int i = 0; i < nums.size(); i++){
      vec[i]=hash[nums[i]];
    }
    return vec;
  }
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    int loop = (min(m, n) + 1) / 2;
    int startx = 0;
    int starty = 0;
    int offset = 1;
    int flag = abs(m - n) % 2;
    vector<int> result;
    int i, j;
    for(; loop > 1|| flag == 0; loop--){
      for(j = starty; j < starty + n - offset; j++){
        result.push_back(matrix[startx][j]);
      }
      for(i = startx; i < startx + m - offset; i++){
        result.push_back(matrix[i][j]);
      }
      for(; j > starty; j--){
        result.push_back(matrix[i][j]);
      }
      for(; i > startx; i--){
        result.push_back(matrix[i][j]);
      }
      startx++;
      starty++;
      offset += 2;
    }
    if(flag == 1){
      i = startx;
      j = starty;
      if(m >= n){
        for(; j < starty + n - offset + 1; j++){
          result.push_back(matrix[i][j]);
        }
      }else{
        for(; i < starty + m - offset + 1; i ++){
          result.push_back(matrix[i][j]);
        }
      }
    }
    return result;
  }
};
int main(){
  vector<int> a={1,1,2,3,4};
  vector<char> b={'a','b','c','d','e','f','g'};
  string c="asdfasdfasdfasdf";
  string e="acacdef";
  Solution A;
  for(auto f:A.searchRange(a,1)){
    cout<<f<<endl;
  }
  getchar();
}