#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utilities.h"

#define MAX_SUPPLIERS 5
#define NAME_LEN      100
#define EMAIL_LEN     100
#define PHONE_LEN     30
#define TOWN_LEN      50

#define SUPPLIER_FILE   "data/suppliers.txt"
#define SUPPLIER_TMP    "data/suppliers.tmp"
#define SUPPLIER_BACKUP "data/suppliers_backup.txt"

static char names[MAX_SUPPLIERS][NAME_LEN];
static char emails[MAX_SUPPLIERS][EMAIL_LEN];
static char phones[MAX_SUPPLIERS][PHONE_LEN];
static char towns[MAX_SUPPLIERS][TOWN_LEN];
static int  count = 0;

void addSupplier(void)
{
    if (count == MAX_SUPPLIERS)
    {
        printf("Supplier list is full.\n");
        return;
    }

    printf("Enter supplier name: ");
    readLine(names[count], NAME_LEN);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(names[i], names[count]) == 0)
        {
            printf("A supplier with that name already exists.\n");
            return;
        }
    }

    printf("Enter email: ");
    readLine(emails[count], EMAIL_LEN);
    printf("Enter phone: ");
    readLine(phones[count], PHONE_LEN);
    printf("Enter town: ");
    readLine(towns[count], TOWN_LEN);

    count++;
    printf("Supplier added.\n");
}

void displaySuppliers(void)
{
    if (count == 0)
    {
        printf("No suppliers recorded yet.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s | %s | %s | %s\n",
               i + 1, names[i], emails[i], phones[i], towns[i]);
    }
}

void searchSupplier(void)
{
    char key[NAME_LEN];
    int found = 0;

    printf("Enter supplier name to search: ");
    readLine(key, NAME_LEN);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(names[i], key) == 0)
        {
            printf("Found: %s | %s | %s | %s\n",
                   names[i], emails[i], phones[i], towns[i]);
            found = 1;
        }
    }

    if (!found)
        printf("Supplier not found.\n");
}

/* Writes every supplier to a temporary file, then replaces the real file. */
int saveSuppliers(void)
{
    FILE *fp = fopen(SUPPLIER_TMP, "w");
    if (fp == NULL)
    {
        perror(SUPPLIER_TMP);
        return 0;
    }

    for (int i = 0; i < count; i++)
    {
        if (fprintf(fp, "%s|%s|%s|%s\n",
                    names[i], emails[i], phones[i], towns[i]) < 0)
        {
            perror("Error writing supplier record");
            fclose(fp);
            remove(SUPPLIER_TMP);
            return 0;
        }
    }

    if (fclose(fp) != 0)
    {
        perror("fclose");
        remove(SUPPLIER_TMP);
        return 0;
    }

    remove(SUPPLIER_FILE);   /* Windows rename() fails if the target exists */
    if (rename(SUPPLIER_TMP, SUPPLIER_FILE) != 0)
    {
        perror("Could not replace suppliers.txt");
        return 0;
    }

    printf("Saved %d supplier record(s).\n", count);
    return 1;
}

/* Loads suppliers from the file into the arrays. Returns the number loaded. */
int loadSuppliers(void)
{
    FILE *fp = fopen(SUPPLIER_FILE, "r");
    char line[512];

    count = 0;

    if (fp == NULL)
    {
        printf("No saved supplier file yet. Starting with an empty list.\n");
        return 0;
    }

    while (count < MAX_SUPPLIERS && fgets(line, sizeof line, fp) != NULL)
    {
        char *fields[4];
        char *p = line;
        int n = 0;

        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0')
            continue;               /* skip blank lines */

        fields[n++] = p;
        while (n < 4 && (p = strchr(p, '|')) != NULL)
        {
            *p++ = '\0';
            fields[n++] = p;
        }

        if (n != 4)
        {
            printf("Skipping malformed supplier record.\n");
            continue;
        }

        snprintf(names[count],  NAME_LEN,  "%s", fields[0]);
        snprintf(emails[count], EMAIL_LEN, "%s", fields[1]);
        snprintf(phones[count], PHONE_LEN, "%s", fields[2]);
        snprintf(towns[count],  TOWN_LEN,  "%s", fields[3]);
        count++;
    }

    fclose(fp);
    printf("Loaded %d supplier record(s).\n", count);
    return count;
}

/* Copies data/suppliers.txt to data/suppliers_backup.txt. */
int backupSuppliers(void)
{
    FILE *src = fopen(SUPPLIER_FILE, "rb");
    FILE *dst;
    char buffer[512];
    size_t n;

    if (src == NULL)
    {
        printf("Nothing to back up yet.\n");
        return 0;
    }

    dst = fopen(SUPPLIER_BACKUP, "wb");
    if (dst == NULL)
    {
        perror(SUPPLIER_BACKUP);
        fclose(src);
        return 0;
    }

    while ((n = fread(buffer, 1, sizeof buffer, src)) > 0)
    {
        if (fwrite(buffer, 1, n, dst) != n)
        {
            perror("Backup write failed");
            fclose(src);
            fclose(dst);
            return 0;
        }
    }

    fclose(src);
    if (fclose(dst) != 0)
    {
        perror("Backup close failed");
        return 0;
    }

    printf("Supplier data backed up to %s.\n", SUPPLIER_BACKUP);
    return 1;
}