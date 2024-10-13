//Pham Phuong Ngan BUi - a1867987
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int HASH_TABLE_SIZE = 26;
enum Status { never_used, tombstone, occupied };

class HashTable {
private:
    //table for storing keys and table for value
    vector<string> table;
    vector<Status> status;

    //get index of last character in word
    int hashing(const string &word) {
        return word.back() - 'a';
    }

public:
    HashTable();
    int searchtable(const string &word);
    void insert(const string &word); 
    void remove(const string &word);
    void printResult(); 
};

//initialise the hastable with never-use
HashTable::HashTable(){
     {
        table.resize(HASH_TABLE_SIZE, "");
        status.resize(HASH_TABLE_SIZE, never_used);
    }
}

//search for word
int HashTable::searchtable(const string &word){
      int ID = hashing(word);
      int intialID = ID;

        while (status[ID] != never_used) { 
            if (status[ID] == occupied && table[ID] == word) {
                return ID;
            }
            ID = (ID + 1) % HASH_TABLE_SIZE;
            if (ID == intialID) {
                break; //exit after cycling through table
            }
        }
        return -1; //return if not found 

}
//insert word into hastable
void HashTable::insert(const string &word){
    int ID = hashing(word);

    {   //if already exist 
        if (searchtable(word) != -1) {
            return; //do nothing 
        }

        while (status[ID] == occupied) {
            ID = (ID + 1) % HASH_TABLE_SIZE;
        }

        table[ID] = word;
        status[ID] = occupied;
    }

}

//delete word 
void HashTable::remove(const string &word){
     int ID = searchtable(word);
        if (ID!= -1) {
            status[ID] = tombstone; 
        }
}

//print the result
 void HashTable::printResult(){
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            if (status[i] == occupied) {
                cout << table[i] << " ";
            }
        }
        cout << endl;
 }

int main() {
    HashTable hashTable;

    string input;
    getline(cin, input);

    string cmd;
    for (size_t i = 0; i <= input.length(); ++i) {
        if (i == input.length() || input[i] == ' ') {
            if (!cmd.empty()) {
            
                char action = cmd[0];
                string word = cmd.substr(1);

                if (action == 'A') {
                    hashTable.insert(word);
                } else if (action == 'D') {
                    hashTable.remove(word);
                }

                cmd.clear(); 
            }
        } else {
            cmd += input[i];
        }
    }
    hashTable.printResult();
    return 0;
}
