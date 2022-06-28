#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
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
  vector<char> b={'a','b','c','d','e','f','g'};
  string c="asdfasdfasdfasdf";
  string e="acacdef";
  Solution A;
  //for(auto c:b)
  getchar();
}