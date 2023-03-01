#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Below is a class for counting sort.
//
// It has a private vector "list" that holds the list to sort.

// It has several public member functions.
// 1. SetList: assign a vector (to sort) to "list".
// 2. GetList: return the current "list"
// 3. ListMax: return the maximum value in "list"
// 4. SortList: sort "list" based on the counting sort algorithm.
class CountSort {
public:
    void SetList(vector<int> InputList);
    vector<int> GetList();
    int ListMax();
    void SortList();
private:
    vector<int> list;
};

void CountSort::SetList(vector<int> InputList) {
    for(int i = 0; i < InputList.size(); ++i){
        list.push_back((InputList.at(i)));
    }
}

vector<int> CountSort::GetList() {
    return list;
}

int CountSort::ListMax() {
    int max = list.at(0);
    for(int i = 1; i < list.size(); ++i){
        if(list.at(i)>max){
            max = list.at(i);
        }
    }
    return max;
}
void CountSort::SortList() {
    vector<int> elementSmaller(list.size());
    for(int i = 0; i < list.size(); ++i){
        for(int j = 0; j < list.size(); ++j){
            if(list.at(j) < list.at(i)){
                elementSmaller.at(i) = elementSmaller.at(i) + 1;
            }
        }
    }
    vector<int> temp(list.size());
    int index = 0;
    int second = 0;
    for(int i = 0; i < list.size(); ++i){
        for(int j = 0; j < list.size(); ++j){
            if(elementSmaller.at(j) == index){
                temp.at(index) = list.at(j);
                ++index;
                for(int k = 0; k < list.size();++k){
                    if(list.at(k) == list.at(j)){
                        ++second;
                    }
                }
                --second;
                if(second > 0){
                    temp.at(index) = list.at(j);
                    ++index;
                    ++i;
                    second = 0;
                }
                break;
            }
        }
    }
    for(int i = 0; i < temp.size(); ++i){
        list.at(i) = temp.at(i);
    }

}

// Below is a class for RadixSort.
//
// It has a private vector "list" that holds the list to sort.

// It has several public member functions.
// 1. SetList: assign a vector (to sort) to "list".
// 2. GetList: return the current "list"
// 3. GetNumBit: return the maximum number of bits of any element in "list"
// 4. GetList_ByBit (int IdxBit): return the "IdxBit"_th LSB's in "list"
// 5. SortList_byBit (int IdxBit): sort "list" based on the IdxBit_th LSB in "list"
class RadixSort {
public:
    void SetList(vector<int> InputList);
    vector<int> GetList();
    int GetNumBit();
    int CountBits(int x);
    vector<int> GetList_byBit(int IdxBit);
    int getLSB(int x, int bit);
    void SortList_byBit(int IdxBit);
private:
    vector<int> list;
};
void RadixSort::SetList(vector<int> InputList) {
    for(int i = 0; i < InputList.size(); ++i){
        list.push_back(InputList.at(i));
    }
}

vector<int> RadixSort::GetList() {
    return list;
}

int RadixSort::GetNumBit() {
    int maxBits = 0;

    for(int i = 0; i < list.size(); ++i){
        if(maxBits < CountBits(list.at(i))){
            maxBits = CountBits(list.at(i));
        }
    }
    return maxBits;
}

int RadixSort::CountBits(int x) {
    if(x == 0) return 0;
    int bits = 0;
    int temp = 1;
    while(temp <= x){
        temp = temp * 10;
        ++bits;
    }
    return bits;
}

vector<int> RadixSort::GetList_byBit(int IdxBit) {
    vector<int> toReturn;
    for(int i = 0; i < list.size(); ++i){
        int toAdd = getLSB(list.at(i), IdxBit);
        toReturn.push_back(toAdd);
    }
    return toReturn;
}

int RadixSort::getLSB(int x, int bit) {
    if(bit > CountBits(x)) return 0;
    else{
        x = x/(pow(10.0, bit-1));
    }
    return x%10;
}

void RadixSort::SortList_byBit(int IdxBit) {
    CountSort LSB;
    LSB.SetList(GetList_byBit(IdxBit));
    LSB.SortList();

    for(int i = 0; i < list.size(); ++i){
        for(int j = i; j < list.size(); ++j){
            if(getLSB(list.at(j),IdxBit) == LSB.GetList().at(i)){
                int temp = list.at(j);
                int fill = j;
                while(fill > i){
                    list.at(fill) = list.at(fill-1);
                    --fill;
                }
                list.at(i) = temp;

                break;
            }
        }
    }
}

// ---------------------------------------------------------------
int main()
{
    // We first input the testing mode, IdxBit and an arbitrary number of non-
    //repeated integers into a vector.
            // The input of this list will terminate when we give an non-integer input
            //e.g., letter 'a'.
            // Then, we pass this vector to the CountSort and RadixSort objects.
            // Then, we test implemented member functions.
            vector<int> InputList;
    vector<int> TestList;
    int temp, mode, IdxBit;
    CountSort x;
    RadixSort y;
    // takie inputs
    cin >> mode >> IdxBit;
    while (cin >> temp) {
        InputList.push_back(temp);
    }
    // pass inputs to class objects
    x.SetList(InputList);
    y.SetList(InputList);
    // start testing functions
    switch (mode) {
        case 1: // check if input of CountSort is corret
            TestList = x.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
        case 2: // check if input of RadixSort is corret
            TestList = y.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
        case 3: // check if ListMax of CountSort is correct
            cout << x.ListMax() << endl;
            break;
        case 4: // check if SortList of CountSort is correct
            x.SortList();
            TestList = x.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;

        case 5: // check if GetNumBit of RadixSort is correct
            cout << y.GetNumBit() << endl;
            break;
        case 6: // check if GetNumBit of RadixSort is correct
            TestList = y.GetList_byBit(IdxBit);
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
        case 7: // check if SortList_byBit of RadixSort is correct
            y.SortList_byBit(IdxBit);
            TestList = y.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
    }
    return 0;
}
