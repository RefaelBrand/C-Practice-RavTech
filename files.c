#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LENGTH 50
#define FILE_NAME "employees.bin"

struct Employee {
	int id;
	char name[NAME_LENGTH];
	float salary;
	struct Employee* next;
};
typedef struct Employee Employee;
typedef struct Employee* EmployeePtr;

EmployeePtr createNewEmployee(const int id, const char* name, const float salary) {
	EmployeePtr newEmployee = (EmployeePtr)malloc(sizeof(struct Employee));
	
	if (newEmployee != NULL) {
		newEmployee->id = id;
		strcpy(newEmployee->name, name);
		newEmployee->salary = salary;
		newEmployee->next = NULL;
	}
	
	return newEmployee;
}

EmployeePtr addNewEmployee(EmployeePtr employeesList, EmployeePtr newEmployee) {
	if (employeesList != NULL) {
		EmployeePtr ptr = employeesList;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = newEmployee;
	}
	else {
		employeesList = newEmployee;
	}
	return employeesList;
}

void saveEmployeesToFile(EmployeePtr head) {
	FILE *file = fopen(FILE_NAME, "wb");
	if (!file) {
		printf("ERROR! Couldn't open file %s.\n", FILE_NAME);
		return;
	}
	
	while (head) {
		fwrite(head, sizeof(Employee), 1, file);
		head = head->next;
	}
	
	fclose(file);
}

EmployeePtr loadEmployeesFromFile() {
	EmployeePtr head = NULL;
	FILE *file = fopen(FILE_NAME, "rb");
	if (!file) {
		printf("ERROR! Couldn't read from file %s.\n", FILE_NAME);
		return head;
	}
	
	Employee newEmployee;
	while (fread(&newEmployee, sizeof(Employee), 1, file)) {
		EmployeePtr newEmployeePtr = createNewEmployee(newEmployee.id, newEmployee.name, newEmployee.salary);
		head = addNewEmployee(head, newEmployeePtr);
	}
	
	fclose(file);
	
	return head;
}

void printEmployees(EmployeePtr head) {
	printf("Employees:\n");
	while (head) {
		printf("id: %d, name: %s, salary: %f\n", head->id, head->name, head->salary);
		head = head->next;
	}
}

void readFromFile(const int index) {
	FILE *file = fopen(FILE_NAME, "rb");
	if (!file) {
		printf("ERROR! Couldn't read from file %s.\n", FILE_NAME);
		return;
	}
	
	fseek(file, index * sizeof(Employee), SEEK_SET);
	Employee employee;
	if (fread(&employee, sizeof(Employee), 1, file)) {
		printf("id: %d, name: %s, salary: %f\n", employee.id, employee.name, employee.salary);
	}
	
	fclose(file);
}

void freeList(EmployeePtr head) {
	while (head) {
		EmployeePtr toFree = head;
		head = head->next;
		free(toFree);
	}
}

// this is for question 4 ****************************************************************************************
#define NEW_FILE_NAME "employees_new.bin"

struct Employee_new {
	int id;
	char name[NAME_LENGTH];
	float salary;
	int age;
	struct Employee_new* next;
};
typedef struct Employee_new Employee_new;
typedef struct Employee_new* EmployeePtr_new;

EmployeePtr_new createNewEmployee_new(const int id, const char* name, const float salary, int age) {
	EmployeePtr_new newEmployee = (EmployeePtr_new)malloc(sizeof(Employee_new));
	
	if (newEmployee != NULL) {
		newEmployee->id = id;
		strcpy(newEmployee->name, name);
		newEmployee->salary = salary;
		newEmployee->age = age;
		newEmployee->next = NULL;
	}
	
	return newEmployee;
}

EmployeePtr_new addNewEmployee_new(EmployeePtr_new employeesList, EmployeePtr_new newEmployee) {
	if (employeesList != NULL) {
		EmployeePtr_new ptr = employeesList;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = newEmployee;
	}
	else {
		employeesList = newEmployee;
	}
	return employeesList;
}

void saveEmployeesToFile_new(EmployeePtr_new head) {
	FILE *file = fopen(NEW_FILE_NAME, "wb");
	if (!file) {
		printf("ERROR! Couldn't open file %s.\n", FILE_NAME);
		return;
	}
	
	while (head) {
		fwrite(head, sizeof(Employee_new), 1, file);
		head = head->next;
	}
	
	fclose(file);
}

void freeList_new(EmployeePtr_new head) {
	while (head) {
		EmployeePtr_new toFree = head;
		head = head->next;
		free(toFree);
	}
}

void convertOldFormatToNew() {
	EmployeePtr_new newList = NULL;
	EmployeePtr oldList = loadEmployeesFromFile();
	EmployeePtr ptr = oldList;
	while (ptr) {
		printf("what is the age of this employee?\n");
		printf("id: %d, name: %s, salary: %f\n", ptr->id, ptr->name, ptr->salary);
		int age;
		scanf("%d", &age);
		EmployeePtr_new newEmployee = createNewEmployee_new(ptr->id, ptr->name, ptr->salary, age);
		addNewEmployee_new(newList, newEmployee);
		ptr = ptr->next;
	}
	saveEmployeesToFile_new(newList);
	
	freeList(oldList);
	freeList_new(newList);
}

// end of implementation of question 4 ****************************************************************************

int main() {
	EmployeePtr employeesList = NULL;
	
	while (1) {
		printf("please enter employee name (or Q to finish): ");
		char name[50];
		scanf("%s", name);
		
		if (strcmp(name, "Q") == 0)
			break;
		
		printf("please enter employee id: ");
		int id;
		scanf("%d", &id);
		printf("please enter employee salary: ");
		float salary;
		scanf("%f", &salary);
		EmployeePtr newEmployee = createNewEmployee(id, name, salary);
		employeesList = addNewEmployee(employeesList, newEmployee);
		saveEmployeesToFile(employeesList);
	}
	
	printf("give me an index of an employee to read: ");
	int index;
	scanf("%d", &index);
	readFromFile(index);
	
	freeList(employeesList);
	
	printf("Now let's convert the old format file to the new one (that includes an age for each employee\n");
	convertOldFormatToNew();
	
	return 0;
}
