#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "common.h"



void displayEmployeeDetails();

// Admin login function
int adminLogin(char* username, char* password) {
    FILE *file = fopen("admin.txt", "r");  
    char stored_username[50], stored_password[50];

    if (file == NULL) {
        printf("Error opening admin.txt\n");
        return 0;
    }

  
    while (fscanf(file, "%s %s", stored_username, stored_password) != EOF) {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            printf("Admin login successful!\n");
            fclose(file);
            return 1;  // Login successful
        }
    }

    printf("Invalid username or password for admin.\n");
    fclose(file);
    return 0;  // Login failed
}
void averageSalaryByDepartment();
void employeesPerDepartment();
void currentProjects();
void highestPaidEmployee();
void addEmployee();
void removeEmployee();
void updateEmployee();
void manageAnnouncements();
void loadProjectsFromFile(Project** head);
void saveProjectsToFile(Project* head);
void updateProjectStatus();
void updateProjects();
void addProject(Project** head);
void removeProject(Project** head);
void viewSalaryIncrementRequests();
// Admin menu
void adminMenu() {
    int choice;

    while (1) {
        printf("\n==== Admin Menu ====\n");
        printf("1. Display Employee Details\n");
        printf("2. Average Salary by Department\n");
        printf("3. Number of Employees per Department\n");
        printf("4. Current Projects\n");
        printf("5. Manage Projects\n");
        printf("6. Highest Paid Employee by Department\n");
        printf("7. Announcements\n");
        printf("8. Add Employee\n");
        printf("9. Remove Employee\n");
        printf("10. Update Employee\n");
        printf("11. View salary Increment Requests\n");
        printf("12. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayEmployeeDetails(); break;
            case 2: averageSalaryByDepartment(); break;
            case 3: employeesPerDepartment(); break;
            case 4: currentProjects(); break;
            case 5: updateProjectStatus(); break;
            case 6: highestPaidEmployee(); break;
            case 7: manageAnnouncements(); break;
            case 8: addEmployee(); break;
            case 9: removeEmployee(); break;
            case 10: updateEmployee(); break;
            case 11: viewSalaryIncrementRequests(); break;
            case 12: return; // Logout
            default: printf("\nInvalid choice. Please try again.\n");
        }
    }
}

#define EMPLOYEE_FILE "employees.txt"

void displayEmployeeDetails() {
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (!file) {
        printf("Error: Could not open employees.txt\n");
        return;
    }

    printf("\n=== Employee Details ===\n");
    printf("ID     |Name           |Gender|Age|Salary        |Experience|Department|\n");
    printf("------------------------------------------------------------------------\n");

    int id, age, experience;
    float salary;
    char name[50], gender[10], department[50];

    // Read each line and parse the data
    while (fscanf(file, "%d %49s %9s %d %f %d %49s",
                  &id, name, gender, &age, &salary, &experience, department) == 7) {
        // Use consistent column widths for alignment
        printf("%-7d|%-15s|%-6s|%-3d|%-14.2f|%-10d|%-10s|\n",
               id, name, gender, age, salary, experience, department);
    }

    fclose(file);
}
void averageSalaryByDepartment() {
    FILE *file = fopen("employees.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open employee_details.txt\n");
        return;
    }

    char department[50][50]; 
    int deptCount[50] = {0}; 
    float deptSalary[50] = {0.0}; 
    int uniqueDepartments = 0;

    char id[10], name[50], gender[10], departmentTemp[50];
    int age, experience;
    float salary;


    while (fscanf(file, "%s %s %s %d %f %d %s", id, name, gender, &age, &salary, &experience, departmentTemp) != EOF) {
        int found = -1;

        for (int i = 0; i < uniqueDepartments; i++) {
            if (strcmp(department[i], departmentTemp) == 0) {
                found = i;
                break;
            }
        }

        if (found != -1) {
            deptSalary[found] += salary;
            deptCount[found]++;
        } else {
            strcpy(department[uniqueDepartments], departmentTemp);
            deptSalary[uniqueDepartments] = salary;
            deptCount[uniqueDepartments] = 1;
            uniqueDepartments++;
        }
    }

    fclose(file);

    printf("\nAverage Salary by Department:\n");
    printf("---------------------------------\n");
    printf("Department\t|Average Salary|\n");
    printf("-------------------------------\n");
    for (int i = 0; i < uniqueDepartments; i++) {
        printf("%s\t\t|%.2f\n", department[i], deptSalary[i] / deptCount[i]);
    }
}
void currentProjects() {

    FILE* file = fopen("projects.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open projects.txt\n");
        return;
    }

    Project* head = NULL;  
    int id;
    char name[MAX_STR_LEN], department[MAX_STR_LEN], status[MAX_STR_LEN], startDate[MAX_STR_LEN], endDate[MAX_STR_LEN];

   
    while (fscanf(file, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%99[^\n]", 
            &id, name, department, status, startDate, endDate) != EOF) {
       
        Project* newProject = (Project*)malloc(sizeof(Project));
        if (newProject == NULL) {
            printf("Error: Memory allocation failed.\n");
            fclose(file);
            return;
        }

        newProject->id = id;
        strcpy(newProject->name, name);
        strcpy(newProject->department, department);
        strcpy(newProject->status, status);
        strcpy(newProject->startDate, startDate);
        strcpy(newProject->endDate, endDate);
        newProject->next = head;  
        head = newProject;
    }

    fclose(file);

    if (head == NULL) {
        printf("No current projects to display.\n");
    } else {
       
        printf("=========================================================================================================\n");
        printf("=                                    Current Projects List                                          =\n");
        printf("=========================================================================================================\n");
        printf("| %-4s | %-22s | %-20s | %-12s | %-12s | %-12s |\n", 
                "ID", "Project Name", "Department", "Status", "Start Date", "End Date");
        printf("----------------------------------------------------------------------------------------------------------\n");

      
        Project* temp = head;
        while (temp != NULL) {
            printf("| %-4d | %-22s | %-20s | %-12s | %-12s | %-12s |\n", 
                    temp->id, temp->name, temp->department, temp->status, temp->startDate, temp->endDate);
            printf("-------------------------------------------------------------------------------------------------------\n");
            temp = temp->next;
        }
    }

    Project* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
void updateProjects(){
        Project* head = NULL;

        //loadProjectsFromFile(&head);
        loadProjectsFromFile(&head);
        int choice;

        while(1){
                printf("\n=== Update Projects ===\n");
                printf("1. Add project\n");
                printf("2. Remove project\n");
                printf("3. Update status of existing project\n");
                printf("4. Logout\n");
                scanf("%d",&choice);

                switch(choice){
                        case 1: addProject(&head); break;
                        case 2: removeProject(&head); break;
                        case 3: updateProjectStatus(head); break;
                        case 4: return;
                        default: printf("\nInvalid choice. Please try again.\n");
                }
        }
}

void displayProjects(Project* head) {
    if (head == NULL) {
        printf("No current projects to display.\n");
        return;
    }

    printf("===============================================================================================================\n");
    printf("=                                       Current Projects List                                      =\n");
    printf("===============================================================================================================\n");
    printf("| %-4s | %-22s | %-20s | %-12s | %-12s | %-12s |\n", 
            "ID", "Project Name", "Department", "Status", "Start Date", "End Date");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    Project* temp = head;
    while (temp != NULL) {
        printf("| %-4d | %-22s | %-20s | %-12s | %-12s | %-12s |\n", 
                temp->id, temp->name, temp->department, temp->status, temp->startDate, temp->endDate);
        printf("------------------------------------------------------------------------------------------------------------\n");
        temp = temp->next;
    }
}
void loadProjectsFromFile(Project** head) {
    FILE* file = fopen("projects.txt", "r"); // Open in read mode
    if (file == NULL) {
        printf("Error: Could not open projects.txt\n");
        return;
    }

    int id;
    char name[MAX_STR_LEN], department[MAX_STR_LEN], status[MAX_STR_LEN];
    char startDate[MAX_STR_LEN], endDate[MAX_STR_LEN];

    while (fscanf(file, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%99[^\n]\n",
                  &id, name, department, status, startDate, endDate) != EOF) {
        // Allocate memory for the project
        Project* newProject = (Project*)malloc(sizeof(Project));
        if (newProject == NULL) {
            printf("Error: Memory allocation failed.\n");
            fclose(file);
            return;
        }

        // Assign values
        newProject->id = id;
        strcpy(newProject->name, name);
        strcpy(newProject->department, department);
        strcpy(newProject->status, status);
        strcpy(newProject->startDate, startDate);
        strcpy(newProject->endDate, endDate);
        newProject->next = *head;

        *head = newProject;
    }

    fclose(file);
    printf("Projects loaded successfully.\n");
}
void addProject(Project** head) {
    FILE* file = fopen("projects.txt", "a"); // Open in append mode
    if (file == NULL) {
        printf("Error: Could not open projects.txt\n");
        return;
    }

    // Allocate memory for the new project
    Project* newProject = (Project*)malloc(sizeof(Project));
    if (newProject == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return;
    }

    // Get project details from the user
    printf("Enter project ID: ");
    scanf("%d", &newProject->id);
    printf("Enter project name: ");
    scanf(" %[^\n]", newProject->name);
    printf("Enter department: ");
    scanf(" %[^\n]", newProject->department);
    printf("Enter status: ");
    scanf(" %[^\n]", newProject->status);
    printf("Enter start date (yyyy-mm-dd): ");
    scanf(" %[^\n]", newProject->startDate);
    printf("Enter end date (yyyy-mm-dd): ");
    scanf(" %[^\n]", newProject->endDate);
    newProject->next = NULL;

    // Add the project to the linked list
    newProject->next = *head;
    *head = newProject;

    // Write the new project to the file
    fprintf(file, "%d,%s,%s,%s,%s,%s\n",
            newProject->id,
            newProject->name,
            newProject->department,
            newProject->status,
            newProject->startDate,
            newProject->endDate);

    fclose(file);
    printf("Project added successfully.\n");
}
void removeProject(Project** head) {
    int id;
    printf("Enter the project ID to remove: ");
    scanf("%d", &id);

    Project *current = *head, *prev = NULL;

    // Search for the project
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Project with ID %d not found.\n", id);
        return;
    }

    // Remove the project from the linked list
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);

    // Rewrite the file with the updated list
    FILE* file = fopen("projects.txt", "w"); // Overwrite mode
    if (file == NULL) {
        printf("Error: Could not open projects.txt\n");
        return;
    }

    Project* temp = *head;
    while (temp != NULL) {
        fprintf(file, "%d,%s,%s,%s,%s,%s\n",
                temp->id,
                temp->name,
                temp->department,
                temp->status,
                temp->startDate,
                temp->endDate);
        temp = temp->next;
    }

    fclose(file);
    printf("Project removed successfully.\n");
}


void updateProjectStatus() {
    FILE* file = fopen("projects.txt", "r+");
    if (file == NULL) {
        printf("Error: Could not open projects.txt\n");
        return;
    }

    Project* head = NULL;
    int id;
    char name[MAX_STR_LEN], department[MAX_STR_LEN], status[MAX_STR_LEN], startDate[MAX_STR_LEN], endDate[MAX_STR_LEN];

    while (fscanf(file, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%99[^\n]", 
            &id, name, department, status, startDate, endDate) != EOF) {

        Project* newProject = (Project*)malloc(sizeof(Project));
        if (newProject == NULL) {
            printf("Error: Memory allocation failed.\n");
            fclose(file);
            return;
        }

        newProject->id = id;
        strcpy(newProject->name, name);
        strcpy(newProject->department, department);
        strcpy(newProject->status, status);
        strcpy(newProject->startDate, startDate);
        strcpy(newProject->endDate, endDate);
        newProject->next = head;  
        head = newProject;
    }

    fclose(file);

    displayProjects(head);

    printf("\nEnter the project ID to update its status: ");
    int projectId;
    scanf("%d", &projectId);

    printf("\nEnter the new status (e.g., Completed, Pending): ");
    char newStatus[MAX_STR_LEN];
    scanf("%s", newStatus);

    Project* temp = head;
    int projectFound = 0;

    while (temp != NULL) {
        if (temp->id == projectId) {
            strcpy(temp->status, newStatus);  
            projectFound = 1;
            break;
        }
        temp = temp->next;
    }

    if (!projectFound) {
        printf("\nError: Project with ID %d not found.\n", projectId);
    } else {
     
        file = fopen("projects.txt", "w");
        if (file == NULL) {
            printf("Error: Could not open projects.txt for writing.\n");
            return;
        }

        temp = head;
        while (temp != NULL) {
            fprintf(file, "%d,%s,%s,%s,%s,%s\n", 
                    temp->id, temp->name, temp->department, temp->status, temp->startDate, temp->endDate);
            temp = temp->next;
        }

        fclose(file);
        printf("\n=====================================================================\n");
        printf("=                 Project Status Updated Successfully       =\n");
        printf("========================================================================\n");
        printf("\nThe status of Project ID %d has been updated to '%s'.\n", projectId, newStatus);
    }

    Project* tempFree;
    while (head != NULL) {
        tempFree = head;
        head = head->next;
        free(tempFree);
    }
}
void employeesPerDepartment() {
    FILE* file = fopen("employees.txt", "r");
    if (file == NULL) {
        printf("\n========================================\n");
        printf("Error: Could not open employees.txt.\n");
        printf("========================================\n");
        return;
    }

    char departments[10][50];
    int departmentCount[10] = {0};
    int numDepartments = 0;

    Employee emp;
    while (fscanf(file, "%d %s %s %d %f %d %s",
                  &emp.id, emp.name, emp.gender, &emp.age, &emp.salary, &emp.experience, emp.department) != EOF) {
        int found = 0;
   
        for (int i = 0; i < numDepartments; i++) {
            if (strcmp(departments[i], emp.department) == 0) {
                departmentCount[i]++;
                found = 1;
                break;
            }
        }
     
        if (!found) {
            strcpy(departments[numDepartments], emp.department);
            departmentCount[numDepartments]++;
            numDepartments++;
        }
    }

    fclose(file);

  
    printf("\n========================================\n");
    printf("          Employees per Department       \n");
    printf("========================================\n");

    printf("%-20s%-10s\n", "Department", "Employees");
    printf("----------------------------------------\n");

    for (int i = 0; i < numDepartments; i++) {
        printf("%-20s%-10d\n", departments[i], departmentCount[i]);
    }

    printf("========================================\n");
}

void highestPaidEmployee() {
    FILE* file = fopen("employees.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open employees.txt.\n");
        return;
    }

    Employee highest[100];
    char departments[100][50];
    int depCount = 0;

    Employee emp;
    while (fscanf(file, "%d %s %s %d %f %d %s", &emp.id, emp.name, emp.gender, &emp.age, &emp.salary, &emp.experience, emp.department) != EOF) {
        int found = -1;
        for (int i = 0; i < depCount; i++) {
            if (strcmp(departments[i], emp.department) == 0) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            strcpy(departments[depCount], emp.department);
            highest[depCount] = emp;
            depCount++;
        } else if (emp.salary > highest[found].salary) {
            highest[found] = emp;
        }
    }

    fclose(file);

    printf("Highest Paid Employee Per Department:\n");
    printf("---------------------------------------------------------\n");
    printf("| %-20s | %-20s | %-10s |\n", "Department", "Name", "Salary");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < depCount; i++) {
        printf("| %-20s | %-20s | %-10.2f |\n", departments[i], highest[i].name, highest[i].salary);
    }
    printf("---------------------------------------------------------\n");
}

void manageAnnouncements() {
    int choice;
    FILE* file;
    char announcement[256];

    // Menu display
    printf("\n========================================\n");
    printf("          Announcements Management       \n");
    printf("========================================\n");
    printf("1. View Announcements\n");
    printf("2. Add Announcement\n");
    printf("========================================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();  

    // View Announcements
    if (choice == 1) {
        file = fopen("announcements.txt", "r");
        if (file == NULL) {
            printf("\n========================================\n");
            printf("Error: Could not open announcements.txt.\n");
            printf("========================================\n");
            return;
        }

        printf("\n========================================\n");
        printf("          Current Announcements          \n");
        printf("========================================\n");
        int announcementCount = 0;
        while (fgets(announcement, sizeof(announcement), file)) {
            printf("%d. %s", ++announcementCount, announcement); 
        }
        if (announcementCount == 0) {
            printf("No announcements available.\n");
        }
        printf("========================================\n");
        fclose(file);

    // Add Announcement
    } else if (choice == 2) {
        file = fopen("announcements.txt", "a");
        if (file == NULL) {
            printf("\n========================================\n");
            printf("Error: Could not open announcements.txt.\n");
            printf("========================================\n");
            return;
        }

        printf("\nEnter the new announcement:\n");
        fgets(announcement, sizeof(announcement), stdin);
        fprintf(file, "%s", announcement);
        fclose(file);

        printf("\n========================================\n");
        printf("Announcement added successfully.\n");
        printf("========================================\n");

   
    } else {
        printf("\n========================================\n");
        printf("Invalid choice. Please try again.\n");
        printf("========================================\n");
    }
}


void addEmployee() {
    FILE* file = fopen("employees.txt", "a");
    if (file == NULL) {
        printf("Error: Could not open employees.txt.\n");
        return;
    }

    Employee newEmployee;
    printf("Enter employee details:\n");
    printf("ID: ");
    scanf("%d", &newEmployee.id);
    printf("Name: ");
    scanf("%s", newEmployee.name);
    printf("Gender: ");
    scanf("%s", newEmployee.gender);
    printf("Age: ");
    scanf("%d", &newEmployee.age);
    printf("Salary: ");
    scanf("%f", &newEmployee.salary);
    printf("Experience (years): ");
    scanf("%d", &newEmployee.experience);
    printf("Department: ");
    scanf("%s", newEmployee.department);

    fprintf(file, "%d %s %s %d %.2f %d %s\n", newEmployee.id, newEmployee.name, newEmployee.gender, newEmployee.age, newEmployee.salary, newEmployee.experience, newEmployee.department);
    fclose(file);

    printf("Employee added successfully.\n");
}

void removeEmployee() {
    int idToRemove, found = 0;
    printf("Enter the ID of the employee to remove: ");
    scanf("%d", &idToRemove);

    FILE* file = fopen("employees.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL) {
        printf("Error: Could not open files.\n");
        return;
    }

    Employee emp;
    while (fscanf(file, "%d %s %s %d %f %d %s", &emp.id, emp.name, emp.gender, &emp.age, &emp.salary, &emp.experience, emp.department) != EOF) {
        if (emp.id == idToRemove) {
            found = 1;
        } else {
            fprintf(temp, "%d %s %s %d %.2f %d %s\n", emp.id, emp.name, emp.gender, emp.age, emp.salary, emp.experience, emp.department);
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("employees.txt");
        rename("temp.txt", "employees.txt");
        printf("Employee removed successfully.\n");
    } else {
        remove("temp.txt");
        printf("Employee with ID %d not found.\n", idToRemove);
    }
}

void updateEmployee() {
    int idToUpdate, found = 0;
    printf("Enter the ID of the employee to update: ");
    scanf("%d", &idToUpdate);

    FILE* file = fopen("employees.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL) {
        printf("Error: Could not open files.\n");
        return;
    }

    Employee emp;
    while (fscanf(file, "%d %s %s %d %f %d %s", &emp.id, emp.name, emp.gender, &emp.age, &emp.salary, &emp.experience, emp.department) != EOF) {
        if (emp.id == idToUpdate) {
            found = 1;
            printf("Enter new details for employee ID %d:\n", idToUpdate);
            printf("Name: ");
            scanf("%s", emp.name);
            printf("Gender: ");
            scanf("%s", emp.gender);
            printf("Age: ");
            scanf("%d", &emp.age);
            printf("Salary: ");
            scanf("%f", &emp.salary);
            printf("Experience (years): ");
            scanf("%d", &emp.experience);
            printf("Department: ");
            scanf("%s", emp.department);
        }
        fprintf(temp, "%d %s %s %d %.2f %d %s\n", emp.id, emp.name, emp.gender, emp.age, emp.salary, emp.experience, emp.department);
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("employees.txt");
        rename("temp.txt", "employees.txt");
        printf("Employee updated successfully.\n");
    } else {
        remove("temp.txt");
        printf("Employee with ID %d not found.\n", idToUpdate);
    }
}
void viewSalaryIncrementRequests() {
    FILE* incFile = fopen("SALARY_INCREMENT_FILE.txt", "r");
    if (incFile == NULL) {
        printf("\n========================================\n");
        printf("      Salary Increment Requests         \n");
        printf("========================================\n");
        printf("No increment requests found.\n");
        printf("========================================\n");
        return;
    }

    int id;
    char name[50];
    float increment;

    printf("\n========================================\n");
    printf("      Pending Salary Increment Requests \n");
    printf("========================================\n");
    printf("%-8s%-16s%-10s\n", "ID", "Name", "Increment");
    printf("----------------------------------------\n");

    int requestCount = 0;
    while (fscanf(incFile, "%d %49s %f", &id, name, &increment) != EOF) {
        printf("%-8d%-16s%-10.2f\n", id, name, increment);
        requestCount++;
    }

    if (requestCount == 0) {
        printf("No pending salary increment requests.\n");
    }

    printf("========================================\n");
    fclose(incFile);
}

