#include <stdio.h>
#include <string.h>
#include "records.h"

#define RECORDS_BIN "data/week11_employees.dat"

static Employee employees[MAX_RECORDS];
static int employeeCount = 0;

int addEmployee(void)
{
    if (employeeCount == MAX_RECORDS)
    {
        printf("Employee list is full.\n");
        return 0;
    }

    printf("Enter employee ID: ");
    scanf("%d", &employees[employeeCount].id);
    getchar();

    printf("Enter name: ");
    fgets(employees[employeeCount].name, sizeof employees[employeeCount].name, stdin);
    employees[employeeCount].name[strcspn(employees[employeeCount].name, "\r\n")] = '\0';

    printf("Enter department: ");
    fgets(employees[employeeCount].department, sizeof employees[employeeCount].department, stdin);
    employees[employeeCount].department[strcspn(employees[employeeCount].department, "\r\n")] = '\0';

    printf("Enter salary: ");
    scanf("%lf", &employees[employeeCount].salary);
    getchar();

    employeeCount++;
    printf("Employee added.\n");
    return 1;
}

void displayEmployees(void)
{
    if (employeeCount == 0)
    {
        printf("No Week 11 employees recorded yet.\n");
        return;
    }

    printf("\n%-6s %-20s %-15s %12s\n", "ID", "Name", "Department", "Salary");
    for (int i = 0; i < employeeCount; i++)
    {
        printf("%-6d %-20s %-15s %12.2f\n",
               employees[i].id, employees[i].name,
               employees[i].department, employees[i].salary);
    }
}

int saveEmployeeRecords(void)
{
    FILE *fp = fopen(RECORDS_BIN, "wb");
    size_t written;

    if (fp == NULL)
    {
        perror(RECORDS_BIN);
        return 0;
    }

    written = fwrite(employees, sizeof employees[0], employeeCount, fp);
    fclose(fp);

    if (written != (size_t)employeeCount)
    {
        perror("Error writing Week 11 employee records");
        return 0;
    }

    printf("Saved %d Week 11 employee record(s) to binary file.\n", employeeCount);
    return 1;
}

int loadEmployeeRecords(void)
{
    FILE *fp = fopen(RECORDS_BIN, "rb");
    size_t count;

    if (fp == NULL)
    {
        employeeCount = 0;
        printf("No binary employee file yet.\n");
        return 0;
    }

    count = fread(employees, sizeof employees[0], MAX_RECORDS, fp);
    fclose(fp);

    employeeCount = (int)count;
    printf("Loaded %d Week 11 employee record(s) from binary file.\n", employeeCount);
    return employeeCount;
}