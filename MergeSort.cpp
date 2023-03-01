#include <iostream>
#include <vector>
using namespace std;
// ---------------------------------------------------------------
// Task 1: Define a MergeSort Class
// ---------------------------------------------------------------
// Below is a class for merge sort.
//
// It has a private vector "list" that holds the list to sort.
// All member functions should operate on "list".
//
// It has several public member functions.
// 1. SetList: assign a vector (to sort) to "list".
// 2. GetList: return the current "list"
// 3. SortList: sort "list" based on the merge sort algorithm.
//
// Parts of the SortList function are given to you.
// You need to complete this function based on the given parts
// (but feel free to add additional functions as you like).
//
// A key feature in the given SortList function is to call
// a recursive function "RecursiveSort", which recursively
// splits the input list, sorts each split, and merges the splits
// Note "RecursiveSort" takes input by value and returns a sorted input.
//
// Your job is to complete the following functions:
// -- SetList()
// -- GetList()
// -- SortList()
// -- RecursiveSort()
class MergeSort {
public:
    void SetList(vector<int> InputList);
    vector<int> GetList();
    void SortList();
    vector<int> mergeList(vector<int> left, vector<int> right);

private:
    vector<int> list;
    vector<int> RecursiveSort(vector<int> x);
};
void MergeSort::SetList(vector<int> InputList) {
    for(int i = 0; i < InputList.size(); ++i){
        list.push_back(InputList.at(i));
    }
}

vector<int> MergeSort::GetList() {
    return list;
}

vector<int> MergeSort::mergeList(vector<int> left, vector<int> right) {
    int i = 0;
    int j = 0;
    vector<int> toReturn;
    while(i < left.size() && j < right.size()){
        if(left.at(i) <= right.at(j)){
            toReturn.push_back(left.at(i));
            ++i;
        }
        else{
            toReturn.push_back(right.at(j));
            ++j;
        }
    }
    while(i < left.size()){
        toReturn.push_back(left.at(i));
        ++i;
    }
    while(j < right.size()){
        toReturn.push_back(right.at(j));
        ++j;
    }
    return toReturn;

}

vector<int> MergeSort::RecursiveSort(vector<int> x) {
    //check base case
    if(x.size() == 1) {
        return x;
    }

    // split x then make recursive calls
   vector<int> list_l(x.begin(),x.begin()+ (x.size()/2));
    vector<int> list_r(x.begin()+ (x.size()/2), x.end());
    list_l = RecursiveSort(list_l);
    list_r = RecursiveSort(list_r);

    // merge list
    x = mergeList(list_l, list_r);
    return x;
}
void MergeSort::SortList() {
    // Step 1. Split "list" into list_l and list_r
    vector<int> list_l(list.begin(),list.begin()+ (list.size()/2));
    vector<int> list_r(list.begin()+ (list.size()/2), list.end());

    // Step 2. Call RecursiveSort to sort each sublist
    list_l = RecursiveSort(list_l);
    list_r = RecursiveSort(list_r);

    // Step 3. Merge list_l and list_r back to "list"
    list = mergeList(list_l, list_r);
};

// ---------------------------------------------------------------
int main()
{
    // The main function is given to you.
    // We first input an arbitrary number of non-repeated integers into a vector.
    // The input of this list will terminate when we give an non-integer input
    //e.g., letter 'a'.
            // Then, we pass this vector to the MergeSort object.
            // Then, we run your implemented functions.
            vector<int> InputList;
    vector<int> TestList;
    int temp, mode;
    MergeSort x;
    // takie inputs
    cin >> mode;
    while (cin >> temp) {
        InputList.push_back(temp);
    }
    x.SetList(InputList);
    // start testing functions
    switch (mode) {
        case 1: // check if input is correct
            TestList = x.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
        case 2: // check if SortList is correct
            x.SortList();
            TestList = x.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
    }
    return 0;
}
