
# 📘 School Management System

A console-based **School Management System** developed in **C**, aimed at helping schools efficiently manage academic records and administrative functions. This lightweight system is designed for educational institutions looking for a simple, offline, and easy-to-modify solution.

---

## 🎯 Purpose

This project was created as part of an academic coursework for the subject **Man C**. It serves as a practical demonstration of:

- File handling in C
- Modular programming (using `.c` and `.h` files)
- Basic data structures
- Real-world application of procedural programming

---

## ⚙️ System Overview

This system supports the following core modules:

### 👤 Admin Module
- Login functionality
- Access control
- User settings

### 🎓 Student Module
- Add new students
- Edit existing student records
- Delete students
- View all student data

### 🧪 Exam Module
- Add exam schedules
- Record exam results
- View exam reports

All data is managed via files, allowing persistent storage without the need for a database.

---

## 🔧 How to Run

### 🖥️ Requirements:
- C Compiler (e.g., GCC)
- Code::Blocks (recommended) or any other IDE

### ▶️ Steps to Run:

#### Option 1: Using Code::Blocks
1. Open `School Management System.cbp` in Code::Blocks.
2. Click “Build and Run”.

#### Option 2: Using Terminal
If you have GCC installed:
```bash
gcc main.c admin.c exam.c student.c -o school_mgmt
./school_mgmt
```

---

## 🌟 Features

- Modular source code (easy to maintain or upgrade)
- File-based data management (no database required)
- Simple and user-friendly console interface
- Separation of concerns with `.c` and `.h` files

---

## 💡 Why Use This Project?

This system is ideal for:

- Students learning C through real-world examples
- Schools with basic computing needs
- Developers looking for a base to build a full-featured school ERP

You can extend it to include:

- Teacher management
- Subject assignments
- Timetables
- GUI (Graphical User Interface) with libraries like GTK

---

## 🤝 Contribution

Feel free to fork and modify this project. Contributions are welcome!

1. Fork the repo
2. Make your changes
3. Submit a pull request

---

## 🔒 License

This project is released under the [MIT License](LICENSE).
