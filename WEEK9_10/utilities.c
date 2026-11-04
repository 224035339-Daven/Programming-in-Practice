#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

void readLine(char text[], int size)
{
    if (fgets(text, size, stdin) == NULL)
    {
        text[0] = '\0';
        return;
    }
    text[strcspn(text, "\n")] = '\0';
}

int readInt(void)
{
    char buffer[50];
    readLine(buffer, sizeof buffer);
    return atoi(buffer);
}

float readFloat(void)
{
    char buffer[50];
    readLine(buffer, sizeof buffer);
    return (float)atof(buffer);
}