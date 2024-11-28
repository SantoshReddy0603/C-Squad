#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// In admin.h (correct)
#include "common.h"

// Declare other admin-specific functions here, without defining Employee again.


// Structure for Project
typedef struct Project {
    int id;                    // Project ID
    char name[100];            // Project name
    char department[50];       // Department name
    char status[20];           // Status (e.g., "Active", "Completed")
    char startDate[20];        // Start date
    char endDate[20];          // End date
    struct Project* next;      // Pointer to the next project (linked list)
} Project;
// Function Prototypes
void adminMenu();
void displayEmployeeDetails();
void averageSalaryByDepartment();
void employeesPerDepartment();
void currentProjects();
void highestPaidEmployee();
void addEmployee();
void removeEmployee();
void updateEmployee();
void manageAnnouncements();
void leaveManagement();
void loadProjectsFromFile(Project** head);
void saveProjectsToFile(Project* head);

#endif
