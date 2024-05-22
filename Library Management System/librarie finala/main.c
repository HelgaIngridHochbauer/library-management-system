#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int main() {
    int c = 8;
    char name[50], surname[50], password[20], email[100];
    while (c != 0)
    {
        // Prompt user to choose between creating an account or registering
        printf("%s", "Please choose:\n 1.Create an account \n 2.Log into account\n 3.Delete account\n 0.Stop the process \n");

        // Validate user input

        scanf("%d", &c);
        if (c != 1 && c != 2 && c != 3 && c != 0)
        {
            printf("Invalid choice. Please enter 1,2,3 or 0; \n");
            scanf("%d", &c);
        }
        if (c == 0)
            break;

        if (c == 1) {
            register_account();
            printf("Now please log in to perform further actions");
        }
        else {
            if (c == 2) {
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter surname: ");
                scanf("%s", surname);
                printf("Enter email: ");
                scanf("%s", email);
                printf("Enter password: ");
                scanf("%s", password);

                login(name, surname, password, email);
            }
            else { delete_account(); }
        }
    }

    
    return 0;
}