#include <iostream>
#include <vector>
using namespace std;
// Below is a class for basic sorting algorithms.
//
// It has a private vector "list" that holds the list to sort.
//
// It has several public member functions.
// 1. SetList: assign a vector (to sort) to "list".
// 2. GetList: return the current "list"
// 3. BubbleSort: sort "list" using bubble sort
// 4. SelectionSort: sort "list" using selection sort
//
// An important feautre of both sorting algorithms is
// the input argument "NumRound". If NumRound=-1, then
// we should run the sorting algorithm until the list
// is fully sorted. If NumRound = x, then we should stop
// when either the list is partially sorted for x rounds
// or when the list becomes fully sorted before x rounds.

class BasicSort {
public:
    void SetList(vector<int> InputList);
    vector<int> GetList();
    void BubbleSort(int NumRound);
    void SelectionSort(int NumRound);
private:
    vector<int> list;
};
// ..............................................................
void BasicSort::SetList(vector<int> InputList) {
    for(int i = 0; i < InputList.size(); ++i){
        list.push_back(InputList.at(i));
    }
}

vector<int> BasicSort::GetList() {
    return list;
}
void BasicSort::BubbleSort(int NumRound) {
    if (NumRound == -1) {
        NumRound = list.size()-1;
    }
    for (int k = 0; k < NumRound; ++k) {
        int flag = 0;
        for (int i = 0; i < list.size() - k - 1; ++i) {
            if (list.at(i) > list.at(i + 1)) {
                int temp = list.at(i);
                list.at(i) = list.at(i + 1);
                list.at(i + 1) = temp;
                flag = 1;
            }
        }
        if (flag == 0)break;
    }
}

void BasicSort::SelectionSort(int NumRound) {
    if(NumRound == -1){
        NumRound = list.size()-1;
    }
    for(int i = 0; i < NumRound; ++i){
        int min = i;
        for(int j = i+1; j < list.size(); ++j){
            if(list.at(j) < list.at(min)){
                min = j;
            }
        }
        int temp = list.at(i);
        list.at(i) = list.at(min);
        list.at(min) = temp;
    }
}
// ---------------------------------------------------------------
int main()
{
    // We first input the testing mode, NumRound and an arbitrary number of non-
    //repeated integers into a vector.
            // The input of this list will terminate when we give an non-integer input
            //e.g., letter 'a'.
            // Then, we pass this vector to the BasicSort object.
            // Then, we test member functions.
            vector<int> InputList;
    vector<int> TestList;
    int temp, mode, NumRound;
    BasicSort x;
    // take inputs
    cin >> mode >> NumRound;
    while (cin >> temp) {
        InputList.push_back(temp);
    }
    // pass inputs to class objects
    x.SetList(InputList);

    // start testing functions
    switch (mode) {
        case 1: // check if input is corret
            TestList = x.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
        case 2: // check if BubbleSort is correct when NumRound=-1
            x.BubbleSort(NumRound);
            TestList = x.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
        case 3: // check if BubbleSort is correct when NumRound
            x.BubbleSort(NumRound);
            TestList = x.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
        case 4: // check if SelectionSort is correct when NumRound=-1
            x.SelectionSort(NumRound);
            TestList = x.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
        case 5: // check if SelectionSort is correct when NumRound
            x.SelectionSort(NumRound);
            TestList = x.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
    }
    return 0;
}
