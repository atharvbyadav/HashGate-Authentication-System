#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

#define ROOT_FILE "root.dat"
#define USERS_FILE "users.dat"

// Simple XOR encryption (for reversible encryption)
string encryptDecrypt(string data, char key) {
    for (size_t i = 0; i < data.size(); i++) {
        data[i] ^= key;
    }
    return data;
}

// Hashing function using SHA-256
string sha256(const string &str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)str.c_str(), str.size(), hash);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Check if the root password exists
bool rootExists() {
    ifstream file(ROOT_FILE);
    return file.good();
}

// Create the root password (only on first launch)
void createRootPassword() {
    string rootPassword;
    cout << "No root password found. Set up a root password (cannot be changed later): ";
    cin >> rootPassword;
    ofstream file(ROOT_FILE);
    file << sha256(rootPassword);  // Store hashed root password
    file.close();
    cout << "Root password set successfully!\n";
}

// Verify the root password
bool verifyRootPassword(const string &inputPassword) {
    ifstream file(ROOT_FILE);
    string storedHash;
    getline(file, storedHash);
    file.close();
    return sha256(inputPassword) == storedHash;
}

// Check if a user exists
bool userExists(const string &username) {
    ifstream file(USERS_FILE);
    string line;
    while (getline(file, line)) {
        if (line.find(username + ":") == 0) {
            return true;
        }
    }
    return false;
}

// Add a new user (only with root password authentication)
void addUser() {
    string rootPassword, username, password;
    cout << "Enter root password: ";
    cin >> rootPassword;
    if (!verifyRootPassword(rootPassword)) {
        cout << "Incorrect root password!\n";
        return;
    }

    cout << "Enter new username: ";
    cin >> username;
    if (userExists(username)) {
        cout << "Username already taken.\n";
        return;
    }

    cout << "Enter new password: ";
    cin >> password;

    ofstream file(USERS_FILE, ios::app);
    file << username << ":" << sha256(password) << endl;  // Store hashed password
    file.close();
    cout << "User created successfully!\n";
}

// Login function
void login() {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file(USERS_FILE);
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(":");
        if (pos != string::npos) {
            string storedUser = line.substr(0, pos);
            string storedHash = line.substr(pos + 1);
            if (storedUser == username && storedHash == sha256(password)) {
                cout << "Login successful!\n";
                return;
            }
        }
    }
    cout << "Invalid username or password.\n";
}

int main() {
    if (!rootExists()) {
        createRootPassword();
    }

    int choice;
    while (true) {
        cout << "\n1. Login\n2. Create User (requires root password)\n3. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: login(); break;
            case 2: addUser(); break;
            case 3: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
