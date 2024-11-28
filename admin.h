#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"



typedef struct Project {
    int id;                    
    char name[100];            
    char department[50];       
    char status[20];       
    char startDate[20];  
    char endDate[20];     
    struct Project* next;     
} Project;

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

#endif
