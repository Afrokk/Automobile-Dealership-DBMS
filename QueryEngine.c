#include <ctype.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "QueryEngine.h"
#include "CRUDFunctions.h"

void QueryEngine(sqlite3 *db) {
  char *ErrMsg = malloc(sizeof(char));
  char *ErrArg = malloc(sizeof(char));
  char *sql = malloc(sizeof(char) * 100);
  char *field = malloc(sizeof(char) * 50);
  int choice = 0;

  do {
    puts("\n------ QUERY MENU ------");
    puts("1. Display Vehicles by Specific Body Type");
    puts("2. Display Number of Vehicles by Manufacturer");
    puts("3. List Vehicles in the Workshop and their Work Orders");
    puts("4. List Mechanics and their assigned tasks.");
    puts("5. List Mechanics and the Vehicles they worked on.");
    puts("6. List Total Number of Vehicles in the Inventory.");
    puts("7. Display Customers with their Vehicle Details.");
    puts(
        "8. Display Workshop Customers, their Vehicle Details and Quoted "
        "Price.");
    puts("9. Display Average Mileage of Vehicles in the Shop.");
    puts("10. Display Total Number of Vehicles in the Shop.");
    puts("11. List Number of Vehicles in the Dealership.");
    puts("12. Display Cars Waiting for Work.");
    puts("0. Return to Main Menu");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
      case 1:
        sql =
            "SELECT ModelYear, Manufacturer, Name, TrimLevel, BodyType,\
        Color FROM Vehicle WHERE BodyType = (?);";
        printf("Enter the Body Type: ");
        fgets(field, 50, stdin);
        field[strlen(field) - 1] = '\0';

        sqlite3_stmt *stmt;
        sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        sqlite3_bind_text(stmt, 1, field, -1, SQLITE_STATIC);

        printf("\nHere are all the %s Vehicles:\n\n", field);

        while ((*ErrMsg = sqlite3_step(stmt)) == SQLITE_ROW) {
          printf("%s  %s  %s  %s  %s  %s\n", sqlite3_column_text(stmt, 0),
                 sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2),
                 sqlite3_column_text(stmt, 3), sqlite3_column_text(stmt, 4),
                 sqlite3_column_text(stmt, 5));
        }
        (int)*ErrMsg;
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError Performing Operation.\n");
        } else {
          printf("\nQuery Executed Successfully.\n");
        }

        *ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
        if (*ErrMsg != SQLITE_OK && ((int)*ErrMsg) != SQLITE_DONE) {
          printf("\nError performing operation: %s\n", sqlite3_errmsg(db));
        }
        break;

      case 2:
        sql =
            "SELECT Manufacturer, COUNT(*) AS NumVehicles FROM Vehicle\
            GROUP BY Manufacturer;";

        *ErrMsg = sqlite3_exec(db, sql, DisplayDataCallback, 0, &ErrArg);

        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrArg);
          sqlite3_free(ErrArg);
        }
        break;

      case 3:
        sql =
            "SELECT ModelYear, Manufacturer, Name, WorkDetails FROM\
            Vehicle, WorkOrder WHERE Vehicle.WorkOrderID =\
            WorkOrder.WorkOrderID;";

        *ErrMsg = sqlite3_exec(db, sql, DisplayDataCallback, 0, &ErrArg);

        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrArg);
          sqlite3_free(ErrArg);
        }
        break;

      case 4:
        sql =
            "SELECT MechanicName, WorkDetails FROM Mechanic, WorkOrder\
        WHERE Mechanic.AssignedWork = WorkOrder.WorkOrderID;";

        *ErrMsg = sqlite3_exec(db, sql, DisplayDataCallback, 0, &ErrArg);

        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrArg);
          sqlite3_free(ErrArg);
        }
        break;

      case 5:
        sql =
            "SELECT MechanicName, ModelYear, Manufacturer, Name\
        FROM Mechanic, Vehicle WHERE Mechanic.MechanicID =\
        Vehicle.MechanicID;";

        *ErrMsg = sqlite3_exec(db, sql, DisplayDataCallback, 0, &ErrArg);

        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrArg);
          sqlite3_free(ErrArg);
        }
        break;

      case 6:
        sql =
            "SELECT SUM(NumVehicles) AS 'Total Vehicles in Inventory' FROM "
            "Inventory;";

        *ErrMsg = sqlite3_exec(db, sql, DisplayDataCallback, 0, &ErrArg);

        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrArg);
          sqlite3_free(ErrArg);
        }
        break;

      case 7:
        sql =
            "SELECT Customer.Name AS CustomerName, Vehicle.ModelYear,\
        Vehicle.Manufacturer, Vehicle.Name AS VehicleName FROM\
        Customer, Vehicle WHERE\
        Customer.CustomerID = Vehicle.CustomerID;";

        *ErrMsg = sqlite3_exec(db, sql, DisplayDataCallback, 0, &ErrArg);

        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrArg);
          sqlite3_free(ErrArg);
        }
        break;

      case 8:
        sql =
            "SELECT Customer.Name AS CustomerName, Vehicle.ModelYear,\
        Vehicle.Manufacturer, Vehicle.Name AS VehicleName,\
        WorkDetails, PriceQuote FROM Customer, Vehicle,\
        WorkOrder WHERE Customer.CustomerID = Vehicle.CustomerID\
        AND Vehicle.WorkOrderID = WorkOrder.WorkOrderID;";

        *ErrMsg = sqlite3_exec(db, sql, DisplayDataCallback, 0, &ErrArg);

        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrArg);
          sqlite3_free(ErrArg);
        }
        break;

      case 9:
        sql =
            "SELECT AVG(Mileage) AS 'Average Mileage', COUNT(*) AS\
        'Total Vehicles in for Service', SUM(PriceQuote) AS\
        'Total PriceQuote ($)' FROM Vehicle, WorkOrder WHERE\
        Vehicle.WorkOrderID = WorkOrder.WorkOrderID;";

        *ErrMsg = sqlite3_exec(db, sql, DisplayDataCallback, 0, &ErrArg);

        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrArg);
          sqlite3_free(ErrArg);
        }
        break;

      case 10:
        sql = "SELECT COUNT(*) AS 'Total Vehicles in Shop' FROM Vehicle;";
        *ErrMsg = sqlite3_exec(db, sql, DisplayDataCallback, 0, &ErrArg);

        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrArg);
          sqlite3_free(ErrArg);
        }
        break;

      case 11:
        sql =
            "SELECT SUM(NumVehicles) AS 'Total Vehicles in Inventory'\
        FROM Inventory;";
        *ErrMsg = sqlite3_exec(db, sql, DisplayDataCallback, 0, &ErrArg);

        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrArg);
          sqlite3_free(ErrArg);
        }
        break;

      case 12:
        sql =
            "SELECT ModelYear, Manufacturer, Name, WorkDetails,\
        group_concat(MechanicName) AS FreeMechanics FROM Vehicle,\
        WorkOrder, Mechanic WHERE Vehicle.WorkOrderID =\
        WorkOrder.WorkOrderID AND Vehicle.MechanicID IS NULL\
        AND Mechanic.AssignedWork IS NULL;";

        printf("\nVehicles Waiting for Work: \n\n");

        *ErrMsg = sqlite3_exec(db, sql, DisplayDataCallback, 0, &ErrArg);

        if (*ErrMsg != SQLITE_OK) {
          printf("SQL error: %s\n", ErrArg);
          sqlite3_free(ErrArg);
        }
        break;

      default:
        printf("\nPlease Enter a Valid Choice: \n");
    }
  } while (choice != 0);
}
