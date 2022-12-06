-- CREATE DATABASE:
BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "Inventory" (
	"LotNumber"	INTEGER NOT NULL,
	"NumVehicles"	INTEGER NOT NULL,
	CONSTRAINT UK_LotNumber UNIQUE(LotNumber)
	PRIMARY KEY("LotNumber" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "Customer" (
	"CustomerID"	INTEGER NOT NULL,
	"Name"	VARCHAR(255) NOT NULL,
	"PhoneNumber"	INTEGER NOT NULL,
	"Salesman"	VARCHAR(255) NOT NULL,
	CONSTRAINT UK_CustomerID UNIQUE(CustomerID)
	CONSTRAINT UK_Name UNIQUE(Name)
	CONSTRAINT UK_PhoneNumber UNIQUE(PhoneNumber)
	CONSTRAINT FK_Customer_Salesman_2_Salesman_SalesmanID FOREIGN KEY("Salesman") REFERENCES "Salesman"("SalesmanID"),
	PRIMARY KEY("CustomerID" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "WorkOrder" (
	"WorkOrderID"	INTEGER NOT NULL,
	"PriceQuote"	NUMERIC NOT NULL,
	"WorkDetails"	TEXT DEFAULT NULL,
	CONSTRAINT UK_WorkOrderID UNIQUE(WorkOrderID)
	PRIMARY KEY("WorkOrderID" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "Mechanic" (
	"MechanicID"	INTEGER NOT NULL,
	"MechanicName"	VARCHAR(255) NOT NULL,
	"AssignedWork"	INTEGER DEFAULT NULL,
	CONSTRAINT UK_MechanicID UNIQUE(MechanicID)
	CONSTRAINT FK_Mechanic_AssignedWork_2_WorkOrder_WorkOrderID FOREIGN KEY("AssignedWork") REFERENCES "WorkOrder"("WorkOrderID"),
	PRIMARY KEY("MechanicID")
);
CREATE TABLE IF NOT EXISTS "Salesman" (
	"SalesmanID"	INTEGER NOT NULL,
	"SalesmanName"	VARCHAR(255) NOT NULL,
	CONSTRAINT UK_SalesmanID UNIQUE(SalesmanID)
	PRIMARY KEY("SalesmanID" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "Vehicle" (
	"VIN"	VARCHAR(255) NOT NULL,
	"Manufacturer"	VARCHAR(255) NOT NULL,
	"ModelYear"	INTEGER NOT NULL,
	"Name"	VARCHAR(255) NOT NULL,
	"TrimLevel"	VARCHAR(255) DEFAULT NULL,
	"BodyType"	VARCHAR(255) NOT NULL,
	"Color"	VARCHAR(255) NOT NULL,
	"Mileage"	NUMERIC NOT NULL,
	"SalesmanID"	INTEGER DEFAULT NULL,
	"CustomerID"	INTEGER DEFAULT NULL,
	"InventoryLotNumber"	INTEGER DEFAULT NULL,
	"MechanicID"	INTEGER DEFAULT NULL,
	"WorkOrderID"	INTEGER DEFAULT NULL,
	CONSTRAINT UK_VIN UNIQUE(VIN)
	CONSTRAINT FK_Vehicle_MechanicID_2_Mechanic_MechanicID FOREIGN KEY("MechanicID") REFERENCES "Mechanic"("MechanicID"),
	CONSTRAINT FK_Vehicle_InventoryLotNumber_2_Inventory_LotNumber FOREIGN KEY("InventoryLotNumber") REFERENCES "Inventory"("LotNumber"),
	CONSTRAINT FK_Vehicle_WorkOrderID_2_WorkOrder_WorkOrderID FOREIGN KEY("WorkOrderID") REFERENCES "WorkOrder"("WorkOrderID"),
	CONSTRAINT FK_Vehicle_CustomerID_2_Customer_CustomerID FOREIGN KEY("CustomerID") REFERENCES "Customer"("CustomerID"),
	CONSTRAINT FK_Vehicle_SalesmanID_2_Salesman_SalesmanID FOREIGN KEY("SalesmanID") REFERENCES "Salesman"("SalesmanID"),
	PRIMARY KEY("VIN")
);
COMMIT;

-- ADD DATA:

-- Insert Salesmen
INSERT INTO Salesman (SalesmanName) VALUES ('Joshua Smith');
INSERT INTO Salesman (SalesmanName) VALUES ('Eric Chuan');
INSERT INTO Salesman (SalesmanName) VALUES ('Hope Song');
INSERT INTO Salesman (SalesmanName) VALUES ('Emory Kang');
INSERT INTO Salesman (SalesmanName) VALUES ('Katana Zhu');

-- Insert Customers
INSERT INTO Customer (Name, PhoneNumber, Salesman) VALUES ('John Doe', '555-555-5555', 2);
INSERT INTO Customer (Name, PhoneNumber, Salesman) VALUES ('Jonathan', '555-555-1234', 1);
INSERT INTO Customer (Name, PhoneNumber, Salesman) VALUES ('Constantine', '555-555-4231', 4);
INSERT INTO Customer (Name, PhoneNumber, Salesman) VALUES ('Ali Spa', '555-123-4231', 2);
INSERT INTO Customer (Name, PhoneNumber, Salesman) VALUES ('Bo Yang', '437-123-2134', 3);

-- Insert Inventory 
INSERT INTO Inventory (NumVehicles) VALUES (5);
INSERT INTO Inventory (NumVehicles) VALUES (2);
INSERT INTO Inventory (NumVehicles) VALUES (4);
INSERT INTO Inventory (NumVehicles) VALUES (1);
INSERT INTO Inventory (NumVehicles) VALUES (6);
INSERT INTO Inventory (NumVehicles) VALUES (2);

-- Create Work Orders
INSERT INTO WorkOrder (PriceQuote, WorkDetails) VALUES (1000, 'Replace engine');
INSERT INTO WorkOrder (PriceQuote, WorkDetails) VALUES (500, 'Rotate tires');  
INSERT INTO WorkOrder (PriceQuote, WorkDetails) VALUES (200, 'Replace windshield');
INSERT INTO WorkOrder (PriceQuote, WorkDetails) VALUES (100, 'Change oil');
INSERT INTO WorkOrder (PriceQuote, WorkDetails) VALUES (300, 'Replace brakes');
INSERT INTO WorkOrder (PriceQuote, WorkDetails) VALUES (3000, 'Replace transmission');

-- Insert Mechanics
INSERT INTO Mechanic (MechanicName) VALUES ('Kenny Chen');
INSERT INTO Mechanic (MechanicName) VALUES ('Zhujing Wang');
INSERT INTO Mechanic (MechanicName, AssignedWork) VALUES ('Jenny Zhu', 2);
INSERT INTO Mechanic (MechanicName, AssignedWork) VALUES ('Ken Pong', 4);
INSERT INTO Mechanic (MechanicName, AssignedWork) VALUES ('Andrew Smith', 4);

-- Insert Vehicles
INSERT INTO Vehicle (VIN, Manufacturer, ModelYear, Name, TrimLevel, BodyType, Color, Mileage, CustomerID, MechanicID, WorkOrderID) VALUES ('1G1YY22G965100001', 'Chevrolet', 2006, 'Cobalt', 'SS', 'Sedan', 'Black', 100000, 2, 3, 2);
INSERT INTO Vehicle (VIN, Manufacturer, ModelYear, Name, TrimLevel, BodyType, Color, Mileage, InventoryLotNumber) VALUES ('1N4AL2AP9CN406388', 'Lexus', 2012, 'IS', '350', 'Sedan', 'Wine Red', 112000, 4);
INSERT INTO Vehicle (VIN, Manufacturer, ModelYear, Name, TrimLevel, BodyType, Color, Mileage, InventoryLotNumber) VALUES ('1FTFW1EV2AFB43128', 'BMW', 2019, 'M6', 'xDrive', 'Sedan', 'Formula Blue', 20000, 4);
INSERT INTO Vehicle (VIN, Manufacturer, ModelYear, Name, TrimLevel, BodyType, Color, Mileage, CustomerID, MechanicID, WorkOrderID) VALUES ('JM1FE173640124314', 'Ford', 2008, 'Fusion', 'SEL', 'Sedan', 'Black', 220000, 3, 4, 4);
INSERT INTO Vehicle (VIN, Manufacturer, ModelYear, Name, TrimLevel, BodyType, Color, Mileage, CustomerID, MechanicID, WorkOrderID) VALUES ('1HD1BMY164Y054797', 'Toyota', 2002, 'Tacoma', 'TRD', 'Pickup', 'Silver', 432000, 4, NULL, 6);
INSERT INTO Vehicle (VIN, Manufacturer, ModelYear, Name, TrimLevel, BodyType, Color, Mileage, InventoryLotNumber) VALUES ('1FDKF37G4VEB19851', 'Lexus', 2023, 'LS 500', 'F Sport', 'Sedan', 'White', 100, 1);
INSERT INTO Vehicle (VIN, Manufacturer, ModelYear, Name, TrimLevel, BodyType, Color, Mileage, InventoryLotNumber) VALUES ('3GNEC16R5XG120530', 'Mercedes-Benz', 2008, 'SLR McLaren', '', 'Coupe', 'Silver', 2300, 1);
INSERT INTO Vehicle (VIN, Manufacturer, ModelYear, Name, TrimLevel, BodyType, Color, Mileage, CustomerID, MechanicID, WorkOrderID) VALUES ('1C4BJWDG2EL256887', 'Infinity', 2012, 'G37x', 'IPL', 'Coupe', 'Black', 86000, 1, 5, 5);

-- QUERIES: 

--Displays Vehicles by Body Type (sedan/SUV/truck), using Sedan in this case.
SELECT ModelYear, Manufacturer, Name, TrimLevel, BodyType, Color, Mileage FROM Vehicle WHERE BodyType = 'Sedan';

-- Displays how many cars of a certain manufacturer are in the Inventory.
SELECT Manufacturer, COUNT(*) AS "Number" FROM Vehicle GROUP BY Manufacturer;

-- Lists vehicles that need work and display the WorkDetails.
SELECT ModelYear, Manufacturer, Name, WorkDetails FROM Vehicle, WorkOrder WHERE Vehicle.WorkOrderID = WorkOrder.WorkOrderID;

-- Shows Mechanics with assigned work and the details of the work.
SELECT MechanicName, WorkDetails FROM Mechanic, WorkOrder WHERE Mechanic.AssignedWork = WorkOrder.WorkOrderID;

-- Lists all vehicles that have been serviced by a specific mechanic.
SELECT MechanicName, ModelYear, Manufacturer, Name FROM Mechanic, Vehicle WHERE Mechanic.MechanicID = Vehicle.MechanicID;

-- Lists the total number of vehicles in the Inventory.
SELECT SUM(NumVehicles) AS 'Total Vehicles in Inventory' FROM Inventory;

-- Lists customer and the details of the vehicle they own.
SELECT Customer.Name AS CustomerName, Vehicle.ModelYear, Vehicle.Manufacturer, Vehicle.Name AS VehicleName FROM Customer, Vehicle WHERE Customer.CustomerID = Vehicle.CustomerID;

-- Displays Customer, their car, the work that their car requires and display the price quoted to them.
SELECT Customer.Name AS CustomerName, Vehicle.ModelYear, Vehicle.Manufacturer, Vehicle.Name AS VehicleName, WorkDetails, PriceQuote FROM Customer, Vehicle, WorkOrder WHERE Customer.CustomerID = Vehicle.CustomerID AND Vehicle.WorkOrderID = WorkOrder.WorkOrderID;

-- Displays average mileage of vehicles that are in for service, the total number of vehicles in for service and display sum of the quoted prices.
SELECT AVG(Mileage) AS 'Average Mileage', COUNT(*) AS 'Total Vehicles in for Service', SUM(PriceQuote) AS 'Total PriceQuote ($)' FROM Vehicle, WorkOrder WHERE Vehicle.WorkOrderID = WorkOrder.WorkOrderID;

-- Shows total number of vehicles in shop.
SELECT COUNT(*) AS 'Total Vehicles in Shop' FROM Vehicle;

-- Shows total number of vehicles in Dealership Inventory.
SELECT SUM(NumVehicles) AS 'Total Vehicles in Inventory' FROM Inventory;

-- Shows vehicles that have work orders but no assigned mechanic. Also shows the work details and free mechanics that could be assigned to the work.
SELECT ModelYear, Manufacturer, Name, WorkDetails, group_concat(MechanicName) AS FreeMechanics FROM Vehicle, WorkOrder, Mechanic WHERE Vehicle.WorkOrderID = WorkOrder.WorkOrderID AND Vehicle.MechanicID IS NULL AND Mechanic.AssignedWork IS NULL;
