# Library Management System

A simple console-based Library Management System written in C using a singly linked list.

## Features

- Add a new book with ID, title, author, and year
- Prevent duplicate book IDs
- Delete a book by ID
- Search books by ID or title (case-insensitive title search)
- Display all books in a tabular format
- Count total books in the library
- Free allocated memory on exit

## File Structure

- `library_management.c` — complete source code for the application

## Build Instructions

Use GCC to compile:

```bash
gcc library_management.c -o library_management
```

## Run Instructions

```bash
./library_management
```

## Menu Options

1. Add Book
2. Delete Book
3. Search Book
4. Display All Books
5. Count Books
6. Exit

## Notes

- Input is taken interactively from the terminal.
- Valid publication year range: `1` to `2100`.
