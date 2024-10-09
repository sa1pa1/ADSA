#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define the size of the hash table (26 letters from 'a' to 'z')
const int TABLE_SIZE = 26;

// Status for each slot in the hash table
enum SlotStatus { NEVER_USED, TOMBSTONE, OCCUPIED };

class HashTable {
private:
    // Hash table to store the keys
    vector<string> table;
    // Status for each slot
    vector<SlotStatus> status;

    // Hash function to get the index based on the last character of the key
    int hashFunction(const string &key) {
        return key.back() - 'a';
    }

public:
    HashTable() {
        // Initialize the table with empty strings and "never used" status
        table.resize(TABLE_SIZE, "");
        status.resize(TABLE_SIZE, NEVER_USED);
    }

    // Search for a key in the hash table
    int search(const string &key) {
        int idx = hashFunction(key);
        int originalIdx = idx;

        while (status[idx] != NEVER_USED) { // If it's not "never used"
            if (status[idx] == OCCUPIED && table[idx] == key) {
                return idx; // Key found
            }
            idx = (idx + 1) % TABLE_SIZE;
            if (idx == originalIdx) {
                break; // We've cycled through the entire table
            }
        }
        return -1; // Key not found
    }

    // Insert a key into the hash table
    void insert(const string &key) {
        if (search(key) != -1) {
            return; // Key already exists, do nothing
        }

        int idx = hashFunction(key);
        int originalIdx = idx;

        while (status[idx] == OCCUPIED) {
            idx = (idx + 1) % TABLE_SIZE;
            if (idx == originalIdx) {
                return; // Table is full, shouldn't happen in this problem constraint
            }
        }

     
        table[idx] = key;
        status[idx] = OCCUPIED;
    }


    void remove(const string &key) {
        int idx = search(key);
        if (idx != -1) {
            status[idx] = TOMBSTONE; 
        }
    }

 
    void printTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (status[i] == OCCUPIED) {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};

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

    // Output the result
    hashTable.printTable();

    return 0;
}
