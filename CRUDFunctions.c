#include <ctype.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CRUDFunctions.h"

int DisplayDataCallback(void *data, int argc, char **argv, char **ColName) {
  for (int i = 0; i < argc; i++) {
    printf("%s = %s\n", ColName[i], argv[i]);
  }
  printf("\n");

  return 0;
}

void AddNewVehicle(sqlite3 *db) {
  char *ErrMsg = malloc(sizeof(char));
  char *sql =
      "INSERT INTO Vehicle (VIN, Manufacturer, ModelYear, Name, TrimLevel, BodyType,\
  Color, Mileage, CustomerID, MechanicID, WorkOrderID, InventoryLotNumber, SalesmanID) VALUES (?,\
  ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
  // take input from the user for all the fields
  char *VIN = malloc(sizeof(char) * 25);
  char *Manufacturer = malloc(sizeof(char) * 20);
  char *ModelYear = malloc(sizeof(char) * 20);
  char *Name = malloc(sizeof(char) * 20);
  char *TrimLevel = malloc(sizeof(char) * 20);
  char *BodyType = malloc(sizeof(char) * 20);
  char *Color = malloc(sizeof(char) * 20);
  char *Mileage = malloc(sizeof(char) * 20);
  char *CustomerID = malloc(sizeof(char) * 20);
  char *MechanicID = malloc(sizeof(char) * 20);
  char *WorkOrderID = malloc(sizeof(char) * 20);
  char *InventoryLotNumber = malloc(sizeof(char) * 20);
  char *SalesmanID = malloc(sizeof(char) * 20);
  puts("\n---- Add a New Vehicle ----\n");
  printf("Enter the Dealership VIN (Numbers Only!): ");
  fgets(VIN, 20, stdin);
  CleanupData(VIN);
  printf("Enter the Manufacturer: ");
  fgets(Manufacturer, 20, stdin);
  CleanupData(Manufacturer);
  printf("Enter the Model Year: ");
  fgets(ModelYear, 20, stdin);
  CleanupData(ModelYear);
  printf("Enter the Vehicle Name: ");
  fgets(Name, 20, stdin);
  CleanupData(Name);

  printf("Optional field, Enter 0 if you don't have a Trim Level.\n");
  printf("Enter the Trim Level: ");
  fgets(TrimLevel, 20, stdin);
  CleanupData(TrimLevel);

  printf("Enter the Body Type: ");
  fgets(BodyType, 20, stdin);
  CleanupData(BodyType);
  printf("Enter the Color: ");
  fgets(Color, 20, stdin);
  CleanupData(Color);
  printf("Enter the Mileage: ");
  fgets(Mileage, 20, stdin);
  CleanupData(Mileage);

  printf(
      "Optional field, Enter 0 if the vehicle does not belong to a "
      "customer.\n");
  printf("Enter the Customer ID: ");
  fgets(CustomerID, 20, stdin);
  CleanupData(CustomerID);

  printf(
      "Optional field, Enter 0 if the vehicle does not have an assigned "
      "mechanic.\n");
  printf("Enter the Mechanic ID: ");
  fgets(MechanicID, 20, stdin);
  CleanupData(MechanicID);

  printf("Optional field, Enter 0 if the vehicle is not in for work.\n");
  printf("Enter the Work Order ID: ");
  fgets(WorkOrderID, 20, stdin);
  CleanupData(WorkOrderID);

  printf(
      "Optional field, Enter 0 if the vehicle does not belong to the "
      "dealership.\n");
  printf("Enter the Inventory Lot Number: ");
  fgets(InventoryLotNumber, 20, stdin);
  CleanupData(InventoryLotNumber);

  printf(
      "Optional field, Enter 0 if the vehicle does not have an assigned "
      "salesman.\n");
  printf("Enter the Salesman ID: ");
  fgets(SalesmanID, 20, stdin);
  CleanupData(SalesmanID);

  // prepare the statement
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  // bind the values to the statement
  sqlite3_bind_text(stmt, 1, VIN, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, Manufacturer, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, ModelYear, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, Name, -1, SQLITE_STATIC);

  if (*TrimLevel == '0') {
    sqlite3_bind_null(stmt, 5);
  } else {
    sqlite3_bind_text(stmt, 5, TrimLevel, -1, SQLITE_STATIC);
  }

  sqlite3_bind_text(stmt, 6, BodyType, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 7, Color, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 8, Mileage, -1, SQLITE_STATIC);

  if (*CustomerID == '0') {
    sqlite3_bind_null(stmt, 9);
  } else {
    sqlite3_bind_text(stmt, 9, CustomerID, -1, SQLITE_STATIC);
  }

  if (*MechanicID == '0') {
    sqlite3_bind_null(stmt, 10);
  } else {
    sqlite3_bind_text(stmt, 10, MechanicID, -1, SQLITE_STATIC);
  }

  if (*WorkOrderID == '0') {
    sqlite3_bind_null(stmt, 11);
  } else {
    sqlite3_bind_text(stmt, 11, WorkOrderID, -1, SQLITE_STATIC);
  }

  if (*InventoryLotNumber == '0') {
    sqlite3_bind_null(stmt, 12);
  } else {
    sqlite3_bind_text(stmt, 12, InventoryLotNumber, -1, SQLITE_STATIC);
  }

  if (*SalesmanID == '0') {
    sqlite3_bind_null(stmt, 13);
  } else {
    sqlite3_bind_text(stmt, 13, SalesmanID, -1, SQLITE_STATIC);
  }
  // execute the statement
  *ErrMsg = sqlite3_step(stmt);
  (int)*ErrMsg;
  // print ErrMsg
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("\nError Performing Operation.\n");
  } else {
    printf("\nVehicle Added Successfully.\n");
  }
  *ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("Error: %s\n", sqlite3_errmsg(db));
  }
  free(ErrMsg);
  free(VIN);
  free(Manufacturer);
  free(ModelYear);
  free(Name);
  free(TrimLevel);
  free(BodyType);
  free(Color);
  free(Mileage);
  free(CustomerID);
  free(MechanicID);
  free(WorkOrderID);
  free(InventoryLotNumber);
  free(SalesmanID);
  return;
}

void AddNewLot(sqlite3 *db) {
  char *ErrMsg = malloc(sizeof(char));
  char *sql = "INSERT INTO Inventory (NumVehicles) VALUES ((?));";
  char *NumVehicles = malloc(sizeof(char) * 20);

  puts("\n---- Add a New Lot ----\n");
  printf("Enter the number of vehicles in the new Lot: ");
  fgets(NumVehicles, 20, stdin);
  while (!isdigit(*NumVehicles)) {
    printf("Please Enter a Number: ");
    fgets(NumVehicles, 20, stdin);
  }
  CleanupData(NumVehicles);

  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  sqlite3_bind_text(stmt, 1, NumVehicles, -1, SQLITE_STATIC);
  *ErrMsg = sqlite3_step(stmt);
  (int)*ErrMsg;
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("\nError Performing Operation.\n");
  } else {
    printf("\nLot Added Successfully.\n");
  }
  *ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("Error: %s\n", sqlite3_errmsg(db));
  }
  free(ErrMsg);
  free(NumVehicles);
  return;
}

void AddNewCustomer(sqlite3 *db) {
  char *ErrMsg = malloc(sizeof(char));
  char *sql =
      "INSERT INTO Customer (Name, PhoneNumber, Salesman)\
  VALUES ((?), (?), (?));";
  char *Name = malloc(sizeof(char) * 50);
  char *PhoneNumber = malloc(sizeof(char) * 20);
  char *Salesman = malloc(sizeof(char) * 20);

  puts("\n---- Add a New Customer ----\n");
  printf("Enter the Customer's Name: ");
  fgets(Name, 50, stdin);
  CleanupData(Name);

  printf("Enter the Customer's Phone Number: ");
  fgets(PhoneNumber, 20, stdin);
  // loop if user doesn't enter a number
  while (!isdigit(*PhoneNumber)) {
    printf("Please Enter a Valid Phone Number: ");
    fgets(PhoneNumber, 20, stdin);
  }
  CleanupData(PhoneNumber);
  printf("Enter the Salesman ID: ");
  fgets(Salesman, 20, stdin);
  // loop if user doesn't enter a number
  while (!isdigit(*Salesman)) {
    printf("Please Enter a Valid Salesman ID: ");
    fgets(Salesman, 20, stdin);
  }
  CleanupData(Salesman);

  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  sqlite3_bind_text(stmt, 1, Name, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, PhoneNumber, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, Salesman, -1, SQLITE_STATIC);
  *ErrMsg = sqlite3_step(stmt);
  (int)*ErrMsg;
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("\nError Performing Operation.\n");
  } else {
    printf("\nNew Customer Added Successfully.\n");
  }
  *ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("Error: %s\n", sqlite3_errmsg(db));
  }
  free(ErrMsg);
  free(Name);
  free(PhoneNumber);
  free(Salesman);
  return;
}

void AddNewSalesman(sqlite3 *db) {
  char *ErrMsg = malloc(sizeof(char));
  char *sql =
      "INSERT INTO Salesman (SalesmanName)\
  VALUES ((?));";
  char *SalesmanName = malloc(sizeof(char) * 50);

  puts("\n---- Add a New Salesman ----\n");
  printf("Enter the Salesman's Name: ");
  fgets(SalesmanName, 50, stdin);
  CleanupData(SalesmanName);

  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  sqlite3_bind_text(stmt, 1, SalesmanName, -1, SQLITE_STATIC);

  *ErrMsg = sqlite3_step(stmt);
  (int)*ErrMsg;
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("\nError Performing Operation.\n");
  } else {
    printf("\nNew Salesman Added Successfully.\n");
  }
  *ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("Error: %s\n", sqlite3_errmsg(db));
  }
  free(ErrMsg);
  free(SalesmanName);
  return;
}

void AddNewMechanic(sqlite3 *db) {
  char *ErrMsg = malloc(sizeof(char));
  char *sql =
      "INSERT INTO Mechanic (MechanicName, AssignedWork)\
  VALUES ((?), (?));";
  char *MechanicName = malloc(sizeof(char) * 50);
  char *AssignedWork = malloc(sizeof(char) * 20);

  puts("\n---- Add a New Mechanic ----\n");
  printf("Enter the Mechanic's Name: ");
  fgets(MechanicName, 50, stdin);
  CleanupData(MechanicName);
  printf("Enter 0 if the mechanic has no work assigned.\n");
  printf("Enter the Assigned Work ID: ");
  fgets(AssignedWork, 20, stdin);

  while (!isdigit(*AssignedWork)) {
    printf("Please Enter a Valid Work ID: ");
    fgets(AssignedWork, 20, stdin);
  }
  CleanupData(AssignedWork);

  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  sqlite3_bind_text(stmt, 1, MechanicName, -1, SQLITE_STATIC);

  if (*AssignedWork == '0') {
    sqlite3_bind_null(stmt, 2);
  } else {
    sqlite3_bind_text(stmt, 2, AssignedWork, -1, SQLITE_STATIC);
  }

  *ErrMsg = sqlite3_step(stmt);
  (int)*ErrMsg;
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("\nError Performing Operation.\n");
  } else {
    printf("\nNew Mechanic Added Successfully.\n");
  }
  *ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("Error: %s\n", sqlite3_errmsg(db));
  }
  free(ErrMsg);
  free(MechanicName);
  return;
}

void AddNewWorkOrder(sqlite3 *db) {
  char *ErrMsg = malloc(sizeof(char));
  char *sql =
      "INSERT INTO WorkOrder (PriceQuote, WorkDetails)\
  VALUES ((?), (?));";
  // Enter a NUMERIC value in PriceQuote
  char *PriceQuote = malloc(sizeof(char) * 20);
  char *WorkDetails = malloc(sizeof(char) * 225);

  puts("\n---- Add a New Work Order ----\n");
  printf("Enter the Quoted Price: ");
  fgets(PriceQuote, 20, stdin);
  // loop if user doesn't enter a number
  while (!isdigit(*PriceQuote)) {
    printf("Please Enter a Valid Price: ");
    fgets(PriceQuote, 20, stdin);
  }
  CleanupData(PriceQuote);

  printf("Optional field, Enter 0 if there are no Work Details.\n");
  printf("Enter the Work Details (Max 220 Characters): ");
  fgets(WorkDetails, 225, stdin);
  CleanupData(WorkDetails);

  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  sqlite3_bind_text(stmt, 1, PriceQuote, -1, SQLITE_STATIC);

  if (*WorkDetails == '0') {
    sqlite3_bind_null(stmt, 2);
  } else {
    sqlite3_bind_text(stmt, 2, WorkDetails, -1, SQLITE_STATIC);
  }

  *ErrMsg = sqlite3_step(stmt);
  (int)*ErrMsg;
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("\nError Performing Operation.\n");
  } else {
    printf("\nWork Order Added Successfully.\n");
  }
  *ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
  if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
    printf("Error: %s\n", sqlite3_errmsg(db));
  }

  free(ErrMsg);
  free(PriceQuote);
  free(WorkDetails);
  return;
}

void RemoveField(sqlite3 *db) {
  char *ErrMsg = malloc(sizeof(char));
  char *ID = malloc(sizeof(char) * 30);
  char *sql = malloc(sizeof(char) * 50);

  int choice = 0;
  do {
    puts("\n---- Remove a Field ----\n");
    puts("What would you like to remove?");
    puts("1. Remove a Customer");
    puts("2. Remove a Salesman");
    puts("3. Remove a Mechanic");
    puts("4. Remove a Work Order");
    puts("5. Remove a Vehicle");
    puts("6. Return to Main Menu");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
      case 1:
        sql = "DELETE FROM Customer WHERE CustomerID = (?);";
        printf("Enter the Customer ID to remove: ");
        fgets(ID, 20, stdin);

        while (!isdigit(*ID)) {
          printf("Please Enter a Valid Customer ID: ");
          fgets(ID, 20, stdin);
        }

        sqlite3_stmt *stmt;
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_text(stmt, 1, ID, -1, SQLITE_STATIC);
        *ErrMsg = sqlite3_step(stmt);
        (int)*ErrMsg;
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError Performing Operation.\n");
        } else {
          printf("\nCustomer Removed Successfully.\n");
        }
        *ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError performing operation.\n");
        }
        break;

      case 2:
        sql = "DELETE FROM Salesman WHERE SalesmanID = (?);";
        printf("Enter the Salesman ID to remove: ");
        fgets(ID, 20, stdin);

        while (!isdigit(*ID)) {
          printf("Please Enter a Valid Salesman ID: ");
          fgets(ID, 20, stdin);
        }

        sqlite3_stmt *stmt2;
        sqlite3_prepare_v2(db, sql, -1, &stmt2, NULL);
        sqlite3_bind_text(stmt2, 1, ID, -1, SQLITE_STATIC);
        *ErrMsg = sqlite3_step(stmt2);
        (int)*ErrMsg;
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError Performing Operation.\n");
        } else {
          printf("\nSalesman Removed Successfully.\n");
        }
        *ErrMsg = (int)sqlite3_finalize(stmt2) * sizeof(int);
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError performing operation.\n");
        }
        break;

      case 3:
        sql = "DELETE FROM Mechanic WHERE MechanicID = (?);";
        printf("Enter the Mechanic ID to remove: ");
        fgets(ID, 20, stdin);

        while (!isdigit(*ID)) {
          printf("Please Enter a Valid Mechanic ID: ");
          fgets(ID, 20, stdin);
        }

        sqlite3_stmt *stmt3;
        sqlite3_prepare_v2(db, sql, -1, &stmt3, NULL);
        sqlite3_bind_text(stmt3, 1, ID, -1, SQLITE_STATIC);
        *ErrMsg = sqlite3_step(stmt3);
        (int)*ErrMsg;
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError Performing Operation.\n");
        } else {
          printf("\nMechanic Removed Successfully.\n");
        }
        *ErrMsg = (int)sqlite3_finalize(stmt3) * sizeof(int);
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError performing operation.\n");
        }
        break;
      case 4:
        sql = "DELETE FROM WorkOrder WHERE WorkOrderID = (?);";
        printf("Enter the Work Order ID to remove: ");
        fgets(ID, 20, stdin);

        while (!isdigit(*ID)) {
          printf("Please Enter a Valid Work Order ID: ");
          fgets(ID, 20, stdin);
        }

        sqlite3_stmt *stmt4;
        sqlite3_prepare_v2(db, sql, -1, &stmt4, NULL);
        sqlite3_bind_text(stmt4, 1, ID, -1, SQLITE_STATIC);
        *ErrMsg = sqlite3_step(stmt4);
        (int)*ErrMsg;
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError Performing Operation.\n");
        } else {
          printf("\nWork Order Removed Successfully.\n");
        }
        *ErrMsg = (int)sqlite3_finalize(stmt4) * sizeof(int);
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError performing operation.\n");
        }
        break;

      case 5:
        sql = "DELETE FROM Vehicle WHERE VIN = (?);";
        printf("Enter the Vehicle VIN to remove: ");
        fgets(ID, 20, stdin);

        sqlite3_stmt *stmt5;
        sqlite3_prepare_v2(db, sql, -1, &stmt5, NULL);
        sqlite3_bind_text(stmt5, 1, ID, -1, SQLITE_STATIC);
        *ErrMsg = sqlite3_step(stmt5);
        (int)*ErrMsg;
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError Performing Operation.\n");
        } else {
          printf("\nVehicle Removed Successfully.\n");
        }
        *ErrMsg = (int)sqlite3_finalize(stmt5) * sizeof(int);
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError performing operation.\n");
        }
        break;

      case 6:
        break;

      default:
        printf("\nInvalid Choice. Please try again.\n");
        break;
    }
  } while (choice < 1 || choice > 6);
  free(ErrMsg);
  free(ID);
  return;
}

void UpdateField(sqlite3 *db) {
  char *ErrMsg = malloc(sizeof(char));
  char *ID = malloc(sizeof(char) * 30);
  char *field = malloc(sizeof(char) * 255);
  char *sql = malloc(sizeof(char) * 100);
  int choice, choice2 = 0;

  do {
    puts("\n---- Update a Field ----\n");
    puts("What Table would you like to Update a Field in?");
    puts("1. Customer");
    puts("2. Salesman");
    puts("3. Mechanic");
    puts("4. Work Order");
    puts("5. Vehicle");
    puts("6. Return to Main Menu");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
      case 1:
        do {
          puts("\nWhich Field in Customer Table would you like to Update?");
          puts("1. Name");
          puts("2. PhoneNumber");
          puts("3. Salesman");
          puts("4. Return to Main Menu");
          printf("Enter your choice: ");
          scanf("%d", &choice2);
          getchar();

          switch (choice2) {
            case 1:
              sql = "UPDATE Customer SET Name = (?) WHERE CustomerID = (?);";
              printf("Enter the Customer ID to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid Customer ID: ");
                fgets(ID, 20, stdin);
              }
              printf("Enter the New Name: ");
              fgets(field, 20, stdin);
              CleanupData(field);

              sqlite3_stmt *stmt1;
              sqlite3_prepare_v2(db, sql, -1, &stmt1, NULL);
              sqlite3_bind_text(stmt1, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt1, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt1);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nCustomer Name Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt1) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError performing operation.\n");
              }
              break;
            case 2:
              sql =
                  "UPDATE Customer SET PhoneNumber = (?) WHERE CustomerID = "
                  "(?);";
              printf("Enter the Customer ID to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid Customer ID: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the New Phone Number: ");
              fgets(field, 20, stdin);
              CleanupData(field);

              sqlite3_stmt *stmt2;
              sqlite3_prepare_v2(db, sql, -1, &stmt2, NULL);
              sqlite3_bind_text(stmt2, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt2, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt2);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nCustomer Phone Number Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt2) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError performing operation.\n");
              }
              break;
            case 3:
              sql =
                  "UPDATE Customer SET Salesman = (?) WHERE CustomerID = (?);";
              printf("Enter the Customer ID to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid Customer ID: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the New Assigned SalesmanID: ");
              fgets(field, 20, stdin);
              CleanupData(field);

              while (!isdigit(*field)) {
                printf("Please Enter a Valid Salesman ID: ");
                fgets(field, 20, stdin);
              }

              sqlite3_stmt *stmt3;
              sqlite3_prepare_v2(db, sql, -1, &stmt3, NULL);
              sqlite3_bind_text(stmt3, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt3, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt3);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nAssigned Salesman Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt3) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError performing operation.\n");
              }
              break;
            case 4:
              break;
            default:
              puts("\nInvalid Choice. Please Try Again.");
              break;
          }
        } while (choice2 < 1 || choice2 > 4);
        break;

      case 2:
        sql = "UPDATE Salesman SET SalesmanName = (?) WHERE SalesmanID = (?);";
        printf("Enter the Salesman ID to Update: ");
        fgets(ID, 20, stdin);

        while (!isdigit(*ID)) {
          printf("Please Enter a Valid Salesman ID: ");
          fgets(ID, 20, stdin);
        }

        printf("Enter the New Salesman Name: ");
        fgets(field, 20, stdin);
        CleanupData(field);

        sqlite3_stmt *stmt4;
        sqlite3_prepare_v2(db, sql, -1, &stmt4, NULL);
        sqlite3_bind_text(stmt4, 1, field, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt4, 2, ID, -1, SQLITE_STATIC);
        *ErrMsg = sqlite3_step(stmt4);
        (int)*ErrMsg;
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError Performing Operation.\n");
        } else {
          printf("\nSalesman Name Updated Successfully.\n");
        }
        *ErrMsg = (int)sqlite3_finalize(stmt4) * sizeof(int);
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError performing operation.\n");
        }
        break;

      case 3:
        do {
          puts("\nWhich Field in Mechanic Table would you like to Update?");
          puts("1. Name");
          puts("2. Assigned Work");
          puts("3. Return to Main Menu");
          printf("Enter your choice: ");
          scanf("%d", &choice2);
          getchar();

          switch (choice2) {
            case 1:
              sql =
                  "UPDATE Mechanic SET MechanicName = (?) WHERE MechanicID = "
                  "(?);";
              printf("Enter the Mechanic ID to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid Mechanic ID: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the New Mechanic Name: ");
              fgets(field, 20, stdin);
              CleanupData(field);

              sqlite3_stmt *stmt5;
              sqlite3_prepare_v2(db, sql, -1, &stmt5, NULL);
              sqlite3_bind_text(stmt5, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt5, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt5);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nMechanic Name Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt5) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError performing operation.\n");
              }
              break;

            case 2:
              sql =
                  "UPDATE Mechanic SET AssignedWork = (?) WHERE MechanicID = "
                  "(?);";
              printf("Enter the Mechanic ID to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid Mechanic ID: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the New Assigned Work: ");
              fgets(field, 20, stdin);
              CleanupData(field);

              while (!isdigit(*field)) {
                printf("Please Enter a Valid Work ID: ");
                fgets(field, 20, stdin);
              }

              sqlite3_stmt *stmt6;
              sqlite3_prepare_v2(db, sql, -1, &stmt6, NULL);
              sqlite3_bind_text(stmt6, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt6, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt6);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("Assigned Work Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt6) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError performing operation.\n");
              }
              break;

            case 3:
              break;

            default:
              puts("\nInvalid Choice. Please Try Again.");
              break;
          }
        } while (choice2 < 1 || choice2 > 3);
        break;

      case 4:
        do {
          puts("\nWhich Field in WorkOrder Table would you like to Update?");
          puts("1. Quoted Price");
          puts("2. Work Details");
          puts("3. Return to Main Menu");
          printf("Enter your choice: ");
          scanf("%d", &choice2);
          getchar();

          switch (choice2) {
            case 1:
              sql =
                  "UPDATE WorkOrder SET PriceQuote = (?) WHERE WorkOrderID = "
                  "(?);";
              printf("Enter the Work Order ID to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid Work Order ID: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Price Quote: ");
              fgets(field, 20, stdin);
              CleanupData(field);

              while (!isdigit(*field)) {
                printf("Please Enter a Valid Price Quote: ");
                fgets(field, 20, stdin);
              }

              sqlite3_stmt *stmt7;
              sqlite3_prepare_v2(db, sql, -1, &stmt7, NULL);
              sqlite3_bind_text(stmt7, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt7, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt7);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nQuoted Price Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt7) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError performing operation.\n");
              }
              break;

            case 2:
              sql =
                  "UPDATE WorkOrder SET WorkDetails = (?) WHERE WorkOrderID = "
                  "(?);";
              printf("Enter the Work Order ID to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid Work Order ID: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter Updated Work Details (max 225 characters): ");
              fgets(field, 230, stdin);
              CleanupData(field);

              sqlite3_stmt *stmt8;
              sqlite3_prepare_v2(db, sql, -1, &stmt8, NULL);
              sqlite3_bind_text(stmt8, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt8, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt8);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nWork Details Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt8) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError performing operation.\n");
              }
              break;

            case 3:
              break;

            default:
              puts("\nInvalid Choice. Please Try Again.");
              break;
          }
        } while (choice2 < 1 || choice2 > 3);
        break;

      case 5:
        do {
          puts("\nWhich Field in the Vehicle Table would you like to Update?");
          puts("1. Manufacturer");
          puts("2. Model Year");
          puts("3. Name");
          puts("4. Trim level");
          puts("5. Body Type");
          puts("6. Color");
          puts("7. Mileage");
          puts("8. Assigned Salesman");
          puts("9. CustomerID");
          puts("10. MechanicID");
          puts("11. Inventory Lot Number");
          puts("12. Work Order Number");
          puts("13. Return to Main Menu");

          printf("Enter your choice: ");
          scanf("%d", &choice2);
          getchar();

          switch (choice2) {
            case 1:
              sql = "UPDATE Vehicle SET Manufacturer = (?) WHERE VIN = (?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Manufacturer: ");
              fgets(field, 50, stdin);
              CleanupData(field);

              sqlite3_stmt *stmt9;
              sqlite3_prepare_v2(db, sql, -1, &stmt9, NULL);
              sqlite3_bind_text(stmt9, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt9, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt9);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nVehicle Manufacturer Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt9) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 2:
              sql = "UPDATE Vehicle SET ModelYear = (?) WHERE VIN = (?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Model Year: ");
              fgets(field, 20, stdin);

              while (!isdigit(*field)) {
                printf("Please Enter a Model Year: ");
                fgets(field, 20, stdin);
              }
              CleanupData(field);

              sqlite3_stmt *stmt10;
              sqlite3_prepare_v2(db, sql, -1, &stmt10, NULL);
              sqlite3_bind_text(stmt10, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt10, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt10);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nVehicle Model Year Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt10) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 3:
              sql = "UPDATE Vehicle SET Name = (?) WHERE VIN = (?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Vehicle Name: ");
              fgets(field, 120, stdin);
              CleanupData(field);

              sqlite3_stmt *stmt11;
              sqlite3_prepare_v2(db, sql, -1, &stmt11, NULL);
              sqlite3_bind_text(stmt11, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt11, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt11);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nVehicle Name Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt11) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 4:
              sql = "UPDATE Vehicle SET TrimLevel = (?) WHERE VIN = (?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Trim Level: ");
              fgets(field, 35, stdin);
              CleanupData(field);

              sqlite3_stmt *stmt12;
              sqlite3_prepare_v2(db, sql, -1, &stmt12, NULL);
              sqlite3_bind_text(stmt12, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt12, 2, ID, -1, SQLITE_STATIC);

              *ErrMsg = sqlite3_step(stmt12);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nVehicle Trim Level Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt12) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 5:
              sql = "UPDATE Vehicle SET BodyType = (?) WHERE VIN = (?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Body Type: ");
              fgets(field, 35, stdin);
              CleanupData(field);

              sqlite3_stmt *stmt13;
              sqlite3_prepare_v2(db, sql, -1, &stmt13, NULL);
              sqlite3_bind_text(stmt13, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt13, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt13);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nVehicle Body Type Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt13) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 6:
              sql = "UPDATE Vehicle SET Color = (?) WHERE VIN = (?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Vehicle Color: ");
              fgets(field, 35, stdin);
              CleanupData(field);

              sqlite3_stmt *stmt14;
              sqlite3_prepare_v2(db, sql, -1, &stmt14, NULL);
              sqlite3_bind_text(stmt14, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt14, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt14);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nVehicle Color Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt14) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 7:
              sql = "UPDATE Vehicle SET Mileage = (?) WHERE VIN = (?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Vehicle Mileage: ");
              fgets(field, 35, stdin);
              CleanupData(field);

              while (!isdigit(*field)) {
                printf("Please Enter a Valid Mileage: ");
                fgets(field, 35, stdin);
              }

              sqlite3_stmt *stmt15;
              sqlite3_prepare_v2(db, sql, -1, &stmt15, NULL);
              sqlite3_bind_text(stmt15, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt15, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt15);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nVehicle Mileage Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt15) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 8:
              sql = "UPDATE Vehicle SET SalesmanID = (?) WHERE VIN = (?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Assigned Salesman ID: ");
              fgets(field, 20, stdin);

              while (!isdigit(*field)) {
                printf("Please Enter a Valid Salesman ID: ");
                fgets(field, 20, stdin);
              }
              CleanupData(field);

              sqlite3_stmt *stmt16;
              sqlite3_prepare_v2(db, sql, -1, &stmt16, NULL);
              sqlite3_bind_text(stmt16, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt16, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt16);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nVehicle Salesman ID Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt16) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 9:
              sql = "UPDATE Vehicle SET CustomerID = ? WHERE VIN = (?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Assigned Customer ID: ");
              fgets(field, 20, stdin);

              while (!isdigit(*field)) {
                printf("Please Enter a Valid Customer ID: ");
                fgets(field, 20, stdin);
              }
              CleanupData(field);

              sqlite3_stmt *stmt17;
              sqlite3_prepare_v2(db, sql, -1, &stmt17, NULL);
              sqlite3_bind_text(stmt17, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt17, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt17);
              (int)*ErrMsg;

              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nVehicle Customer ID Updated Successfully.\n");
              }

              *ErrMsg = (int)sqlite3_finalize(stmt17) * sizeof(int);

              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 10:
              sql = "UPDATE Vehicle SET MechanicID = (?) WHERE VIN = (?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Assigned Mechanic ID: ");
              fgets(field, 20, stdin);

              while (!isdigit(*field)) {
                printf("Please Enter a Valid Mechanic ID: ");
                fgets(field, 20, stdin);
              }
              CleanupData(field);

              sqlite3_stmt *stmt18;
              sqlite3_prepare_v2(db, sql, -1, &stmt18, NULL);
              sqlite3_bind_text(stmt18, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt18, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt18);
              (int)*ErrMsg;

              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf("\nVehicle Mechanic ID Updated Successfully.\n");
              }

              *ErrMsg = (int)sqlite3_finalize(stmt18) * sizeof(int);

              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 11:
              sql =
                  "UPDATE Vehicle SET InventoryLotNumber = (?) WHERE VIN = "
                  "(?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Assigned Inventory Lot Number: ");
              fgets(field, 20, stdin);

              while (!isdigit(*field)) {
                printf("Please Enter a Valid Inventory Lot Number: ");
                fgets(field, 20, stdin);
              }
              CleanupData(field);

              sqlite3_stmt *stmt19;
              sqlite3_prepare_v2(db, sql, -1, &stmt19, NULL);
              sqlite3_bind_text(stmt19, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt19, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt19);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError Performing Operation.\n");
              } else {
                printf(
                    "\nVehicle Inventory Lot Number Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt19) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 12:
              sql = "UPDATE Vehicle SET WorkOrderID = (?) WHERE VIN = (?);";
              printf("Enter the VIN of the Vehicle to Update: ");
              fgets(ID, 20, stdin);

              while (!isdigit(*ID)) {
                printf("Please Enter a Valid VIN: ");
                fgets(ID, 20, stdin);
              }

              printf("Enter the Assigned Work Order ID: ");
              fgets(field, 20, stdin);

              while (!isdigit(*field)) {
                printf("Please Enter a Valid Work Order ID: ");
                fgets(field, 20, stdin);
              }
              CleanupData(field);

              sqlite3_stmt *stmt20;
              sqlite3_prepare_v2(db, sql, -1, &stmt20, NULL);
              sqlite3_bind_text(stmt20, 1, field, -1, SQLITE_STATIC);
              sqlite3_bind_text(stmt20, 2, ID, -1, SQLITE_STATIC);
              *ErrMsg = sqlite3_step(stmt20);
              (int)*ErrMsg;
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("\nError performing operation.\n");
              } else {
                printf("\nVehicle Work Order Updated Successfully.\n");
              }
              *ErrMsg = (int)sqlite3_finalize(stmt20) * sizeof(int);
              if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
                printf("Error performing operation.\n");
              }
              break;

            case 13:
              break;

            default:
              printf("Invalid Selection. Please Try Again.\n");
              break;
          }
        } while (choice2 < 1 || choice2 > 13);
        break;

      case 6:
        break;

      default:
        printf("\nInvalid Choice. Please try again.\n");
        break;
    }
  } while (choice < 1 || choice > 6);
  free(ErrMsg);
  free(ID);
  free(field);
  return;
}

void DisplayFields(sqlite3 *db, char *sql) {
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  int col = sqlite3_column_count(stmt);
  int result = 0;
  puts("\nRetrieved Data: \n");
  for (int i = 0; i < col; i++) {
    printf("%s\t\t", sqlite3_column_name(stmt, i));
  }
  printf("\n");
  while (1) {
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
      for (int i = 0; i < col; i++) {
        printf("%s\t\t\t", sqlite3_column_text(stmt, i));
      }
      printf("\n");
    } else {
      break;
    }
  }
  sqlite3_finalize(stmt);
  return;
}

void CleanupData(char *string) {
  for (int i = 0; i < strlen(string); i++) {
    if (string[i] == '\r' || string[i] == '\n') {
      string[i] = '\0';
    }
  }
}
