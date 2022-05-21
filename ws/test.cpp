#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
#include<unordered_set>
#include<cstring>
#include<math.h>
#include<algorithm>
using namespace std;


class solution{
private:
    vector<int> path; // 用来存放符合条件结果
    int count = 0;
    void backtrackingToFindAllSum2(vector<int>& candidates, int targetSum, int startIndex, int sum){
      if(sum == targetSum&& !path.empty()){
        count++;
        return;
      }
      for(int i = startIndex; i < candidates.size() && sum + candidates[i] <= targetSum ; i++){
        sum += candidates[i];
        path.push_back(candidates[i]);
        backtrackingToFindAllSum2(candidates,targetSum,i+1,sum);
        path.pop_back();
        sum-=candidates[i];
      }
    }

public:
  int combinationSum2(vector<int>& candidates, int target) {
      path.clear();
      sort(candidates.begin(),candidates.end());
      backtrackingToFindAllSum2(candidates,target,0,0);
      return count;
  }
};

int main(){
    
    int k,n,temp;
    vector<int> candidates;
    cin>>n>>k;
    for(int i = 0; i < n; i++){
        cin>>temp;
        candidates.push_back(temp);
    }
    sort(candidates.begin(),candidates.end());
    solution A;
    int count=A.combinationSum2(candidates,k);
    cout<<count;
    getchar();
}
