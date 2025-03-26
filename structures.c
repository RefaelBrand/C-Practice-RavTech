#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee {
	int id;
	char name[50];
	float salary;
	struct Employee *next;
};

typedef struct Employee* employeePtr;

void printEmployees() {
	printf("not implemented\n");
}

void fillOutEmployeeData(struct Employee *employee) {
	int id;
	char name[50];
	float salary;
	
	printf("please enter id:\n");
	scanf("%d", &id);
	printf("please enter name\n");
	scanf("%s", name);
	printf("please enter salary\n");
	scanf("%f", &salary);
	
	employee->id = id;
	strcpy(employee->name, name);
	employee->salary = salary;
	employee->next = NULL;
}

struct Employee* addEmp(struct Employee *head, int id, const char *name, float salary) {
	struct Employee *newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
	newEmployee->id = id;
	strcpy(newEmployee->name, name);
	newEmployee->salary = salary;
	
	if (head != NULL) {
		struct Employee* ptr = head;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = newEmployee;
	}
	else {
		head = newEmployee;
	}
	return head;
}

void printEmployee(struct Employee *employee) {
	if (!employee)
		return;

	printf("id: %d ,", employee->id);
	printf("name: %s ,", employee->name);
	printf("salary: %f\n", employee->salary);
}

struct Employee* addNewEmployee(struct Employee *head) {
	int id = 0;
	char name[50];
	float salary = 0;
	
	printf("please enter id: \n");
	scanf("%d", &id);
	printf("please enter name: \n");
	scanf("%s", name);
	printf("please enter salary: \n");
	scanf("%f", &salary);
	
	head = addEmp(head, id, name, salary);
	return head;
}

employeePtr findTopEmp(employeePtr employees) {
	if (!employees)
		return NULL;
	
	employeePtr maxEmployee = employees;
	while (employees) {
		if (employees->salary > maxEmployee->salary)
			maxEmployee = employees;
		employees = employees->next;
	}
	return maxEmployee;
}

int main() {
	struct Employee *employees = NULL;
	
	printf("please enter the number of employees\n");
	int numberOfEmployees = 0;
	scanf("%d", &numberOfEmployees);
	
	for (int i = 0; i < numberOfEmployees; i++) {
		employees = addNewEmployee(employees);
	}
	
	employeePtr maxEmployee = findTopEmp(employees);
	printf("the employee with the highest salary:\n");
	printEmployee(maxEmployee);
	
	return 0;
}