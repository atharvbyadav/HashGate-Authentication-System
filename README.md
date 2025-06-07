# 🔐 HashGate Authentication System (Stage 1)

<p align="center">
  <a href="#">
    <img alt="Language|C++" src="https://img.shields.io/badge/Language-C++-blue?style=for-the-badge" />
  </a>
  <a href="#">
    <img alt="SHA-256|HASHING" src="https://img.shields.io/badge/SHA--256-Hashing-critical?style=for-the-badge" />
  </a>
  <a href="#">
    <img alt="PLATFORM" src="https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-informational?style=for-the-badge" />
  </a>
  <a href="#">
    <img alt="LICENSE" src="https://img.shields.io/badge/License-MIT-success?style=for-the-badge" />
  </a>
  <a href="https://www.python.org/downloads/">
    <img alt="STAGE|1" src="https://img.shields.io/badge/Project%20Stage-1--of--X-yellow?style=for-the-badge" />
  </a>
</p>

---

## 📝 Overview

The **HashGate Authentication System** is a secure, file-based user authentication program written in C++. It provides a simple yet effective way to manage user authentication with the following features:

- **🔑 User Login** with SHA-256 hashed passwords.
- **👤 User Creation** (requires root password verification).
- **🗑️ User Deletion** (requires root password verification and confirmation).
- **🔒 Secure Root Password Setup** on the first run.
- **🙈 Hidden Password Input** for security during login and root password prompts.

This system ensures that user credentials are stored securely using hashing techniques and provides a basic but effective local authentication mechanism.

🚀 **Note:** This program is just a part of a bigger project I am working on. It serves as the **front-end login system** for a larger application currently under development.

## 🚀 Features

- **SHA-256 Hashing**: Ensures passwords are stored securely.
- **Root Password Protection**: Required for adding and deleting users.
- **Hidden Password Input**: Conceals passwords while typing.
- **File-Based Storage**: User credentials are stored safely in local files (`users.dat` and `root.dat`).

## 🛠️ How It Works

1. **First Run Setup**: The system prompts the user to set a **root password** (this cannot be changed later).
2. Users can:
   - **🔑 Login** with a username and password.
   - **➕ Create a new user** (requires root password verification).
   - **🗑️ Delete a user** (requires root password verification and confirmation).
   - **❌ Exit** the program.
3. Passwords are stored **securely as SHA-256 hashes** to prevent unauthorized access.

## ⚙️ Setup and Compilation

### **Requirements**

- C++ compiler (e.g., `g++` for Linux or MinGW for Windows)
- OpenSSL library for SHA-256 hashing

### **Compilation on Linux**

```sh
 g++ authentication.cpp -o hashgate -lssl -lcrypto
```

### **Compilation on Windows (MinGW)**

```sh
g++ authentication.cpp -o hashgate.exe -lssl -lcrypto
```

## 📌 Usage

1. Run the compiled executable:
   ```sh
   ./hashgate   # Linux
   hashgate.exe # Windows
   ```
2. **First Run**:
   - The program will prompt for a **root password**.
   - This password is required to create or delete users.
3. **🔑 Login**:
   - Enter a valid username and password.
   - If correct, access is granted; otherwise, an error is shown.
4. **➕ Create a User**:
   - Enter the root password.
   - Provide a new username and password.
5. **🗑️ Delete a User**:
   - Enter the root password.
   - Provide the username to delete.
   - Confirm deletion.
6. **❌ Exit** the program by selecting option `4`.

## 🔒 Security Considerations

- **Root Password Security**: The root password is stored as a SHA-256 hash and cannot be changed after setup.
- **User Passwords**: Stored securely using SHA-256 hashing.
- **File Storage**:
  - `root.dat`: Contains the hashed root password.
  - `users.dat`: Stores user credentials in `username:hashed_password` format.

## 📜 License

This project is open-source and free to use under the MIT License.

---

Contributions and suggestions are welcome! 🚀

## 🤝 Collaboration & Contributions

I am open to collaboration if you have great ideas to implement! Feel free to **open issues**, **submit pull requests**, or discuss enhancements. Let's make **HashGate Authentication System** even better together! 💡🔧

