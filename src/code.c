#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX 100
#define ISSUE_DAYS 15

// -------------------- STRUCTURES --------------------

struct Book {
    int id;
    char title[50];
    char author[50];
    int issued;     // 0 = available, 1 = issued
    int issuedTo;   // roll number of student
    time_t issueDate;
};

struct Student {
    int roll;
    char name[50];
    char password[20];
};

// -------------------- GLOBAL --------------------

struct Book books[MAX];
struct Student students[MAX];
int bookCount = 0, studentCount = 0;

// -------------------- UTIL --------------------

void saveData();
void loadData();

int daysBetween(time_t t1, time_t t2) {
    double seconds = difftime(t2, t1);
    return (int)(seconds / 86400);
}

// -------------------- STUDENT LOGIN --------------------

int studentLogin() {
    int roll;
    char pass[20];

    printf("\nEnter Roll Number: ");
    scanf("%d", &roll);

    printf("Enter Password: ");
    scanf("%s", pass);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].roll == roll &&
            strcmp(students[i].password, pass) == 0) {
            printf("\nLogin Successful! Welcome %s\n", students[i].name);
            return roll;
        }
    }

    printf("\nInvalid login!\n");
    return -1;
}

// -------------------- ADD STUDENT --------------------

void addStudent() {
    struct Student s;

    printf("\nEnter Student Roll: ");
    scanf("%d", &s.roll);

    printf("Enter Student Name: ");
    getchar();
    fgets(s.name, 50, stdin);

    printf("Enter Password: ");
    scanf("%s", s.password);

    students[studentCount++] = s;

    printf("\nStudent added successfully!\n");
    saveData();
}

// -------------------- ADD BOOK --------------------

void addBook() {
    struct Book b;

    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Book Title: ");
    getchar();
    fgets(b.title, 50, stdin);

    printf("Enter Author: ");
    fgets(b.author, 50, stdin);

    b.issued = 0;
    b.issuedTo = -1;

    books[bookCount++] = b;
    printf("\nBook Added!\n");

    saveData();
}

// -------------------- VIEW BOOKS --------------------

void viewBooks() {
    printf("\n--------- ALL BOOKS -----------\n");

    for (int i = 0; i < bookCount; i++) {
        printf("\nID: %d", books[i].id);
        printf("\nTitle: %s", books[i].title);
        printf("Author: %s", books[i].author);
        printf("Status: %s", books[i].issued ? "Issued" : "Available");
        if (books[i].issued)
            printf(" (Issued to Roll: %d)", books[i].issuedTo);
        printf("\n");
    }
}

// -------------------- ISSUE BOOK --------------------

void issueBook(int roll) {
    int id;

    printf("\nEnter Book ID to Issue: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            if (books[i].issued == 1) {
                printf("Book already issued.\n");
                return;
            }

            books[i].issued = 1;
            books[i].issuedTo = roll;
            books[i].issueDate = time(NULL);

            printf("\nBook Issued! Return within %d days.\n", ISSUE_DAYS);
            saveData();
            return;
        }
    }

    printf("Book not found.\n");
}

// -------------------- RETURN BOOK --------------------

void returnBook(int roll) {
    int id;
    printf("\nEnter Book ID to Return: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id && books[i].issuedTo == roll) {

            time_t now = time(NULL);
            int diff = daysBetween(books[i].issueDate, now);

            if (diff > ISSUE_DAYS) {
                printf("\nReturn Late! Due date passed by %d days.\n", diff - ISSUE_DAYS);
            } else {
                printf("\nReturned on time!\n");
            }

            books[i].issued = 0;
            books[i].issuedTo = -1;

            saveData();
            return;
        }
    }

    printf("You have not issued this book.\n");
}

// -------------------- REISSUE --------------------

void reissueBook(int roll) {
    int id;
    printf("\nEnter Book ID to Reissue: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id && books[i].issuedTo == roll) {

            time_t now = time(NULL);
            int diff = daysBetween(books[i].issueDate, now);

            if (diff > ISSUE_DAYS) {
                printf("\nCannot reissue. Due date already passed!\n");
                return;
            }

            books[i].issueDate = now;
            printf("\nBook Reissued for another %d days!\n", ISSUE_DAYS);

            saveData();
            return;
        }
    }

    printf("No such book issued by you.\n");
}

// -------------------- DUE DATE CHECK --------------------

void checkDueDates(int roll) {
    printf("\n------ DUE DATE ALERTS ------\n");

    for (int i = 0; i < bookCount; i++) {
        if (books[i].issuedTo == roll) {
            time_t now = time(NULL);
            int diff = daysBetween(books[i].issueDate, now);

            if (diff > ISSUE_DAYS) {
                printf("⚠ Book ID %d is LATE! Please return immediately.\n", books[i].id);
            }
        }
    }
}

// -------------------- FILE HANDLING --------------------

void saveData() {
    FILE *f;

    f = fopen("books.dat", "wb");
    fwrite(&bookCount, sizeof(int), 1, f);
    fwrite(books, sizeof(struct Book), bookCount, f);
    fclose(f);

    f = fopen("students.dat", "wb");
    fwrite(&studentCount, sizeof(int), 1, f);
    fwrite(students, sizeof(struct Student), studentCount, f);
    fclose(f);
}

void loadData() {
    FILE *f;

    f = fopen("books.dat", "rb");
    if (f) {
        fread(&bookCount, sizeof(int), 1, f);
        fread(books, sizeof(struct Book), bookCount, f);
        fclose(f);
    }

    f = fopen("students.dat", "rb");
    if (f) {
        fread(&studentCount, sizeof(int), 1, f);
        fread(students, sizeof(struct Student), studentCount, f);
        fclose(f);
    }
}

// -------------------- MAIN --------------------

void studentMenu(int roll) {
    int ch;

    while (1) {
        printf("\n----- STUDENT MENU -----\n");
        printf("1. View Books\n");
        printf("2. Issue Book\n");
        printf("3. Return Book\n");
        printf("4. Reissue Book\n");
        printf("5. Check Due Messages\n");
        printf("6. Logout\n");

        scanf("%d", &ch);

        switch (ch) {
            case 1: viewBooks(); break;
            case 2: issueBook(roll); break;
            case 3: returnBook(roll); break;
            case 4: reissueBook(roll); break;
            case 5: checkDueDates(roll); break;
            case 6: return;
            default: printf("Invalid!\n");
        }
    }
}

int main() {
    loadData();

    int choice;

    while (1) {
        printf("\n===== LIBRARY SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Add Book\n");
        printf("3. Student Login\n");
        printf("4. Exit\n");

        scanf("%d", &choice);

        if (choice == 1) addStudent();
        else if (choice == 2) addBook();
        else if (choice == 3) {
            int roll = studentLogin();
            if (roll != -1) studentMenu(roll);
        }
        else if (choice == 4) {
            printf("\nGoodbye darling ❤️\n");
            break;
        }
        else printf("Invalid choice!\n");
    }

    return 0;
}
