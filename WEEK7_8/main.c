#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUPPLIERS 5
#define NAME_LEN      100
#define EMAIL_LEN     100
#define PHONE_LEN     30
#define TOWN_LEN      50

char supplierNames[MAX_SUPPLIERS][NAME_LEN];
char supplierEmails[MAX_SUPPLIERS][EMAIL_LEN];
char supplierPhones[MAX_SUPPLIERS][PHONE_LEN];
char supplierTowns[MAX_SUPPLIERS][TOWN_LEN];
int  supplierCount = 0;

void  displayWelcome(void);
void  displayMenu(void);
float calculateVAT(float amount);
float calculateSalary(float basic, float housing, float transport);
float calculateBudget(float revenue, float expenses);
int   searchEmployee(int id, int ids[], int size);
void  printBudgetStatus(float balance);
void  removeNewline(char text[]);
void  readLine(char text[], int size);
int   readInt(void);
float readFloat(void);
void  addSupplier(void);
void  displaySupplier(void);
int   findSupplier(const char name[]);
void  searchSupplier(void);

int main(void)
{
    int employeeIDs[] = {101, 102, 103, 104, 105};
    int employeeCount = sizeof(employeeIDs) / sizeof(employeeIDs[0]);
    int choice;
    float amount, basic, housing, transport, revenue, expenses, balance;
    int empId, pos;

    displayWelcome();

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
            displaySupplier();
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
            printf("Budget balance: %.2f\n", balance);
            printBudgetStatus(balance);
            break;

        case 7:
            printf("Enter employee ID: ");
            empId = readInt();
            pos = searchEmployee(empId, employeeIDs, employeeCount);
            if (pos == -1)
                printf("Employee not found.\n");
            else
                printf("Employee found at position %d.\n", pos);
            break;

        case 8:
            printf("Goodbye.\n");
            break;

        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 8);

    return 0;
}


void displayWelcome(void)
{
    printf("Welcome to the Municipal Financial Management System\n");
}

void displayMenu(void)
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
    printf("8. Exit\n");
    printf("Enter choice: ");
}


float calculateVAT(float amount)
{
    return amount * 0.15f;
}

float calculateSalary(float basic, float housing, float transport)
{
    return basic + housing + transport;
}

float calculateBudget(float revenue, float expenses)
{
    return revenue - expenses;
}

void printBudgetStatus(float balance)
{
    if (balance > 0)
        printf("SURPLUS\n");
    else if (balance < 0)
        printf("DEFICIT\n");
    else
        printf("BALANCED\n");
}

int searchEmployee(int id, int ids[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (ids[i] == id)
            return i;
    }
    return -1;
}

/* ---------- Input helpers ---------- */

void removeNewline(char text[])
{
    text[strcspn(text, "\n")] = '\0';
}

void readLine(char text[], int size)
{
    fgets(text, size, stdin);
    removeNewline(text);
}

int readInt(void)
{
    char buffer[50];
    readLine(buffer, sizeof(buffer));
    return atoi(buffer);
}

float readFloat(void)
{
    char buffer[50];
    readLine(buffer, sizeof(buffer));
    return (float)atof(buffer);
}


void addSupplier(void)
{
    int i = supplierCount;

    if (i >= MAX_SUPPLIERS)
    {
        printf("Supplier list is full (maximum %d).\n", MAX_SUPPLIERS);
        return;
    }

    printf("Enter supplier name: ");
    readLine(supplierNames[i], NAME_LEN);

    printf("Enter email: ");
    readLine(supplierEmails[i], EMAIL_LEN);

    printf("Enter phone: ");
    readLine(supplierPhones[i], PHONE_LEN);

    printf("Enter town: ");
    readLine(supplierTowns[i], TOWN_LEN);

    supplierCount++;
    printf("Supplier added.\n");
}

void displaySupplier(void)
{
    if (supplierCount == 0)
    {
        printf("No suppliers recorded yet.\n");
        return;
    }

    for (int i = 0; i < supplierCount; i++)
    {
        printf("\n--- SUPPLIER %d DETAILS ---\n", i + 1);
        printf("Name : %s\n", supplierNames[i]);
        printf("Email: %s\n", supplierEmails[i]);
        printf("Phone: %s\n", supplierPhones[i]);
        printf("Town : %s\n", supplierTowns[i]);
        printf("Name length: %zu\n", strlen(supplierNames[i]));
    }
}

int findSupplier(const char name[])
{
    for (int i = 0; i < supplierCount; i++)
    {
        if (strcmp(supplierNames[i], name) == 0)
            return i;
    }
    return -1;
}

void searchSupplier(void)
{
    char searchName[NAME_LEN];
    char backup[NAME_LEN];
    char description[300];
    int index;

    printf("Enter supplier name to search: ");
    readLine(searchName, NAME_LEN);

    index = findSupplier(searchName);
    if (index == -1)
    {
        printf("Supplier not found.\n");
        return;
    }

    printf("Supplier found.\n");

    strcpy(backup, supplierNames[index]);
    printf("Backup name: %s\n", backup);


    strcpy(description, supplierNames[index]);
    strcat(description, " operates in ");
    strcat(description, supplierTowns[index]);
    strcat(description, ".");
    printf("%s\n", description);
}