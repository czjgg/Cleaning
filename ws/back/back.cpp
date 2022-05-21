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
    unordered_map<string, map<string, int>> targets;
    vector<vector<int>> result; // 存放符合条件结果的集合
    vector<int> path; // 用来存放符合条件结果
    vector<string> resultStr;
    vector<string> pathPalindrome;
    vector<vector<string>> resultPalindrome;
    vector<vector<string>> resultQueen;
    string s;

    
    const string letterMap[10] = {
        "", // 0
        "", // 1
        "abc", // 2
        "def", // 3
        "ghi", // 4
        "jkl", // 5
        "mno", // 6
        "pqrs", // 7
        "tuv", // 8
        "wxyz", // 9
    };

    bool backtrackingToShuDu(vector<vector<char>>& board){
      for(int i = 0; i < board.size(); i++){
        for( int j = 0; j < board[0].size(); j++){
          if(board[i][j] != '.'){
            continue;
          }
          for(char k = '1'; k <= '9'; k++){
            if(isValidBoard(i, j , k, board)){
              board[i][j] = k;
              if(backtrackingToShuDu(board)) return true;
              board[i][j] = '.';
            }
          }
          return false;
        }
      }
      return true;
    }
    bool isValidBoard(int row, int col,char val,vector<vector<char>>& board){
      for(int i = 0; i < 9; i++){
        if(board[row][i] == val){
          return false;
        }
      }
      for(int j = 0; j < 9; j++){
        if(board[j][col] == val){
          return false;
        }
      }
      int startRow = (row/3) * 3;
      int startCol = (col/3) * 3;
      for(int i = startRow; i < startRow + 3; i++){
        for(int j = startCol; j < startCol + 3; j++){
          if(board[i][j] == val){
            return false;
          }
        }
      }
      return true;
    }
    void backtrackingNQueen(int n, int row, vector<string>& chessboard) {
      if(row == n){
        resultQueen.push_back(chessboard);
        return;
      }
      for(int col = 0; col < n; col++){
        if(isValidChess(row, col, chessboard, n)){
          chessboard[row][col] = 'Q';
          backtrackingNQueen(n, row + 1, chessboard);
          chessboard[row][col] = '.';
        }
      }
    }
    bool isValidChess(int row, int col, vector<string>& chessboard, int n) {
      for(int i = 0; i < row; i++){
        if(chessboard[i][col] == 'Q'){
          return false;
        }
      }
      for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--){
        if(chessboard[i][j] == 'Q'){
          return false;
        }
      }
      for(int i = row - 1, j= col + 1; i >= 0 && j < n; i--, j++){
        if(chessboard[i][j] == 'Q'){
          return false;
        }
      }
      return true;
    }
    bool backtrackingToFindRoute(int ticketNum, vector<string>& result) {
      if(result.size() == ticketNum + 1){
        return true;
      }
      for(pair<const string , int>& target: targets[result[result.size()-1]]){
        if(target.second > 0){
          result.push_back(target.first);
          target.second--;
          if(backtrackingToFindRoute(ticketNum, result)) return true;
          target.second++;
          result.pop_back();
        }
      }
      return false;
    }
    void backtrackingToFIndPermute2 (vector<int>& nums, vector<bool>& used){
      if(path.size() == nums.size()){
        result.push_back(path);
        return;
      }
      for(int i = 0; i < nums.size(); i++){
        if(i > 0 && nums[i] == nums[i - 1] && used[i -1] == false){
          continue;
        }
        if(used[i] == false){
          used[i] = true;
          path.push_back(nums[i]);
          backtrackingToFIndPermute2(nums, used);
          path.pop_back();
          used[i] = false;
        }
      }
    }
    void backtrackingToFIndPermute (vector<int>& nums, vector<bool>& used){
      if(path.size() == nums.size()){
        result.push_back(path);
        return;
      }
      for(int i = 0; i < nums.size(); i++){
        if(used[i]){
          continue;
        }
        used[i] = true;
        path.push_back(nums[i]);
        backtrackingToFIndPermute(nums, used);
        path.pop_back();
        used[i] = false;
      }
    }
    void backtrackingToFindSubsequences(vector<int>& nums, int startIndex) {
      if(path.size()>1){
        result.push_back(path);
      }
      int used[201]={0};
      for(int i = startIndex; i < nums.size(); i++){
        if(!path.empty() && nums[i] < path.back() || used[nums[i] + 100] == 1){
          continue;
        }
        used[nums[i] + 100] = 1;
        path.push_back(nums[i]);
        backtrackingToFindSubsequences(nums, i +1);
        path.pop_back();
      }    
    }
    void backtrackingToFindSubsets2(vector<int>& nums, int startIndex){
      result.push_back(path);
      for(int i = startIndex; i < nums.size(); i++){
        if(i > 0 && nums[i] == nums[i-1] && i != startIndex){
          continue;
        }
        path.push_back(nums[i]);
        backtrackingToFindSubsets(nums, i + 1);
        path.pop_back();
      }
    }
    void backtrackingToFindSubsets(vector<int>& nums, int startIndex){
      result.push_back(path);
      for(int i = startIndex; i < nums.size(); i++){
        path.push_back(nums[i]);
        backtrackingToFindSubsets(nums, i + 1);
        path.pop_back();
      }
    }
    void backtrackingToCheckIPAddress(string& s, int startIndex, int pointNum){
      if(pointNum == 3){
        if(isValidIPAddress(s, startIndex, s.size()-1)){
          resultStr.push_back(s);
        }
        return;
      }
      for(int i = startIndex; i < s.size(); i++){
        if(isValidIPAddress(s, startIndex, i)){
          s.insert(s.begin() + i + 1, '.');
          pointNum++;
          backtrackingToCheckIPAddress(s, i + 2, pointNum);
          pointNum--;
          s.erase(s.begin()+ i + 1);
        }else break;
      }
      
    }
    bool isValidIPAddress(const string& s, int start, int end){
      if(start > end){
        return false;
      }
      if(s[start] == '0' && start != end){
        return false;
      }
      int num = 0;
      for(int i = start; i <= end; i++){
        if(s[i] > '9' || s[i] < '0'){
          return false;
        }else{
          num = 10 * num + (s[i] - '0');
        }
        if(num > 255){
        return  false;
        }
      }
      return true;
    }
    void backtrackingToDividePalindrome (const string& s, int startIndex) {
      if(startIndex>=s.size()){
        resultPalindrome.push_back(pathPalindrome);
        return ;
      }
      for(int i = startIndex; i < s.size(); i++){
        if(isPalindrome(s, startIndex, i)){
          string s = s.substr(startIndex, i - startIndex + 1);
          pathPalindrome.push_back(s);
        }else{
          continue;
        }
        backtrackingToDividePalindrome(s, i+1);
        pathPalindrome.pop_back();
      }
    }
    bool isPalindrome(const string& s, int start, int end) {
      for(int i = start, j = end; i <= j; i++,j--){
        if(s[i] != s[j]){
          return false;
        }
      }
      return true;
    }
    void backtrackingToFindAllSum2(vector<int>& candidates, int targetSum, int startIndex, int sum){
      if(sum == targetSum){
        result.push_back(path);
        return;
      }
      for(int i = startIndex; i < candidates.size() && sum + candidates[i] <= targetSum ; i++){
        if (i > startIndex && candidates[i] == candidates[i - 1]) {
                continue;
        }
        sum += candidates[i];
        path.push_back(candidates[i]);
        backtrackingToFindAllSum2(candidates,targetSum,i+1,sum);
        path.pop_back();
        sum-=candidates[i];
      }
    }
    void backtrackingToFindAllSum(vector<int>& candidates, int targetSum, int startIndex, int sum){
      if(sum == targetSum){
        result.push_back(path);
        return;
      }
      for(int i = startIndex; i < candidates.size()&& sum + candidates[i] <= targetSum; i++){
        sum += candidates[i];
        path.push_back(candidates[i]);
        backtrackingToFindAllSum(candidates,targetSum,i,sum);
        path.pop_back();
        sum-=candidates[i];
      }
    }
    void backtrackingToFindAllString(const string& digits, int index) {
      if(index==digits.size()){
        resultStr.push_back(s);
        return;
      }
      int digit=digits[index]-'0';
      string letters=letterMap[digit];
      for(int i=0;i<letters.size();i++){
        s.push_back(letters[i]);
        backtrackingToFindAllString(digits,index+1);
        s.pop_back();
      }
    }
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

    void solveSudoku(vector<vector<char>>& board) {
      backtrackingToShuDu(board);
    }
    vector<vector<string>> solveNQueens(int n) {
      resultQueen.clear();
      vector<string> chessboard(n, string(n, '.'));
      backtrackingNQueen(n, 0, chessboard);
      return resultQueen;
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
      targets.clear();
      vector<string> resultRoute;
      for(const vector<string>& vec : tickets){
        targets[vec[0]][vec[1]]++;
      }
      resultRoute.push_back("JFK");
      backtrackingToFindRoute(tickets.size(),resultRoute);
      return resultRoute;
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
      result.clear();
      path.clear();
      vector<bool> used(nums.size(), false);
      sort(nums.begin(),nums.end());
      backtrackingToFIndPermute2(nums, used);
      return result;
    }
    vector<vector<int>> permute(vector<int>& nums) {
      result.clear();
      path.clear();
      vector<bool> used(nums.size(), false);
      backtrackingToFIndPermute(nums, used);
      return result;
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
      path.clear();
      result.clear();
      backtrackingToFindSubsequences(nums, 0);
      return result;
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
      path.clear();
      result.clear();
      sort(nums.begin(),nums.end());
      backtrackingToFindSubsets2(nums,0);
      return result;
    } 
    vector<vector<int>> subsets(vector<int>& nums) {
      path.clear();
      result.clear();
      backtrackingToFindSubsets(nums,0);
      return result;
    }
    vector<string> restoreIpAddresses(string s) {
      resultStr.clear();
      if(s.size() > 12) return resultStr;
      backtrackingToCheckIPAddress(s, 0, 0);
      return resultStr;
    }
    vector<vector<string>> partition(string s) {
      resultPalindrome.clear();
      pathPalindrome.clear();
      backtrackingToDividePalindrome(s, 0);
      return resultPalindrome;
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
      result.clear();
      path.clear();
      sort(candidates.begin(),candidates.end());
      backtrackingToFindAllSum2(candidates,target,0,0);
      return result; 
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
      result.clear();
      path.clear();
      sort(candidates.begin(),candidates.end());
      backtrackingToFindAllSum(candidates,target,0,0);
      return result;  
    }
    vector<string> letterCombinations(string digits) {
      s.clear();
      resultStr.clear();
      if(digits.size()==0){
        return resultStr;
      }
      backtrackingToFindAllString(digits,0);
      return resultStr;
    }
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