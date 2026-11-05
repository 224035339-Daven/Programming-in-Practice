#include <stdio.h>
#include <string.h>
#include "employees.h"

#define MAX_EMPLOYEES 50
#define EMP_NAME_LEN  50
#define EMP_FILE      "data/employees.txt"
#define EMP_TMP       "data/employees.tmp"

typedef struct {
    int    id;
    char   name[EMP_NAME_LEN];
    double salary;
} StaffRecord;

/* Default records, used when no saved file exists yet. */
static StaffRecord employees[MAX_EMPLOYEES] = {
    {101, "Maria",        18500.50},
    {102, "Simon",        17200.00},
    {103, "Employee 103",     0.00},
    {104, "Employee 104",     0.00},
    {105, "Employee 105",     0.00}
};
static int employeeCount = 5;

int getEmployeeCount(void)
{
    return employeeCount;
}

int getEmployeeID(int index)
{
    return employees[index].id;
}

int searchEmployee(int id)
{
    for (int i = 0; i < employeeCount; i++)
    {
        if (employees[i].id == id)
            return i;
    }
    return -1;
}

float calculateSalary(float basic, float housing, float transport)
{
    return basic + housing + transport;
}

/* Writes all employees to a temporary file, then replaces the real file. */
int saveEmployees(void)
{
    FILE *fp = fopen(EMP_TMP, "w");
    if (fp == NULL)
    {
        perror(EMP_TMP);
        return 0;
    }

    for (int i = 0; i < employeeCount; i++)
    {
        if (fprintf(fp, "%d|%s|%.2f\n",
                    employees[i].id, employees[i].name, employees[i].salary) < 0)
        {
            perror("Error writing employee record");
            fclose(fp);
            remove(EMP_TMP);
            return 0;
        }
    }

    if (fclose(fp) != 0)
    {
        perror("fclose");
        remove(EMP_TMP);
        return 0;
    }

    remove(EMP_FILE);   /* Windows rename() fails if the target exists */
    if (rename(EMP_TMP, EMP_FILE) != 0)
    {
        perror("Could not replace employees.txt");
        return 0;
    }

    printf("Saved %d employee record(s).\n", employeeCount);
    return 1;
}

/* Loads employees from file. If no file exists, the default records stay. */
int loadEmployees(void)
{
    FILE *fp = fopen(EMP_FILE, "r");
    char line[256];
    int loaded = 0;

    if (fp == NULL)
    {
        printf("No saved employee file yet. Using default employees.\n");
        return 0;
    }

    while (loaded < MAX_EMPLOYEES && fgets(line, sizeof line, fp) != NULL)
    {
        StaffRecord e;

        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0')
            continue;

        if (sscanf(line, "%d|%49[^|]|%lf", &e.id, e.name, &e.salary) != 3)
        {
            printf("Skipping malformed employee record.\n");
            continue;
        }

        employees[loaded++] = e;
    }

    fclose(fp);
    employeeCount = loaded;
    printf("Loaded %d employee record(s).\n", employeeCount);
    return employeeCount;
}