
#include <stdio.h>

#define NUM_EMPLOYEES 50

/* Function prototypes */
void captureSalaries(float salaries[], int n);
void displaySalaries(float salaries[], int n, const char *title);
float calculateTotal(float salaries[], int n);
float calculateAverage(float salaries[], int n);
float findHighest(float salaries[], int n);
float findLowest(float salaries[], int n);
void searchSalary(float salaries[], int n);
void bubbleSort(float salaries[], int n);

int main(void) {
    float salaries[NUM_EMPLOYEES];
    float total, average, highest, lowest;
    int choice;

    printf("============================================\n");
    printf("  MUNICIPAL EMPLOYEE SALARY MANAGEMENT\n");
    printf("============================================\n\n");

   
    captureSalaries(salaries, NUM_EMPLOYEES);

    do {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Display all salaries\n");
        printf("2. Show total salary expenditure\n");
        printf("3. Show average salary\n");
        printf("4. Show highest salary\n");
        printf("5. Show lowest salary\n");
        printf("6. Search for a salary\n");
        printf("7. Sort salaries (lowest to highest)\n");
        printf("8. Display sorted salaries\n");
        printf("9. Full salary report\n");
        printf("0. Exit\n");
        printf("===============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySalaries(salaries, NUM_EMPLOYEES, "All Employee Salaries");
                break;
            case 2:
                total = calculateTotal(salaries, NUM_EMPLOYEES);
                printf("\nTotal salary expenditure: %.2f\n", total);
                break;
            case 3:
                average = calculateAverage(salaries, NUM_EMPLOYEES);
                printf("\nAverage salary: %.2f\n", average);
                break;
            case 4:
                highest = findHighest(salaries, NUM_EMPLOYEES);
                printf("\nHighest salary: %.2f\n", highest);
                break;
            case 5:
                lowest = findLowest(salaries, NUM_EMPLOYEES);
                printf("\nLowest salary: %.2f\n", lowest);
                break;
            case 6:
                searchSalary(salaries, NUM_EMPLOYEES);
                break;
            case 7:
                bubbleSort(salaries, NUM_EMPLOYEES);
                printf("\nSalaries sorted successfully (lowest to highest).\n");
                break;
            case 8:
                displaySalaries(salaries, NUM_EMPLOYEES, "Sorted Employee Salaries");
                break;
            case 9:
                total   = calculateTotal(salaries, NUM_EMPLOYEES);
                average = calculateAverage(salaries, NUM_EMPLOYEES);
                highest = findHighest(salaries, NUM_EMPLOYEES);
                lowest  = findLowest(salaries, NUM_EMPLOYEES);

                printf("\n========== SALARY REPORT ==========\n");
                printf("Number of employees : %d\n", NUM_EMPLOYEES);
                printf("Total expenditure   : %.2f\n", total);
                printf("Average salary      : %.2f\n", average);
                printf("Highest salary      : %.2f\n", highest);
                printf("Lowest salary       : %.2f\n", lowest);
                printf("===================================\n");
                break;
            case 0:
                printf("\nExiting program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

void captureSalaries(float salaries[], int n) {
    printf("Enter salaries for %d employees:\n", n);
    printf("(Enter positive values only)\n\n");

    for (int i = 0; i < n; i++) {
        do {
            printf("Employee %2d salary: ", i + 1);
            scanf("%f", &salaries[i]);
            if (salaries[i] < 0) {
                printf("  Negative salary not allowed. Please re-enter.\n");
            }
        } while (salaries[i] < 0);
    }
    printf("\nAll %d salaries captured successfully.\n", n);
}

void displaySalaries(float salaries[], int n, const char *title) {
    printf("\n--- %s ---\n", title);
    for (int i = 0; i < n; i++) {
        printf("Employee %2d: %.2f\n", i + 1, salaries[i]);
    }
}

float calculateTotal(float salaries[], int n) {
    float total = 0.0f;
    for (int i = 0; i < n; i++) {
        total += salaries[i];
    }
    return total;
}

float calculateAverage(float salaries[], int n) {
    return calculateTotal(salaries, n) / n;
}

float findHighest(float salaries[], int n) {
    float highest = salaries[0];
    for (int i = 1; i < n; i++) {
        if (salaries[i] > highest) {
            highest = salaries[i];
        }
    }
    return highest;
}

float findLowest(float salaries[], int n) {
    float lowest = salaries[0];
    for (int i = 1; i < n; i++) {
        if (salaries[i] < lowest) {
            lowest = salaries[i];
        }
    }
    return lowest;
}

void searchSalary(float salaries[], int n) {
    float searchValue;
    int found = 0;
    int positions[NUM_EMPLOYEES];
    int count = 0;

    printf("\nEnter salary to search for: ");
    scanf("%f", &searchValue);

    for (int i = 0; i < n; i++) {
        if (salaries[i] == searchValue) {
            positions[count++] = i + 1;
            found = 1;
        }
    }

    if (found) {
        printf("Salary %.2f found at employee position(s): ", searchValue);
        for (int i = 0; i < count; i++) {
            printf("%d", positions[i]);
            if (i < count - 1) printf(", ");
        }
        printf("\n");
    } else {
        printf("Salary %.2f not found.\n", searchValue);
    }
}

void bubbleSort(float salaries[], int n) {
    float temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (salaries[j] > salaries[j + 1]) {
                temp = salaries[j];
                salaries[j] = salaries[j + 1];
                salaries[j + 1] = temp;
            }
        }
    }
}