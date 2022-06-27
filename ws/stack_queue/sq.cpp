#include<iostream>
#include<stack>
#include<queue>
#include<algorithm>
#include<unordered_map>
using namespace std;
class MyQueue {
public:
    stack<int> stIn;
    stack<int> stOut;
    MyQueue() {

    }
    
    void push(int x) {
      stIn.push(x);
    }
    
    int pop() {
      if(stOut.empty()){
        while(!stIn.empty()){
          stOut.push(stIn.top());
          stIn.pop();
        }
      }
      int ans= stOut.top();
      stOut.pop();
      return ans;
    }
    
    int peek() {
      int ans=pop();
      stOut.push(ans);
      return ans;
    }
    
    bool empty() {
      return stOut.empty()&&stIn.empty();
    }
};
class MyStack {
public:
    queue<int> myQue;
    MyStack() {

    }
    
    void push(int x) {
      myQue.push(x);
    }
    
    int pop() {
      int size=myQue.size();
      size--;
      while(size--){
        myQue.push(myQue.front());
        myQue.pop();
      }
      int ans=myQue.front();
      myQue.pop();
      return ans;
    }
    
    int top() {
      return myQue.back();
    }
    
    bool empty() {
      return myQue.empty();
    }
};
class deQueue {
  public:
    deque<int> que;
    int largestRectangleArea(vector<int>& heights) {
      //单调栈思路
      stack<int> st;
      heights.insert(heights.begin(),0);
      heights.push_back(0);
      st.push(0);
      int result = 0;
      for(int i = 1; i < heights.size(); i++){
        while(heights[i] < heights[st.top()]){
          int mid = st.top();
          st.pop();
          int w = i - st.top() - 1;
          result = max(heights[mid] * w, result);
        }
        st.push(i);
      }
      return result;
      // 动态规划思路
      // int result = 0;
      // vector<int> lHeights(heights.size(), -1);
      // vector<int> rHeights(heights.size(), heights.size());
      // for(int i = 1; i < heights.size() ; i++){
      //   int t = i - 1;
      //   while(t >= 0 && heights[t] >= heights[i]) t = lHeights[t];
      //   lHeights[i] = t;
      // }
      // for(int i = heights.size() - 2; i >= 0; i--){
      //   int t = i + 1;
      //   while(t < heights.size() && heights[t] > heights[i]) t = rHeights[t];
      //   rHeights[i] = t;
      // }
      // for(int i = 0; i < heights.size(); i++){
      //   int m = heights[i] * (rHeights[i] - lHeights[i] - 1);
      //   if(m > result) result = m;
      // }
      // return result;
    }
    int trap(vector<int>& height) {
      if(height.size() <= 2) return 0;
      stack<int> st;
      st.push(0);
      int sum = 0;
      for(int i = 1; i < height.size(); i++){
        if(height[i] < height[st.top()]){
          st.push(i);
        }
        if(height[i] == height[st.top()]){
          st.pop();
          st.push(i);
        }else{
          while(!st.empty() && height[i] > height[st.top()]){
            int mid = height[st.top()];
            st.pop();
            if(!st.empty()){
              int h = min(height[st.top()], height[i]) - mid;
              int w = i - st.top() - 1;
              sum += w * h;
            }
          }
          st.push(i);
        }
      }
      return sum;
    }
    vector<int> nextGreaterElements(vector<int>& nums) {
      stack<int> st;
      vector<int> result(nums.size(), - 1);
      if(nums.size() == 0) return result;
      st.push(0);
      for (int i = 0; i < nums.size() * 2; i++) {
            // 模拟遍历两边nums，注意一下都是用i % nums.size()来操作
            while (!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
                result[st.top()] = nums[i % nums.size()];
                st.pop();
            }
            st.push(i % nums.size());
        }
      return result;
    }
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
      stack<int> st;
      vector<int> result(nums1.size(), - 1);
      if(nums1.size() == 0) return result;
      
      unordered_map<int, int> umap;
      for(int i = 0; i < nums1.size(); i++){
        umap[nums1[i]] = i;
      }
      st.push(0);
      for(int i = 1; i < nums2.size(); i++){
        while(!st.empty() && nums2[i] > nums2[st.top()]){
          if(umap.count(nums2[st.top()]) > 0){
            int index = umap[nums2[st.top()]];
            result[index] = nums2[i];
          }
          st.pop();
        }
        st.push(i);
      }
      return result;
    }
    vector<int> dailyTemperatures(vector<int>& temperatures) {
      stack<int> st;
      vector<int> result(temperatures.size(),0);
      for(int i = 0;i < temperatures.size(); i++){
        while(!st.empty() && temperatures[i] > temperatures[st.top()]){
          result[st.top()] = i - st.top();
          st.pop();
        }
        st.push(i);
      }
      return result;
    }
    void pop(int value){
      if(!que.empty()&&value==que.front()){
        que.pop_front();
      }
    }
    void push(int value){
      while(!que.empty()&&value>que.back()){
        que.pop_back();
      }
      que.push_back(value);
    }
    int front(){
      return que.front();
    }
};
class Solution {
public:
    class myComp{
      public:
        bool operator()(const pair<int,int> &lhs, const pair<int,int> &rhs){
          return lhs.second> rhs.second;
        }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
      unordered_map<int,int> myMap;
      for(int i=0;i<nums.size();i++){
        myMap[nums[i]]++;
      }
      priority_queue<pair<int,int>,vector<pair<int,int>>,myComp> pri_que;
      for(unordered_map<int,int>::iterator it=myMap.begin();it!=myMap.end();it++){
        pri_que.push(*it);
        if(pri_que.size()>k){
          pri_que.pop();
        }
      }
      vector<int> result(k);
      for(int i=k-1;i>=0;i--){
        result[i]=pri_que.top().first;
        pri_que.pop();
      }
      return result;
    }
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deQueue que;
        vector<int> ans;
        for(int i=0;i<k;i++){
          que.push(nums[i]);
        }
        ans.push_back(que.front());
        for(int i=k;i<nums.size();i++){
          que.pop(nums[i-k]);
          que.push(nums[i]);
          ans.push_back(que.front());
        }
        return ans;
    }
    int evalRPN(vector<string>& tokens) {
      stack<int> st;
      for(auto s:tokens){
        if(s=="+"||s=="-"||s=="*"||s=="/"){
          int num1 = st.top();
          st.pop();
          int num2 = st.top();
          st.pop();
          if (s == "+") st.push(num2 + num1);
          if (s == "-") st.push(num2 - num1);
          if (s == "*") st.push(num2 * num1);
          if (s == "/") st.push(num2 / num1);
        }else{
          st.push(stoi(s));
        }
      }
      int ans=st.top();
      st.pop();
      return ans;
    }
    string removeDuplicates(string s) {
      stack<char> st;
      for(char c:s){
        if(st.empty()||st.top()!=c){
          st.push(c);
        }else{
          st.pop();
        }
      }
      string ans="";
      while(!st.empty()){
        ans+=st.top();
        st.pop();
      }
      reverse(ans.begin(),ans.end());
      return ans;
    }
    bool isValid(string s) {
      stack<int> st;
      int slen=s.size();
      for(int i=0;i<slen;i++){
        if(s[i]=='(')st.push(')');
        else if(s[i]=='{') st.push('}');
        else if(s[i]=='[') st.push(']');
        else if(st.empty()||st.top()!=s[i]) return false;
        else st.pop();
      }
      return st.empty();
    }
};
int main(){
  string s="abccbad";
  vector<string> ipt={"5","6","9","-","+"};
  vector<int> a={1,1,1,2,2,3,4,4,4,4,4,6,6,6,45,4,54,54,54,54,5,5,45,5,66,4,};
  Solution A;
  /*cout<<A.removeDuplicates(s);
  cout<<A.evalRPN(ipt);*/
  vector<int> ans=A.topKFrequent(a,4);
  for(auto i:ans){
    cout<<i<<' ';
  }
  getchar();
}