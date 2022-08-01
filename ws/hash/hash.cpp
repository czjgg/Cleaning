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
    vector<string> commonChars(vector<string>& words) {
      int hash[26] = {0};
      for(int i = 0; i < words[0].size(); i++){
        hash[words[0][i] - 'a']++;
      }
      int hashOther[26]={0};
      for(int i = 1; i<words.size(); i++){
        memset(hashOther, 0, 26*sizeof(int));
        for(int j = 0; j < words[i].size(); j++){
          hashOther[words[i][j] - 'a']++;
        }
        for(int k = 0; k < 26; k++){
          hash[k] = min(hash[k], hashOther[i]);
        }
      }
      vector<string> result;
      for(int k = 0; k < 26; k++){
        while (hash[k] != 0) { // 注意这里是while，多个重复的字符
        string s(1, k + 'a'); // char -> string
        result.push_back(s);
        hash[k]--;
        }
      }
      return result;
    }
    bool isIsomorphic(string s, string t) {
      unordered_map<char, char> map1;
      unordered_map<char, char> map2;
      for(int i = 0, j = 0; i < s.size(); i++){
        if(map1.find(s[i]) != map1.end()){
          map1[s[i]] = t[j];
        }
        if(map2.find(t[j]) != map2.end(); j++){
          map2[t[j]] = s[i];
        }
        if(map1[s[i]] != t[j] || map2[t[j]] != s[i]){
          return false;
        }
      }
      return true;
    }
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size();i++){
          if(nums[i]>0){
            continue;
          }
          if(i>0&&nums[i]==nums[i-1]){
            continue;
          }
          int j=i+1,k=nums.size()-1;
          while(j<k){
            if(nums[i]+nums[j]+nums[k]>0){
              k--;
            }else if(nums[i]+nums[j]+nums[k]<0){
              j++;
            }else{
              ans.push_back({nums[i],nums[j],nums[k]});
              while(j<k&&nums[k]==nums[k-1]) k--;
              while(j<k&&nums[j]==nums[j+1]) j++;
              k--;
              j++;
            }
          }
        }
      return ans;
    }
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int,int> ABmap;
        int count=0;
        for(auto i:nums1){
          for(auto j:nums2){
            ABmap[i+j]++;
          }
        }
        for(auto c:nums3){
          for(auto d:nums4){
            if(ABmap.find(0-(c+d))!=ABmap.end()){
              count+=ABmap[0-(c+d)];
            }
          }
        }
        return count;
    }
    vector<int> twoSum(vector<int>& nums, int target) {
      unordered_map<int,int> Sum_set;
      vector<int> ans;
      for(int i=0;i<nums.size();i++){
        auto iter=Sum_set.find(target-nums[i]);
        if(iter!=Sum_set.end()){
          ans.push_back(Sum_set[target-nums[i]]);
          ans.push_back(i);
          return ans;
        }else{
          Sum_set.insert(pair<int,int>(nums[i],i));
        }
      }
      return {};  
    }
    bool isHappy(int n) {
        unordered_set<int> sum_set;
        int sum=0;
        int temp=n;
        while(1){
          sum=0;
          while(temp!=0){
            sum+=pow((temp%10),2);
            temp/=10;
          }
          if(sum==1)return true;
          else{
            if(sum_set.find(sum)!=sum_set.end()) return false;
            else {
              sum_set.insert(sum);
              temp=sum;
            }
          }
        }
    }
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> result;
        unordered_set<int> num_set(nums1.begin(),nums1.end());
        for(int num:nums2){
          if(num_set.find(num)!=num_set.end()){
            result.insert(num);
          }
        }
        return vector<int>(result.begin(),result.end());
    }
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> magmap;
        unordered_map<char, int> ransommap;
        for(auto c:ransomNote){
          ransommap[c]++;
        }
        for(auto c:magazine){
          magmap[c]++;
        }
        for(auto c:ransommap){
          if(c.second>magmap[c.first])return false;
        }
        return true;
    }
    bool isValid(unordered_map<char, int>& m1, unordered_map<char, int>& m2) {
        for(auto c:m1){
            if(c.second!=m2[c.first]){
              return false;
            }
        }
    return true;
    }

    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> cnt;
        unordered_map<char, int> m;
        for(auto c:p){
          cnt[c]++;
        }
        int l=0;
        int r=p.size()-1;
        vector<int> ans;
        for(int i=0;i<r;i++){
          m[s[i]]++;
        }
        while(r<s.size()){
          m[s[r]]++;
          if(isValid(cnt,m)) ans.push_back(l);
          m[s[l]]--;
          l++;
          r++;
        }
    return ans;
    }
    bool isAnagram(string s, string t) {
        int record[26]={0};
        for(char c:s){
          record[c-'a']++;
        }
        for(char c:t){
          record[c-'a']--;
        }
        for(int i=0;i<26;i++){
          if(record[i]) return false;
        }
        return true;
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
  vector<vector<int>> result=A.threeSum(a);
  for(vector<int> a:result){
      for(int j:a){
        cout<<j<<' ';
      }
      cout<<endl;
  }
  //cout<<A.fourSumCount(a,b,c,d)<<endl;
  getchar();
}