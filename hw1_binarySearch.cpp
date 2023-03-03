#include <iostream>
using namespace std;

class Student {
    public:
        void SetSID(int a);
        int GetSID();
    private:
        int SID;
    };

    void Student::SetSID(int a) {
        SID = a;
    }

    int Student::GetSID() {
        return SID;
    }

int* BinarySearch(Student* ptr, int arr_size, int key) {
    int keyIndex{-1};
    int iterations{0};
    int first{0};
    int last{arr_size-1};
    int center;

    while(first <= last){
        center = (first + last)/2;
        if(ptr[center].GetSID() > key){
            last = center - 1;
            ++iterations;
        }
        else if(ptr[center].GetSID() < key){
            first = center + 1;
            ++iterations;
        }
        else{
            keyIndex = center;
            ++iterations;
            break;
        }
    }

    static int val[2]; // to prevent the content of array from being lost
    val[0] = keyIndex;
    val[1] = iterations;
    return val;
}
int CheckOrder(Student* ptr, int arr_size) {
    // Return 1 if sorted, and return 0 if not.
    // If the SID's of ptr[0], ptr[1], ptr[3] are 3, 1, 5,
    // then it is not sorted. Return 0.
    for(int i = 0; i < arr_size-1; ++i){
        if(ptr[i].GetSID() > ptr[i + 1].GetSID()){
            return 0;
        }
    }
    return 1;
}
int main() {
    Student x[7];
    int temp, key, mode, *value;
    cin >> mode >> key;
    for (int i = 0; i < 7; i++) {

        cin >> temp;
        x[i].SetSID(temp);
    }
    switch (mode) {

        case 1: // check correction of the CheckOrder function

            cout << CheckOrder(x, 7) << endl;
            break;
        case 2: // check correction of the returned index of the search
            if (CheckOrder(x, 7)) {
                value = BinarySearch(x, 7, key);
                cout << value[0] << endl;
            } else {
                cout << -2 << endl;
            }
            break;
        case 3: // check correction of the number of search iterations
            if (CheckOrder(x, 7)) {
                value = BinarySearch(x, 7, key);
                cout << value[1] << endl;
            } else {
                cout << -2 << endl;
            }
            break;
    }
    return 0;
}
