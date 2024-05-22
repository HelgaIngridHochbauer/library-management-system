#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 1000
#define BOOKS_FILE "books.txt"
#define LOANS_FILE "loans.txt"
#define PERSONS_FILE "persons.txt"

typedef struct {
    char name[50];
    char surname[50];
    char password[50];
    char email[100];
}Person;

typedef struct {
    char title[100];
    char author[100];
    int copies_available;
}Book;

typedef struct {
    char name[50];
    char surname[50];
    char title[100];
    char author[100];
} Loan;

// Global arrays to store books and loans
Book books[100]; // Assuming there are up to 100 books in the library
Loan loans[100]; // Assuming there are up to 100 active loans
Person persons[100]; // Assuming there are up to 100 registered users

// Function prototypes
void login(char name[], char surname[], char password[], char email[]);
void register_account();
void delete_account();
void borrow_books(Person person);
void return_books(Person person);
void donate_books();
void view_loans(Person person);
void search_books();

#endif