
// Arsh Kochhar, 20104779, 17ak126
//Gavin Anderson, 20116948, 17GKA2
//Shiyan Boxer, 20106887, 17sb79


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM 100 //Take 100 usernames
#define MAXLEN 20 // Max username and password length

// Function declarations
int readDatabase(char *usrDB[], int pswrdDB[]);
char *getUsername();
char *getPassword();
int searchUsername(char *username, char *usernameDB[], int size);
int attemptLogin(int passwordDB[], int idx);
int hashPassword(char *password);

int main(int argc, char **argv)
{
	char *usernameDB[NUM];		// Array of pointers to strings. Will read usernames from file into this array
	int passwordDB[NUM];		// Array of ints. Will read password hashes from file into this array.
	int numUsers = 0;				// The number of users.
	char response[MAXLEN] = {};	// Generic array for user input.
	
    numUsers = readDatabase(usernameDB, passwordDB);
	// Infinite loop
	while(1){
		int usrIdx;			// Index of target username
		int loginStatus;	// Indicates whether passwords match
		char *username;		// User specified username
		
		//-----------------------------------------------------------
		
		//-----------------------------------------------------------
		    do
    {
        username = getUsername();
        usrIdx = searchUsername(username, usernameDB, numUsers); // Look through the databse for the specified userrname given
        
        if(usrIdx == -1)
        {
            printf ("Username is not found. \n"); //tell the user that the userrnma is not found
    }
    } while (usrIdx == -1); // this makes them try again
     
     do
     {
     
     loginStatus = attemptLogin(passwordDB, usrIdx);
     if (loginStatus == 0)
     {
         printf("The passsword does not match.\n"); // This tels teh user that the passwrod did not match
     }
     }
     
     while (loginStatus == 0);
		
		fgets(response, MAXLEN, stdin);
		printf("Logged out.\n\n");
		
		printf("Log in to another account? (Y/N)");
		fgets(response, MAXLEN, stdin);
		if ((response[0] == 'N') || (response[0] == 'n'))
			break;
	}
	
	return numUsers;
}

// Function definitions

int readDatabase(char *usrDB[], int pswrdDB[]){
    int numUsers = 0, numPasswords = 0;
    char userBuffer[MAXLEN];
    
    FILE*usrFP = fopen("../usernames.txt","r");
    
    if(usrFP==NULL) {
        
        printf("This file could not be opened");
        exit(1);
        
        while(fgets(userBuffer,MAXLEN,usrFP)){ //read the usernames
        
        strtok(userBuffer,"\n");
        usrDB[numUsers] = (char *)malloc(strlen(userBuffer) +1); //This function is used to allocate the space for the string 
        
        if(usrDB[numUsers] == NULL)
        {
            printf ("error allocating memory");
            exit(1);                              //If allocation of memory fails, exit the program
        
        }
        
        strcpy(usrDB[numUsers], userBuffer); // This function is used to copy the string into the memory
        numUsers++;
    
        }
        
        fclose(usrFP); //The file is closed here
        
        
        FILE*pswrdFP = fopen("../password.txt","r"); // This function is used to open the passowrd text file
    
    if(pswrdFP==NULL) {                              // exit oif the file could not be opened
        
        printf("This file could not be opened");
        exit(1);
        
        
    }
    
    while (!feof(pswrdFP)) { //This loop is used to determine if the file still has data in it
    
    fscanf(pswrdFP, "%d", &pswrdDB[numPasswords]); //read the integers from the file into the array
    
    numPasswords++; //implement incrementation of the index
}

        fclose(pswrdFP); //close the file containing the passwords
        
        if (numPasswords != numUsers) {
                return -1;               //if the passwords and the usernames are not the same or do not match, an absurd value is returned
}

return numPasswords; 
    }
}

char *getPassword()
    
    {
        
        char *username = (char *)malloc(MAXLEN);  //This function is used to allocate the memory for the string
        
        printf("Please enter your password: ");
        fgets (username, MAXLEN, stdin); //read the string
        strtok(username, "\n"); //Remove the \n
        return username; // this fucntiuon is used to return the string
            
        }
        
        char *getUsername()
        {
             char *username = (char *)malloc(MAXLEN);  //This function is used to allocate the memory for the string
        
        printf("Please enter your Username: ");
        fgets (username, MAXLEN, stdin); //read the string that the users provides
        strtok(username, "\n"); //Remove the \n
        return username; // this function is used to return the string
        }
        
   


int searchUsername(char *username, char *usernameDB[], int size){
    
    int i, idx = -1;
    for(i=0; i < size; i++) 
    {
        if (strcmp(username, username[i]) == 0) // compare the user input the value that exists at index i
        idx = i;
    }
        
    return idx; // This function is used to return the index of th user 
}

int attemptLogin(int passwordDB[], int idx){
    
    char *password = getPassword();
    int n = 4891;
    int hash = 0; 
    
    for(int i = 0; i < strlen(password); i++) // This loop allows us to go through every character in the string
    
    {
        hash += password[i]; // this function adds the ascii value to hash
    }
    
    hash *= hash; // this is used to square the hash value
    hash = hash % n; // this will mod the hash
    
    if (passwordDB[idx] == hash)
        {
    
        return 1; //if the hashes do match then 1 is returned
    
    }


    return 0; // if the hashes do not match 0 is returned 
    }


