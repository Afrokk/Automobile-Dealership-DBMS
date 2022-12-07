RunDBMS: AutomobileDealershipDBMS.o CRUDFunctions.o QueryEngine.o
	gcc -o RunDBMS AutomobileDealershipDBMS.o CRUDFunctions.o QueryEngine.o -l sqlite3 

AutomobileDealershipDBMS.o: AutomobileDealershipDBMS.c CRUDFunctions.h QueryEngine.h
	gcc -c AutomobileDealershipDBMS.c -l sqlite3
	
CRUDFunctions.o: CRUDFunctions.c CRUDFunctions.h
	gcc -c CRUDFunctions.c -l sqlite3 

QueryEngine.o: QueryEngine.c QueryEngine.h
	gcc -c QueryEngine.c -l sqlite3 
