#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
  
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