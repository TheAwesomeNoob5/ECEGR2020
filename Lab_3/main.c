#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int theArray[10] = {1,2,3,4,5,6,7,8,9,10};

typedef struct student{
		int ID;
		char firstName[30];
		char lastName[30];
		float GPA;
	} Student; 

Student* adding(void);
void gpaOrganizer(Student** newArray, int num);
Student** studentInfoFile(void);

void ReverseArray(void){ //Reverses the array
	int n = sizeof(theArray)/sizeof(theArray[0]);
	int size = n;
	int start = 0;
	int end = n - 1;
	int temp;
	while(start < end){
		temp = theArray[start]; //holds the starting value temporary 
		theArray[start] = theArray[end]; //makes the end value to the start value
		theArray[end] = temp;//makes the temporary value into the end value
		start++; 
		end--;
	}
	for (int i = 0; i < size; i++){
		printf("%d,", theArray[i]); //print the values of the new array
	}
}

void gpaOrganizer(Student** newArray , int num){ //organizes the gpa 
	for (int i = 0; i < num; i++){
		for (int j = 0; j < num; j++){
			if (newArray[i] -> GPA > newArray[j] -> GPA){
				Student* temp = newArray[i]; //holds the 1st student values temporary 
				newArray[i] = newArray[j]; //takes the 2nd student information to become the 1st order of the list
				newArray[j] = temp; //sets the 1st student to be 2nd on the list
			}
		}
	}
}

Student* adding(void){
	Student* ptr = (Student*)malloc(sizeof(Student));
	int identity = 0;
	char first[30] = "";
	char last[30] = "";
	float grade; 
	printf("Input ID number \n");
	scanf("%d", &identity);
	ptr -> ID = identity;//points to the memory allocation of Student struct and sets ID as number
	printf("Input firstname \n");
	scanf("%s", &first);
	strcpy(ptr -> firstName,first ); //points to the memory allocation of Student struct and sets firstName as a string
	printf("Input lastname \n");
	scanf("%s", &last);
	strcpy(ptr -> lastName, last); //points to the memory allocation of Student struct and sets lastName as a string
	printf("Input grade \n");
	scanf("%f",&grade);
	ptr -> GPA = grade; //points to the memory allocation of Student struct and sets GPA as a float
	return ptr;
}

void readFile(Student** array){
	int giveMeYourID = 0;
	char fiName[30] = "";
	char laName[30] = "";
	float leGrades;
	int studentNum = 0;
	float averageGPA = 0.0;
	char c;
	Student* pointer = (Student*)malloc(sizeof(Student)); //sets up a pointer to student memory allocation
	//Student **newArray = (Student**)malloc(studentNum * sizeof(Student*));
	//newArray[i] = (Student*)malloc(sizeof(Student));
	FILE *gpaFile;
	gpaFile = fopen("gpaOrganizer.txt", "r"); //reads the text file
	
	if(gpaFile == NULL){
		printf("File does not exist\n"); //checking if the file exists
		return NULL;
	}
	
	fscanf(gpaFile, "Number of Student: %d", &studentNum); //looks at the first line to take the number of students
	printf("Number of Student: %d\n", studentNum);
	
	for(int i = 0; i < studentNum; i++){
		fscanf(gpaFile, "\nStudent ID: %d", &giveMeYourID ); //looks at the next line and sets variable as id
		fscanf(gpaFile, "\nStudent firstname: %s", fiName);//looks at the next line and sets variable as firstname
		fscanf(gpaFile, "\nStudent lastname: %s", laName);//looks at the next line and sets variable as lastname
		fscanf(gpaFile, "\nStudent GPA: %f", &leGrades);//looks at the next line and sets variable as gpa
		
		pointer -> ID = giveMeYourID; //sets up the id of the student struct as the value of id in the file
		strcpy(pointer -> firstName,fiName); //sets up the firstname of the student struct as the string of firstname in the file
		strcpy(pointer -> firstName,laName);//sets up the lastname of the student struct as the string of lastname in the file
		pointer -> GPA = leGrades;  //sets up the gpa of the student struct as the value of gpa in the file
		
		printf("Student ID: %d\n", giveMeYourID); //prints the values into command prompt
		printf("Student firstname: %s\n", fiName);
		printf("Student lastname: %s\n", laName);
		printf("Student GPA: %f\n", leGrades);
		
		array[i] = pointer; // updates the struct array to be the values saved in the pointer
		averageGPA += leGrades; //takes the values of gpa in the file and adds them up
	}
	averageGPA /= studentNum; //gets the average gpa
	printf("There are %d students and the average GPA is: %f\n", studentNum, averageGPA);
}

int main(int argc, char **argv)
{
	ReverseArray();
	int number;
	printf("\nNumber of students\n");
	scanf("%d",&number);
	Student **newArray =(Student*)malloc(number*sizeof(Student));
	
	for (int i =0; i < number; i++){
		newArray[i] = adding(); 
	}
	
	gpaOrganizer(newArray,number);
	
	FILE *fp; // uses file io commands to open a new txt that saves the orginal number and reversed number
	fp = fopen("gpaOrganizer.txt","wt");
	fprintf(fp, "Number of Student: %d\n", number);
	for (int j = 0; j < number; j++){//prints the student info into a txt file
		fprintf(fp,"Student ID: %d\n", newArray[j] -> ID);
		fprintf(fp,"Student firstname: %s\n", newArray[j] ->  firstName);
		fprintf(fp,"Student lastname: %s\n", newArray[j] ->  lastName);
		fprintf(fp,"Student GPA: %f\n", newArray[j] ->  GPA);
	} 
	fclose(fp);
	free(newArray);
	
	Student** stuInfo = (Student**)malloc(number*sizeof(Student*));
	readFile(stuInfo);
	free(stuInfo);
	return 0;
}
