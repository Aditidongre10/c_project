#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// -------------------- MACROS --------------------
#define MAX 100
#define ISSUE_DAYS 15

// -------------------- STRUCTURES --------------------
struct Book {
    int id;
    char title[50];
    char author[50];
    int issued;         // 0 = available, 1 = issued
    int issuedTo;       // roll number of student
    time_t issueDate;
};

struct Student {
    int roll;
    char name[50];
    char password[20];
};

// -------------------- GLOBAL VARIABLES --------------------
extern struct Book books[MAX];
extern struct Student students[MAX];
extern int bookCount;
extern int studentCount;

// -------------------- FUNCTION PROTOTYPES --------------------

// Data handling
void saveData();
void loadData();
int daysBetween(time_t t1, time_t t2);

// Student functions
void addStudent();
int studentLogin();

// Book functions
void addBook();
void viewBooks();
void issueBook(int roll);
void returnBook(int roll);
void reissueBook(int roll);
void checkDueDates(int roll);

// Menu
void studentMenu(int roll);

#endif
