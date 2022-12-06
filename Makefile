RunDBMS: AutomobileDealershipDBMS.o CRUDFunctions.o
	gcc -o RunDBMS AutomobileDealershipDBMS.o CRUDFunctions.o -l sqlite3 

AutomobileDealershipDBMS.o: AutomobileDealershipDBMS.c CRUDFunctions.h
	gcc -c AutomobileDealershipDBMS.c -l sqlite3 
	
CRUDFunctions.o: CRUDFunctions.c CRUDFunctions.h
	gcc -c CRUDFunctions.c -l sqlite3 
