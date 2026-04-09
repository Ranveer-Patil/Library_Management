/*
 ============================================================
  LIBRARY BOOK MANAGEMENT SYSTEM
  Data Structure Used: Singly Linked List
  Department of First Year Engineering - VIT
  Academic Year: 2025-26
 ============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─── Node Structure ─────────────────────────────────────── */
struct Book {
    int    id;
    char   title[100];
    char   author[100];
    int    year;
    struct Book *next;
};

typedef struct Book Book;

/* Global head pointer */
Book *head = NULL;

/* ─── Utility: Print a decorative line ───────────────────── */
void printLine() {
    printf("\n============================================================\n");
}

/* ─── 1. ADD BOOK (Insert at end) ────────────────────── */
void addBook() {
    Book *newBook = (Book *)malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("\n  [ERROR] Memory allocation failed!\n");
        return;
    }

    printf("\n  --- Add New Book ---\n");
    printf("  Enter Book ID     : ");
    scanf("%d", &newBook->id);
    getchar(); /* flush newline */

    printf("  Enter Book Title  : ");
    fgets(newBook->title, 100, stdin);
    newBook->title[strcspn(newBook->title, "\n")] = '\0';

    printf("  Enter Author Name : ");
    fgets(newBook->author, 100, stdin);
    newBook->author[strcspn(newBook->author, "\n")] = '\0';

    printf("  Enter Year        : ");
    scanf("%d", &newBook->year);

    newBook->next = NULL;

    /* If list is empty, new node becomes head */
    if (head == NULL) {
        head = newBook;
    } else {
        Book *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newBook;
    }

    printf("\n  [SUCCESS] Book \"%s\" added successfully!\n", newBook->title);
}

/* ─── 2. DELETE BOOK (by ID) ─────────────────────────────── */
void deleteBook() {
    if (head == NULL) {
        printf("\n  [INFO] Library is empty. Nothing to delete.\n");
        return;
    }

    int id;
    printf("\n  --- Delete Book ---\n");
    printf("  Enter Book ID to delete: ");
    scanf("%d", &id);

    Book *temp = head;
    Book *prev = NULL;

    /* Search for the book */
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\n  [ERROR] Book with ID %d not found!\n", id);
        return;
    }

    if (prev == NULL)
        head = temp->next;   /* Deleting head node */
    else
        prev->next = temp->next;

    printf("\n  [SUCCESS] Book \"%s\" deleted successfully!\n", temp->title);
    free(temp);
}

/* ─── 3. SEARCH BOOK (by Title or ID) ───────────────────── */
void searchBook() {
    if (head == NULL) {
        printf("\n  [INFO] Library is empty. No books to search.\n");
        return;
    }

    printf("\n  --- Search Book ---\n");
    printf("  Search by:\n");
    printf("   1. Book ID\n");
    printf("   2. Book Title\n");
    printf("  Enter choice: ");

    int choice;
    scanf("%d", &choice);
    getchar();

    Book *temp = head;
    int found = 0;

    if (choice == 1) {
        int id;
        printf("  Enter Book ID: ");
        scanf("%d", &id);

        while (temp != NULL) {
            if (temp->id == id) {
                found = 1;
                break;
            }
            temp = temp->next;
        }
    } else if (choice == 2) {
        char title[100];
        printf("  Enter Book Title: ");
        fgets(title, 100, stdin);
        title[strcspn(title, "\n")] = '\0';

        while (temp != NULL) {
            if (strcasecmp(temp->title, title) == 0) {
                found = 1;
                break;
            }
            temp = temp->next;
        }
    } else {
        printf("\n  [ERROR] Invalid choice!\n");
        return;
    }

    if (found) {
        printf("\n  [FOUND] Book Details:\n");
        printf("  ┌──────────────────────────────────────┐\n");
        printf("  │ ID     : %-28d│\n", temp->id);
        printf("  │ Title  : %-28s│\n", temp->title);
        printf("  │ Author : %-28s│\n", temp->author);
        printf("  │ Year   : %-28d│\n", temp->year);
        printf("  └──────────────────────────────────────┘\n");
    } else {
        printf("\n  [NOT FOUND] No matching book found.\n");
    }
}

/* ─── 4. DISPLAY ALL BOOKS ───────────────────────────────── */
void displayBooks() {
    if (head == NULL) {
        printf("\n  [INFO] Library is empty. No books to display.\n");
        return;
    }

    printf("\n  --- All Books in Library ---\n");
    printf("  %-6s %-30s %-25s %-6s\n", "ID", "Title", "Author", "Year");
    printf("  %-6s %-30s %-25s %-6s\n",
           "------", "------------------------------",
           "-------------------------", "------");

    Book *temp = head;
    int count = 0;
    while (temp != NULL) {
        printf("  %-6d %-30s %-25s %-6d\n",
               temp->id, temp->title, temp->author, temp->year);
        temp = temp->next;
        count++;
    }

    printf("\n  Total Books: %d\n", count);
}

/* ─── 5. COUNT BOOKS ─────────────────────────────────────── */
void countBooks() {
    int count = 0;
    Book *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("\n  [INFO] Total number of books in library: %d\n", count);
}

/* ─── 6. FREE ALL MEMORY ─────────────────────────────────── */
void freeLibrary() {
    Book *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* ─── MAIN MENU ──────────────────────────────────────────── */
int main() {
    int choice;

    printLine();
    printf("     LIBRARY BOOK MANAGEMENT SYSTEM");
    printf("\n     Data Structure: Singly Linked List");
    printf("\n     VIT - Department of First Year Engineering");
    printf("\n     Academic Year: 2025-26");
    printLine();

    do {
        printf("\n  MENU:\n");
        printf("   1. Add Book\n");
        printf("   2. Delete Book\n");
        printf("   3. Search Book\n");
        printf("   4. Display All Books\n");
        printf("   5. Count Books\n");
        printf("   6. Exit\n");
        printf("\n  Enter your choice: ");
        scanf("%d", &choice);

        printLine();

        switch (choice) {
            case 1: addBook();     break;
            case 2: deleteBook();  break;
            case 3: searchBook();  break;
            case 4: displayBooks();break;
            case 5: countBooks();  break;
            case 6:
                freeLibrary();
                printf("\n  Thank you! Exiting Library Management System.\n");
                break;
            default:
                printf("\n  [ERROR] Invalid choice! Please enter 1-6.\n");
        }

        printLine();

    } while (choice != 6);

    return 0;
}
