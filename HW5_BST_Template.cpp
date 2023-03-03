#include <iostream>
#include <vector>
#include<queue>
using namespace std;
class Node {
private:
    Node* parent;
    Node* left;
    Node* right;
    int SID;
public:
    Node();
    void SetParent(Node* ptr);
    void SetLeft(Node* ptr);
    void SetRight(Node* ptr);
    void SetSID(int data);
    Node* GetParent();
    Node* GetLeft();
    Node* GetRight();
    int GetSID();
};
Node::Node() {
    parent = NULL;
    left = NULL;
    right = NULL;
    SID = -1;
};
void Node::SetParent(Node* ptr) {
    parent = ptr;
};
void Node::SetLeft(Node* ptr) {
    left = ptr;
};
void Node::SetRight(Node* ptr) {
    right = ptr;
};
void Node::SetSID(int data) {
    SID = data;
};
Node* Node::GetParent() {
    return parent;
};
Node* Node::GetLeft() {
    return left;
};
Node* Node::GetRight() {
    return right;
};
int Node::GetSID() {
    return SID;
};

class BinarySearchTree {
private:
    Node* root;
    Node* Max = new Node();
    Node* Min = new Node();
public:
    BinarySearchTree();
    void SetRoot(Node* ptr);
    Node* GetRoot();
    void PreTraverse(Node* ptr);
    int BFSTraverse();
    int Size();
    Node* Search(Node* node, int key);
    void Add(Node* ptr);
    Node* FindMax(Node* ptr);
    Node* FindMin(Node* ptr);
    void Remove1(int key);
    void Remove2(int key);
    bool IsLeaf (Node* ptr);
    void Copy(Node* ptr, Node* copy);
    int countChild (Node* ptr);
};

// This function initializes the tree.
BinarySearchTree::BinarySearchTree() {
    root = NULL;

};

// This function set the root pointer.
void BinarySearchTree::SetRoot(Node* ptr) {
    root = ptr;
    Min->SetSID(ptr->GetSID());
};

// This function returns the root pointer.
Node* BinarySearchTree::GetRoot() {
    return root;
};

// This function performs pre-order traverse of the tree.
void BinarySearchTree::PreTraverse(Node* ptr) {
    if (ptr->GetSID() == -1) {
        return;
    }
    else {
        cout << ptr->GetSID() << endl;
        PreTraverse(ptr->GetLeft());
        PreTraverse(ptr->GetRight());
    }
};
int BinarySearchTree::BFSTraverse(){
    queue<Node*> list;
    list.push(root);
    int count = 0;
    while(!list.empty()){
        ++count;
        if(list.front()->GetLeft()->GetSID() != -1){
            list.push(list.front()->GetLeft());
        }
        if(list.front()->GetRight()->GetSID() != -1){
            list.push(list.front()->GetRight());
        }
        list.pop();
    }
    return count;
};

// This function returns the number of non-NIL nodes in the tree.
int BinarySearchTree::Size() {
    return BFSTraverse();
};

Node* BinarySearchTree::Search(Node* node, int key){
    if(node->GetSID() == -1){
        return node;
    }
    else if(key == node->GetSID()){
        return node;
    }
    else if(key < node->GetSID()){
        Search(node->GetLeft(), key);
    }
    else{
        Search(node->GetRight(), key);
    }
};

// This function adds a node at address "ptr" to the tree.
void BinarySearchTree::Add(Node *ptr) {
    if(GetRoot() == NULL){
        SetRoot(ptr);
        ptr->SetRight(new Node());
        ptr->SetLeft(new Node());
        ptr->GetRight()->SetParent(ptr);
        ptr->GetLeft()->SetParent(ptr);
        return;
    }
    else {
        Node *temp = Search(GetRoot(), ptr->GetSID());
        temp = temp->GetParent();
        if (ptr->GetSID() > temp->GetSID()) {
            temp->SetRight(ptr);

        } else {
            temp->SetLeft(ptr);
        }
        ptr->SetParent(temp);
        ptr->SetRight(new Node());
        ptr->SetLeft(new Node());
        ptr->GetRight()->SetParent(ptr);
        ptr->GetLeft()->SetParent(ptr);
    }
};

// This function returns the address of the maximum node
Node* BinarySearchTree::FindMax(Node *ptr) {
    if (ptr->GetSID() == -1) {
        return Max;
    }
    else {
        if (ptr->GetSID() > Max->GetSID()) {
            Max = ptr;
        }
        FindMax(ptr->GetRight());
    }

};

// This function returns the address of the minimum node
Node* BinarySearchTree::FindMin(Node *ptr) {
    if (ptr->GetSID() == -1) {
        return Min;
    }
    else {
        if (ptr->GetSID() < Min->GetSID()) {
            Min = ptr;
        }
        FindMin(ptr->GetLeft());
    }
};
bool BinarySearchTree::IsLeaf(Node *ptr) {
    if(ptr->GetLeft()->GetSID() == -1 && ptr->GetRight()->GetSID() == -1){
        return true;
    }
    else return false;
}

// This function removes the node whose SID==key from the tree.
// If this node is not in the tree, do nothing.
// This function implements Algorithm 1 (recursively fill holes)
void BinarySearchTree::Remove1(int key) {
    Node* temp = Search(root, key);


     if(temp->GetSID() == -1){
        return;
    }
    if(IsLeaf(temp)){
        temp->SetLeft(NULL);
        temp->SetRight(NULL);
        temp->SetSID(-1);
    }
    else {
        //temp->SetSID(-2);
        Node* filler;
        if (temp->GetLeft()->GetSID() != -1) {
            filler = FindMax(temp->GetLeft());
        }
        else{
            filler = FindMin(temp->GetRight());
        }
        temp->SetSID(filler->GetSID());
        Max = new Node();
        filler->SetSID(-2);
        Remove1(filler->GetSID());


    }
};
int BinarySearchTree::countChild(Node* ptr){
    int count = 0;
    if(ptr->GetLeft()->GetSID() != -1){
        ++count;
    }
    if(ptr->GetRight()->GetSID() != -1){
        ++count;
    }
    return count;
}

// This function removes the node whose SID==key from the tree.
// If this node is not in the tree, do nothing.
// This function implements Algorithm 2 (replace single-child node
// with its only sub-tree) 
void BinarySearchTree::Remove2(int key) {
    Node* temp = Search(root, key);
    if(temp->GetSID() == -1){
        return;
    }
    if(countChild(temp) == 1){
        if(temp->GetLeft()->GetSID() == -1){
            if(temp->GetParent()->GetRight() == temp)
            temp->GetParent()->SetRight(temp->GetRight());

            else
                temp->GetParent()->SetLeft(temp->GetRight());
        }
        else {
            if(temp->GetParent()->GetRight() == temp)
                temp->GetParent()->SetRight(temp->GetLeft());

            else
                temp->GetParent()->SetLeft(temp->GetLeft());
        }
        return;
    }
    else{
        Node* filler;
        if (temp->GetLeft()->GetSID() != -1) {
            filler = FindMax(temp->GetLeft());
        }
        else{
            filler = FindMin(temp->GetRight());
        }
        temp->SetSID(filler->GetSID());
        Remove2(filler->GetSID());
    }

}
;
int main()
{
    int mode, key;
    cin >> mode >> key;
    BinarySearchTree x;
    int temp_SID;
    Node* temp_node;
    // now we construct the tree using "Add"

    while (cin >> temp_SID) {
        temp_node = new Node;
        temp_node->SetSID(temp_SID);
        x.Add(temp_node);

    }
    switch (mode) {
        case 1: // check the "Size" function
            cout << x.Size() << endl;

            break;
        case 2: // check the "Add" function
            x.PreTraverse(x.GetRoot());
            break;
        case 3: // check the "FindMax" function, assuming tree is not empty
            cout << x.FindMax(x.GetRoot())->GetSID();
            break;
        case 4: // check the "FindMin" function, assuming tree is not empty
            cout << x.FindMin(x.GetRoot())->GetSID();
            break;
        case 5: // check the "Remove1" function
            x.Remove1(key);
            x.PreTraverse(x.GetRoot());
            break;
        case 6: // check the "Remove2" function
            x.Remove2(key);
            x.PreTraverse(x.GetRoot());
            break;
        case 7:
            cout << x.Search(x.GetRoot(), -2);
            break;
    }
    return 0;
}
