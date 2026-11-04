#ifndef BUDGET_H
#define BUDGET_H

float       calculateVAT(float amount);
float       calculateBudget(float revenue, float expenses);
const char *budgetStatus(float balance);

#endif