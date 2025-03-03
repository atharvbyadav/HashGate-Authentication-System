#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <openssl/sha.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

#define ROOT_FILE "root.dat"
#define USERS_FILE "users.dat"

// Function to hide password input
string getHiddenInput() {
    string password;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    cin >> password;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    cout << endl;
    return password;
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

bool rootExists() {
    ifstream file(ROOT_FILE);
    return file.good();
}

void createRootPassword() {
    string rootPassword;
    cout << "No root password found. Set up a root password (cannot be changed later): ";
    rootPassword = getHiddenInput();
    ofstream file(ROOT_FILE);
    file << sha256(rootPassword);
    file.close();
    cout << "Root password set successfully!\n";
}

bool verifyRootPassword(const string &inputPassword) {
    ifstream file(ROOT_FILE);
    string storedHash;
    getline(file, storedHash);
    file.close();
    return sha256(inputPassword) == storedHash;
}

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

void addUser() {
    string rootPassword, username, password;
    cout << "Enter root password: ";
    rootPassword = getHiddenInput();
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
    password = getHiddenInput();

    ofstream file(USERS_FILE, ios::app);
    file << username << ":" << sha256(password) << endl;
    file.close();
    cout << "User created successfully!\n";
}

void deleteUser() {
    string rootPassword, username;
    cout << "Enter root password: ";
    rootPassword = getHiddenInput();
    if (!verifyRootPassword(rootPassword)) {
        cout << "Incorrect root password!\n";
        return;
    }

    cout << "Enter username to delete: ";
    cin >> username;
    if (!userExists(username)) {
        cout << "User does not exist!\n";
        return;
    }

    cout << "Are you sure you want to delete user '" << username << "'? (yes/no): ";
    string confirmation;
    cin >> confirmation;
    if (confirmation != "yes") {
        cout << "User deletion canceled.\n";
        return;
    }

    ifstream file(USERS_FILE);
    ofstream tempFile("temp.dat");
    string line;

    while (getline(file, line)) {
        if (line.find(username + ":") != 0) {
            tempFile << line << "\n";
        }
    }

    file.close();
    tempFile.close();
    remove(USERS_FILE);
    rename("temp.dat", USERS_FILE);

    cout << "User deleted successfully!\n";
}

void login() {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    password = getHiddenInput();

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
        cout << "\n1. Login\n2. Create User (requires root password)\n3. Delete User (requires root password)\n4. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: login(); break;
            case 2: addUser(); break;
            case 3: deleteUser(); break;
            case 4: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
