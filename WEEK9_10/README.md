# PAP521S MFMS: Week 9 and 10

Municipal Financial Management System, modularised into separate source files, with text file persistence for suppliers and employees.

## Modules

| File | Responsibility |
|---|---|
| `main.c` | Program flow and the menu. Loads data at startup and saves it on Exit. |
| `employees.c / employees.h` | Employee records, ID search, salary calculation, and text save/load. |
| `budget.c / budget.h` | Budget calculation, status, and budget report. |
| `utilities.c / utilities.h` | Reusable input helpers (`readInt`, `readFloat`, `readLine`). |
| `reports.c / reports.h` | Employee and budget reports. |
| `suppliers.c / suppliers.h` | Supplier records, search, duplicate-name check, text save/load, and backup. |

Each header holds only the prototypes other modules need, and each has an include guard.

## Build

From the `WEEK9_10` folder:

```powershell
gcc -std=c99 -Wall -Wextra -pedantic -c main.c employees.c budget.c utilities.c reports.c suppliers.c
gcc main.o employees.o budget.o utilities.o reports.o suppliers.o -o mfms.exe
.\mfms.exe
```

## Data files

The program stores data in the `data/` folder inside `WEEK9_10`. Create it before the first run:

```powershell
mkdir data
```

- `data/suppliers.txt`: one supplier per line, fields separated by `|`: `name|email|phone|town`
- `data/employees.txt`: one employee per line: `id|name|salary`
- `data/suppliers_backup.txt`: a copy of `suppliers.txt`, made by menu option 11

## Known limitations

- **Pipe separator:** a `|` inside a name, email, phone or town breaks the record format. Such records are not supported.
- **Save on Exit only:** suppliers and employees are written to disk when you choose Exit (10). If the window is closed or the program crashes, changes since the last load are lost.
- **Case-sensitive duplicate check:** `City Stationery` and `city stationery` are treated as different suppliers.
- **Fixed capacity:** the program holds up to 5 suppliers (`MAX_SUPPLIERS`) and 50 employees.
- **Malformed records:** lines that don't have the expected fields are skipped with a message, and not loaded.

## Testing

Tests run on Windows with PowerShell. Results are from the Week 10 test sequence:

1. **First run, no data files:** prints "No saved supplier file yet" and "No saved employee file yet", and starts with default employees.
2. **Add and duplicate check:** two suppliers added. Adding a supplier with an existing name prints "A supplier with that name already exists."
3. **Display:** both suppliers listed with name, email, phone and town.
4. **Save on Exit:** prints "Saved 2 supplier record(s)" and "Saved 5 employee record(s)". The file contents match the pipe format.
5. **Reload:** prints "Loaded 2 supplier record(s)" and the suppliers display unchanged.
6. **Backup (option 11):** `suppliers_backup.txt` matches `suppliers.txt`.
7. **Malformed line:** a line with no pipes prints "Skipping malformed supplier record." The two valid suppliers still load. The line is removed on the next save.
8. **Missing file:** with `suppliers.txt` deleted, the program starts with an empty list and displays "No suppliers recorded yet."
9. **Other menu options (4 to 9):** VAT of 10000 gives 1500.00; salary of 1000 + 2000 + 1000 gives 4000.00; budget of 5000 - 4400 gives a 600.00 surplus; employee ID 101 found at position 1, 999 not found; both reports print.

## Git

Build outputs (`*.o`, `*.exe`) and the `data/` folder are excluded by `.gitignore`.