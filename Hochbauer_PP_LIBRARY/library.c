#include <stdio.h>
#include <string.h>
#include "library.h"
void login(char name[], char surname[], char password[], char email[]) {
    // Open the file for reading
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    // Read each line from the file
    Person currentPerson;
    int found = 0;
    // Compare the input data with the data read from the file
    while (fscanf(file, "%s %s %s %s", currentPerson.name, currentPerson.surname, currentPerson.email, currentPerson.password) != EOF) {
        if (strcmp(currentPerson.name, name) == 0 && strcmp(currentPerson.surname, surname) == 0 && strcmp(currentPerson.email, email) == 0) {
            found = 1;
            if (strcmp(currentPerson.password, password) == 0) {
                printf("Logged in as %s %s\n", name, surname);
                printf("Now that you are conected choose an action:\n 1 search books,\n 2 borrow books,\n 3 return books,\n 4 donate books, \n 5 view loans, \n 0 to log out\n");
                int i;
                scanf("%d", &i);
                while (i != 0) {
                    if (i == 2)
                        borrow_books(currentPerson);
                    if (i == 1)
                        search_books();
                    if (i == 3)
                        return_books(currentPerson);
                    if (i == 4)
                        donate_books();
                    if (i == 5)
                        view_loans(currentPerson);

                    printf("\nPlease choose an action:\n 1 search books,\n 2 borrow books,\n 3 return books,\n 4 donate books, \n 5 view loans, 0 to log out\n ");

                    scanf("%d", &i);
                }
            }
            else {
                printf("Incorrect password.\n");
            }
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("User not found.\n");
    }
}


void register_account() {
    printf("Enter your name: ");
    char name[50];
    scanf("%s", name);
    printf("Enter your surname: ");
    char surname[50];
    scanf("%s", surname);
    printf("Enter your email: ");
    char email[100];
    scanf("%s", email);
    printf("Enter a password: ");
    char password[20];
    scanf("%s", password);


    FILE* file = fopen("users.txt", "a"); // Open or create the file in append mode
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s %s %s %s\n", name, surname, email, password); // Write user data to the file

    fclose(file); // Close the file when done

    printf("Account registered successfully.\n");
}


void delete_account() {
    printf("Enter your name: ");
    char name[50];
    scanf("%s", name);
    printf("Enter your surname: ");
    char surname[50];
    scanf("%s", surname);
    printf("Enter your email: ");
    char email[100];
    scanf("%s", email);
    printf("Enter your password: ");
    char password[50];
    scanf("%s", password);

    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE* temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error creating temp file.\n");
        fclose(file);
        return;
    }

    Person currentPerson;
    int found = 0;
    while (fscanf(file, "%s %s %s %s", currentPerson.name, currentPerson.surname, currentPerson.email, currentPerson.password) != EOF) {
        if (strcmp(currentPerson.name, name) == 0 && strcmp(currentPerson.surname, surname) == 0 && strcmp(currentPerson.email, email) == 0 && strcmp(currentPerson.password, password) == 0) {
            found = 1;
        }
        else {
            fprintf(temp, "%s %s %s %s\n", currentPerson.name, currentPerson.surname, currentPerson.email, currentPerson.password);
        }
    }

    fclose(file);
    fclose(temp);

    if (!found) {
        printf("User not found or incorrect password.\n");
        remove("temp.txt"); // Remove the temporary file
        return;
    }

    remove("users.txt");
    rename("temp.txt", "users.txt");
    printf("Account deleted successfully.\n");
}
void borrow_books(Person person) {
    FILE* booksFile = fopen("books.txt", "r");
    if (booksFile == NULL) {
        printf("Error opening books file.\n");
        return;
    }

    // Print all available books
    printf("Available books:\n");
    char title[100], author[100];
    int copies_available;
    while (fscanf(booksFile, "%[^|]|%[^|]|%d\n", title, author, &copies_available) != EOF) {
        printf("Title: %s | Author: %s | Copies available: %d\n", title, author, copies_available);
    }
    fclose(booksFile); // Close the file after reading

    // Prompt the user to enter the title of the book they want to borrow
    char title1[100];
    printf("Enter the title of the book you want to borrow: ");
    scanf("%s", title1);

    // Open the books file again for writing to update copies_available
    booksFile = fopen("books.txt", "r");
    if (booksFile == NULL) {
        printf("Error opening books file.\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w"); // Temporary file for rewriting
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(booksFile);
        return;
    }

    // Iterate through each book in the file
    int found = 0;
    while (fscanf(booksFile, "%[^|]|%[^|]|%d\n", title, author, &copies_available) != EOF) {
        if (strcmp(title, title1) == 0) {
            found = 1;
            if (copies_available <= 0) {
                printf("Sorry, the book is not available for borrowing.\n");
                fclose(booksFile);
                fclose(tempFile);
                remove("temp.txt"); // Remove temporary file
                return;
            }
            else {
                copies_available--; // Decrease the number of copies available
            }
        }
        fprintf(tempFile, "%s|%s|%d\n", title, author, copies_available); // Write to temporary file
    }

    fclose(booksFile);
    fclose(tempFile);

    if (!found) {
        printf("Book not found.\n");
        remove("temp.txt"); // Remove temporary file
        return;
    }

    // Replace original file with the temporary file
    remove("books.txt");
    rename("temp.txt", "books.txt");

    // Write loan information to "loans.txt" file
    FILE* loansFile = fopen("loans.txt", "a");
    if (loansFile == NULL) {
        printf("Error opening loans file.\n");
        return;
    }
    fprintf(loansFile, "%s|%s|%s|%s\n", person.name, person.surname, title1, author);
    fclose(loansFile);

    printf("Book '%s' borrowed successfully.\n", title1);
}



void return_books(Person person) {
    FILE* loansFile = fopen("loans.txt", "r");
    if (loansFile == NULL) {
        printf("Error opening loans file.\n");
        return;
    }

    // Prompt user to enter the title of the book to be returned
    printf("Enter the title of the book you are returning: ");
    char returnTitle[100];
    scanf("%99s", returnTitle); // Limiting input size to prevent buffer overflow

    // Temporary file to store updated loan information
    FILE* tempFile = fopen("temp_loans.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(loansFile);
        return;
    }

    // Read each loan from loans.txt, check if it matches the book to be returned
    char name[50], surname[50], title[100], author[100];
    int bookReturned = 0; // Flag to track if the book was found and returned
    while (fscanf(loansFile, "%49[^|]|%49[^|]|%99[^|]|%99[^|\n]\n", name, surname, title, author) != EOF) {
        if (strcmp(title, returnTitle) == 0 &&
            strcmp(name, person.name) == 0 &&
            strcmp(surname, person.surname) == 0) {
            bookReturned = 1; // Set flag to indicate book was found and returned
            printf("Book '%s' by %s returned successfully.\n", returnTitle, author);
        }
        else {
            // If the loan doesn't match the book to be returned or belongs to another user,
            // write it back to the temporary file
            fprintf(tempFile, "%s|%s|%s|%s\n", name, surname, title, author);
        }
    }

    fclose(loansFile);
    fclose(tempFile);

    if (bookReturned == 0) {
        printf("You have not borrowed '%s'.\n", returnTitle);
        remove("temp_loans.txt"); // Remove temporary file
        return;
    }

    remove("loans.txt"); // Remove original loans file
    rename("temp_loans.txt", "loans.txt"); // Rename temporary file to loans.txt

    // Now you can append the returned book with the decreased number of copies to the end of the file
    FILE* booksFile = fopen("books.txt", "r+");
    if (booksFile == NULL) {
        printf("Error opening books file.\n");
        return;
    }

    int copies_available;
    int p = 0;

    // Find the book in the books file and update the number of copies
    while ((fscanf(booksFile, "%99[^|]|%99[^|]|%d\n", title, author, &copies_available) != EOF) && p == 0) {
        if (strcmp(title, returnTitle) == 0) {
            // Decrease the number of copies available
            copies_available--;
            p = 1;
            // Write the updated book information back to the file
            fseek(booksFile, (long)(-(long)strlen(title) - (long)strlen(author) - 3), SEEK_CUR); // Move back to the beginning of the line
            fprintf(booksFile, "%s|%s|%d\n", title, author, copies_available); // Update the line with new copies_available
            fclose(booksFile);
            return; // Return after updating the book information
        }

    }

    // If the book was not found in the file
    printf("Book '%s' not found in the library.\n", returnTitle);
    fclose(booksFile);
}




void donate_books() {
    FILE* booksFile = fopen("books.txt", "a");
    if (booksFile == NULL) {
        printf("Error opening books file.\n");
        return;
    }

    printf("Enter the title of the book you are donating: ");
    char donateTitle[100];
    scanf("%s", donateTitle);

    // Append the donated book information to the books.txt file
    char author[100];
    int copiesAvailable;
    printf("Enter the author of the book: ");
    scanf("%s", author);
    printf("Enter the number of copies available: ");
    scanf("%d", &copiesAvailable);

    // Write the donated book information to the file
    fprintf(booksFile, "%s|%s|%d\n", donateTitle, author, copiesAvailable);

    printf("Book '%s' by %s donated successfully.\n", donateTitle, author);

    // Close the file
    fclose(booksFile);
}

void view_loans(Person person) {
    // Open the loans file for reading
    FILE* loansFile = fopen("loans.txt", "r");
    if (loansFile == NULL) {
        printf("Error opening loans file.\n");
    }
    printf("Loans for %s %s:\n", person.name, person.surname);
    Loan loan;
    while (fscanf(loansFile, "%99[^|]|%99[^|]|%99[^|]|%99[^|\n]\n", loan.name, loan.surname, loan.title, loan.author) != EOF) {
        if (strcmp(loan.name, person.name) == 0 && strcmp(loan.surname, person.surname) == 0) {
            printf("Title: %s | Author: %s\n", loan.title, loan.author);
        }
    }

    // Close the file
    fclose(loansFile);
}

void search_books() {
    // Open the books file for reading
    FILE* booksFile = fopen("books.txt", "r");
    if (booksFile == NULL) {
        printf("Error opening books file.\n");
        return;
    }

    // Prompt the user to input a book title
    char titleToSearch[100];
    printf("Enter the title of the book you want to search for: ");
    scanf("%s", titleToSearch);

    // Read book information from the file and search for the specified title
    char title[100], author[100];
    int copies_available;
    int found = 0; // Flag to indicate if the book is found

    while (fscanf(booksFile, "%[^|]|%[^|]|%d\n", title, author, &copies_available) != EOF) {
        if (strcmp(title, titleToSearch) == 0) {
            found = 1;
            if (copies_available > 0) {
                printf("Book '%s' by %s is available.\n", title, author);
            }
            else {
                printf("Book '%s' by %s is not available.\n", title, author);
            }
            break; // Exit the loop after finding the book
        }
    }

    // If the book is not found
    if (!found) {
        printf("Book '%s' not found.\n", titleToSearch);
    }

    // Close the file
    fclose(booksFile);
}