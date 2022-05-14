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
private:

    vector<vector<int>> results;
    vector<int> path;
    int minGap=INT_MAX;
    TreeNode* pre;
    int maxCount;
    int count;
    vector<int> resultOfMode;
    int preval;
    
    void traversalToTransGreatSumTree(TreeNode* cur){
      if(cur==nullptr)return;
      traversalToTransGreatSumTree(cur->right);
      cur->val+=preval;
      preval=cur->val;
      traversalToTransGreatSumTree(cur->left);
    }
    TreeNode* traversalToStructBST(vector<int>& nums,int left,int right){
      if(left>right) return nullptr;
      int mid=left+(right-left)/2;
      TreeNode* cur=new TreeNode(nums[mid]);
      cur->left=traversalToStructBST(nums,left,mid-1);
      cur->right=traversalToStructBST(nums,mid+1,right);
      return cur;
    }
    void searchBST(TreeNode* cur){
      if(cur==NULL) return;
      searchBST(cur->left);
      if(pre==nullptr){
        count=1;
      }else if(pre->val==cur->val){
        count++;
      }else{
        count=1;
      }
      pre=cur;
      if(maxCount==count){
        resultOfMode.push_back(cur->val);
      }
      if(maxCount<count){
        maxCount=count;
        resultOfMode.clear();
        resultOfMode.push_back(cur->val);
      }
      searchBST(cur->right);
      return ;
    }
    void traversalToFindMinGap(TreeNode* cur){
      if(cur==nullptr)return;
      traversalToFindMinGap(cur->left);
      if(pre!=nullptr){
        minGap=min(minGap,cur->val-pre->val);
      }
      pre=cur;
      traversalToFindMinGap(cur->right);
    }

    TreeNode* traversalPreStruct (vector<int>& inorder, int inorderBegin, int inorderEnd, vector<int>& preorder, int preorderBegin, int preorderEnd) {
      if(inorderBegin==inorderEnd) return NULL;

      int rootValue=preorder[preorderBegin];
      TreeNode* root=new TreeNode(rootValue);

      if(preorderEnd-preorderBegin==1) return root;

      int delimiterIndex;
      for (delimiterIndex = inorderBegin; delimiterIndex < inorderEnd; delimiterIndex++) {
        if (inorder[delimiterIndex] == rootValue) break;
      }

      int leftInorderBegin = inorderBegin;
      int leftInorderEnd = delimiterIndex;
      int rightInorderBegin = delimiterIndex + 1;
      int rightInorderEnd = inorderEnd;
      
      int leftPreorderBegin =  preorderBegin + 1;
      int leftPreorderEnd = preorderBegin + 1 + delimiterIndex - inorderBegin; // 终止位置是起始位置加上中序左区间的大小size
      
      int rightPreorderBegin = preorderBegin + 1 + (delimiterIndex - inorderBegin);
      int rightPreorderEnd = preorderEnd;

      root->left = traversalPreStruct(inorder, leftInorderBegin, leftInorderEnd,  preorder, leftPreorderBegin, leftPreorderEnd);
      root->right = traversalPreStruct(inorder, rightInorderBegin, rightInorderEnd, preorder, rightPreorderBegin, rightPreorderEnd);

      return root;
    }

    TreeNode* traversalStruct (vector<int>& inorder, vector<int>& postorder) {
      if(postorder.size()==0) return NULL;

      int rootValue=postorder[postorder.size()-1];
      TreeNode* root= new TreeNode(rootValue);
      
      if(postorder.size()==1) return root;

      int delimiterIndex;
      for(delimiterIndex=0;delimiterIndex<inorder.size();delimiterIndex++){
        if(inorder[delimiterIndex]==rootValue){
          break;
        }
      }

      vector<int> leftInorder(inorder.begin(),inorder.begin()+delimiterIndex);
      vector<int> rightInorder(inorder.begin()+delimiterIndex+1,inorder.end());

      postorder.resize(postorder.size()-1);
      vector<int> leftPostorder(postorder.begin(),postorder.begin()+leftInorder.size());
      vector<int> rightPostorder(postorder.begin()+leftInorder.size() ,postorder.end());

      root->left=traversalStruct(leftInorder,leftPostorder);
      root->right=traversalStruct(rightInorder,rightPostorder);
      return root;
    }
    // void traversal(TreeNode* cur, vector<int>& path, vector<string>& result) {
    //   path.push_back(cur->val);
    //   if(cur->left==nullptr&&cur->right==nullptr){
    //     string sPath;
    //     for(int i=0;i<path.size()-1;i++){
    //       sPath += to_string(path[i]);
    //       sPath += "->";
    //     }
    //     sPath += to_string(path[path.size()-1]);
    //     result.push_back(sPath);
    //     return ;
    //   }
    //   if(cur->left){
    //     traversal(cur->left,path,result);
    //     path.pop_back();
    //   }
    //   if(cur->right){
    //     traversal(cur->right,path,result);
    //     path.pop_back();
    //   }
    // }
    // void traversal(TreeNode* cur, string path, vector<string>& result) {//精简版
    //   path += to_string(cur->val);
    //   if(cur->left!=nullptr&&cur->right!=nullptr){
    //     result.push_back(path);
    //     return;
    //   }
    //   if(cur->left) traversal(cur->left,path + "->",result);
    //   if(cur->right) traversal(cur->right,path + "->",result);
    // }
public:
    int result;
    bool tag=false;
    int maxLen = INT_MIN;
    int maxleftValue;
    vector<int> vec98;   
    TreeNode* parent;

    TreeNode* deleteNode(TreeNode* root, int key) {
     if(root==nullptr) return root;
     if(root->val==key){
       if(root->left==nullptr&&root->right==nullptr){
         delete root;
         return nullptr;
       }else if(root->left==nullptr){
         auto temp=root->right;
         delete root;
         return temp;
       }else if(root->right==nullptr){
         auto temp=root->left;
         delete root;
         return temp;
       }else{
         TreeNode* temp=root->right;
         while(temp->left!=nullptr){
           temp=temp->left;
         }
         temp->left=root->left;
         temp=root->right;
         delete root;
         return temp;
       }
     }  
     if(root->val>key){
       root->left=deleteNode(root->left,key);
     }
     if(root->val<key){
       root->right=deleteNode(root->right,key);
     }
     return root;   
    }
    void traversalToFindNullChild(TreeNode* cur, int val) {
      if(cur==nullptr){
        TreeNode* temp=new TreeNode(val);
        if(parent->val>val){
          parent->left=temp;
        }else{
          parent->right=temp;
        }
        return ;
      }
      parent=cur;
      if(cur->val>val){
        traversalToFindNullChild(cur->left,val);
      }
      if(cur->val<val){
        traversalToFindNullChild(cur->right,val);
      }
      return;
    }
    TreeNode* insertIntoBST(TreeNode* root, int val) {
      parent=new TreeNode(0);
      if(root==nullptr){
        return new TreeNode(val);
      }
      traversalToFindNullChild(root,val);
      return root;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
      if(root->val>p->val&&root->val>q->val){
        return lowestCommonAncestor(root->left,p,q);
      }else if(root->val<p->val&&root->val<q->val){
        return lowestCommonAncestor(root->right,p,q);
      }else{
        return root;
      }
    }
    TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
      if(root==q||root==p||root==nullptr) return root;

      TreeNode* left= lowestCommonAncestor(root->left,p,q);
      TreeNode* right= lowestCommonAncestor(root->right,p,q);

      if(left!=nullptr&&right!=nullptr){
        return root;
      }
      if(left!=nullptr&&right==nullptr){
        return left;
      }else if(left==nullptr&&right!=nullptr){
        return right;
      }else{
        return nullptr;
      }

    }
    TreeNode* convertBST(TreeNode* root) {
      preval=0;
      traversalToTransGreatSumTree(root);
      return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
      return traversalToStructBST(nums,0,nums.size()-1);
    }
    TreeNode* trimBST(TreeNode* root, int low, int high) {  
      // 递归法
      // if(root==nullptr) return nullptr;
      // if(root->val>high) return trimBST(root->left,low,high);
      // if(root->val<low) return trimBST(root->right,low,high);
      // root->left=trimBST(root->left,low,high);
      // root->right=trimBST(root->right,low,high);
      // return root;

      //迭代法
      if(root==nullptr)return nullptr;
      while(root!=nullptr&&(root->val<low||root->val>high)){
        if(root->val<low){
          root=root->right;
        }else{
          root=root->left;
        }
      }
      TreeNode* cur=root;
      while(cur!=nullptr){
        while (cur->left && cur->left->val < low) {
                cur->left = cur->left->right;
            }
        cur = cur->left;
      }
      cur=root;
      while(cur!=nullptr){
        while (cur->right && cur->right->val > high) {
                cur->right = cur->right->left;
            }
        cur = cur->right;
      }
      return root;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
      if(root==q||root==p||root==nullptr) return root;
      TreeNode* left=lowestCommonAncestor(root->left,p,q);
      TreeNode* right=lowestCommonAncestor(root->right,p,q);

      if(left!=nullptr&&right!=nullptr) return root;
      if(left!=nullptr&&right==nullptr) return left;
      else if(left==nullptr&&right!=nullptr) return right;
      else return nullptr; 

    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
      
      //中序和后序
      // if(inorder.size()==0&&postorder.size()==0)return NULL;
      // return traversalStruct(inorder,postorder);

      //前序和中序
      if(inorder.size()==0||preorder.size()==0)return NULL;
      return traversalPreStruct(inorder,0,inorder.size(),preorder,0,preorder.size());
    }
    vector<int> findMode(TreeNode* root) {
      count=0;
      maxCount=0;
      resultOfMode.clear();
      pre=NULL;
      searchBST(root);
      return resultOfMode;
    }
    int getMinimumDifference(TreeNode* root) {
      traversalToFindMinGap(root);
      return minGap;
    }
    void traversalToVec(TreeNode* root) {
      if(root==nullptr)return;
      traversalToVec(root->left);
      vec98.push_back(root->val);
      traversalToVec(root->right);
    }
    bool isValidBST(TreeNode* root) {
      vec98.clear();
      traversalToVec(root);
      for(int i=1;i<vec98.size();i++){
        if(vec98[i]<=vec98[i-1]) return false;
      }
      return true;
    }
    TreeNode* searchBST(TreeNode* root, int val) {
      if(root==nullptr||root->val==val) return root;
      if(root->val>val) return searchBST(root->left,val);
      else return searchBST(root->right,val);
      return NULL;
    }
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
      if(root1==nullptr)return root2;
      if(root2==nullptr)return root1;

      root1->val+=root2->val;
      root1->left=mergeTrees(root1->left,root2->left);
      root1->right=mergeTrees(root1->right,root2->right);
      return root1;
    }
    void traversal(TreeNode* cur,int count){
      if(cur->left==nullptr&&cur->right==nullptr&&count==cur->val){
        results.push_back(path);
        return;
      }
      if(!cur->left&&!cur->right){
        return;
      }
      if(cur->left){
        path.push_back(cur->left->val);
        count-=cur->val;
        traversal(cur->left,count);
        count+=cur->val;
        path.pop_back();
      }
      if(cur->right){
        path.push_back(cur->right->val);
        count-=cur->val;
        traversal(cur->right,count);
        count+=cur->val;
        path.pop_back();
      }
      return;
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
      results.clear();
      path.clear();
      if(root==nullptr) return results;
      path.push_back(root->val);
      traversal(root,targetSum);
      return results;
    }
    // void traversal(TreeNode* root, int leftLen) {
    //   if(!root->left&&!root->right){
    //     if(leftLen>maxLen){
    //       maxLen=leftLen;
    //       maxleftValue=root->val;
    //     }
    //     return;
    //   }
    //   if(root->left) traversal(root->left,leftLen+1);
    //   if(root->right) traversal(root->right,leftLen+1);
    //   return;
    // }
    int findBottomLeftValue(TreeNode* root) {
      // 递归法
      // traversal(root, 0);
      // return maxleftValue;
      
      //迭代法
      queue<TreeNode*> queT;
      int res=INT_MIN;
      if(root !=nullptr) queT.push(root);
      while(!queT.empty()){
        int size=queT.size();
        for(int i=0; i<size;i++){
          TreeNode* node = queT.front();
          queT.pop();
          if(i==0) res = node->val;
          if(node->left) queT.push(node->left);
          if(node->right) queT.push(node->right);
        }
      } 
      return res;
    }
    int sumOfLeftLeaves(TreeNode* root) {
      if(root==nullptr) return 0;
      int leftValue=sumOfLeftLeaves(root->left);
      int rightValue=sumOfLeftLeaves(root->right);

      int midValue=0;
      if(root->left&&!root->left->left&&!root->left->right){
        midValue=root->left->val;
      }
      int sum=leftValue+rightValue+midValue;
      return sum;
    }
    void getDfsOrder(TreeNode* cur,vector<char> &res){
      if(cur==nullptr) return ;
      res.push_back(cur->val);
      if(cur->left) getDfsOrder(cur->left,res);
      else res.push_back('l'-48);
      if(cur->right) getDfsOrder(cur->right,res);
      else res.push_back('r'-48);
      return ;
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
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
      // if(!root&&!subRoot){
      //   return true;
      // }
      // if((!root&&subRoot) || (root&&!subRoot)){
      //     return false;
      // }
      // return DFS(root,subRoot);
      vector<char> leftStr;
      getDfsOrder(root,leftStr);
      vector<char> rightStr;
      getDfsOrder(subRoot,rightStr);
		  string lst,rst;
		  for(int i=0;i<leftStr.size();i++)
      {
        lst += leftStr[i]+48;
      }
      for(int i=0;i<rightStr.size();i++)
      {
        rst += rightStr[i]+48;
      }

      cout<<lst<<endl;
      cout<<rst<<endl;
      return strStr(lst,rst)!=-1;
    }
    bool DFS(TreeNode* root,TreeNode* subRoot){
      if(tag) return true;
      if(compare2(root,subRoot)) {
        tag=true;
        return true;
      }
      if (root->left) DFS(root->left,subRoot);
      if (root->right) DFS(root->right,subRoot);
      if(tag) return true;
      return false;
    }
    bool compare2(TreeNode* left,TreeNode* right){
      if(left==nullptr&&right!=nullptr)return false;
      else if(left!=nullptr&&right==nullptr)return false;
      else if(left==nullptr&&right==nullptr)return true;
      else if(left->val!=right->val)return false;
      bool outside=compare2(left->left,right->left);
      bool inside=compare2(left->right,right->right);
      bool isSame=outside && inside;
      return isSame;
    }
    vector<string> binaryTreePaths2(TreeNode* root) {
      stack<TreeNode*> treeST;
      stack<string> pathST;
      vector<string> result;
      if(root==nullptr) return result;
      treeST.push(root);
      pathST.push(to_string(root->val));
      while(!treeST.empty()){
        TreeNode* node=treeST.top();treeST.pop();
        string path=pathST.top();pathST.pop();
        if(node->left==nullptr&&node->right==nullptr){
          result.push_back(path);
        }
        if(node->right){
          treeST.push(node->right);
          pathST.push(path + "->"+ to_string(node->right->val));
        }
        if(node->left){
          treeST.push(node->left);
          pathST.push(path + "->"+ to_string(node->left->val));
        }
      }
      return result;
    }
    // vector<string> binaryTreePaths(TreeNode* root) {
    //   vector<string> result;
    //   // vector<int> path;
    //   string path;
    //   if(root==nullptr) return result;
    //   traversal(root,path,result);
    //   return result;
    // }
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
  TreeNode* root=new TreeNode(3);
  treeInsert(root,4,true);
  treeInsert(root,5,false);
  treeInsert(root->left,1,true);
  treeInsert(root->left,2,false);
  TreeNode* subRoot=new TreeNode(4);
  treeInsert(subRoot,1,true);
  treeInsert(subRoot,2,false);
  // treeInsert(root->right,7,true);
  // treeInsert(root->right,9,false);
  // treeInsert(root->left->left,12,true);
  // treeInsert(root->left->left,8,false);
  // treeInsert(root->right->left,6,true);
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
  cout<<A.isSubtree(root, subRoot);
  getchar();
}