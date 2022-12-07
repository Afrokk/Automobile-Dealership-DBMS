#include <ctype.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CRUDFunctions.h"
#include "QueryEngine.h"

int main(int argc, char **argv) {
  sqlite3 *db;
  char *UserSelection = malloc(sizeof(char));
  int *UserSelectionInt = malloc(sizeof(int));
  char *ErrMsg = malloc(sizeof(char));
  char *ErrArg = malloc(sizeof(char));
  char *sql = malloc(sizeof(char) * 50);
  
  //CHANGE DATABASE FILE NAME HERE, IF NEEDED
  //RUN SampleAutomobileDatabase.db to Test with Sample Data
  *ErrMsg = (int)sqlite3_open_v2("AutomobileDatabase.db", &db,
                                 SQLITE_OPEN_READWRITE, NULL) *
            sizeof(int);

  if (*ErrMsg != 0) {
    printf("Error: Can't open database: %s\n", sqlite3_errmsg(db));
    return 1;
  } else {
    printf("Connected to the database successfully.\n");
  }
  printf("\nWelcome to the Automobile Dealership DBMS\n");
  do {
    puts("\n------ MENU ------");
    puts("\n-- CRUD Operations --");
    puts("1) Add a New Vehicle");
    puts("2) Add a New Lot in the Inventory");
    puts("3) Add a New Customer");
    puts("4) Add a New Salesman");
    puts("5) Add a New Mechanic");
    puts("6) Add a New Work Order");
    puts("");
    puts("7) Delete a Field");
    puts("8) Update a Field");
    puts("");
    puts("9) Display All Vehicles");
    puts("10) Display All Lots");
    puts("11) Display All Customers");
    puts("12) Display All Salesmen");
    puts("13) Display All Mechanics");
    puts("14) Display All Work Orders");
    puts("");
    puts("-- Queries --");
    puts("15) Run a Query");
    puts("Press 0 to Exit.\n");
    printf("Please Choose an Option from the Menu: ");
    fgets(UserSelection, 20, stdin);

    while (isdigit(*UserSelection) == 0) {
      printf("\nInvalid Input. Please Enter a Valid Choice: ");
      fgets(UserSelection, 20, stdin);
    }
    *UserSelectionInt = atoi(UserSelection);

    switch (*UserSelectionInt) {
      case 1:
        AddNewVehicle(db);
        break;
      case 2:
        AddNewLot(db);
        break;
      case 3:
        AddNewCustomer(db);
        break;
      case 4:
        AddNewSalesman(db);
        break;
      case 5:
        AddNewMechanic(db);
        break;
      case 6:
        AddNewWorkOrder(db);
        break;
      case 7:
        RemoveField(db);
        break;
      case 8:
        UpdateField(db);
        break;
      case 9:
        puts("\nRetrieved Data: \n");
        *ErrMsg = sqlite3_exec(db, "SELECT * FROM Vehicle;",
                               DisplayDataCallback, 0, &ErrArg);
        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrMsg);
          sqlite3_free(ErrMsg);
        }
        break;
      case 10:
        sql = "SELECT * FROM Inventory;";
        DisplayFields(db, sql);
        break;
      case 11:
        puts("\nRetrieved Data: \n");
        *ErrMsg = sqlite3_exec(db, "SELECT * FROM Customer;",
                               DisplayDataCallback, 0, &ErrArg);
        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrMsg);
          sqlite3_free(ErrMsg);
        }
        break;
      case 12:
        sql = "SELECT * FROM Salesman;";
        DisplayFields(db, sql);
        break;
      case 13:
        sql = "SELECT * FROM Mechanic;";
        DisplayFields(db, sql);
        break;
      case 14:
        sql = "SELECT * FROM WorkOrder;";
        DisplayFields(db, sql);
        break;
      case 15:
        QueryRunner(db);
      case 0:
        printf(
            "\nThank you for using the Automobile Dealership DBMS. Goodbye!\n");
        break;
      default:
        printf("\nInvalid Input. Please Enter a Valid Choice and Try Again.\n");
        break;
    }
  } while (*UserSelectionInt != 0);

  sqlite3_close(db);
  free(UserSelection);
  free(UserSelectionInt);
  free(ErrMsg);
  free(ErrArg);
  return 0;
}
