#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "common.h"

// Function Prototypes for Employee Features
void viewPersonalDetails(char* username);
void updatePassword(char* username);
void requestSalaryIncrement(char* username);
void viewLeaveBalance(char* username);
void viewAnnouncements();
void accessHandbook();
void employeeMenu(char* username);  // Keep this version, only one function with username
int employeeLogin(char* username, char* password);  // Keep the password argument for future use

#endif
