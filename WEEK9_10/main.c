#include <stdio.h>
#include "utilities.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "reports.h"

static void displayWelcome(void)
{
    printf("Welcome to the Municipal Financial Management System\n");
}

static void displayMenu(void)
{
    printf("\n================================\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT\n");
    printf("================================\n");
    printf("1. Add Supplier\n");
    printf("2. Display Suppliers\n");
    printf("3. Search Supplier\n");
    printf("4. Calculate VAT\n");
    printf("5. Calculate Salary\n");
    printf("6. Calculate Budget\n");
    printf("7. Search Employee\n");
    printf("8. Employee Report\n");
    printf("9. Budget Report\n");
    printf("10. Exit\n");
    printf("11. Backup Suppliers\n");
    printf("Enter choice: ");
}

int main(void)
{
    int choice;
    int empId, pos;
    float amount, basic, housing, transport, revenue, expenses, balance;

    displayWelcome();
    loadSuppliers();
    loadEmployees();

    do
    {
        displayMenu();
        choice = readInt();

        switch (choice)
        {
        case 1:
            addSupplier();
            break;
        case 2:
            displaySuppliers();
            break;
        case 3:
            searchSupplier();
            break;
        case 4:
            printf("Enter amount: ");
            amount = readFloat();
            printf("VAT: %.2f\n", calculateVAT(amount));
            break;
        case 5:
            printf("Basic salary: ");
            basic = readFloat();
            printf("Housing allowance: ");
            housing = readFloat();
            printf("Transport allowance: ");
            transport = readFloat();
            printf("Gross salary: %.2f\n", calculateSalary(basic, housing, transport));
            break;
        case 6:
            printf("Revenue: ");
            revenue = readFloat();
            printf("Expenses: ");
            expenses = readFloat();
            balance = calculateBudget(revenue, expenses);
            printf("Budget balance: %.2f (%s)\n", balance, budgetStatus(balance));
            break;
        case 7:
            printf("Enter employee ID: ");
            empId = readInt();
            pos = searchEmployee(empId);
            if (pos == -1)
                printf("Employee not found.\n");
            else
                printf("Employee found at position %d.\n", pos + 1);
            break;
        case 8:
            employeeReport();
            break;
        case 9:
            printf("Revenue: ");
            revenue = readFloat();
            printf("Expenses: ");
            expenses = readFloat();
            budgetReport(revenue, expenses);
            break;
        case 10:
            if (!saveSuppliers())
                printf("Warning: supplier data could not be saved.\n");
            if (!saveEmployees())
                printf("Warning: employee data could not be saved.\n");
            printf("Goodbye.\n");
            break;
        case 11:
            backupSuppliers();
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 10);

    return 0;
}