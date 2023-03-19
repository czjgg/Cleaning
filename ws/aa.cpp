#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<stack>
using namespace std;
int main(){
  int q;
  cin>>q;
  vector<string> strPattern(2*q);
  for(int i = 0;i < q; i++){
    cin>>strPattern[2*i];
    cin>>strPattern[2*i + 1];
  }
  vector<string> result;
  
  for(int i = 0; i < q; i++){
    unordered_map<char,int> sMap,tMap;
    string s = strPattern[2*i];
    string t = strPattern[2*i + 1];
    for(auto c : s){
      if(sMap.find(c) != sMap.end()){
        sMap[c]++;
      }else{
        sMap[c] = 1;
      }
    }
    for(char c : t){
      if(tMap.find(c) != tMap.end()){
        tMap[c]++;
      }else{
        tMap[c] = 1;
      }
    }
    bool isContinue =false;
    for(auto tItem : tMap){
      if(tItem.first != 'm' && tItem.first != 'h' && tItem.first != 'y'){
        if(sMap.find(tItem.first) == sMap.end() || tItem.second != sMap[tItem.first]){
          result.push_back("No");
          isContinue = true;
          break;
        }
      }
    }
    if(isContinue){
      continue;
    }
    stack<char> mst, mhst;
    for(int m = 0, n = 0; m < s.size() && n < t.size(); ){
      if(s[m] != t[n]){
        if((s[m] != 'm' && t[n] != 'm') &&(s[m] != 'h' && t[n] != 'h')&&(s[m] != 'y' && t[n] != 'y')){
          result.push_back("No");
          isContinue = true;
          break;
        }else if(s[m] == 'm' || s[m] == 'h' || s[m] == 'y'){
          if(s[m] = 'm'){
            mst.push(s[m]);
          }else if(s[m] == 'h'){
            if( !mst.empty()){
              mhst.push('m');
              mhst.push('h');
              mst.pop();
            }else{
              result.push_back("No");
              isContinue = true;
              break;
            }
          }else{
            if( !mhst.empty()){
              mhst.pop();
              mhst.pop();
            }else{
              result.push_back("No");
              isContinue = true;
              break;
            }
          }
          m++;
        }else{
          if(t[n] = 'm'){
            mst.push(s[m]);
          }else if(t[n] == 'h'){
            if( !mst.empty()){
              mhst.push('m');
              mhst.push('h');
              mst.pop();
            }else{
              result.push_back("No");
              isContinue = true;
              break;
            }
          }else{
            if( !mhst.empty()){
              mhst.pop();
              mhst.pop();
            }else{
              result.push_back("No");
              isContinue = true;
              break;
            }
          }
          n++;
        }

      }else{
        m++;
        n++;
      }
    }
    if(isContinue){
      continue;
    }
    result.push_back("Yes");
  }
  for(auto str: result){
      cout<< str<<endl;
  }
}