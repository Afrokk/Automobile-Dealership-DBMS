#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sqlite3.h>

static int DisplayDataCallback(void *data, int argc, char **argv, char **ColName);
void AddNewVehicle(sqlite3* db);
void AddNewLot(sqlite3* db);
void AddNewCustomer(sqlite3* db);
void AddNewSalesman(sqlite3* db);
void AddNewMechanic(sqlite3* db);
void AddNewWorkOrder(sqlite3* db);
void RemoveField(sqlite3* db);

int main(int argc, char **argv) {
	sqlite3 *db;
	char *UserSelection = malloc(sizeof(char));
	int *UserSelectionInt = malloc(sizeof(int));
	char *ErrMsg = malloc(sizeof(int));
	*ErrMsg = (int)sqlite3_open_v2("AutomobileDatabase.db", &db, SQLITE_OPEN_READWRITE, NULL) * sizeof(int);

	if (*ErrMsg != SQLITE_OK) {
		printf("Error: Can't open database! %s\n", sqlite3_errmsg(db));
		return 1;
	}
	else {
		printf("Connected to the database successfully.\n");
	}
	printf("\nWelcome to the Automobile Dealership DBMS\n");
	do {
    puts("\n------ MENU ------");
	puts("\n-- CRUD Operations --");
    puts("1) Add a New Vehicle");
    puts("2) Add a New Lot in the Inventory");
	puts("3) Enter a New Customer");
	puts("4) Enter a New Salesman");
	puts("5) Enter a New Mechanic");
	puts("6) Add a New Work Order");
	puts("7) Delete a Field");
	puts("Press 0 to Exit.\n");
	printf("Plase Choose an Option from the Menu: ");
    //take integer input from the user and store it in UserSelection using fgets
	fgets(UserSelection, 20, stdin);
	while (isdigit(*UserSelection) == 0) {
		printf("\nInvalid Input. Please Enter a Valid Choice: ");
		fgets(UserSelection, 20, stdin);
	}
	*UserSelectionInt = atoi(UserSelection);

    switch(*UserSelectionInt) {
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
	case 0:
		printf("\nThank you for using the Automobile Dealership DBMS. Goodbye!\n");
		break;
    default:
        printf("\nInvalid Input. Please Enter a Valid Choice and Try Again.\n");
        break;
    }

    } while(*UserSelectionInt != 0);

	sqlite3_close(db);
	free(UserSelection);
	free(ErrMsg);
	return 0;
}

static int DisplayDataCallback(void *data, int argc, char **argv, char **ColName) {
	for(int i = 0; i<argc; i++) {       
		printf("%s = %s\n", ColName[i], argv[i]);    
	} 
	printf("\n");

	return 0;
}

void AddNewVehicle(sqlite3* db) {
	char *ErrMsg = malloc(sizeof(int));
	char* sql = "INSERT INTO Vehicle (VIN, Manufacturer, ModelYear, Name, TrimLevel, BodyType,\
	Color, Mileage, CustomerID, MechanicID, WorkOrderID, InventoryLotNumber, SalesmanID) VALUES (?,\
	?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
	//take input from the user for all the fields
	char* VIN = malloc(sizeof(char) * 25);
	char* Manufacturer = malloc(sizeof(char) * 20);
	char* ModelYear = malloc(sizeof(char) * 20);
	char* Name = malloc(sizeof(char) * 20);
	char* TrimLevel = malloc(sizeof(char) * 20);
	char* BodyType = malloc(sizeof(char) * 20);
	char* Color = malloc(sizeof(char) * 20);
	char* Mileage = malloc(sizeof(char) * 20);
	char* CustomerID = malloc(sizeof(char) * 20);
	char* MechanicID = malloc(sizeof(char) * 20);
	char* WorkOrderID = malloc(sizeof(char) * 20);
	char* InventoryLotNumber = malloc(sizeof(char) * 20);
	char* SalesmanID = malloc(sizeof(char) * 20);
	puts("\n---- Add a New Vehicle ----\n");
	printf("Enter the VIN: ");
	fgets(VIN, 20, stdin);
	printf("Enter the Manufacturer: ");
	fgets(Manufacturer, 20, stdin);
	printf("Enter the Model Year: ");
	fgets(ModelYear, 20, stdin);
	printf("Enter the Vehicle Name: ");
	fgets(Name, 20, stdin);

	printf("Optional field, Enter 0 if you don't have a Trim Level.\n");
	printf("Enter the Trim Level: ");
	fgets(TrimLevel, 20, stdin);


	printf("Enter the Body Type: ");
	fgets(BodyType, 20, stdin);
	printf("Enter the Color: ");
	fgets(Color, 20, stdin);
	printf("Enter the Mileage: ");
	fgets(Mileage, 20, stdin);

	printf("Optional field, Enter 0 if the vehicle does not belong to a customer.\n");
	printf("Enter the Customer ID: ");
	fgets(CustomerID, 20, stdin);

	printf("Optional field, Enter 0 if the vehicle does not have an assigned mechanic.\n");
	printf("Enter the Mechanic ID: ");
	fgets(MechanicID, 20, stdin);


	printf("Optional field, Enter 0 if the vehicle is not in for work.\n");
	printf("Enter the Work Order ID: ");
	fgets(WorkOrderID, 20, stdin);

	printf("Optional field, Enter 0 if the vehicle does not belong to the dealership.\n");
	printf("Enter the Inventory Lot Number: ");
	fgets(InventoryLotNumber, 20, stdin);
	
	printf("Optional field, Enter 0 if the vehicle does not have an assigned salesman.\n");
	printf("Enter the Salesman ID: ");
	fgets(SalesmanID, 20, stdin);
	
	//prepare the statement
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	//bind the values to the statement
	sqlite3_bind_text(stmt, 1, VIN, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, Manufacturer, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, ModelYear, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, Name, -1, SQLITE_STATIC);
	
	if (*TrimLevel == '0') {
		sqlite3_bind_null(stmt, 5);
	}
	else {
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
	//execute the statement
	sqlite3_step(stmt);
	//finalize the statement with error checking
	*ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
	if (*ErrMsg != SQLITE_OK) {
		printf("Error: %s\n", sqlite3_errmsg(db));
	}
	else {
		printf("Vehicle added successfully.\n");
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

void AddNewLot(sqlite3* db) {
	char* ErrMsg = malloc(sizeof(int));
	char* sql = "INSERT INTO Inventory (NumVehicles) VALUES ((?));";
	char* NumVehicles = malloc(sizeof(char) * 20);

	puts("\n---- Add a New Lot ----\n");
	printf("Enter the number of vehicles in the new Lot: ");
	fgets(NumVehicles, 20, stdin);
	while (!isdigit(*NumVehicles)) {
		printf("Please Enter a Number: ");
		fgets(NumVehicles, 20, stdin);
	}

	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, NumVehicles, -1, SQLITE_STATIC);
	sqlite3_step(stmt);

	*ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
	if (*ErrMsg != SQLITE_OK) {
		printf("Error: %s\n", sqlite3_errmsg(db));
	}
	else {
		printf("New Lot added Successfully.\n");
	}
	free(ErrMsg);
	free(NumVehicles);
	return;
}

void AddNewCustomer(sqlite3* db) {
	char* ErrMsg = malloc(sizeof(int));
	char* sql = "INSERT INTO Customer (Name, PhoneNumber, Salesman)\
	VALUES ((?), (?), (?));";
	char* Name = malloc(sizeof(char) * 50);
	char* PhoneNumber = malloc(sizeof(char) * 20);
	char* Salesman = malloc(sizeof(char) * 20);

	puts("\n---- Add a New Customer ----\n");
	printf("Enter the Customer's Name: ");
	fgets(Name, 50, stdin);
	printf("Enter the Customer's Phone Number: ");
	fgets(PhoneNumber, 20, stdin);
	//loop if user doesn't enter a number
	while (!isdigit(*PhoneNumber)) {
		printf("Please Enter a Valid Phone Number: ");
		fgets(PhoneNumber, 20, stdin);
	}
	printf("Enter the Salesman ID: ");
	fgets(Salesman, 20, stdin);
	//loop if user doesn't enter a number
	while (!isdigit(*Salesman)) {
		printf("Please Enter a Valid Salesman ID: ");
		fgets(Salesman, 20, stdin);
	}

	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, Name, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, PhoneNumber, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, Salesman, -1, SQLITE_STATIC);
	sqlite3_step(stmt);

	*ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
	if (*ErrMsg != SQLITE_OK) {
		printf("\nError: %s\n", sqlite3_errmsg(db));
	}
	else {
		printf("\nNew Customer added Successfully.\n");
	}
	free(ErrMsg);
	free(Name);
	free(PhoneNumber);
	free(Salesman);
	return;
}

void AddNewSalesman(sqlite3* db) {
	char* ErrMsg = malloc(sizeof(int));
	char* sql = "INSERT INTO Salesman (SalesmanName)\
	VALUES ((?));";
	char* SalesmanName = malloc(sizeof(char) * 50);

	puts("\n---- Add a New Salesman ----\n");
	printf("Enter the Salesman's Name: ");
	fgets(SalesmanName, 50, stdin);

	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, SalesmanName, -1, SQLITE_STATIC);
	sqlite3_step(stmt);

	*ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
	if (*ErrMsg != SQLITE_OK) {
		printf("\nError: %s\n", sqlite3_errmsg(db));
	}
	else {
		printf("\nNew Salesman added Successfully.\n");
	}
	free(ErrMsg);
	free(SalesmanName);
	return;
}

void AddNewMechanic(sqlite3* db) {
	char* ErrMsg = malloc(sizeof(int));
	char* sql = "INSERT INTO Mechanic (MechanicName, AssignedWork)\
	VALUES ((?), (?));";
	char* MechanicName = malloc(sizeof(char) * 50);
	char* AssignedWork = malloc(sizeof(char) * 20);

	puts("\n---- Add a New Mechanic ----\n");
	printf("Enter the Mechanic's Name: ");
	fgets(MechanicName, 50, stdin);
	printf("Enter 0 if the mechanic has no work assigned.\n");
	printf("Enter the Assigned Work ID: ");
	fgets(AssignedWork, 20, stdin);

	while (!isdigit(*AssignedWork)) {
		printf("Please Enter a Valid Work ID: ");
		fgets(AssignedWork, 20, stdin);
	}

	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, MechanicName, -1, SQLITE_STATIC);

	if (*AssignedWork == '0') {
		sqlite3_bind_null(stmt, 2);
	} else {
		sqlite3_bind_text(stmt, 2, AssignedWork, -1, SQLITE_STATIC);
	}

	sqlite3_step(stmt);

	*ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
	if (*ErrMsg != SQLITE_OK) {
		printf("\nError: %s\n", sqlite3_errmsg(db));
	}
	else {
		printf("\nNew Mechanic added Successfully.\n");
	}
	free(ErrMsg);
	free(MechanicName);
	return;
}

void AddNewWorkOrder(sqlite3* db) {
	char* ErrMsg = malloc(sizeof(int));
	char* sql = "INSERT INTO WorkOrder (PriceQuote, WorkDetails)\
	VALUES ((?), (?));";
	//Enter a NUMERIC value in PriceQuote
	char* PriceQuote = malloc(sizeof(char) * 20);
	char* WorkDetails = malloc(sizeof(char) * 225);

	puts("\n---- Add a New Work Order ----\n");
	printf("Enter the Quoted Price: ");
	fgets(PriceQuote, 20, stdin);
	//loop if user doesn't enter a number
	while (!isdigit(*PriceQuote)) {
		printf("Please Enter a Valid Price: ");
		fgets(PriceQuote, 20, stdin);
	}
	printf("Optional field, Enter 0 if there are no Work Details.\n");
	printf("Enter the Work Details (Max 220 Characters): ");
	fgets(WorkDetails, 225, stdin);

	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, PriceQuote, -1, SQLITE_STATIC);

	if (*WorkDetails == '0') {
		sqlite3_bind_null(stmt, 2);
	} else {
		sqlite3_bind_text(stmt, 2, WorkDetails, -1, SQLITE_STATIC);
	}
	
	sqlite3_step(stmt);

	*ErrMsg = (int)sqlite3_finalize(stmt) * sizeof(int);
	if (*ErrMsg != SQLITE_OK) {
		printf("\nError: %s\n", sqlite3_errmsg(db));
	}
	else {
		printf("\nNew Work Order added Successfully.\n");
	}
	free(ErrMsg);
	free(PriceQuote);
	free(WorkDetails);
	return;
}

void RemoveField(sqlite3* db) {
	char* ErrMsg = malloc(sizeof(int));
	
}
