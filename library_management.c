/*
 ============================================================
  LIBRARY BOOK MANAGEMENT SYSTEM
  Data Structure Used: Singly Linked List
 ============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ─── Node Structure ─────────────────────────────────────── */
typedef struct Book {
    char id[50];
    char title[100];
    char author[100];
    int year;
    struct Book *next;
} Book;

/* Global head pointer */
Book *head = NULL;

/* ─── Case-insensitive string compare ──────────────────── */
int compareIgnoreCase(char a[], char b[]) {
    // FIX: lengths must match first
    if (strlen(a) != strlen(b)) return 0;

    for (int i = 0; a[i] && b[i]; i++) {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i]))
            return 0;
    }
    return 1;
}

/* ─── Utility Line ──────────────────────────────────────── */
void printLine() {
    printf("\n============================================================\n");
}

/* ─── ADD BOOK ──────────────────────────────────────────── */
void addBook() {
    Book *newBook = (Book *)malloc(sizeof(Book));

    if (newBook == NULL) {
        printf("\n[ERROR] Memory allocation failed!\n");
        return;
    }

    printf("\n--- Add New Book ---\n");
    printf("Enter Book ID: ");
    scanf("%49s", newBook->id);
    getchar();

    /* Check duplicate ID */
    Book *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->id, newBook->id) == 0) {
            printf("[ERROR] Book ID %s already exists!\n", newBook->id);
            free(newBook);
            return;
        }
        temp = temp->next;
    }

    printf("Enter Book Title: ");
    fgets(newBook->title, 100, stdin);
    newBook->title[strcspn(newBook->title, "\n")] = '\0';

    printf("Enter Author Name: ");
    fgets(newBook->author, 100, stdin);
    newBook->author[strcspn(newBook->author, "\n")] = '\0';

    /* IMPROVEMENT: Validate year input */
    do {
        printf("Enter Year (e.g. 2024): ");
        scanf("%d", &newBook->year);
        getchar();
        if (newBook->year <= 0 || newBook->year > 2100)
            printf("[ERROR] Please enter a valid year.\n");
    } while (newBook->year <= 0 || newBook->year > 2100);

    newBook->next = NULL;

    /* Add to end of list */
    if (head == NULL) {
        head = newBook;
    } else {
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newBook;
    }

    printf("\n[SUCCESS] Book \"%s\" added successfully!\n", newBook->title);
}

/* ─── DELETE BOOK ───────────────────────────────────────── */
void deleteBook() {
    if (head == NULL) {
        printf("\n[INFO] Library is empty.\n");
        return;
    }

    char id[50];
    printf("\nEnter Book ID to delete: ");
    scanf("%49s", id);
    getchar();

    Book *temp = head, *prev = NULL;

    while (temp != NULL && strcmp(temp->id, id) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("[ERROR] Book with ID %s not found!\n", id);
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    printf("[SUCCESS] Book \"%s\" deleted!\n", temp->title);
    free(temp);
    temp = NULL; // IMPROVEMENT: avoid dangling pointer
}

/* ─── SEARCH BOOK ───────────────────────────────────────── */
void searchBook() {
    if (head == NULL) {
        printf("\n[INFO] Library is empty.\n");
        return;
    }

    int choice;
    printf("\nSearch by:\n1. ID\n2. Title\nEnter choice: ");
    scanf("%d", &choice);
    getchar();

    Book *temp = head;
    int found = 0;

    if (choice == 1) {
        char id[50];
        printf("Enter Book ID: ");
        scanf("%49s", id);
        getchar();

        while (temp != NULL) {
            if (strcmp(temp->id, id) == 0) { found = 1; break; }
            temp = temp->next;
        }
    }
    else if (choice == 2) {
        char title[100];
        printf("Enter Title: ");
        fgets(title, 100, stdin);
        title[strcspn(title, "\n")] = '\0';

        while (temp != NULL) {
            if (compareIgnoreCase(temp->title, title)) { found = 1; break; }
            temp = temp->next;
        }
    }
    else {
        printf("[ERROR] Invalid choice!\n");
        return;
    }

    if (found) {
        printf("\n--- Book Found ---\n");
        printf("  ID     : %s\n",   temp->id);
        printf("  Title  : %s\n",   temp->title);
        printf("  Author : %s\n",   temp->author);
        printf("  Year   : %d\n",   temp->year);
    } else {
        printf("[NOT FOUND] No book matches your search.\n");
    }
}

/* ─── DISPLAY BOOKS ─────────────────────────────────────── */
void displayBooks() {
    if (head == NULL) {
        printf("\n[INFO] No books available.\n");
        return;
    }

    Book *temp = head;
    int serial = 1;

    // IMPROVEMENT: Cleaner column layout using fixed width
    printf("\n%-4s %-10s %-30s %-25s %-6s\n",
           "No.", "ID", "Title", "Author", "Year");
    printf("------------------------------------------------------------"
           "---------------------\n");

    while (temp != NULL) {
        printf("%-4d %-10s %-30s %-25s %-6d\n",
               serial++, temp->id, temp->title, temp->author, temp->year);
        temp = temp->next;
    }
}

/* ─── COUNT BOOKS ───────────────────────────────────────── */
void countBooks() {
    int count = 0;
    Book *temp = head;

    while (temp != NULL) { count++; temp = temp->next; }

    printf("\nTotal Books in Library: %d\n", count);
}

/* ─── FREE MEMORY ───────────────────────────────────────── */
void freeLibrary() {
    Book *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("[INFO] Memory freed successfully.\n");
}

/* ─── MAIN FUNCTION ─────────────────────────────────────── */
int main() {
    int choice;

    do {
        printLine();
        printf("       LIBRARY MANAGEMENT SYSTEM\n");
        printLine();
        printf("  1. Add Book\n");
        printf("  2. Delete Book\n");
        printf("  3. Search Book\n");
        printf("  4. Display All Books\n");
        printf("  5. Count Books\n");
        printf("  6. Exit\n");
        printLine();
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addBook();      break;
            case 2: deleteBook();   break;
            case 3: searchBook();   break;
            case 4: displayBooks(); break;
            case 5: countBooks();   break;
            case 6:
                freeLibrary();
                printf("\nGoodbye! Exiting...\n");
                break;
            default:
                printf("[ERROR] Invalid choice! Please enter 1-6.\n");
        }

    } while (choice != 6);

    return 0;
}
