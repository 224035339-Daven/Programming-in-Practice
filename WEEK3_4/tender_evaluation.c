#include <stdio.h>

int main()
{
    char supplierName[50];
    float price, budget;
    int registered, documentsComplete;

    printf("TENDER EVALUATION SYSTEM\n\n");

    printf("Enter supplier name: ");
    scanf("%49s", supplierName);

    printf("Enter tender price: ");
    scanf("%f", &price);

    printf("Enter available budget: ");
    scanf("%f", &budget);

    printf("Is supplier registered? (1=Yes, 0=No): ");
    scanf("%d", &registered);

    printf("Are all documents complete? (1=Yes, 0=No): ");
    scanf("%d", &documentsComplete);

    printf("\n---------------------------------\n");
    printf("Supplier: %s\n", supplierName);

    if (registered == 0 || documentsComplete == 0)
    {
        printf("Status  : Disqualified\n");
    }
    else if (price > budget)
    {
        printf("Status  : Disqualified\n");
    }
    else
    {
        printf("Status  : Qualified\n");
    }
    printf("---------------------------------\n");

    return 0;
}