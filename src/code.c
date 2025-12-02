#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    char title[50];
    char author[50];
    int issued;
};

struct Book library[100];
int count = 0;

void flush() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addBook() {
    printf("\nEnter Book ID: ");
    scanf("%d", &library[count].id);
    flush();

    printf("Enter Book Title: ");
    fgets(library[count].title, 50, stdin);

    printf("Enter Author Name: ");
    fgets(library[count].author, 50, stdin);

    library[count].issued = 0;
    count++;

    printf("\nBook Added Successfully!\n");
}

void viewBooks() {
    if (count == 0) {
        printf("\nNo books available.\n");
        return;
    }

    printf("\n--- All Books ---\n");
    for (int i = 0; i < count; i++) {
        printf("\nID: %d", library[i].id);
        printf("Title: %s", library[i].title);
        printf("Author: %s", library[i].author);
        printf("Status: %s\n", library[i].issued ? "Issued" : "Available");
    }
}

void searchBook() {
    int id;
    printf("\nEnter Book ID to Search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (library[i].id == id) {
            printf("\nBook Found!\n");
            printf("Title: %s", library[i].title);
            printf("Author: %s", library[i].author);
            printf("Status: %s\n", library[i].issued ? "Issued" : "Available");
            return;
        }
    }
    printf("Book Not Found.\n");
}

void deleteBook() {
    int id;
    printf("\nEnter Book ID to Delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (library[i].id == id) {
            for (int j = i; j < count - 1; j++)
                library[j] = library[j + 1];
            count--;
            printf("Book Deleted Successfully!\n");
            return;
        }
    }
    printf("Book Not Found.\n");
}

void issueBook() {
    int id;
    printf("\nEnter Book ID to Issue: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (library[i].id == id) {
            if (library[i].issued == 1) {
                printf("Book already issued.\n");
                return;
            }
            library[i].issued = 1;
            printf("Book Issued Successfully!\n");
            return;
        }
    }
    printf("Book Not Found.\n");
}

void returnBook() {
    int id;
    printf("\nEnter Book ID to Return: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (library[i].id == id) {
            if (library[i].issued == 0) {
                printf("Book is not issued.\n");
                return;
            }
            library[i].issued = 0;
            printf("Book Returned Successfully!\n");
            return;
        }
    }
    printf("Book Not Found.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n\n=== Library Management System ===\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Search Book\n");
        printf("4. Delete Book\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Enter numbers only.\n");
            flush();
            continue;
        }

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: issueBook(); break;
            case 6: returnBook(); break;
            case 7: printf("Bye \n"); return 0;
            default: printf("Invalid Choice!\n");
        }
    }
}
