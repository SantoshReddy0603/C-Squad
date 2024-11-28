#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "employee.h"
#include "common.h"

void adminMenu();
void employeeMenu();

// Main function
int main() {
    int choice;
    char username[50], password[50];

    while (1) {
        printf("\n================================");
        printf("\n|| Employee Management System ||");
        printf("\n================================");
        printf("1. Admin Login\n");
        printf("2. Employee Login\n");
        printf("3. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n\nEnter Admin Username: ");
                scanf("%s", username);
                printf("Enter Admin Password: ");
                scanf("%s", password);

                // Hardcoded admin credentials
                if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
                    adminMenu();
                } else {
                    printf("\nInvalid Admin Credentials.\n");
                }
                break;

            case 2:
                printf("\nEnter Employee Username: ");
                scanf("%s", username);
                printf("Enter Employee Password: ");
                scanf("%s", password);

                
                if (employeeLogin(username, password)) {
                    employeeMenu(username);
                } else {
                    printf("\nInvalid Employee Credentials.\n");
                }
                break;

            case 3:
                printf("\nExiting the system. Goodbye!\n");
                exit(0);

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
    return 0;
}
