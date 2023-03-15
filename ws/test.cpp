#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
#include<unordered_set>
#include<cstring>
#include<math.h>
#include<list>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;

stack<int> sq;
deque<int> q;
vector<vector<int>> results;

void backTracking(int count, int n,stack<int> sq,deque<int> que,bool isright){
  if(count > n) return;
  if(count == n){
    vector<int> path;
    while(!que.empty()){
      path.push_back(que.front());
      que.pop_front();
    }
    while(!sq.empty()){
      path.push_back(sq.top());
      sq.pop();
    }
    results.push_back(path);
    return;
  }
  sq.push(count + 1);
  backTracking(count + 1, n, sq, que, false);

  sq.pop();

  que.push_front(sq.top());
  sq.pop();
  return;
}
int main(){
        int n =0;
        cin>>n;
        backTracking(0,n,sq,q,false);
        for(auto a: results){
          for(auto b:a){
                cout<< b<< ' ';
        }
       cout<< endl;
      }
      while(cin>>n, !cin.eof()){
        if(cin.bad()){
          throw std::runtime_error("cin is corrupted");
        }
        if(cin.fail()){
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
          continue;
        }
      }
      getchar();
      getchar();
}
