#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"

void employeeReport(void)
{
    printf("\n--- EMPLOYEE REPORT ---\n");
    printf("Total employees: %d\n", getEmployeeCount());

    for (int i = 0; i < getEmployeeCount(); i++)
        printf("Employee %d: ID %d\n", i + 1, getEmployeeID(i));
}

void budgetReport(float revenue, float expenses)
{
    float balance = calculateBudget(revenue, expenses);

    printf("\n--- BUDGET REPORT ---\n");
    printf("Revenue : %.2f\n", revenue);
    printf("Expenses: %.2f\n", expenses);
    printf("Balance : %.2f (%s)\n", balance, budgetStatus(balance));
}