#include<iostream>
#include<limits>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
void treeInsert(TreeNode* cur,int val,bool left){
  TreeNode* temp=new TreeNode(val);
  if(left){
    cur->left=temp;
  }else{
    cur->right=temp;
  }
  return;
}
class Solution {
public:
    int result;

    int getHeight(TreeNode* node) {
      if(node ==nullptr){
        return 0;
      }
      int leftHeight = getHeight(node->left);
      if(leftHeight == -1) return -1;
      int rightHeight = getHeight(node->right);
      if(rightHeight == -1) return -1;
      return abs(leftHeight-rightHeight) > 1? -1: max(leftHeight,rightHeight) + 1;
    }
    bool isBalanced(TreeNode* root) {
      return getHeight(root) == -1 ? false:true;
    }
    void getDepth(TreeNode* node, int depth) {//前序遍历求节点深度逻辑
        result=depth>result?depth:result;
        if(node->left!=nullptr){
          getDepth(node->left,depth+1);
        }
        if(node->right!=nullptr){
          getDepth(node->right,depth+1);
        }
        return ;
    }
    int maxDepth(TreeNode* root) {
      //以下是递归法
      // if(root==nullptr) return 0;
      // int depth=0;
      // for(int i=0;i<root->children.size();i++){
      //   depth=max(depth,maxDepth(root->children[i]));
      // }
      // return depth+1;
      
      //以下是迭代
      // queue<Node*> que;
      // if(root!=nullptr) que.push(root);
      // int depth=0;
      // while(!que.empty()){
      //   int size=que.size();
      //   depth++;
      //   for(int i=0;i<size;i++){
      //     Node *node=que.front();
      //     que.pop();
      //     for(int j=0;j<node->children.size();j++){
      //       if(node->children[j]!=nullptr) que.push(node->children[j]);
      //     }
      //   }
      // }
      // return depth;

      result=0;    //前序遍历求节点深度逻辑
      if(root==nullptr) return result;
      getDepth(root,1);
      return result;
    }
    int countNodes(TreeNode* root) {
      if(root==nullptr) return 0;
      TreeNode *left=root->left;
      TreeNode *right=root->right;
      int leftHight=0,rightHight=0;
      while(left!=nullptr){
        left=left->left;
        leftHight++;
      }
      while(right){
        right=right->right;
        rightHight++;
      }
      if(leftHight==rightHight){
        return (2<<leftHight)-1;
      }
      return countNodes(root->left)+countNodes(root->right)+1;
    }
    int getNodeNum(TreeNode* root){
      if(root==nullptr) return 0;
      int leftTreeNum=getNodeNum(root->left);
      int rightTreeNum=getNodeNum(root->right);
      int sum= leftTreeNum+rightTreeNum+1;
      return sum;
    }
    bool compare(TreeNode* left,TreeNode* right){
      if(left==nullptr&&right!=nullptr)return false;
      else if(left!=nullptr&&right==nullptr)return false;
      else if(left==nullptr&&right==nullptr)return true;
      else if(left->val!=right->val)return false;
      bool outside=compare(left->left,right->right);
      bool inside=compare(left->right,right->left);
      bool isSame=outside && inside;
      return isSame;
    }
    bool isSymmetric2(TreeNode* root) {
      if(root==nullptr) return true;
      return compare(root->left,root->right);
    }
    bool isSymmetric(TreeNode* root) {
      if(root==nullptr) return false;
      queue<TreeNode*> que;
      que.push(root->left);
      que.push(root->right);
      while(!que.empty()){
        TreeNode* left=que.front();que.pop();
        TreeNode* right=que.front();que.pop();
        if(left==nullptr&&right==nullptr) continue;
        if(left==nullptr||right==nullptr||left->val!=right->val) return false;
        que.push(left->left);
        que.push(right->right);
        que.push(left->right);
        que.push(right->left);
      }
      return true;
    }
    bool isEvenOddTree(TreeNode* root) {
      queue<TreeNode*> que;
      if(root!=nullptr) que.push(root);
      bool isOdd=false;
      while(!que.empty()){
        int size=que.size();
        for(int i=0;i<size;i++){
          TreeNode* temp=que.front();
          que.pop();
          if(isOdd){
            if(i!=size-1){
              if(temp->val<=que.front()->val) return false;
            }
            if(temp->val%2!=0) return false;
          }else{
            if(i!=size-1){
              if(temp->val>=que.front()->val) return false;
            }
            if(temp->val%2!=1) return false;
          }
          if(temp->left!=nullptr) que.push(temp->left);
          if(temp->right!=nullptr) que.push(temp->right);
        }
        isOdd=!isOdd;
      }
      return true;
    }
    TreeNode* invertTree(TreeNode* root) {
      if(root==nullptr) return root;
      stack<TreeNode*> st;
      st.push(root);
      while(!st.empty()){
        TreeNode* temp=st.top();
        if(temp!=nullptr){
          st.pop();
          if(temp->right!=nullptr) st.push(temp->right);
          if(temp->left!=nullptr) st.push(temp->left);
          st.push(temp);
          st.push(nullptr);
        }else{
          st.pop();
          temp=st.top();
          st.pop();
          swap(temp->left,temp->right);
        }
      }
      return root;
    }
    int minDepth(TreeNode* root) {
      queue<TreeNode*> que;
      if(root!=nullptr) que.push(root);
      int ans=0;
      TreeNode* temp;
      while(!que.empty()){
        int size= que.size();
        for(int i=0;i<size;i++){
          temp= que.front();
          que.pop();
          if(temp->left!=nullptr) que.push(temp->left);
          if(temp->right!=nullptr) que.push(temp->right);
          if(temp->right==nullptr&&temp->left==nullptr) return ans+1;
        }
        ans++;
      }  
      return ans; 
    }
    // int maxDepth(TreeNode* root) {
    //   queue<TreeNode*> que;
    //   if(root!=nullptr) que.push(root);
    //   int ans=0;
    //   TreeNode* temp;
    //   while(!que.empty()){
    //     int size= que.size();
    //     for(int i=0;i<size;i++){
    //       temp= que.front();
    //       que.pop();
    //       if(temp->left!=nullptr) que.push(temp->left);
    //       if(temp->right!=nullptr) que.push(temp->right);
    //     }
    //     ans++;
    //   }  
    //   return ans;         
    // }
    vector<int> largestValues(TreeNode* root) {
       vector<int> ans;
       queue<TreeNode*> que;
       if(root!=nullptr) que.push(root);
       while(!que.empty()){
         int size=que.size();
         TreeNode* newNode;
         int maxNum= INT32_MIN;
         for(int i=0;i<size;i++){
          newNode=que.front();
          que.pop();
          if(newNode->val>maxNum){
            maxNum=newNode->val;
          }
          if(newNode->left!=nullptr) que.push(newNode->left);
          if(newNode->right!=nullptr) que.push(newNode->right);
         }
         ans.push_back(maxNum);
       } 
       return ans;
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
      vector<vector<int>> ans;
      queue<TreeNode*> qe;
      if(root!=nullptr) qe.push(root);
      while(!qe.empty()){
        int size=qe.size();
        vector<int> temp;
        TreeNode* node;
        for(int i=0;i<size;i++){
          node=qe.front();
          qe.pop();
          if(node->left) qe.push(node->left);
          if(node->right) qe.push(node->right);
          temp.push_back(node->val);
        }
        ans.push_back(temp);
      }    
      return ans;
    }
    vector<int> rightSideView(TreeNode* root) {
      vector<int> ans;
      queue<TreeNode*> qe;
      if(root!=nullptr) qe.push(root);
      while(!qe.empty()){
        int size=qe.size();
        TreeNode* node;
        for(int i=0;i<size;i++){
          node=qe.front();
          qe.pop();
          if(i==size-1){
            ans.push_back(node->val);
          }
          if(node->left) qe.push(node->left);
          if(node->right) qe.push(node->right);
        }
      }    
      return ans;
    }
    vector<double> averageOfLevels(TreeNode* root) {
      vector<double> ans;
      queue<TreeNode*> qe;
      qe.push(root);
      while(!qe.empty()){
        int size=qe.size();
        double cnt=0;
        for(int i=0;i<size;i++){
          TreeNode* temp=qe.front();
          qe.pop();
          cnt+=(temp->val);
          if(temp->left!=nullptr) qe.push(temp->left);
          if(temp->right!=nullptr) qe.push(temp->right);
        }
        ans.push_back(cnt/(double)size);
      }
      return ans;
    }
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
      vector<vector<int>> ans;
      queue<TreeNode*> qe;
      if(root!=nullptr) qe.push(root);
      while(!qe.empty()){
        int size=qe.size();
        vector<int> temp;
        TreeNode* node;
        for(int i=0;i<size;i++){
          node=qe.front();
          qe.pop();
          if(node->left) qe.push(node->left);
          if(node->right) qe.push(node->right);
          temp.push_back(node->val);
        }
        ans.push_back(temp);
      }
      reverse(ans.begin(),ans.end());    
      return ans;
    }
    vector<int> preorderTraversal3(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty()){// 统一迭代代码
          TreeNode* temp= st.top();
          if(temp!=nullptr){
            st.pop();
            st.push(temp);
            st.push(nullptr);
            st.push(temp->right);
            st.push(temp->left);
            
          }else{
            st.pop();
            temp=st.top();
            st.pop();
            ans.push_back(temp->val);
          }
          return ans;
        }
    }
    void traversalpost(TreeNode* cur,vector<int>& vec){
      if(cur==nullptr) return;
      traversalpost(cur->left,vec);
      traversalpost(cur->right,vec);
      vec.push_back(cur->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        traversalpost(root,ans);
        return ans;
    }
    vector<int> postorderTraversal2(TreeNode* root) {
      stack<TreeNode*> st;
      vector<int> ans;
      if(root==nullptr) return ans;
      TreeNode* temp;
      st.push(root);
      while(!st.empty()){
        temp=st.top();
        st.pop();
        ans.push_back(temp->val);
        if(temp->left) st.push(temp->left);
        if(temp->right) st.push(temp->right);
      }
      reverse(ans.begin(),ans.end());
      return ans;
    }
    
    void traversalMid(TreeNode* cur,vector<int>& vec){
      if(cur==nullptr) return;
      traversalMid(cur->left,vec);
      vec.push_back(cur->val);
      traversalMid(cur->right,vec);
    }
    vector<int> inorderTraversal(TreeNode* root) {
      vector<int> ans;
      traversalMid(root,ans);
      return ans;
    }
    vector<int> inorderTraversal2(TreeNode* root) {
      stack<TreeNode*> st;
      vector<int> ans;
      if(root==nullptr) return ans;
      TreeNode* temp=root;
      while(temp!=nullptr||!st.empty()){
        if(temp!=nullptr){
          st.push(temp);
          temp=temp->left;
        }else{
          temp=st.top();
          st.pop();
          ans.push_back(temp->val);
          temp=temp->right;
        }
      }
      return ans;
    }
    vector<int> preorderTraversal2(TreeNode* root) {
      stack<TreeNode*> st;
      vector<int> ans;
      if(root==nullptr) return ans;
      st.push(root);
      TreeNode* temp;
      while(!st.empty()){
        temp=st.top();
        st.pop();
        ans.push_back(temp->val);
        if(temp->right!=nullptr) st.push(temp->right);
        if(temp->left!=nullptr) st.push(temp->left);
      }
      return ans;
    }
    void traversalpre(TreeNode* cur,vector<int>& vec){
        if(cur==nullptr) return;
        vec.push_back(cur->val);
        traversalpre(cur->left,vec);
        traversalpre(cur->right,vec);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        traversalpre(root,ans);
        return ans;
    }
};
int main(){
  vector<int> ans;
  int res;
  TreeNode* root=new TreeNode(1);
  treeInsert(root,10,true);
  treeInsert(root,4,false);
  treeInsert(root->left,3,true);
  treeInsert(root->right,7,true);
  treeInsert(root->right,9,false);
  treeInsert(root->left->left,12,true);
  treeInsert(root->left->left,8,false);
  treeInsert(root->right->left,6,true);
  // treeInsert(root->right->right,2,false);
  //以下语句可以将这棵树补成完全二叉树
  // treeInsert(root->left,15,false);
  // treeInsert(root->left->right,14,true);
  // treeInsert(root->left->right,16,false);
  // treeInsert(root->right->right,18,true);
  // treeInsert(root->right->left,19,false);
  Solution A;
  // res=A.minDepth(root);
  // for(auto v:ans){
  //   cout<<v<<endl;
  // }
  // cout<<res;
  // 
  cout<<A.isBalanced(root);
  getchar();
}