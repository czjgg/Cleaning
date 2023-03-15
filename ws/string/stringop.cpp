#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
  bool backspaceCompare(string S, string T) {
        int sSkipNum = 0; // 记录S的#数量
        int tSkipNum = 0; // 记录T的#数量
        int i = S.size() - 1;
        int j = T.size() - 1;
        while (1) {
            while (i >= 0) { // 从后向前，消除S的#
                if (S[i] == '#') sSkipNum++;
                else {
                    if (sSkipNum > 0) sSkipNum--;
                    else break;
                }
                i--;
            }
            while (j >= 0) { // 从后向前，消除T的#
                if (T[j] == '#') tSkipNum++;
                else {
                    if (tSkipNum > 0) tSkipNum--;
                    else break;
                }
                j--;
            }
            // 后半部分#消除完了，接下来比较S[i] != T[j]
            if (i < 0 || j < 0) break; // S 或者T 遍历到头了
            if (S[i] != T[j]) return false;
            i--;j--;
        }
        // 说明S和T同时遍历完毕
        if (i == -1 && j == -1) return true;
        return false;
  }
  bool isLongPressedName(string name, string typed) {
    int i = 0, j = 0;
    while(i < name.size() && j < typed.size()){
      if(name[i] == typed[j]){
        i++;
        j++;
      }else{
        if(j == 0) return false;
        if(typed[j] == typed[j - 1]) {
          j++;
          continue;
        }
        return  false;
      }
    }
    if(i < name.size()){
      return false;
    }
    while(j < typed.size()){
      if(typed[j] == typed[j - 1]) j++;
      else return false;
    }
    return true;
  }
  int extent(const string& s, int i ,int j,int n){
    int res = 0;
    while(i >= 0 && j <= n && s[i] == s[j]){
      res++;
      i--;
      j++;
    }
    return res;
  }
  string longestPalindrome(string s) {
    int result = 0;
    int left,right;
    for(int i = 0; i < s.size(); i++){
      int cen = extent(s, i, i, s.size());
      if(cen * 2 - 1 > result){
        left = i - (cen - 1) ;
        right = i + (cen - 1) ;
        result = cen * 2 - 1;
      }
      int mid = extent(s, i, i + 1, s.size());
      if(mid * 2 > result){
        left = i - mid + 1;
        right = i + mid ;
        result = 2 * mid;
      }
    }
    return s.substr(left,right - left + 1);
  }
  void getnext(int* next,const string& s){
    int j=0;
    next[0]=0;
    for(int i=1;i<s.size();i++){
      while(j>0&&s[j]!=s[i]){
        j=next[j-1];
      }
      if(s[i]==s[j]){
        j++;
      }
      next[i]=j;
    }
  }
  bool repeatedSubstringPattern(string s) {
    if(s.size()==0){
      return 0;
    }
    int next[s.size()];
    getnext(next,s);
    int len=s.size();
    if(next[len-1]!=0&&len%(len-next[len-1])==0){
      return true;
    }
    return false;
  }
  int strStr(string haystack, string needle) {
    if(needle.size()==0){
      return 0;
    }      
    int next[needle.size()];
    getnext(next,needle);
    int j=0;
    for(int i=0;i<haystack.size();i++){
      while(j>0&&haystack[i]!=needle[j]){
        j=next[j-1];
      }
      if(haystack[i]==needle[j]){
        j++;
      }
      if(j==needle.size()){
        return (i-needle.size()+1);
      }
    }
    return -1;
  }
  string reverseLeftWords(string s, int n) {
      reverse(s,0,s.size()-1);
      reverse(s,0,s.size()-1-n);
      reverse(s,s.size()-n,s.size()-1);
      return s;
  }
  void reverse(string& s,int start,int end){
    for(int i=start,j=end;i<j;i++,j--){
      swap(s[i],s[j]);
    }
  }
  void removeExtraSpace(string& s){
    int slen=s.size();
    int i=0,j=0;
    while(slen>0&&s[i]==' '&&i<slen){
        i++;
    }
    while(i<slen){
      if(i>0&&s[i]==' '&&s[i]==s[i-1]){
        i++;
      }else{
        s[j]=s[i];
        i++;
        j++;
      }
    }
    if(s[j-1]==' '){
      s.resize(j-1);
    }else{
      s.resize(j);
    }
  }
  string reverseWords(string s) {
    removeExtraSpace(s);
    reverse(s,0,s.size()-1);
    int i=0,j=0;
    while(i<s.size()){
      while(s[i]!=' '&&i<s.size()){
        i++;
      }
      reverse(s,j,i-1);
      j=i+1;
      i++;
    }
    return s;
  }
  string replaceSpace(string s) {
    int count=0;
    int slen=s.size();
    for(int i=0;i<slen;i++){
      if(s[i]==' '){
        count++;
      }
    }
    s.resize(slen+2*count);
    for(int i=slen-1,j=s.size()-1;i>=0;i--,j--){
      if(s[i]==' '){
        s[j]='0';
        s[j-1]='2';
        s[j-2]='%';
        j-=2;
      }else{
        s[j]=s[i];
      }
    }
    return s;
  }
  string reverseStr(string s, int k) {
    int n=0,m=s.size();
    while(n+2*k<m){
      for(int i=n,j=n+k-1; i<j; i++, j--){
        swap(s[i],s[j]);
      }
      n+=2*k;
    }
    if(n+k<m){
      for(int i=n,j=n+k-1; i<j; i++, j--){
        swap(s[i],s[j]);
      }
    }else{
      for(int i=n,j=m-1; i<j; i++, j--){
        swap(s[i],s[j]);
      }
    }
    return s;
  }
  void reverseString(vector<char>& s) {
    char temp;
    for(int i=0,j=s.size()-1; i<j; i++, j--){
      temp=s[i];
      s[i]=s[j];
      s[j]=temp;
    }        
  }
};
int main(){
  vector<char> b={'a','b','c','d','e','f','g'};
  string c="asdfasdfasdfasdf";
  string e="acacdef";
  Solution A;
  bool d=A.repeatedSubstringPattern(c);
  //for(auto c:b)
  cout<<d<<endl;
  getchar();
}