//Hong Wei Phang G00388774 - Procedual Project 2022
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	int companyId;
	char name[30];
	char country[30];
	int year;
	char email[30];
	char contactName[30];
	int lastOrder;
	int numOfEmployees;
	float averageOrder;
	int vat;
	int averageTurnOver;
	int numOfStaff;
	int areaOfSales;

	struct node* NEXT;
}nodeT;

typedef struct LoginNode
{
	char username[50];       
	char password[50];       
	struct LoginNode* next;  
} LoginNodeT;

void main();

//all the function
int checkLogin(); // to check username and password , let password show * on screen
void addAtTheStartList(struct node** top, int newId); // if head pointer is null (empty linked list) then add at the start list
void addAtTheEnd(nodeT* top, int newId); // add at end of the linked list if not empty
int search(nodeT* top,int searchVal); //function to make sure crn is unique
void displayList(nodeT* top); //display all the node in the list
void displayClient(nodeT* top, int searchId); // let user input crn and display the client
void updateClient(nodeT* top, int searchId); // let user input crn and update the client details
int deleteClient(nodeT** top, int searchId); // let user input crn and delete the client
void criteriaAreaOfCompanySales(nodeT* top, int selection); // to generate a statistic based on area of company sales
void criteriaNumberOfEmployees(nodeT* top, int selection); // to generate a statistic based on number of staff
void listInOrder(nodeT** top);
void writeReport(nodeT* top); //create a report.txt and write all the clients and statistic into the file
void writeFile(nodeT* top); // write all user data into clients.txt to save 
struct node* readFile(); // read the saved data and create the list

void main()
{
	FILE* fp;
	struct nodeT* headPtr = NULL;
	nodeT* newNode;
	nodeT* temp;
	int found;
	int searchId = 0;
	int choice;
	int option;
	int result;
	int checkNewId;
	int selection;

	if (checkLogin() == 0)//if login detail correct then will start the programme
	{
		headPtr = readFile();
		system("cls");
		printf("======================================\n");
		printf("XYX Medical Supplier Ltd\n");
		printf("client record application\n");
		printf("======================================\n\n");

		printf("Please enter 1 to add a client\n");
		printf("Please enter 2 to display all the client\n");
		printf("Please enter 3 to display client details\n");
		printf("Please enter 4 to update a client details\n");
		printf("Please enter 5 to delete client\n");
		printf("Please enter 6 to generate statistics (a - c) based on the user selecting one of the criteria listed in I - II\n");
		printf("\tA. Less than 1 Million Euro\n\tB. Less than 10 Million Euro\n\tC. Over 10 Million Euro\n");
		printf("\tI. Area of Company Sales\n\tII.Number of Employees\n"); 
		printf("Please enter 7 to print all client details into a report file\n");
		printf("Please enter 8 to list all the clients in order of their last average turnover\n");
		printf("Please enter -1 to exit\n");
		scanf("%d", &choice);

		while (choice != -1)
		{
			if (choice == 1)
			{
				printf("\nPlease enter the Company Registration Number\n");
				scanf("%d", &checkNewId);

				result = search(headPtr, checkNewId);

				while (result == 0)
				{
					printf("Sorry the Company Registration Number is not available. Please enter again\n");
					scanf("%d", &checkNewId);
					result = search(headPtr, checkNewId);
				}

				if (headPtr == NULL)
				{
					addAtTheStartList(&headPtr, checkNewId);
				}
				else
				{
					addAtTheEnd(headPtr,checkNewId);
				}										
			}
			else if (choice == 2)
			{
				displayList(headPtr);
			}
			else if (choice == 3)
			{
				printf("\nPlease enter the Company Registration Number you wish to display\n");
				scanf("%d", &searchId);

				displayClient(headPtr, searchId);
			}
			else if (choice == 4)
			{
				printf("\nPlease enter the Company Registration Number you wish to update\n");
				scanf("%d", &searchId);

				displayClient(headPtr, searchId);
				updateClient(headPtr, searchId);
			}
			else if (choice == 5)
			{
				printf("\nPlease enter the Company Registration Number you wish to delete\n");
				scanf("%d", &searchId);

				if (deleteClient(&headPtr, searchId) == 0)
				{
					printf("Sorry the Company Registration Number does not exsist\n");
				}
			}
			else if (choice == 6)
			{
				printf("\nYou have chosen the option 6 to generate statistics, please selected if you want it completed by 1. Area of Company Sales or 2. Number of Employees\n");
				scanf("%d", &option);

				if (option == 1)
				{
					printf("Next Selection is 1. ICT 2. Medical Devices 3. Other Area\n");
					scanf("%d", &selection);

					criteriaAreaOfCompanySales(headPtr, selection);
				}
				else if (option == 2)
				{
					printf("Next Selection is 1. Less than 10 2. Less than 100 3. More than 100\n");
					scanf("%d", &selection);

					criteriaNumberOfEmployees(headPtr, selection);
				}
			}
			else if (choice == 7)
			{
				writeReport(headPtr);
			}
			else if (choice == 8)
			{

			}
 
			printf("\nPlease enter 1 to add a client\n");
			printf("Please enter 2 to display all the client\n");
			printf("Please enter 3 to display client details\n");
			printf("Please enter 4 to update a client details\n");
			printf("Please enter 5 to delete client\n");
			printf("Please enter 6 to generate statistics (a - c) based on the user selecting one of the criteria listed in I - II\n");
			printf("\tA. Less than 1 Million Euro\n\tB. Less than 10 Million Euro\n\tC. Over 10 Million Euro\n");
			printf("\tI. Area of Company Sales\n\tII.Number of Employees\n");
			printf("Please enter 7 to print all client details into a report file\n");
			printf("Please enter 8 to list all the clients in order of their last average turnover\n");
			printf("Please enter -1 to exit\n");
			scanf("%d", &choice);

		}//end of while choice != -1

		writeFile(headPtr);

	}//end of if statement for correct login details

}//end of main

int checkLogin()
{
	//variables for login page.
	LoginNodeT* login = NULL;
	FILE* fp;
	char inputUsername[30];//to store user input
	char inputPass[30];//to store input password.
	int i = 0;
	char a;//a Temp char

	printf("Please enter username:\n");
	scanf("%s", inputUsername);

	printf("Please enter password:\n");

	while (i <= 5)
	{
		for (i = 0;;)//infinite loop
		{
			a = getch();//stores char typed in a
			if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
				//check if a is numeric or alphabet
			{
				inputPass[i] = a;//stores a in pass
				++i;
				printf("*");
			}
			if (a == '\b' && i >= 1)//if user typed backspace
				//i should be greater than 1.
			{
				printf("\b \b");
				--i;
			}
			if (a == '\r')//if enter is pressed
			{
				inputPass[i] = '\0';//null means end of string
				printf("\n");
				break;//break the loop
			}
		}

		if (i <= 5)
		{
			printf("Mininum 6 digits needed.\nEnter Again:\n");
		}
	}


	//Read in the contents of the file....
	fp = fopen("login.txt", "r");
	LoginNodeT* user = NULL;

	if (fp == NULL)
	{
		printf("Sorry the file could not be opened for reading\n");
	}
	else
	{
		while (!feof(fp))
		{
			LoginNodeT* newNode = (LoginNodeT*)malloc(sizeof(LoginNodeT));
			fscanf(fp, "%s %s\n", newNode->username, newNode->password);
			newNode->next = NULL;

			if (login == NULL)
			{
				login = newNode;
				user = login;
			}
			else
			{
				user->next = newNode;
			}
			user = newNode;
		}
		fclose(fp);
	}

	for (LoginNodeT* node = login; node != NULL; node = node->next)
	{
		if (strcmp(node->username, inputUsername) == 0 && strcmp(node->password, inputPass) == 0)
		{
			return 0;
		}
		else
		{
			printf("Wrong user password\n");
			return 1;
		}
	}

}

void addAtTheStartList(struct node** top, int newId)
{
	struct node* newNode;
	const char checkEmail[30];
	int validationEmail = 0;
	int checkOption;

	newNode = (struct node*)malloc(sizeof(struct node));

	newNode->companyId = newId;

	printf("Please enter the Company Name\n");
	scanf("%s", newNode->name);
	printf("Please enter the Company Country\n");
	scanf("%s", newNode->country);
	printf("Please enter the Year Company Founded\n");
	scanf("%d", &newNode->year);

	do {
		printf("Please enter the Email Address (must contain an @, a full stop and a .com)\n");
		scanf("%s", checkEmail);

		char* atIndex = strstr(checkEmail, "@");
		char* comIndex = strstr(checkEmail, ".com");

		if(atIndex != NULL && comIndex != NULL && comIndex > atIndex)
		{
			validationEmail = 1;
		}
		else
		{
			printf("Invalid Email Address (must contain an @, a full stop and a .com)\n");
		}
	} while (validationEmail == 0);

	strcpy(newNode->email, checkEmail);

	printf("Please enter the Company Contact Name\n");
	scanf("%s", newNode->contactName);
	printf("Please enter the Last Order\n");
	scanf("%d", &newNode->lastOrder);
	printf("Please enter the Number of Employees\n");
	scanf("%d", &newNode->numOfEmployees);
	printf("Please enter the Average Annual Order\n");
	scanf("%f", &newNode->averageOrder);
	printf("Is the Client Vat Registered?\nPress 1 - yes\nPress 2 - no\n");
	scanf("%d", &checkOption);

	while (!(checkOption <= 2 && checkOption >= 1))
	{
		printf("Please select 1 or 2\n");
		scanf("%d", &checkOption);
	}

	newNode->vat = checkOption;

	printf("What are the Clients Average Turnover?\nPress 1 - Less than 1 Million Euro\nPress 2 - Less than 10 Million Euro\nPress 3 - Over 10 Million Euro\n");
	scanf("%d", &checkOption);

	while (!(checkOption <= 3 && checkOption >= 1))
	{
		printf("Please select 1 or 2 or 3\n");
		scanf("%d", &checkOption);
	}

	newNode->averageTurnOver = checkOption;

	printf("How many staff are employed in the Client Company?\nPress 1 - Less than 10\nPress 2 - Less than 100\nPress 3 - Over 100\n");
	scanf("%d", &checkOption);

	while (!(checkOption <= 3 && checkOption >= 1))
	{
		printf("Please select 1 or 2 or 3\n");
		scanf("%d", &checkOption);
	}

	newNode->numOfStaff = checkOption;

	printf("Which area of sales is the company?\nPress 1 -ICT\nPress 2 - Medical Devices\nPress 3 - Other area\n");
	scanf("%d", &checkOption);

	while (!(checkOption <= 3 && checkOption >= 1))
	{
		printf("Please select 1 or 2 or 3\n");
		scanf("%d", &checkOption);
	}

	newNode->areaOfSales = checkOption;

	newNode->NEXT = *top;
	*top = newNode;
}

void addAtTheEnd(nodeT* top, int newId)
{
	struct node* temp;
	struct node* newNode;
	const char checkEmail[30];
	int validationEmail = 0;
	int checkOption;

	temp = top;

	while (temp->NEXT != NULL)
	{
		temp = temp->NEXT;
	}


	newNode = (struct node*)malloc(sizeof(struct node));

	newNode->companyId = newId;

	printf("Please enter the Company Name\n");
	scanf("%s", newNode->name);
	printf("Please enter the Company Country\n");
	scanf("%s", newNode->country);
	printf("Please enter the Year Company Founded\n");
	scanf("%d", &newNode->year);

	do {
		printf("Please enter the Email Address (must contain an @, a full stop and a .com)\n");
		scanf("%s", checkEmail);

		char* atIndex = strstr(checkEmail, "@");
		char* comIndex = strstr(checkEmail, ".com");

		if (atIndex != NULL && comIndex != NULL && comIndex > atIndex)
		{
			validationEmail = 1;
		}
		else
		{
			printf("Invalid Email Address (must contain an @, a full stop and a .com)\n");
		}
	} while (validationEmail == 0);

	strcpy(newNode->email, checkEmail);

	printf("Please enter the Company Contact Name\n");
	scanf("%s", newNode->contactName);
	printf("Please enter the Last Order\n");
	scanf("%d", &newNode->lastOrder);
	printf("Please enter the Number of Employees\n");
	scanf("%d", &newNode->numOfEmployees);
	printf("Please enter the Average Annual Order\n");
	scanf("%f", &newNode->averageOrder);
	printf("Is the Client Vat Registered?\nPress 1 - yes\nPress 2 - no\n");
	scanf("%d", &checkOption);

	while (!(checkOption <= 2 && checkOption >= 1))
	{
		printf("Please select 1 or 2\n");
		scanf("%d", &checkOption);
	}

	newNode->vat = checkOption;

	printf("What are the Clients Average Turnover?\nPress 1 - Less than 1 Million Euro\nPress 2 - Less than 10 Million Euro\nPress 3 - Over 10 Million Euro\n");
	scanf("%d", &checkOption);

	while (!(checkOption <= 3 && checkOption >= 1))
	{
		printf("Please select 1 or 2 or 3\n");
		scanf("%d", &checkOption);
	}

	newNode->averageTurnOver = checkOption;

	printf("How many staff are employed in the Client Company?\nPress 1 - Less than 10\nPress 2 - Less than 100\nPress 3 - Over 100\n");
	scanf("%d", &checkOption);

	while (!(checkOption <= 3 && checkOption >= 1))
	{
		printf("Please select 1 or 2 or 3\n");
		scanf("%d", &checkOption);
	}

	newNode->numOfStaff = checkOption;

	printf("Which area of sales is the company?\nPress 1 -ICT\nPress 2 - Medical Devices\nPress 3 - Other area\n");
	scanf("%d", &checkOption);

	while (!(checkOption <= 3 && checkOption >= 1))
	{
		printf("Please select 1 or 2 or 3\n");
		scanf("%d", &checkOption);
	}

	newNode->areaOfSales = checkOption;


	temp->NEXT = newNode;
	newNode->NEXT = NULL;
}

int search(nodeT* top, int searchVal)
{
	struct node* temp = top;
	int found = -1;

	while (temp != NULL)
	{
		if (temp->companyId == searchVal)
		{
			found = 0;
		}

		temp = temp->NEXT;
	}

	return found;
}

void displayList(nodeT* top)
{
	struct node* temp;

	temp = top;

	while (temp != NULL)
	{
		printf("\n-------------------------------------\n");
		printf("Company Registration Number: %d\n",temp->companyId);
		printf("Company Name: %s\n", temp->name);
		printf("Company Country: %s\n", temp->country);
		printf("Year Company Founded: %d\n", temp->year);
		printf("Email Address: %s\n", temp->email);
		printf("Company Contact Name: %s\n", temp->contactName);
		printf("Last Order: %d\n", temp->lastOrder);
		printf("Number of Employees: %d\n", temp->numOfEmployees);
		printf("Average Annual Order: %.2f\n", temp->averageOrder);
		
		if (temp->vat == 1)
		{
			printf("Client Vat Registered: Yes\n");
		}
		else if (temp->vat == 2)
		{
			printf("Client Vat Registered: No\n");
		}

		if (temp->averageTurnOver == 1)
		{
			printf("Clients Average Turnover: Less than 1 Million Euro\n");
		}
		else if (temp->averageTurnOver == 2)
		{
			printf("Clients Average Turnover: Less than 10 Million Euro\n");
		}
		else if (temp->averageTurnOver == 3)
		{
			printf("Clients Average Turnover: Over 10 Million Euro\n");
		}

		if (temp->numOfStaff == 1)
		{
			printf("Staff employed in the Client Company: Less than 10\n");
		}
		else if (temp->numOfStaff == 2)
		{
			printf("Staff employed in the Client Company: Less than 100\n");
		}
		else if (temp->numOfStaff == 3)
		{
			printf("Staff employed in the Client Company: Over 100\n");
		}

		if (temp->areaOfSales == 1)
		{
			printf("Area Of Sales: ICT\n");
		}
		else if (temp->areaOfSales == 2)
		{
			printf("Area Of Sales: Medical Devices\n");
		}
		else if (temp->areaOfSales == 3)
		{
			printf("Area Of Sales: Other area\n");
		}
		printf("-------------------------------------\n");

		temp = temp->NEXT;
	}
}

void displayClient(nodeT* top, int searchId)
{
	struct node* temp = top;
	int found = -1;

	while (temp != NULL)
	{
		if (temp->companyId == searchId)
		{
			printf("\n-------------------------------------\n");
			printf("Company Registration Number: %d\n", temp->companyId);
			printf("Company Name: %s\n", temp->name);
			printf("Company Country: %s\n", temp->country);
			printf("Year Company Founded: %d\n", temp->year);
			printf("Email Address: %s\n", temp->email);
			printf("Company Contact Name: %s\n", temp->contactName);
			printf("Last Order: %d\n", temp->lastOrder);
			printf("Number of Employees: %d\n", temp->numOfEmployees);
			printf("Average Annual Order: %.2f\n", temp->averageOrder);

			if (temp->vat == 1)
			{
				printf("Client Vat Registered: Yes\n");
			}
			else if (temp->vat == 2)
			{
				printf("Client Vat Registered: No\n");
			}

			if (temp->averageTurnOver == 1)
			{
				printf("Clients Average Turnover: Less than 1 Million Euro\n");
			}
			else if (temp->averageTurnOver == 2)
			{
				printf("Clients Average Turnover: Less than 10 Million Euro\n");
			}
			else if (temp->averageTurnOver == 3)
			{
				printf("Clients Average Turnover: Over 10 Million Euro\n");
			}

			if (temp->numOfStaff == 1)
			{
				printf("Staff employed in the Client Company: Less than 10\n");
			}
			else if (temp->numOfStaff == 2)
			{
				printf("Staff employed in the Client Company: Less than 100\n");
			}
			else if (temp->numOfStaff == 3)
			{
				printf("Staff employed in the Client Company: Over 100\n");
			}

			if (temp->areaOfSales == 1)
			{
				printf("Area Of Sales: ICT\n");
			}
			else if (temp->areaOfSales == 2)
			{
				printf("Area Of Sales: Medical Devices\n");
			}
			else if (temp->areaOfSales == 3)
			{
				printf("Area Of Sales: Other area\n");
			}

			printf("-------------------------------------\n");

			found = 0;
		}
		temp = temp->NEXT;
	}

	if (found == -1)
	{
		printf("Sorry the Company Registration Number does not exsist\n");
	}
}

void updateClient(nodeT* top, int searchId)
{
	struct node* temp = top;
	const char checkEmail[30];
	int validationEmail = 0;
	int checkOption;

	while (temp != NULL)
	{
		if (temp->companyId == searchId)
		{

			printf("Please enter the Company Name\n");
			scanf("%s", temp->name);
			printf("Please enter the Company Country\n");
			scanf("%s", temp->country);
			printf("Please enter the Year Company Founded\n");
			scanf("%d", &temp->year);

			do {
				printf("Please enter the Email Address (must contain an @, a full stop and a .com)\n");
				scanf("%s", checkEmail);

				char* atIndex = strstr(checkEmail, "@");
				char* comIndex = strstr(checkEmail, ".com");

				if (atIndex != NULL && comIndex != NULL && comIndex > atIndex)
				{
					validationEmail = 1;
				}
				else
				{
					printf("Invalid Email Address (must contain an @, a full stop and a .com)\n");
				}
			} while (validationEmail == 0);

			strcpy(temp->email, checkEmail);

			printf("Please enter the Company Contact Name\n");
			scanf("%s", temp->contactName);
			printf("Please enter the Last Order\n");
			scanf("%d", &temp->lastOrder);
			printf("Please enter the Number of Employees\n");
			scanf("%d", &temp->numOfEmployees);
			printf("Please enter the Average Annual Order\n");
			scanf("%f", &temp->averageOrder);
			printf("Is the Client Vat Registered?\nPress 1 - yes\nPress 2 - no\n");
			scanf("%d", &checkOption);

			while (!(checkOption <= 2 && checkOption >= 1))
			{
				printf("Please select 1 or 2\n");
				scanf("%d", &checkOption);
			}

			temp->vat = checkOption;

			printf("What are the Clients Average Turnover?\nPress 1 - Less than 1 Million Euro\nPress 2 - Less than 10 Million Euro\nPress 3 - Over 10 Million Euro\n");
			scanf("%d", &checkOption);

			while (!(checkOption <= 3 && checkOption >= 1))
			{
				printf("Please select 1 or 2 or 3\n");
				scanf("%d", &checkOption);
			}

			temp->averageTurnOver = checkOption;

			printf("How many staff are employed in the Client Company?\nPress 1 - Less than 10\nPress 2 - Less than 100\nPress 3 - Over 100\n");
			scanf("%d", &checkOption);

			while (!(checkOption <= 3 && checkOption >= 1))
			{
				printf("Please select 1 or 2 or 3\n");
				scanf("%d", &checkOption);
			}

			temp->numOfStaff = checkOption;

			printf("Which area of sales is the company?\nPress 1 -ICT\nPress 2 - Medical Devices\nPress 3 - Other area\n");
			scanf("%d", &checkOption);

			while (!(checkOption <= 3 && checkOption >= 1))
			{
				printf("Please select 1 or 2 or 3\n");
				scanf("%d", &checkOption);
			}

			temp->areaOfSales = checkOption;

		}
		temp = temp->NEXT;
	}
}

int deleteClient(nodeT** top, int searchId)
{
	nodeT* prev = NULL;

	for (nodeT* node = *top; node != NULL; node = node->NEXT)
	{
		// if found the company registration number
		if (node->companyId == searchId)
		{
			// delete at start if the first node are the same
			if ((*top)->companyId == searchId)
			{
				nodeT* temp = *top;
				(*top) = (*top)->NEXT;
				free(temp);
			}
			else
			{							 
				//let temp equals to the node -> NEXT before delete the node
				nodeT* temp = node->NEXT;

				//   0  |   1  |   2		 |   3
				// prev | node | node->NEXT	 | node->NEXT ->NEXT

				///////  temp  ///////
				//   2  |   3
				// temp | temp -> NEXT

				//delete the current node
				free(node);
				//   0  | NULL |
				// prev | NULL |


				//let the prev -> NEXT equals to temp 
				prev->NEXT = temp;
				//   0  |   2  |   3
				// prev | temp | temp->NEXT
			}
			return 1;//end the function and return 1 for the output
		}
		//   0  |   1  |   2
		// prev | node | node->NEXT		
		prev = node;
	}
	return 0;//if company registration number not found in the list
}

void criteriaAreaOfCompanySales(nodeT* top, int selection)
{
	struct node* temp = top;

	int statisticsA = 0;
	int statisticsB = 0;
	int statisticsC = 0;
	int total = 0;

	while (temp != NULL)
	{
		if (temp->areaOfSales == selection)
		{
			if (temp->averageTurnOver == 1)
			{
				statisticsA++;
			}
			else if (temp->averageTurnOver == 2)
			{
				statisticsB++;
			}
			else if (temp->averageTurnOver == 3)
			{
				statisticsC++;
			}

			total++;
		}

		temp = temp->NEXT;
	}

	printf("\nThe Statistic are as follows:\n");
	printf("A. Less then 1 Million Euro - %.f%%\n",((float)statisticsA/total)*100);
	printf("B. Less then 10 Million Euro - %.f%%\n", ((float)statisticsB / total*100));
	printf("C. Over 10 Million Euro - %.f%%\n", ((float)statisticsC / total*100));
}

void criteriaNumberOfEmployees(nodeT* top, int selection)
{
	struct node* temp = top;

	int statisticsA = 0;
	int statisticsB = 0;
	int statisticsC = 0;
	int total = 0;

	while (temp != NULL)
	{
		if (temp->numOfStaff == selection)
		{
			if (temp->averageTurnOver == 1)
			{
				statisticsA++;
			}
			else if (temp->averageTurnOver == 2)
			{
				statisticsB++;
			}
			else if (temp->averageTurnOver == 3)
			{
				statisticsC++;
			}

			total++;
		}

		temp = temp->NEXT;
	}

	printf("\nThe Statistic are as follows:\n");
	printf("A. Less then 1 Million Euro - %.f%%\n", ((float)statisticsA / total) * 100);
	printf("B. Less then 10 Million Euro - %.f%%\n", ((float)statisticsB / total * 100));
	printf("C. Over 10 Million Euro - %.f%%\n", ((float)statisticsC / total * 100));
}

void listInOrder(nodeT** top)
{

}

void writeReport(nodeT* top)
{
	FILE* fp = fopen("report.txt", "w");
	struct node* temp;
	temp = top;
	//variables for printing to report file
	int companyId;
	char name[30];
	char country[30];
	int year;
	char email[30];
	char contactName[30];
	int lastOrder;
	int numOfEmployees;
	float averageOrder;
	int vat;
	int averageTurnOver;
	int numOfStaff;
	int areaOfSales;


	// writing all the nodes of the linked list to the file
	while (temp != NULL)
	{
		fprintf(fp,"\n-------------------------------------\n");
		companyId = temp->companyId;
		fprintf(fp,"Company Registration Number: %d\n", companyId);
		strcpy(name, temp->name);
		fprintf(fp, "Company Registration Name: %s\n", name);
		strcpy(country, temp->country);
		fprintf(fp, "Company Registration Country: %s\n", country);
		year = temp->year;
		fprintf(fp, "Year Company Founded: %d\n", year);
		strcpy(email, temp->email);
		fprintf(fp, "Email Address: %s\n", email);
		strcpy(contactName, temp->contactName);
		fprintf(fp, "Company Contact Name: %s\n", contactName);
		lastOrder = temp->lastOrder;
		fprintf(fp, "Last Order: %d\n", lastOrder);
		numOfEmployees = temp->numOfEmployees;
		fprintf(fp, "Number of Employees: %d\n", numOfEmployees);
		averageOrder = temp->averageOrder;
		fprintf(fp, "Average Annual Order: %.2f\n", averageOrder);

		if (temp->vat == 1)
		{
			fprintf(fp,"Client Vat Registered: Yes\n");
		}
		else if (temp->vat == 2)
		{
			fprintf(fp,"Client Vat Registered: No\n");
		}

		if (temp->averageTurnOver == 1)
		{
			fprintf(fp,"Clients Average Turnover: Less than 1 Million Euro\n");
		}
		else if (temp->averageTurnOver == 2)
		{
			fprintf(fp,"Clients Average Turnover: Less than 10 Million Euro\n");
		}
		else if (temp->averageTurnOver == 3)
		{
			fprintf(fp,"Clients Average Turnover: Over 10 Million Euro\n");
		}

		if (temp->numOfStaff == 1)
		{
			fprintf(fp,"Staff employed in the Client Company: Less than 10\n");
		}
		else if (temp->numOfStaff == 2)
		{
			fprintf(fp,"Staff employed in the Client Company: Less than 100\n");
		}
		else if (temp->numOfStaff == 3)
		{
			fprintf(fp,"Staff employed in the Client Company: Over 100\n");
		}

		if (temp->areaOfSales == 1)
		{
			fprintf(fp,"Area Of Sales: ICT\n");
		}
		else if (temp->areaOfSales == 2)
		{
			fprintf(fp,"Area Of Sales: Medical Devices\n");
		}
		else if (temp->areaOfSales == 3)
		{
			fprintf(fp,"Area Of Sales: Other area\n");
		}
		fprintf(fp,"-------------------------------------\n");

		temp = temp->NEXT;
	}

	fclose(fp);
}

void writeFile(nodeT* top)
{
	FILE* fp = fopen("clients.txt", "w");
	struct node* temp;
	temp = top;

	// writing all the nodes of the linked list to the file
	while (temp != NULL)
	{
		fwrite(temp, sizeof(struct node), 1, fp);
		temp = temp->NEXT;
	}

	if (fwrite != 0)
	{
		printf("Linked List stored in the file successfully\n");
	}
	else
	{
		printf("Error While Writing\n");
	}

	fclose(fp);
}

struct node* readFile()
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));;
	struct node* head; // points to the first node of the linked list in the file
	struct node* last; // points to the last node of the linked list in the file
	last = head = NULL;

	FILE* file;
	file = fopen("clients.txt", "r");


	if (file == NULL)
	{
		printf("Sorry the file could not be opened for reading\n");
		return head;
	}

	while (fread(temp, sizeof(struct node), 1, file))
	{

		if (head == NULL)
		{
			head = last = (struct node*)malloc(sizeof(struct node));
		}
		else
		{
			last->NEXT = (struct node*)malloc(sizeof(struct node));
			last = last->NEXT;
		}
		last->companyId = temp->companyId;
		strcpy(last->name, temp->name);
		strcpy(last->country, temp->country);
		last->year = temp->year;
		strcpy(last->email, temp->email);
		strcpy(last->contactName, temp->contactName);
		last->lastOrder = temp->lastOrder;
		last->numOfEmployees = temp->numOfEmployees;
		last->averageOrder = temp->averageOrder;
		last->vat = temp->vat;
		last->averageTurnOver = temp->averageTurnOver;
		last->numOfStaff = temp->numOfStaff;
		last->areaOfSales = temp->areaOfSales;
		last->NEXT = NULL;
	}

	fclose(file);

	return head;
}





