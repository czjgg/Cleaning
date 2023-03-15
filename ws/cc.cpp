#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
#include<algorithm>
using namespace std;
int main(){
  int N;
  cin>>N;
  vector<string> questionPaper(N);
  unordered_map<string,int> letterMap;
  for(int i = 0; i < N; i++){
    cin>>questionPaper[i];
    if(letterMap.count(questionPaper[i]) == 0) letterMap[questionPaper[i]] = 1;
    else letterMap[questionPaper[i]]++;
  }
  vector<pair<string,pair<int,int>>> ABC;
  char lowletter, highletter;
  for(int i = 0; i < 3; i++){
    int peopleNum, price;
    cin>> peopleNum>>price;
    ABC.push_back({to_string('A' + i),{peopleNum,price}});
  }
  int count = 0;
  sort(ABC.begin(),ABC.end(),[](pair<string,pair<int,int>> a , pair<string,pair<int,int>> b){
    return a.second.first < b.second.first;
  });
  if(letterMap[ABC[0].first]  < ABC[0].second.first) {
    cout<<"No"
  }
  
}