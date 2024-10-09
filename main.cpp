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
    int hashFunction(const string &word) {
        return word.back() - 'a';
    }

public:
    HashTable();
    int search(const string &key);
    void insert(const string &key); 
    void remove(const string &key);
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
int HashTable::search(const string &word){
      int ID = hashFunction(word);
      int intialID = ID;

        while (status[ID] != never_used) { 
            if (status[ID] == occupied && table[ID] == word) {
                return ID;
            }
            ID = (ID + 1) % HASH_TABLE_SIZE;
            if (ID == intialID) {
                break; //after cycling through whole table, break
            }
        }
        return -1; //error

}
//insert word into hastable
void HashTable::insert(const string &word){
    int ID = hashFunction(word);

    {   //if already exist 
        if (search(word) != -1) {
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
     int ID = search(word);
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

    string command;
    for (size_t i = 0; i <= input.length(); ++i) {
        if (i == input.length() || input[i] == ' ') {
            if (!command.empty()) {
            
                char action = command[0];
                string word = command.substr(1);

                if (action == 'A') {
                    hashTable.insert(word);
                } else if (action == 'D') {
                    hashTable.remove(word);
                }

                command.clear(); 
            }
        } else {
            command += input[i];
        }
    }
    hashTable.printResult();
    return 0;
}
