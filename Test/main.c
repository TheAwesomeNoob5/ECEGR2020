#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *filePtr; // File pointer to use for reading and writing to a file.

typedef struct student // struct student being defined and type defined.
{
    int ID;
    char firstName[30];
    char lastName[30];
    float GPA;
	struct student* next; // struct student pointer to point at the next pointer in a list (used for linked lists).
} Student; // struct student will have be called when type Student is used.

Student* firstStudent = NULL; // Creating the first student pointer to be used in a linked list, because the list starts empty the pointer points to NULL.

////////////////////////////////////////////////////////////////////
//								  //
//			   Node Functions			  //
//								  //
////////////////////////////////////////////////////////////////////

/*
 * Linked lists made up of nodes, these nodes are just pointers. For the purpose of this lab we will be using a single linked list, so where 
 * one node points to the next node in the list, until the end of the list (called the tail) points to NULL. To iterate through a linked list
 * we will commonly be using a while loop that checks to see if the current pointer is not pointing to null, and if it isn't it will iterate
 * and point to the next node. This acts similarly to a for loop iterating through an array with the maximum range being the array length,
 * except we don't know how large our linked list is going to be at all times. The following functions are functions to either create nodes,
 * add nodes, delete nodes, or insert nodes.
 */

Student* createStudentNode(int id_in, char first_in[30], char last_in[30], float gpa_in) // Creates a student node with inputs for each part of the original student struct.
{
	Student* newStudent = (Student*) malloc(sizeof(Student)); // Allocates memory for a new student pointer to be made.
	
	if(newStudent != NULL) // Null checks the malloc to make sure there was enough memor allocated for a student pointer.
	{
		newStudent->ID = id_in;
		strcpy(newStudent->firstName, first_in);
		strcpy(newStudent->lastName, last_in);
		newStudent->GPA = gpa_in;
		newStudent->next = NULL;
	}
	
	return newStudent; // Returns the new student that was just created.
}

void addStudentNode(Student* newStudent) // Adds a student input to the end of the linked list.
{
	Student* currentStudent = firstStudent; // Creates a new student pointer to keep track of the current student. Sets the pointer at the start of the linked list.
	
	if(firstStudent == NULL) // Checks to see if the linked list is empty.
	{
		firstStudent = newStudent; // If empty, set the input student as the head node.
		return; // return allows us to leave the function without going through the rest of the code in the function.
	}
	
	while(currentStudent->next != NULL) // If there's a linked list, then we iterate through the list.
	{				    // We check to see if our current pointer is pointing to NULL so we know when we have arrived at the end of the linked list.
		currentStudent = currentStudent->next; // This is how to iterate trhough a linked list, it's the same idea as i++ for a for loop;
	}
	currentStudent->next = newStudent; // After iterating through the list to arrive at the tail, we set the current tail
	newStudent->next = NULL;	   // to the student input and set the new student pointer to NULL, defining it as the new tail.
}

void instertStudentNode(Student* newStudent) // Inserts a student into the linked list. NOTE: This is where the list sorts by GPA as well. 
{
	Student* node = firstStudent; // Creates a new student pointer to keep track of the current student. Sets the pointer at the start of the linked list.
	
	while(node->next != NULL) // While loop to iterate through the linked list.
	{
		Student* nextNode = node->next; // Creates another student pointer to keep track of the student that comes after the current student (hence the name nextNode).
		
		if((node->GPA > newStudent->GPA) && (newStudent->GPA >= nextNode->GPA)) // This if statement compares to see if the current student's GPA is greater than the new student GPA,
		{									// and if the next student's GPA is less than or equal to the new student GPA.
			newStudent->next = node->next; // Takes the student input and links it to the next node in the list.
			node->next = newStudent; // Links the current student to the student input.
			return; // Leaves the function.
		}
		
		else if(node->GPA <= newStudent->GPA) // If the first check fails, then this check is to see if the student input GPA is the greatest GPA.
		{				      // NOTE: This should only happen to the head node in the linked list.
			newStudent->next = node; // Links the new student to the current node (which should be the head node).
			firstStudent = newStudent; // Sets the new student as the head node (aka first student in the linked list).
			return; // Leaves the function.
		}
		
		node = node->next; // Iterates the current node to the next to traverse the linked list. Remember, it works like i++ in a for loop.
	}
	
	node->next = newStudent; // If neitehr condition is met in the whole linked list, then the new student GPA is the lowest GPA, and will be made the new tail of the linked list.
	newStudent->next = NULL; // Links the new student to NULL to indicate the end of the linked list, the previous line linked the previous tail to the new student to crate the new tail.
	return; // Leaves the function.
	
}

void deleteStudentNode(Student* delStudent) // Deletes a student given a student input to delete.
{
	Student* currentStudent = firstStudent; // Creates a new student pointer to keep track of the current student. Sets the pointer at the start of the linked list.
	Student* prevSudent = NULL; // Creates a new student pointer to keep track of the previous student. This will be delayed in the iteration when traversing the list.
	
	if(firstStudent == delStudent) // This if statement checks to see if the desired student to delete is the first student in the list.
	{
		firstStudent = firstStudent->next; // Sets the next student in the list as the head node (aka first student).
		free(delStudent); // Frees the memory of the student input.
		return; // Leaves the function.
	}
	
	while(currentStudent != NULL && currentStudent != delStudent) // Iterates through the list until the desired student is found.
	{
		prevSudent = currentStudent; // The present becomes the past.
		currentStudent = currentStudent->next; // The future becomes the present.
	}
	
	if(currentStudent != NULL) // Checks to see if we are still in the linked list.
	{
		prevSudent->next = currentStudent->next; // This sucessfully unlinks our desired node from the linked list by having the 
	}						 // previous node link skip the currnet node and link to the next one.
	
	free(delStudent); // Deletes the desired student and frees the its memory.
}

/*
 * Function delcarations for the rest of the program.
 * Kind of acts like a table of contents.  
 */

void readStudentRecords(void); // Reads the StudentRecords.txt file and writes it into a linked list.
//
// Linked List Functions
//
void readList(void); // Iterates through the linked list and prints out all the students in the linked list.
void freeList(void); // Iterates through the linked list and deletes all the students in the linked list, thus freeing the memory.
void saveList(void); // Iterates through the linked list and writes all the student details in the same format into the StudentRecords.txt file.
//
// Specific Student Functions
//
void removeStudent(int id_in); // Removes a student from the linked list by searching for their specific ID.
void updateStudent(int id_in); // Updates a function based on the user input for any attribute of the student based on their specific ID.
//
// Menu Displays (just a bunch of prtint commands)
//
void menuDisplay(void); // Displays the default menu.
void updateStudentMenu(char first[30], char last[30]); // Displays the menu for the specific student to have their attributes updated.

////////////////////////////////////////////////////////////////////
//								  //
//			   Main Function		          //
//								  //
////////////////////////////////////////////////////////////////////

int main()
{
	int user_in; // Declares a new variable to scan for user input later.
	
	readStudentRecords(); // Reads the StudentRecords.txt file and writes it into a linked list.
	do // Begins the do-while loop to keep the user in the program.
	{
		//
		// Declarations for placeholder variables.
		//
		int id_input;
		char first_input[30] = "";
		char last_input[30] = "";
		float gpa_input = 0.0;
		int userID_in; // Variable to scan for user input later for menu options 3 and 4.
		Student* idCheck = firstStudent; // Variable to use as a check for later.
		
		menuDisplay(); // Displays the default menu.
		printf("\nWhat would you like to do? "); // Prompts the user to enter an input.
		scanf("%d", &user_in); // Scans the input into the user_in variable that was declared at the beginning of the main() function.
		
		switch(user_in) // Switch-case to check which case the user desired.
		{
			case 1 : // 1) List all students
				readList(); // Iterates through the linked list and prints out all the students in the linked list.
				break; // Leave the switch-case.
				
			case 2 : // 2) Add Student
				printf("\nEnter the ID of the student: "); // Prompts the user to enter an input.
				scanf("%d", &id_input); // Scans the input into the id_input variable that was declared at the beginning of the do-while loop.
				while(idCheck != NULL) // Iterates through the linked list.
				{
					if(id_input == idCheck->ID) // Checks to see if the ID already exists.
					{
						printf("\nEntered ID is currently used by and existing student."); // Let the user know that this ID can't be used.
						idCheck = firstStudent; // Set the check back to the beginning of the linked list.
						printf("\nEnter the ID of the student: "); // Prompt the user to enter an input.
						scanf("%d", &id_input); // Scans the input into the id_input variable that was declared at the beginning of the do-while loop.
					}
					idCheck = idCheck->next; // Iterates the current node to the next to traverse the linked list. Remember, it works like i++ in a for loop.
				}
				
				printf("\nEnter the first name of the student: "); // Prompts the user to enter an input.
				scanf("%29s", first_input); // Scans the input into the first_input variable that was declared at the beginning of the do-while loop.
				
				printf("\nEnter the last name of the student: "); // Prompts the user to enter an input.
				scanf("%29s", last_input); // Scans the input into the last_input variable that was declared at the beginning of the do-while loop.
				
				printf("\nEnter the GPA of the student: "); // Prompts the user to enter an input.
				scanf("%f", &gpa_input); // Scans the input into the gpa_input variable that was declared at the beginning of the do-while loop.
				while((gpa_input > 4.0) || (gpa_input < 1.0)) // Checks the gpa_input to see if it is within the 4.0 GPA scale.
				{
					printf("\nPlease enter a GPA in the range of 4.0 and 1.0."); // Let the user know that this GPA can't be used.
					printf("\nEnter the GPA of the student: "); // Prompt the user to enter an input.
					scanf("%f", &gpa_input); // Scans the input into the gpa_input variable that was declared at the beginning of the do-while loop.
				}
				
				Student* peterPtr = createStudentNode(id_input, first_input, last_input, gpa_input); // Takes all the scanned inputs and creates a new student pointer from it.
				instertStudentNode(peterPtr); // Takes the new student pointer and insterts it into the linked list.
				break; // Leave the switch-case.
				
			case 3 : // 3) Remove Student
				printf("\nEnter the ID of the student you wish to delete: "); // Prompts the user to enter an input.
				scanf("%d", &userID_in); // Scans the input into the userID_in variable that was declared at the beginning of the do-while loop.
				removeStudent(userID_in);// Takes the scanned userID_in and removes a student from the linked list by searching for userID_in.
				break; // Leave the switch-case.
				
			case 4 : // 4) Update Student
				printf("\nEnter the ID of the student you wish to update: "); // Prompts the user to enter an input.
				scanf("%d", &userID_in); // Scans the input into the userID_in variable that was declared at the beginning of the do-while loop.
				updateStudent(userID_in); // Takes the scanned userID_in and updates the student based on the user input for any attribute of the student based on userID_in.
				break; // Leave the switch-case.
			
			case 5 : // 5) Quit
				printf("\nExiting Student Program..."); // Let the user know the program is closing.
				break; // Leave the switch-case.
			
			default : // If there is an input that isn't any of the above listed cases.
				printf("\nInvalid input\n"); 
		}
	}while(user_in != 5); // Leave the do-while if option 5 is chosen.
	saveList(); // Iterates through the linked list and writes all the student details in the same format into the StudentRecords.txt file.
	freeList(); // Iterates through the linked list and deletes all the students in the linked list, thus freeing the memory.
}

////////////////////////////////////////////////////////////////////
//								  //
//		      	Linked List Functions			  //
//								  //
////////////////////////////////////////////////////////////////////

void readStudentRecords() // Reads the StudentRecords.txt file and writes it into a linked list.
{
	//
	// Declarations for placeholder variables.
	//
	char first_out[30], last_out[30];
	int numOut, id_out;
	float gpa_out;
	
	filePtr = fopen("gpaOrganizer.txt", "r"); // Set the file pointer to open and read the StudentRecords.txt file.
	fscanf(filePtr, "Number of students: %d", &numOut); // Scan for the specfic number of students in the cass defined in the beginning of the file.
	
	for(int i=0; i<numOut; i++) // Iterate through the file as many times as however many students were said to be in the file.
	{
		//
		// Scanning the ID, first and last name, and GPA of each student and assigning their values to the placeholder variables declared at the beginning of the function.
		//
		fscanf(filePtr, "\nStudent ID: %d", &id_out);
		fscanf(filePtr, "\nStudent First Name: %s", first_out);
		fscanf(filePtr, "\nStudent Last Name: %s", last_out);
		fscanf(filePtr, "\nStudent GPA: %f", &gpa_out);
		
		Student* piperPtr = createStudentNode(id_out, first_out, last_out, gpa_out); // Create a node to be placed in the linked list.
		addStudentNode(piperPtr); // Construct a linked list by placing the previously created node on to the end of the list.
					  // NOTE: This does not use the insert function because the file shold alrady be formatted in GPA descending order.
	}
	printf("StudentRecords.txt successfully scanned\n"); // Let user know the function worked.
}

void readList() // Iterates through the linked list and prints out all the students in the linked list.
{
	Student* node = firstStudent; // Creates a new student pointer to keep track of the current node (aka student). Sets the pointer at the start of the linked list.
	printf("\n==========STUDENT LINKED LIST=========="); // Formatting.
	while(node != NULL) // While loop to iterate through the linked list.
	{
		//
		// Print the attributes of each student in the linked list.
		//
		printf("\nStudent ID: %d", node->ID);
		printf("\nStudent First Name: %s", node->firstName);
		printf("\nStudent Last Name: %s", node->lastName);
		printf("\nStudent GPA: %f", node->GPA);
		node = node->next; // i++
	}
	printf("\n\n======================================="); // Formatting.
}

void freeList() // Iterates through the linked list and deletes all the students in the linked list, thus freeing the memory.
{
	Student* node = firstStudent; // Creates a new student pointer to keep track of the current node (aka student). Sets the pointer at the start of the linked list.
	Student* nextNode = firstStudent->next; // Creates a new student pointer to keep track of the next node (aka student). Sets the pointer at the second node of the linked list.
	while(node != NULL) // While loop to iterate through the linked list.
	{
		deleteStudentNode(node); // Free the current node.
		node = nextNode; // Iterate through, i++. 
				 // NOTE: Using another pointer instead of using node = node->next; because node is now equal to NULL.
		nextNode = nextNode->next; // Iterate to the next node.
	}
}

void saveList() // Iterates through the linked list and writes all the student details in the same format into the StudentRecords.txt file.
{
	filePtr = fopen("gpaOrganizer.txt", "w+"); // Set the file pointer to open and read the StudentRecords.txt file.
	Student* node = firstStudent; // Creates a new student pointer to keep track of the current node (aka student). Sets the pointer at the start of the linked list.
	int studentCount = 0; // New variable to count the total students in the linked list.
	while(node != NULL) // While loop to iterate through the linked list.
	{
		studentCount++; // For every node in the list, add 1 to count. End result should be the total amont of nodes in the list.
		node = node->next; // Iterate.
	}
	
	fprintf(filePtr, "Number of students: %d ", studentCount); // Print in the same format as the file was scanned for consistency.
	node = firstStudent; // Reset the node to the beginning of the list.
	while(node != NULL) // While loop to iterate through the linked list.
	{
		//
		// Printing the ID, first and last name, and GPA of each student.
		//
		fprintf(filePtr, "\nStudent ID: %d", node->ID);
		fprintf(filePtr, "\nStudent First Name: %s", node->firstName);
		fprintf(filePtr, "\nStudent Last Name: %s", node->lastName);
		fprintf(filePtr, "\nStudent GPA: %f", node->GPA);
		node = node->next; // Iterate.
	}
	fclose(filePtr); // Close the file.
}

////////////////////////////////////////////////////////////////////
//								  //
//		      Specfic Student Functions			  //
//								  //
////////////////////////////////////////////////////////////////////

void removeStudent(int id_in) // Removes a student from the linked list by searching for their specific ID.
{
	Student* node = firstStudent; // Creates a new student pointer to keep track of the current node (aka student). Sets the pointer at the start of the linked list.
	int check = 0; // Initialzed a variable to check if the ID was found or not. 0 if not found, 1 if found.
	while(node != NULL) // While loop to iterate through the linked list.
	{
		if(id_in == node->ID) // Check if the current node in the list shares the ID of the resired input ID.
		{
			char first[30];
			char last[30];
			strcpy(first, node->firstName);
			strcpy(last, node->lastName);
			deleteStudentNode(node); // Remove and free the node from the list.
			check = 1; // Iterate check so that the ID was found.
			printf("\n%s %s was successfully deleted.", first, last); // Success message for the user.
			return; // Leave the function.
		}
		node = node->next; // Iterate.
	}
	if(check == 0) // If the ID was not found.
	{
		printf("\nThere is no student associated with the given ID."); // Let the user know that the ID was invalid.
		return; // Leave the function.
	}
	return; // Leave the function.
}

void updateStudent(int id_in) // Updates a function based on the user input for any attribute of the student based on their specific ID.
{
	Student* node = firstStudent; // Creates a new student pointer to keep track of the current node (aka student). Sets the pointer at the start of the linked list.
	Student* prevNode = node; // Creates a new student pointer to keep track of the previous node (aka student). Sets the pointer at the start of the linked list.
	int check = 0; // Initialzed a variable to check if the ID was found or not. 0 if not found, 1 if found.
	int user_input = 0; // Declares a new variable to scan for user input later.
	while(node != NULL) // While loop to iterate through the linked list.
	{
		if(id_in == node->ID) // Check if the current node in the list shares the ID of the resired input ID.
		{
			do // Begins the do-while loop to keep the user in the update student system.
			{
				updateStudentMenu(node->firstName, node->lastName); // Display the update student menu for the specific student desired.
				scanf("%d", &user_input); // Scans the input into the user_input variable that was declared at the beginning of the updateStudent() function.
				//
				// Declarations for placeholder variables.
				//
				int new_id, old_id;
				char new_first[30], old_first[30];
				char new_last[30], old_last[30];
				float new_gpa, old_gpa;
				Student* idCheck = firstStudent;
				
				switch(user_input) // Switch-case to check which case the user desired.
				{
					case 1 : // 1) Update ID
						printf("\nEnter the new ID: "); // Prompts the user to enter an input.
						scanf("%d", &new_id); // Scans the input into the new_id variable that was declared at the beginning of the do-while loop.
						while(idCheck != NULL) // Iterates through the linked list.
						{
							if(new_id == idCheck->ID) // Checks to see if the ID already exists.
							{
								printf("\nEntered ID is currently used by and existing student."); // Let the user know that this ID can't be used.
								idCheck = firstStudent; // Set the check back to the beginning of the linked list.
								printf("\nEnter the ID of the student: "); // Prompt the user to enter an input.
								scanf("%d", &new_id); // Scans the input into the new_id variable that was declared at the beginning of the do-while loop.
							}
							idCheck = idCheck->next; // Iterates the current node to the next to traverse the linked list. Remember, it works like i++ in a for loop.
						}
						old_id = node->ID; // Formatting.
						node->ID = new_id; // Change the ID.
						printf("\n%d was sucessfully updated to %d", old_id, new_id); // Success message for the user.
						break; // Leave the switch-case.
					case 2 : // 2) Update First Name
						printf("\nEnter the new first name: "); // Prompts the user to enter an input.
						scanf("%29s", new_first); // Scans the input into the new_first variable that was declared at the beginning of the do-while loop.
						strcpy(old_first, node->firstName); // Formatting.
						strcpy(node->firstName, new_first); // Change the first name.
						printf("\n%s was sucessfully updated to %s", old_first, new_first); // Success message for the user.
						break; // Leave the switch-case.
					case 3 : // 3) Update Last Name
						printf("\nEnter the new last name: "); // Prompts the user to enter an input.
						scanf("%29s", new_last); // Scans the input into the new_last variable that was declared at the beginning of the do-while loop.
						strcpy(old_last, node->lastName); // Formatting.
						strcpy(node->lastName, new_last); // Change the last name.
						printf("\n%s was sucessfully updated to %s", old_last, new_last); // Success message for the user.
						break; // Leave the switch-case.
					case 4 : // 4) Update GPA
						printf("\nEnter the new GPA: "); // Prompts the user to enter an input.
						scanf("%f", &new_gpa); // Scans the input into the new_gpa variable that was declared at the beginning of the do-while loop.
						while((new_gpa > 4.0) || (new_gpa < 1.0)) // Checks the gpa_input to see if it is within the 4.0 GPA scale.
						{
							printf("\nPlease enter a GPA in the range of 4.0 and 1.0."); // Let the user know that this GPA can't be used.
							printf("\nEnter the GPA of the student: "); // Prompts the user to enter an input.
							scanf("%f", &new_gpa); // Scans the input into the new_gpa variable that was declared at the beginning of the do-while loop.
						}
						old_gpa = node->GPA; // Formatting.
						node->GPA = new_gpa; // Change the GPA.
						if(prevNode == node) // Checks if this is the first node in the list.
						{
							node->next = NULL; // If so, unlink the current node from the list.
							instertStudentNode(node); // Re-insert the node so the list is still sorted by GPA.
						}
						else // At any other part of the list...
						{
							prevNode->next = node->next; // Unlink the current node by linking the node before it to the node in front of it.
							instertStudentNode(node); // Re-insert the node so the list is still sorted by GPA.
						}
						printf("\n%f was sucessfully updated to %f", old_gpa, new_gpa); // Success message for the user.
						break; // Leave the switch-case.
					
					case 5 : // 5) Quit
						break; // Leave the switch-case.
					
					default : // If there is an input that isn't any of the above listed cases.
						printf("\nInvalid input\n");
				}
			} while(user_input != 5); // Leave the do-while if option 5 is chosen.
			return; // Leave the function.
		}
		prevNode = node; // Makes sure prevNode is 1 iteratoin behind node.
		node = node->next; // Iterate node
	}
	if(check == 0) // If the ID was not found.
	{
		printf("\nThere is no student associated with the given ID."); // Let the user know that the ID was invalid.
		return; // Leave the function.
	}
}

void menuDisplay() // Displays the default menu.
{
	printf("\n====================STUDENT MENU====================");
	
	printf("\n\n[1] List All Students");
	printf("\n[2] Add Student");
	printf("\n[3] Remove Student");
	printf("\n[4] Update Student");
	
	printf("\n\n[5] Quit");
	printf("\n\n====================================================");
	printf("\n\n");
}

void updateStudentMenu(char first[30], char last[30]) // Displays the menu for the specific student to have their attributes updated.
{
	printf("\n====================UPDATE STUDENT MENU====================");
	printf("\nWhat would you like to update about %s %s?", first, last);
	printf("\n\n[1] ID");
	printf("\n[2] First Name");
	printf("\n[3] Last Name");
	printf("\n[4] GPA");
	
	printf("\n\n[5] Quit");
	printf("\n\n===========================================================");
	printf("\n\n");
}