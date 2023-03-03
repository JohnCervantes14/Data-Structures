#include <iostream>
#include <vector>
using namespace std;
enum major { CS, CE, NA };
class Student {
public:
    int SID;
    major MAJ;
    Student* next;
    Student();
};
Student::Student() {
    SID = -1;
    MAJ = NA;
    next = NULL;
};
class HashTable {
private:
    Student** table;
    int size;
public:
    HashTable(int table_size);
    void Add_Head(Student x);
    void Add_Order(Student x);
    void Remove(int key);
    major Search(int key);
    void Print();
    int Hash(int key);
};
HashTable::HashTable(int table_size) {
    size = table_size;
    table = new Student * [size];
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
};
int HashTable::Hash(int key) {
    return key % size;
};

// This function add a new student x to the head of the list at table[x.SID].
// For example, suppose the hash function is key%3
// and if the current hash table is
// table[0] -> 3 -> 9
// table[1] -> 1 -> 4
// table[2] -> 2 -> 5
void HashTable::Add_Head(Student x) {
    int index = Hash(x.SID);
    Student* add = new Student(x);
    Student* head = table[index];
    if(table[index] == NULL){
        table[index] = add;
    }
    else{
        add->next = head;
        table[index] = add;
    }
}

// This function add a new student x to the list at table[x.SID] such that the list remains sorted in ascending order.
// For example, suppose the hash function is key%3
// and if the current hash table is
// table[0] -> 3 -> 9
// table[1] -> 1 -> 4
// table[2] -> 2 -> 5
void HashTable::Add_Order(Student x) {
    //if list at SID is empty
    int index = Hash(x.SID);
    Student* copy = new Student(x);
    if(table[index] == NULL){
        table[index] = copy;
    }
    else{
        Student* temp = table[index];
        //check head of SID list
        if(temp->SID > copy->SID){
            copy->next = temp;
            table[index] = copy;
        }
        //check rest of list
        else {
            while (temp->next != NULL) {
                if (temp->next->SID > copy->SID) {
                    copy->next = temp->next;
                    temp->next = copy;
                    break;
                } else {
                    temp = temp->next;
                }
            }
            //add to tail if not added
            if (temp->next == NULL) {
                temp->next = copy;
            }
        }
    }
}

// This function removes a student x from the table if x.SID == key.
// If the student is not in the table, do nothing.
// For example, if the current hash table is
// table[0] -> 6 -> 3
// table[1] -> 4 -> 1
// table[2] -> 5 -> 2
void HashTable::Remove(int key) {
    Student* temp = table[Hash(key)];
   if(temp->SID == key){
        table[Hash(key)] = temp->next;
    }
   else {
       while (temp->next != NULL) {
           if (temp->next->SID == key) {
                temp->next = temp->next->next;
                break;
           }
           else temp = temp->next;
       }
   }

}

// This function returns the major of student x in the table if x.SID == key.
// If the student is not in the table, return NA.
// For example, if the current hash table is
// table[0] -> 6 -> 3
// table[1] -> 4 -> 1
// table[2] -> 5 -> 2
major HashTable::Search(int key) {
    Student* temp = table[Hash(key)];
    if(temp->SID == key){
        return temp->MAJ;
    }
    else {
        while (temp->next != NULL) {
            if (temp->next->SID == key) {
                return temp->next->MAJ;
            }
            else temp = temp->next;
        }
        return NA;
    }

}

// This function prints all SIDs in the table row by row and head-to-tail per row.
// For example, if the current hash table is
// table[0] -> 6 -> 3
// table[1] -> 4 -> 1
// table[2] -> 5 -> 2
// if we run Print(), we should see "6 3 4 1 5 2" (vertically)
void HashTable::Print() {
    Student* temp;// used to store the node we want to print

    for(int i = 0; i < size; ++i){
        temp = table[i];
        while(temp != NULL){
            cout << temp->SID << endl;
            temp = temp->next;
        }
    }
};
int main()
{
    int mode, size, key, sid, maj;
    vector<Student> input;
    Student temp;
    // Input test mode, table size, search key.
    cin >> mode >> size >> key;
    
    while (cin >> sid >> maj) {
        temp.SID = sid;
        temp.MAJ = static_cast<major>(maj);
        input.push_back(temp);
    };
    // Now construct and test the hash table.
    HashTable x(size);
    switch (mode) {
    case 1: // check the Add_Head and Print functions
        for (int i = 0; i < input.size(); i++) {
            x.Add_Head(input.at(i));
        }
        x.Print();
        break;
    case 2: // check the Add_Order function
        for (int i = 0; i < input.size(); i++) {
            x.Add_Order(input.at(i));
        }
        x.Print();
        break;
    case 3: // check the Search function (based on Add_Order)
        for (int i = 0; i < input.size(); i++) {
            x.Add_Order(input.at(i));
        }
        switch (x.Search(key)) {
        case 0:
            cout << "CS" << endl;
            break;
        case 1:
            cout << "CE" << endl;
            break;
        case 2:
            cout << "NA" << endl;
            break;
        }
        break;
    case 4: // check the Remove function (based on Add_Order)
        for (int i = 0; i < input.size(); i++) {
            x.Add_Order(input.at(i));
        }
        x.Remove(key);
        x.Print();
        break;
    }
    return 0;
}
