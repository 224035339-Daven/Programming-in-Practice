#include <stdio.h>

int main()
{
    float basicSalary, housing, transport, tax;
    float grossSalary, netSalary;

    printf("EMPLOYEE SALARY CALCULATOR\n\n");

    printf("Enter basic salary: ");
    scanf("%f", &basicSalary);

    printf("Enter housing allowance: ");
    scanf("%f", &housing);

    printf("Enter transport allowance: ");
    scanf("%f", &transport);

    printf("Enter tax: ");
    scanf("%f", &tax);

    grossSalary = basicSalary + housing + transport;
    netSalary = grossSalary - tax;

    printf("\n---------------------------------\n");
    printf("Gross Salary : %.2f\n", grossSalary);
    printf("Net Salary   : %.2f\n", netSalary);

    // Extension from the notes
    if (netSalary >= 20000)
    {
        printf("Income Level : High Income\n");
    }
    else
    {
        printf("Income Level : Standard Income\n");
    }
    printf("---------------------------------\n");

    return 0;
}