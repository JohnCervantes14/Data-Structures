
#include <iostream>
using namespace std;
// Node Class Definition
class Node {
private:
    int data;
    Node* link_next;
public:
    void SetData(int x);
    int GetData();
    void SetLink_Next(Node* ptr);
    Node* GetLink_Next();
    Node();
};
Node::Node() {
    data = 0;
    link_next = NULL;
}
void Node::SetData(int x) {
    data = x;
}
int Node::GetData() {
    return data;
}
void Node::SetLink_Next(Node* ptr) {
    link_next = ptr;
}
Node* Node::GetLink_Next() {
    return link_next;
}

// Singly Linked List Class Definition
// *************
// 1. GetSize()
// This function returns the number of nodes in the list.
// *************************
// 2. LinearSearch(int key)
// This function performs linear search on the list with the given key.
// If key is not found or the list is empty, return -1.
// If key is found, return location of the node holding that key.
// Location will start from 0 and ends at n-1.
// *************************
// 3. Add(int val, int idx)
// This function adds a node with data "val" at location "idx".
// Here, "idx" starts from 0 (head node) and ends at n-1 (tail node).
// If the input "idx" is bigger than n-1, then add node to the tail.
// *******************
// 4. Remove(int idx)
// This function removes the node at location "idx".
// Here, "idx" starts from 0 (head node) and ends at n-1 (tail node).
// If the input "idx" is bigger than n-1, then remove the tail.
// *************
// 5. Reverse()
// This function reverses the current list.
// If the list is empty or contains only one node, do nothing.

class SList {
private:
    Node* head;
public:
    // The following four functions are given to you.
    // The SetHead and GetHead functions are only useful for merge sort.
    SList();
    void Print();
    void SetHead(Node* ptr);
    Node* GetHead();
    // You need to complete the following five functions.
    int GetSize();
    int LinearSearch(int key);
    void Add(int val, int idx);
    void Remove(int idx);
    void Reverse();
};
SList::SList() {
    head = NULL;
}
void SList::Print() {
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->GetData() << endl;
        temp = temp->GetLink_Next();
    }
}
Node* SList::GetHead() {
    return head;
}
void SList::SetHead(Node* ptr) {
    head = ptr;
}
int SList::GetSize() {
    int size = 0;
    Node *temp = head;
    while(temp != NULL){
        ++size;
        temp = temp->GetLink_Next();
    }
    return size;
}
int SList::LinearSearch(int key) {
    Node *temp = head;
    int pos {0};
    while(temp != NULL){
        if(temp->GetData() == key){
            return pos;
        }
        temp = temp->GetLink_Next();
        ++pos;
    }
    return -1;
}
void SList::Add(int val, int idx) {
    Node *newNode = new Node();
    newNode->SetData(val);
    // adding a node to the beginning
    if(idx == 0){
        newNode->SetLink_Next(head);
        head = newNode;
    }
    //adding a node to the tail
    else if(GetSize() <= idx){
        Node *temp = head;
        while(temp->GetLink_Next()!= NULL){
            temp = temp->GetLink_Next();
        }
        temp->SetLink_Next(newNode);
    }
    //adding one in the middle
    else {
        Node *temp = head;
        int pos{0};
        while (pos != idx-1) {
            temp = temp->GetLink_Next();
            ++pos;
        }
        newNode->SetLink_Next(temp->GetLink_Next());
        temp->SetLink_Next(newNode);

    }

}
void SList::Remove(int idx) {
    //remove at beginning of list
    if(idx == 0){
        head = head->GetLink_Next();
    }
    //remove at the end
    else if(idx >= GetSize()-1){
        Node *temp = head;
        while(temp->GetLink_Next()->GetLink_Next() != NULL){
            temp = temp->GetLink_Next();
        }
        temp->SetLink_Next(NULL);
    }
    //remove anywhere
    else{
        Node *temp = head;
        int pos{0};
        while(pos != idx-1){
            temp = temp->GetLink_Next();
            ++pos;
        }
        temp->SetLink_Next(temp->GetLink_Next()->GetLink_Next());
    }
}
void SList::Reverse() {
    SList *list = new SList();
    Node *temp = head;
    while(temp != NULL){
        list->Add(temp->GetData(), 0);
        temp = temp->GetLink_Next();
    }
    head = list->GetHead();
}
//
// -----------
// Merge Sort
// -----------
// The following is an incomplete merge sort function.
// Its input is the head pointer of a singly linked list.
// Its output is the head pointer of the sorted list.
// We will test this function in the following way:
// First, use your SList class to generate a singly linked list.
// Then, retrive its head pointer and pass it to the merge sort function.
// Finally, get a new head pointer of the sorted list, pass it back to the list
//class and print it.
// You can see the testing code in the main function (mode = 7)
// .........
// Your task is to design and implement this merge sort function
// based on the singly linked list data structure.
// No array or vector can be used.
// Tip: it should be recursive.

//helper method to merge two lists
Node* MergeList(Node* list1, Node* list2){
    Node *temp = new Node();
    Node *current = temp;
    while(list1 != NULL && list2 != NULL){
        if(list1->GetData() < list2->GetData()) {
            current->SetLink_Next(list1);
            list1 = list1->GetLink_Next();
        }
        else{
            current->SetLink_Next(list2);
            list2 = list2->GetLink_Next();
        }
        current = current->GetLink_Next();
    }
    if(list1 != NULL){
        current->SetLink_Next(list1);
    }
    if(list2 != NULL){
        current->SetLink_Next(list2);
    }
    return temp->GetLink_Next();
}
Node* MergeSort(Node* ptr) {
    SList *left = new SList();
    SList *right = new SList();

    int size = 0;
    Node *temp = ptr;
    while(temp != NULL){
        ++size;
        temp = temp->GetLink_Next();
    }
    //check base case size == 1
    if(size < 2){
        return ptr;
    }
    int midPoint = size/2;
    Node* temp2 = ptr;
    //split given list into two lists
    for(int i = 0; i < midPoint; ++i){
        left->Add(temp2->GetData(), i);
        temp2 = temp2->GetLink_Next();
    }
    for(int i = midPoint; i < size; ++i){
        int pos = 0;
        right->Add(temp2->GetData(), pos);
        ++pos;
        temp2 = temp2->GetLink_Next();
    }
    //recursive call
    left->SetHead(MergeSort(left->GetHead()));
    right->SetHead(MergeSort(right->GetHead()));
    //merge into new list
    SList *sortedList = new SList();
    sortedList->SetHead(MergeList(left->GetHead(), right->GetHead()));
    return sortedList->GetHead();
}
int main()
{
    SList x;

    int mode, value, idx, key;
    cin >> mode >> value >> idx >> key;
    int temp;
    for (int i = 0; i < 4; i++) {
        cin >> temp;
        x.Add(temp,0);
    }
    switch (mode) {
        case 1: // check your add function with idx = 0
            x.Print();
            break;
        case 2: // check your GetSize function
            cout << x.GetSize();
            break;
        case 3: // check your LinearSearch function
            cout << x.LinearSearch(key);
            break;
        case 4: // check your add function with arbitrary idx
            x.Add(value, idx);
            x.Print();
            break;
        case 5: // check your remove function
            x.Remove(idx);
            x.Print();
            break;
        case 6: // check your reverse function
            x.Reverse();
            x.Print();
            break;
        case 7: // check your merge sort function
            x.SetHead(MergeSort(x.GetHead()));
            x.Print();
            break;
    }
    return 0;
}
