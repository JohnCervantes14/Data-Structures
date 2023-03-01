#include <iostream>
using namespace std;

class Student {
    public:
        void SetSID(int a);
        int GetSID();
    private:
        int SID;
    };

// Please define the function of SetID() here;
// It should assign an input integer a to SID
// ...........................................
    void Student::SetSID(int a) {
        SID = a;
    }

// Please define the function of GetID() here;
// It should return the value of SID
// ...........................................
    int Student::GetSID() {
        return SID;
    }

int* BinarySearch(Student* ptr, int arr_size, int key) {
    // --------------------------------------------------------------------
    // Please implement binary search here
    // Input: an array of student objects, the array size and a search key
    // Output: an array of two integers (declared for you below)
    //         The 1st element is the search result: index of
    //         the key in the array if it is found or -1
    //         The 2nd element is the number of search iterations
    //         it takes for your algorithm to return the result
    // --------------------------------------------------------------------
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
    //

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
    // The main function is given to you.
    // It first declares an array of seven student objects.
    // It then takes a key and seven SID's as input and
    // assigns the ID's to the seven students.
    //
    // Then, it checks if the input SID's are sorted in
    // ascending order.
    // If so, it will perform binary search.
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
