#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main(){
  int T,N;
  cin>> T>> N;
  vector<vector<int>> life(T,vector<int>(N));
  for(int i = 0; i< T; i++){
    for(int j = 0; j < N; j++){
      cin>>life[i][j];
    }
  }
  for(int i = 0; i< T; i++){
    bool hasOne = false;
    int opTimes = 0;
    for(int j = 0; j < N; j++){
      if(life[i][j] == 1 ){
        if(hasOne){
          hasOne = false;
          opTimes++;//当存在两个1，使用一次a键
        }else{
          hasOne =true;//只有一个1，先别急
        }
      }else if(life[i][j] >= 2){
        opTimes++;//大于2是吧，秒了你
      }
    }
    if(hasOne) opTimes++;//出来把剩下的一个1处理了
    cout<<opTimes<<endl;
  }
}