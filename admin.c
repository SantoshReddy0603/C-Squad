#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "common.h"
#include <ctype.h>



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
            return 1;  
        }
    }

    printf("Invalid username or password for admin.\n");
    fclose(file);
    return 0;  
}
void displayEmployeeDetails();
void averageSalaryByDepartment();
void employeesPerDepartment();
void currentProjects();
void highestPaidEmployee();
void addEmployee();
void removeEmployee();
void updateEmployee();
void manageAnnouncements();
void editLeaveBalance();
void loadProjectsFromFile(Project** head);
void saveProjectsToFile(Project* head);
void addProject(Project** head);
void removeProject(Project** head);
void updateProjectStatus();
void updateProjects();
void viewSalaryIncrementRequests();

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
        printf("8. Leave Management\n");
        printf("9. Add Employee\n");
        printf("10. Remove Employee\n");
        printf("11. Update Employee\n");
        printf("12. View salary Increment Requests\n");
        printf("13. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayEmployeeDetails(); break;
            case 2: averageSalaryByDepartment(); break;
            case 3: employeesPerDepartment(); break;
            case 4: currentProjects(); break;
            case 5: updateProjects(); break;
            case 6: highestPaidEmployee(); break;
            case 7: manageAnnouncements(); break;
            case 8: editLeaveBalance(); break;
            case 9: addEmployee(); break;
            case 10: removeEmployee(); break;
            case 11: updateEmployee(); break;
            case 12: viewSalaryIncrementRequests(); break;
            case 13: return; // Logout
            default: printf("\nInvalid choice. Please try again.\n");
        }
    }
}

#define EMPLOYEE_FILE "employees.txt"
void updateProjects(){
	Project* head = NULL;

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
			case 3: updateProjectStatus(&head); break;
			case 4: return;
			default: printf("\nInvalid choice. Please try again.\n");
		}
	}
}
void displayEmployeeDetails() {
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (!file) {
        printf("Error: Could not open employees.txt\n");
        return;
    }

    printf("\n=== Employee Details ===\n");
    printf("%-8s%-20s%-10s%-6s%-18s%-12s%s\n", 
           "ID", "Name", "Gender", "Age", "Salary(In LPA)", "Experience", "Department");
    printf("----------------------------------------------------------------------------------\n");

    int id, age, experience;
    float salary;
    char name[50], gender[10], department[50];


    while (fscanf(file, "%d %49s %9s %d %f %d %49s",
                  &id, name, gender, &age, &salary, &experience, department) == 7) {
        printf("%-8d%-20s%-10s%-6d%-18.2f%-12d%-20s\n",
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
    printf("Department\tAverage Salary(In LPA)\n");
    printf("---------------------------------\n");
    for (int i = 0; i < uniqueDepartments; i++) {
        printf("%s\t\t%.2f\n", department[i], deptSalary[i] / deptCount[i]);
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

void addProject(Project** head) {
    FILE* file = fopen("projects.txt", "a"); 
    if (file == NULL) {
        printf("Error: Could not open projects.txt\n");
        return;
    }

    
    Project* newProject = (Project*)malloc(sizeof(Project));
    if (newProject == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return;
    }

    
    printf("Enter project ID: ");
    scanf("%d", &newProject->id);

    
    Project* temp = *head;
    while (temp != NULL) {
        if (temp->id == newProject->id) {
            printf("Error: A project with ID %d already exists. Cannot add duplicate.\n", newProject->id);
            free(newProject); 
            fclose(file);
            return;
        }
        temp = temp->next;
    }

    
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

   
    newProject->next = *head;
    *head = newProject;

    
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

    
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Project with ID %d not found.\n", id);
        return;
    }

    
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);

    
    FILE* file = fopen("projects.txt", "w"); 
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
      
void updateProjectStatus(Project** head) {
    if (*head == NULL) {
        printf("No projects available to update.\n");
        return;
    }

    
    displayProjects(*head);

    
    printf("Enter the project ID to update its status: ");
    int projectId;
    scanf("%d", &projectId);

    
    Project* temp = *head;
    while (temp != NULL) {
        if (temp->id == projectId) {
           
            printf("Enter new status for the project:\n");
            printf("  0 - Pending\n");
            printf("  1 - Active\n");
            printf("  2 - Completed\n");
            int statusOption;
            scanf("%d", &statusOption);

            
            if (statusOption < 0 || statusOption > 2) {
                printf("Invalid status option. Please enter 0, 1, or 2.\n");
                return;
            }

            
            switch (statusOption) {
                case 0:
                    strcpy(temp->status, "Pending");
                    break;
                case 1:
                    strcpy(temp->status, "Active");
                    break;
                case 2:
                    strcpy(temp->status, "Completed");
                    break;
            }
            printf("Project status updated successfully.\n");

                        saveProjectsToFile(*head);
            return;
        }
        temp = temp->next;
    }

    
    printf("Error: No project with ID %d found.\n", projectId);
}


void saveProjectsToFile(Project* head) {
    FILE* file = fopen("projects.txt", "w");
    if (file == NULL) {
        printf("Error: Could not open projects.txt for saving.\n");
        return;
    }

    Project* temp = head;
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
}


void loadProjectsFromFile(Project** head) {
    FILE* file = fopen("projects.txt", "r"); 
    if (file == NULL) {
        printf("Error: Could not open projects.txt\n");
        return;
    }

    int id;
    char name[MAX_STR_LEN], department[MAX_STR_LEN], status[MAX_STR_LEN];
    char startDate[MAX_STR_LEN], endDate[MAX_STR_LEN];

    while (fscanf(file, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%99[^\n]\n",
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
        newProject->next = *head;

        *head = newProject;
    }

    fclose(file);
    printf("Projects loaded successfully.\n");
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

    
    printf("\n========================================\n");
    printf("          Announcements Management       \n");
    printf("========================================\n");
    printf("1. View Announcements\n");
    printf("2. Add Announcement\n");
    printf("========================================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    
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
#define MAX_STR_LEN 100

void editLeaveBalance() {
    FILE* file = fopen("leave_balances.txt", "r");
    if (file == NULL) {
        printf("\n========================================\n");
        printf("        Leave Balance Editor            \n");
        printf("========================================\n");
        printf("Error: Could not open leave balances file.\n");
        printf("========================================\n");
        return;
    }

    char name[MAX_STR_LEN];
    int leaveBalance;

   
    char tempName[MAX_STR_LEN];
    int tempLeaveBalance;
    int found = 0;

    printf("\n========================================\n");
    printf("        Leave Balance Editor            \n");
    printf("========================================\n");
    printf("Enter the username of the employee: ");
    scanf("%s", name);

    
    while (fscanf(file, "%s %d", tempName, &tempLeaveBalance) != EOF) {
        if (strcmp(tempName, name) == 0) {
            printf("Current Leave Balance for '%s': %d days\n", tempName, tempLeaveBalance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Error: Employee with username '%s' not found.\n", name);
        printf("========================================\n");
        fclose(file);
        return;
    }

    fclose(file);

   
    printf("Enter the new leave balance for '%s': ", name);
    scanf("%d", &leaveBalance);

    file = fopen("leave_balances.txt", "r");
    FILE* tempFile = fopen("temp_leave_balances.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%s %d", tempName, &tempLeaveBalance) != EOF) {
        if (strcmp(tempName, name) == 0) {
            fprintf(tempFile, "%s %d\n", tempName, leaveBalance);
        } else {
            fprintf(tempFile, "%s %d\n", tempName, tempLeaveBalance);
        }
    }

    fclose(file);
    fclose(tempFile);

    
    remove("leave_balances.txt");
    rename("temp_leave_balances.txt", "leave_balances.txt");

    printf("Leave balance for '%s' updated successfully.\n", name);
    printf("========================================\n");
}

int isIdExists(int id) {
    FILE* file = fopen("employees.txt", "r");
    if (file == NULL) {
        return 0; 
    }

    Employee employee;
    while (fscanf(file, "%d %s %s %d %f %d %s", &employee.id, employee.name, employee.gender, &employee.age,
                  &employee.salary, &employee.experience, employee.department) == 7) { 
        if (employee.id == id) {
            fclose(file);
            return 1; 
        }
    }

    fclose(file);
    return 0; 
}


void addEmployee() {
    FILE* employeeFile = fopen("employees.txt", "a"); 
    FILE* credentialsFile = fopen("employee.txt", "a"); 
    FILE* leaveFile = fopen("leave_balances.txt", "a"); 

    if (employeeFile == NULL || credentialsFile == NULL || leaveFile == NULL) {
        printf("Error: Could not open one of the files.\n");
        return;
    }

    Employee newEmployee;
    printf("Enter employee details:\n");
    printf("ID: ");
    scanf("%d", &newEmployee.id);

       if (isIdExists(newEmployee.id)) {
        printf("Error: Employee with ID %d already exists.\n", newEmployee.id);
        fclose(employeeFile);
        fclose(credentialsFile);
        fclose(leaveFile);
        return;
    }

    printf("Name: ");
    scanf("%s", newEmployee.name);

    
    while (1) {
        printf("Gender (Male/Female): ");
        scanf("%s", newEmployee.gender);

                for (int i = 0; newEmployee.gender[i]; i++) {
            newEmployee.gender[i] = tolower(newEmployee.gender[i]);
        }

        if (strcmp(newEmployee.gender, "male") == 0 || strcmp(newEmployee.gender, "female") == 0) {

            newEmployee.gender[0] = toupper(newEmployee.gender[0]);
            break;
        } else {
            printf("Invalid input. Please enter 'Male' or 'Female'.\n");
        }
    }

    printf("Age: ");
    scanf("%d", &newEmployee.age);
    printf("Salary: ");
    scanf("%f", &newEmployee.salary);
    printf("Experience (years): ");
    scanf("%d", &newEmployee.experience);
    printf("Department (In Capitals): ");
    scanf("%s", newEmployee.department);

 
    char password[50];
    printf("Enter password for employee login: ");
    scanf("%s", password);

   
    fprintf(employeeFile, "%d %s %s %d %.2f %d %s\n",
            newEmployee.id,
            newEmployee.name,
            newEmployee.gender,
            newEmployee.age,
            newEmployee.salary,
            newEmployee.experience,
            newEmployee.department);

   
    fprintf(credentialsFile, "%s %s\n", newEmployee.name, password);

    // Store leave balance in leave_balances.txt (default balance = 10)
    fprintf(leaveFile, "%s 10\n", newEmployee.name);

    fclose(employeeFile);
    fclose(credentialsFile);
    fclose(leaveFile);

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
            printf("Department(In Capitals): ");
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
