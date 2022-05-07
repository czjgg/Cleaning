#include<iostream>
using namespace std;
struct ListNode {
       int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};
void addAtHead(int val,ListNode* _dummyhead) {
        ListNode* temp=new ListNode(val);
        temp->next=_dummyhead->next;
        _dummyhead->next=temp;
}
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast_p=head;
        ListNode *slow_p=head;
        while(fast_p!=NULL&&fast_p->next!=NULL){
            fast_p=fast_p->next->next;
            slow_p=slow_p->next;
            if(fast_p==slow_p){
              fast_p=head;
              while(1){
                if(fast_p==slow_p){
                  return fast_p;
                }
                fast_p=fast_p->next;
                slow_p=slow_p->next;
              }
            }
        }
        return NULL;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode* long_p=headA;
    ListNode* short_p=headB;
    int countA=0,countB=0;
    while(long_p!=NULL){
        long_p=long_p->next;
        countA++;
    }
    while (short_p!=nullptr){
      short_p=short_p->next;
      countB++;
    }
    int i;
    if(countA<countB){
      long_p=headB;
      short_p=headA;
      i=countB-countA;
    }else{
      long_p=headA;
      short_p=headB;
      i=countA-countB;
    }
    while (i!=0)
    {
      long_p=long_p->next;
      i--;
    }
    while(long_p!=nullptr){
      if(long_p==short_p){
        return long_p;
      }else{
        long_p=long_p->next;
        short_p=short_p->next;
      }
    }
    return NULL;
    }
    ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* _dummyhead=new ListNode();
    _dummyhead->next=head;
    ListNode* cur=_dummyhead;
    ListNode* pre=_dummyhead;
    while(n!=0){
    cur=cur->next;
    n--;
    }
    while(cur->next!=NULL){
    cur=cur->next;
    pre=pre->next;
    }
    ListNode* temp=pre->next;
    pre->next=pre->next->next;
    delete temp;
    return _dummyhead->next;   
}
ListNode* swapPairs(ListNode* head) {
        ListNode* _dummyhead=new ListNode();
        _dummyhead->next=head;
        ListNode* cur=_dummyhead;
        if(_dummyhead->next==nullptr||_dummyhead->next->next==nullptr)return head;
        while(cur->next!=nullptr&&cur->next->next!=nullptr){
            ListNode* temp=cur->next;
            ListNode* temp2=cur->next->next->next;
            cur->next=cur->next->next;
            cur->next->next=temp;
            temp->next=temp2;
            cur=cur->next->next;
        }
        return _dummyhead->next;
    }
};
int main(){
  ListNode* _dummyhead=new ListNode();
  ListNode* second_list=new ListNode(4);
  //addAtHead(4,_dummyhead);
  addAtHead(0,_dummyhead);
  addAtHead(2,_dummyhead);
  addAtHead(3,_dummyhead);
  _dummyhead->next->next->next->next=second_list;
  second_list->next=_dummyhead->next->next;
  //second_list->next=_dummyhead->next->next->next;
  //addAtHead(9,second_list);
  Solution A;
  //_dummyhead=A.removeNthFromEnd(_dummyhead->next,2);
  //_dummyhead=A.swapPairs(_dummyhead->next);
  _dummyhead=A.detectCycle(_dummyhead->next);
  /*while(_dummyhead!=nullptr){
    cout<<_dummyhead->val<<endl;
    _dummyhead=_dummyhead->next;
  }*/
  cout<<_dummyhead->val<<endl;
  getchar();
}