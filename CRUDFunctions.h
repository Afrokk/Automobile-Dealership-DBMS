void AddNewVehicle(sqlite3* db);
void AddNewLot(sqlite3* db);
void AddNewCustomer(sqlite3* db);
void AddNewSalesman(sqlite3* db);
void AddNewMechanic(sqlite3* db);
void AddNewWorkOrder(sqlite3* db);
void RemoveField(sqlite3* db);
void UpdateField(sqlite3* db);
void DisplayFields(sqlite3* db, char* sql);
void CleanupData(char* string);
int DisplayDataCallback(void* data, int argc, char** argv, char** ColName);

// Path: Automobile-Dealership-DBMS/CRUDFunctions.c
