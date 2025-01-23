# Library Management System

## Overview
A C++ implementation of a library management system that handles book inventory, user management, and borrowing/returning operations. Features include book search, user tracking, and library status reporting.

## Features
- **Book Management**:
  - Add new books with ID, name, and quantity
  - Track borrowed copies and borrowers
  - Sort books by ID or name
  - Search books by name prefix
- **User Management**:
  - Add/remove users
  - Track borrowed books per user
  - Validate user-book relationships
- **Operations**:
  - Borrow/return books with validation
  - View all users and their borrowed books
  - See who borrowed specific books
- **Safety Features**:
  - Input validation
  - Maximum limits (100 books/100 users)
  - Quantity checks for availability

## Installation
1. Ensure you have a C++ compiler (e.g., g++)
2. Compile the source file:
```bash
g++ library_system.cpp -o library
```
3. run the .exe file
```bash
./library
```

## Usage
#### Main Menu Options:
```
1) Add book
2) Search books by prefix
3) Print who borrowed book by name
4) Print library by ID
5) Print library by name
6) Add user
7) User borrow book
8) User return book
9) Print users
10) Exit
```
### Example workflow
#### Adding a Book:
```
1) Add book
Enter book id: 101
Enter book's name: The_C++_Programming_Language
Enter quantity: 5
Book added successfully
```
#### Borrowing a Book:
```
7) User borrow book
Enter user name: John
Enter book name: The_C++_Programming_Language
Congratulations. The_C++_Programming_Language Book borrowed successfully
```
#### Returning a Book:
```
8) User return book
Enter user name: John
Enter book name: The_C++_Programming_Language
Congratulations, The_C++_Programming_Language book returned successfully
```
#### Searching Books:
```
2) Search books by prefix
Enter query: The
3 books matching
id: 101  name: The_C++_Programming_Language  quantity: 4  totalborrowed: 1
```
## Notes
### Limitations:
- Maximum 100 books and 100 users
- Book/user names cannot contain spaces
- No persistent storage (data lost on exit)
### Input Requirements:
- Book IDs must be unique integers
- User names must match exactly for operations
- Quantity must be ≥0
### Implementation Details:
- Uses recursive array shifting for list management
- Sorts books using comparator functions
- Prefix search is case-sensitive
