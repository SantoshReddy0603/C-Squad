#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "common.h"

void viewPersonalDetails(char* username);
void updatePassword(char* username);
void requestSalaryIncrement(char* username);
void viewLeaveBalance(char* username);
void viewAnnouncements();
void accessHandbook();
void employeeMenu(char* username);  
int employeeLogin(char* username, char* password); 

#endif
