#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"
#include "common.h"

// Function prototypes
int employeeLogin(char* username, char* password);
void viewPersonalDetails(char* username);
void updatePassword(char* username);
void requestSalaryIncrement(char* username);
void viewLeaveBalance(char* username);
void viewAnnouncements();
void accessHandbook();

// Employee menu
void employeeMenu(char* username) {
    int choice;

    while (1) {
        printf("\n==== Employee Menu ====\n");
        printf("1. View Personal Details\n");
        printf("2. Update Login Password\n");
        printf("3. Request Salary Increment\n");
        printf("4. View Leave Balance\n");
        printf("5. View Announcements\n");
        printf("6. Access Employee Handbook\n");
        printf("7. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewPersonalDetails(username); break;
            case 2: updatePassword(username); break;
            case 3: requestSalaryIncrement(username); break;
            case 4: viewLeaveBalance(username); break;
            case 5: viewAnnouncements(); break;
            case 6: accessHandbook(); break;
            case 7: return; // Logout
            default: printf("\nInvalid choice. Please try again.\n");
        }
    }
}

// Functions for employee operations will be implemented here

#include <stdio.h>
#include <string.h>
#include "common.h"

void viewPersonalDetails(char* username) {
    FILE* file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL) {
        printf("\n========================================\n");
        printf("          Employee Details               \n");
        printf("========================================\n");
        printf("Error: Could not open employee file.\n");
        printf("========================================\n");
        return;
    }

    Employee emp;
    int found = 0;

    // Read each employee record from the file
    while (fscanf(file, "%d %s %s %d %f %d %s",
                  &emp.id, emp.name, emp.gender, &emp.age, &emp.salary, &emp.experience, emp.department) != EOF) {
        // Check if the username matches the employee's name
        if (strcmp(emp.name, username) == 0) {
            printf("\n========================================\n");
            printf("        Personal Details for %s          \n", emp.name);
            printf("========================================\n");
            printf("%-15s: %d\n", "ID", emp.id);
            printf("%-15s: %s\n", "Gender", emp.gender);
            printf("%-15s: %d\n", "Age", emp.age);
            printf("%-15s: %.2f\n", "Salary", emp.salary);
            printf("%-15s: %d years\n", "Experience", emp.experience);
            printf("%-15s: %s\n", "Department", emp.department);
            printf("========================================\n");
            found = 1;
            break;  // Exit the loop once the employee is found
        }
    }

    if (!found) {
        printf("\n========================================\n");
        printf("          Employee Details               \n");
        printf("========================================\n");
        printf("Error: Employee with username '%s' not found.\n", username);
        printf("========================================\n");
    }

    fclose(file);
}

void displayUpdatePasswordHeader() {
    printf("=============================================================\n");
    printf("=                   Update Password                        =\n");
    printf("=============================================================\n");
}

// Function to update password
void updatePassword(char* username) {
    displayUpdatePasswordHeader();

    char oldPassword[MAX_STR_LEN], newPassword[MAX_STR_LEN];
    int found = 0;

    // Prompt for old password
    printf("Enter your old password: ");
    scanf("%s", oldPassword);

    // Open the employee file to read existing credentials
    FILE* file = fopen("employee.txt", "r+");
    if (file == NULL) {
        printf("Error: Could not open employee.txt\n");
        return;
    }

    // Create a temporary file to store updated credentials
    FILE* tempFile = fopen("temp_employee.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(file);
        return;
    }

    char fileUsername[MAX_STR_LEN], filePassword[MAX_STR_LEN];

    // Read each line from the file, check credentials, and write to the temp file
    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(fileUsername, username) == 0 && strcmp(filePassword, oldPassword) == 0) {
            // If username and old password match, update the password
            printf("\nUsername and old password verified successfully!\n");
            printf("Enter your new password: ");
            scanf("%s", newPassword);
            fprintf(tempFile, "%s %s\n", fileUsername, newPassword);  // Update with new password
            found = 1;
        } else {
            // Otherwise, keep the old record
            fprintf(tempFile, "%s %s\n", fileUsername, filePassword);
        }
    }

    // Check if the username and password were found
    if (!found) {
        printf("\nError: Username or password is incorrect.\n");
    } else {
        printf("\nPassword updated successfully!\n");
    }

    // Close the original and temporary file
    fclose(file);
    fclose(tempFile);

    // Replace the old file with the new one
    remove("employee.txt");
    rename("temp_employee.txt", "employee.txt");

    printf("=============================================================\n");
}
//    FILE* file = fopen(EMPLOYEE_FILE, "r+");
//    if (file == NULL) {
//        printf("Could not open employee file.\n");
//        return;
//    }

//    Employee emp;
//    int found = 0;
//    long pos;

    // Search for the employee with the matching username
//    while (fscanf(file, "%d %s %s %d %f %d %s", &emp.id, emp.name, emp.gender, &emp.age, &emp.salary, &emp.experience, emp.department) != EOF) {
//        pos = ftell(file) - sizeof(Employee);
//        if (strcmp(emp.name, username) == 0) {
//            found = 1;
//            printf("Enter salary increment amount: ");
//            float increment;
//            scanf("%f", &increment);
//            emp.salary += increment;  // Apply the increment
            
//            // Update the employee's salary in the file
//            fseek(file, pos + sizeof(Employee) - sizeof(emp.salary), SEEK_SET);
//            fprintf(file, "%.2f\n", emp.salary);
//            break;
//        }
//    }

//    if (!found) {
//        printf("Employee with username '%s' not found.\n", username);
//    }
//
//    fclose(file);
//}

void requestSalaryIncrement(char* username) {
    FILE* empFile = fopen(EMPLOYEE_FILE, "r");
    if (empFile == NULL) {
        printf("\n========================================\n");
        printf("        Salary Increment Request         \n");
        printf("========================================\n");
        printf("Error: Could not open employee file.\n");
        printf("========================================\n");
        return;
    }

    FILE* incFile = fopen("SALARY_INCREMENT_FILE.txt", "a");
    if (incFile == NULL) {
        printf("\n========================================\n");
        printf("        Salary Increment Request         \n");
        printf("========================================\n");
        printf("Error: Could not open increment request file.\n");
        printf("========================================\n");
        fclose(empFile);
        return;
    }

    Employee emp;
    int found = 0;

    printf("\n========================================\n");
    printf("        Salary Increment Request         \n");
    printf("========================================\n");

    // Search for the employee with the matching username
    while (fscanf(empFile, "%d %s %s %d %f %d %s", &emp.id, emp.name, emp.gender, &emp.age, &emp.salary, &emp.experience, emp.department) != EOF) {
        if (strcmp(emp.name, username) == 0) {
            found = 1;
            printf("Enter salary increment amount for %s: ", emp.name);
            float increment;
            scanf("%f", &increment);

            // Log the increment request in the increment file
            fprintf(incFile, "%d %s %.2f\n", emp.id, emp.name, increment);
            printf("\n========================================\n");
            printf("Request logged successfully!\n");
            printf("ID: %d\n", emp.id);
            printf("Name: %s\n", emp.name);
            printf("Proposed Increment: %.2f\n", increment);
            printf("========================================\n");
            break;
        }
    }

    if (!found) {
        printf("\n========================================\n");
        printf("Error: Employee with username '%s' not found.\n", username);
        printf("========================================\n");
    }

    fclose(empFile);
    fclose(incFile);
}

#include <stdio.h>
#include <string.h>

void viewLeaveBalance(char* username) {
    FILE* file = fopen("leave_balances.txt", "r");
    if (file == NULL) {
        printf("\n========================================\n");
        printf("           Leave Balance Viewer          \n");
        printf("========================================\n");
        printf("Error: Could not open leave balances file.\n");
        printf("========================================\n");
        return;
    }

    char name[MAX_STR_LEN];
    int leaveBalance;
    int found = 0;

    printf("\n========================================\n");
    printf("           Leave Balance Viewer          \n");
    printf("========================================\n");

    // Read each line to find the matching employee's leave balance
    while (fscanf(file, "%s %d", name, &leaveBalance) != EOF) {
        if (strcmp(name, username) == 0) {
            printf("%-15s: %s\n", "Employee", name);
            printf("%-15s: %d days\n", "Leave Balance", leaveBalance);
            printf("========================================\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Error: Employee with username '%s' not found.\n", username);
        printf("========================================\n");
    }

    fclose(file);
}


void accessHandbook() {
    FILE* file = fopen("handbook.txt", "r");
    if (file == NULL) {
        printf("\n========================================\n");
        printf("           Employee Handbook             \n");
        printf("========================================\n");
        printf("Error: Could not open handbook file.\n");
        printf("========================================\n");
        return;
    }

    char line[256];
    printf("\n========================================\n");
    printf("           Employee Handbook             \n");
    printf("========================================\n");

    // Read and display the contents of the handbook file
    printf("Welcome to the Employee Handbook!\n");
    printf("Here are the guidelines and policies:\n");
    printf("----------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    printf("\n========================================\n");
    printf("End of Employee Handbook.\n");
    printf("========================================\n");

    fclose(file);
}


void viewAnnouncements() {
    FILE* file = fopen("announcements.txt", "r");
    if (file == NULL) {
        printf("\n========================================\n");
        printf("          Latest Announcements           \n");
        printf("========================================\n");
        printf("Error: Could not open announcements file.\n");
        printf("========================================\n");
        return;
    }

    char line[256];
    printf("\n========================================\n");
    printf("          Latest Announcements           \n");
    printf("========================================\n");

    // Display the announcements
    printf("Here are the latest company announcements:\n");
    printf("----------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    printf("\n========================================\n");
    printf("End of Announcements.\n");
    printf("========================================\n");

    fclose(file);
}


// Employee login function
int employeeLogin(char* username, char* password) {
    FILE *file = fopen("employee.txt", "r");  // Open the employee.txt file
    char stored_username[50], stored_password[50];

    if (file == NULL) {
        printf("\n========================================\n");
        printf("           Employee Login               \n");
        printf("========================================\n");
        printf("Error: Could not open employee.txt file.\n");
        printf("========================================\n");
        return 0;  // Login failed
    }

    printf("\n========================================\n");
    printf("           Employee Login               \n");
    printf("========================================\n");

    // Read the file to check for matching credentials
    while (fscanf(file, "%s %s", stored_username, stored_password) != EOF) {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            printf("========================================\n");
            printf("Login Successful!\n");
            printf("Welcome, %s!\n", username);  // Personalized greeting
            printf("========================================\n");
            fclose(file);
            return 1;  // Login successful
        }
    }

    printf("========================================\n");
    printf("Invalid username or password for employee.\n");
    printf("========================================\n");
    fclose(file);
    return 0;  // Login failed
}

