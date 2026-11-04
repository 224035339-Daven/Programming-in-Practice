#include "budget.h"

float calculateVAT(float amount)
{
    return amount * 0.15f;
}

float calculateBudget(float revenue, float expenses)
{
    return revenue - expenses;
}

const char *budgetStatus(float balance)
{
    if (balance > 0)
        return "SURPLUS";
    if (balance < 0)
        return "DEFICIT";
    return "BALANCED";
}