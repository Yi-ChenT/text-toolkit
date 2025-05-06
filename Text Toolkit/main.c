#include <stdio.h>
// Import the stdlib.h to use functions such as malloc(), free(), exit() and so on.
#include <stdlib.h>
// Import the string.h to use string manipulation functions such as strlen(), strcpy() and so on.
#include <string.h>
// Import the ctype.h to use character conversion functions such as tolower(), toupper() and so on.
#include <ctype.h>  // Reference: https://www.tutorialspoint.com/c_standard_library/ctype_h.htm
// Import the fileProcessing.h to use file processing functions such as readFile, writeFile, freeLines.
#include "fileProcessing.h"
// Import the operations.h to use operations functions such as filterLines, transformLines, summarizeLines.
#include "operations.h"
  
// Declare a constant to store the maximum length
#define MAX_LENGTH 100
// Declare a constant to store the buffer size of a line
#define BUFFER_SIZE_OF_LINE 100
// Declare a constant to store the maximum length of the keyword
#define MAX_KEYWORD_LENGTH 50
// Declare a constant to store the maximum length of the action
#define MAX_ACTION_LENGTH 50
// Declare a constant to store the maximum length of the lowercase of a line
#define MAX_LINE_LOWER_LENGTH 50
// Declare a constant to store the maximum length of the lowercase of a word
#define MAX_WORD_LOWER_LENGTH 50
// Declare a constant to store the maximum length of the word for calculating frequency
#define MAX_LENGTH_FOR_WORD_FOR_FREQUENCY 50

//Declare a function pointer for operations functions that process lines. The function pointer is used to take an array of strings, the number of lines, a configuration pointer, and a pointer to an integer for the new number of lines.
typedef char **(*funcPtr)(char **lines, int numberOfLines, void *config, int *newNumberOfLines);

// Prototype of keyCheck
static int keyCheck(const char *line, const char *keyword); // Using static to make keyCheck function only can be called in the main.c file
                                                            // Reference: https://www.geeksforgeeks.org/what-are-static-functions-in-c/

int main(void) {
    // Declare an array to store the input file name
    char inputFile[MAX_LENGTH];
    // Declare an array to store the output file name
    char outputFile[MAX_LENGTH];
    // Declare a file pointer
    FILE *filePtr = NULL;
  
    // Using while loop to prompt the user until a valid input file is provided
    while (1) {
        // Print a word to ask for the file name
        printf("Enter the name of the input file: ");
        // Using fgets to read a line of input
        if (fgets(inputFile, MAX_LENGTH, stdin) == NULL) {
            // If reading fails, print an error message
            printf("Error: Cannot read the input file name.\n");
            // Continue the loop
            continue;
        }
        // Calculate the length of the input file name
        int len = (int)strlen(inputFile);
        // If the last character is a newline, replace it with the null terminator
        if (len > 0 && inputFile[len - 1] == '\n')
            inputFile[len - 1] = '\0';
  
        // Using fopen to open the input file in read mode
        filePtr = fopen(inputFile, "r");
        // Using if statement to check if the file exist or not
        if (filePtr == NULL) {
            // Print an error message to the screen
            printf("Error: Cannot find the file '%s'\n", inputFile);
        } else {
            // Close the file pointer
            fclose(filePtr);
            // Break out of the loop
            break;
        }
    }
  
    // Print the word to ask for a output file name
    printf("Enter the name of the output file: ");
    // Using fgets to read the output file name
    if (fgets(outputFile, MAX_LENGTH, stdin) == NULL) {
        // Print an error message to the screen
        printf("Error: Cannot read the output file name.\n");
        //Return 1 indicates false
        return 1;
    }
    // Calculate the length of the output file name
    int len = (int)strlen(outputFile);
    // If the last character is a newline, remove it by replacing with the null terminator
    if (len > 0 && outputFile[len - 1] == '\n')
        outputFile[len - 1] = '\0';
  
    // Declare a variable to store the number of lines read from the input file
    int numberOfLines = 0;
    // Call the readFile function to read the input file content into an array of strings
    char **lines = readFile(inputFile, &numberOfLines);
    // Check if readFile returned NULL, indicating failure to read the file
    if (lines == NULL) {
        // Print an error message to the screen
        printf("Failed to read file: %s\n", inputFile);
        // Return 1 indicates false
        return 1;
    }
  
    // Write the original file content to the output file using writeFile function
    if (writeFile(outputFile, lines, numberOfLines) == 0)
        // Print a success message
        printf("Processed lines written to '%s'.\n", outputFile);
    else
        // Print an error message
        printf("Error: Cannot write processed lines to '%s'.\n", outputFile);
  
    // Declare a variable to store the user's option
    int option;
    // Using while loop to display the menu and process operations from user
    while (1) {
        // Print the word to the screen
        printf("\nFile Processing Operations:\n");
        // Print the word to the screen
        printf("1. Filter lines\n");
        // Print the word to the screen
        printf("2. Transform lines\n");
        // Print the word to the screen
        printf("3. Summarize lines\n");
        // Print the word to the screen
        printf("4. Exit\n");
        // Print the word to the screen
        printf("Enter your choice: ");
        // Using scanf to read the user's choice
        if (scanf("%d", &option) != 1) {
            // Print an error message
            printf("Invalid input.\n");
            // Using getchar to clear the input buffer
            while (getchar() != '\n');
            // Continue the loop
            continue;
        }
        // Using getchar to clear the input buffer
        while (getchar() != '\n');
  
        // If user choose option 4, then exit the loop
        if (option == 4)
            // Break out of the loop
            break;
  
        // Declare a function pointer for the selected operation
        funcPtr operations = NULL;
        // Declare an integer to store the new number of lines
        int newNumberOfLines = 0;
        // Declare a pointer to store the new lines
        char **newLines = NULL;
  
        // If the user selects option 1
        if (option == 1) {
            // Declare an array to store the keyword
            char keyword[MAX_KEYWORD_LENGTH];
            // Print the word to ask for enter a keyword
            printf("Enter a keyword to filter lines: ");
            // Using scanf to read the keyword
            if (scanf("%s", keyword) != 1) {
                // Print an error message
                printf("Invalid input.\n");
                // Using getchar to clear the input buffer
                while (getchar() != '\n');
                // Continue the loop
                continue;
            }
            // Using getchar to clear the input buffer
            while (getchar() != '\n');
  
            // Declare an integer to check if the keyword exists in lines
            int found = 0;
            // Using for loop to traverse each line
            for (int i = 0; i < numberOfLines; i++) {
                // If the keyCheck function returns true for the current line and keyword
                if (keyCheck(lines[i], keyword)) {
                    // Assign 1 to found
                    found = 1;
                    // Break out of the loop
                    break;
                }
            }
            // If the keyword was not found in lines
            if (found == 0) {
                // Print an error message
                printf("Error: Cannot find the keyword '%s'.\n", keyword);
                // Continue the loop
                continue;
            }
  
            // Declare a FilterConfig structure to store filtering parameters
            FilterConfig config;
            // Allocate memory for the keywords array
            config.keywords = (char **)malloc(sizeof(char *));
            // Using if statement to check if memory allocation failed
            if (config.keywords == NULL) {
                // Print an error message and exit the program
                fprintf(stderr, "Memory allocation error.\n");
                exit(1);
            }
            // Allocate memory for the keyword string
            config.keywords[0] = (char *)malloc(strlen(keyword) + 1);
            // Using if statement to check if memory allocation failed for the keyword string
            if (config.keywords[0] == NULL) {
                // Print an error message and exit the program
                fprintf(stderr, "Memory allocation error.\n");
                exit(1);
            }
            // Using strcpy to copy the keyword from the user into the allocated memory
            strcpy(config.keywords[0], keyword);
            // Set the number of keywords in the configuration to 1
            config.numberOfKeywords = 1;
  
            // Set the operations function pointer to point to the filterLines function
            operations = filterLines;
            // Call the filterLines function using the operations pointer, passing the arguments
            newLines = operations(lines, numberOfLines, &config, &newNumberOfLines);
  
            // Free the allocated memory for the keyword string
            free(config.keywords[0]);
            // Free the allocated memory for the keywords array
            free(config.keywords);
            // Free the memory allocated for the original lines
            freeLines(lines, numberOfLines);  // from ctype.h
            // Update the lines pointer to point to the newly filtered lines
            lines = newLines;
            // Update the number of lines to reflect the filtered result
            numberOfLines = newNumberOfLines;
  
            // Write the filtered lines to the output file using writeFile function
            if (writeFile(outputFile, lines, numberOfLines) == 0)
                // Print a success message if writing succeeded
                printf("Processed lines written to '%s'.\n", outputFile);
            else
                // Print an error message
                printf("Error: Cannot write processed lines to '%s'.\n", outputFile);
        }
        // If the user selects option 2
        else if (option == 2) {
            // Declare an array to store the transformation action
            char action[MAX_ACTION_LENGTH];
            // Print the word to the screen
            printf("Please select transformation type (U for uppercase, R for reverse): ");
            // Using scanf to read the transformation rule from standard input
            if (scanf("%s", action) != 1) {
                // Print an error message
                printf("Invalid input.\n");
                // Using getchar to clear the input buffer
                while (getchar() != '\n');
                // Continue the loop
                continue;
            }
            // Using getchar to clear the input buffer
            while (getchar() != '\n');
  
            // Using if statement to check that the action is exactly one character
            if (!((action[0] == 'U' || action[0] == 'u' || action[0] == 'R' || action[0] == 'r') && action[1] == '\0')) {
                // Print the error message
                printf("Error: Invalid input. Please enter 'U' or 'R' for doing operation.\n");
                // Continue the loop
                continue;
            }
  
            // Declare a TransformConfig structure to store transformation parameters
            TransformConfig config;
            // Using strcpy to copy the action from the user into the action field of the config structure
            strcpy(config.action, action);
  
            // Set the operations function pointer to point to the transformLines function
            operations = transformLines;
            // Call the transformLines function using the operations pointer, passing the arguments
            newLines = operations(lines, numberOfLines, &config, &newNumberOfLines);
  
            // Free the memory allocated for the original lines
            freeLines(lines, numberOfLines);  // from ctype.h
            // Update the lines pointer to point to the transformed lines
            lines = newLines;
            // Update the number of lines to reflect the transformed result
            numberOfLines = newNumberOfLines;
            // Using if statement to check if the selected transformation action is used or not
            if (action[0] == 'U' || action[0] == 'u')
                // Print the word to the screen
                printf("Uppercase transformation applied successfully.\n");
            // Using if statement to check if the selected transformation action is used or not
            else if (action[0] == 'R' || action[0] == 'r')
                // Print the word to the screen
                printf("Reverse transformation applied successfully.\n");
  
            // Using writeFile function to write the transformed lines to the output file 
            if (writeFile(outputFile, lines, numberOfLines) == 0)
                // Print a success message
                printf("Processed lines written to '%s'.\n", outputFile);
            else
                // Print an error message
                printf("Error writing processed lines to '%s'.\n", outputFile);
        }
        // If the user selects option 3
        else if (option == 3) {
            // Declare an array to store the word used for frequency calculation
            char wordForFrequency[MAX_LENGTH_FOR_WORD_FOR_FREQUENCY];
            // Print the word to ask for a word to calculate frequency
            printf("Enter a word for frequency calculation: ");
            // Using scanf to read the word
            if (scanf("%s", wordForFrequency) != 1) {
                // Print an error message
                printf("Invalid input.\n");
                // Using getchar to clear the input buffer
                while (getchar() != '\n');
                // Continue the loop
                continue;
            }
            // Using getchar to clear the input buffer
            while (getchar() != '\n');
  
            // Declare an integer to check if the word exists
            int found = 0;
            // Declare an array to store a lowercase copy of a line
            char lineLower[MAX_WORD_LOWER_LENGTH];
            // Declare an array to store a lowercase copy of the word
            char wordLower[MAX_WORD_LOWER_LENGTH];
            // Declare an integer to get the length of the word
            int wordLen = (int)strlen(wordForFrequency);
            // Using for loop to convert each character of the word to lowercase and store it in wordLower
            for (int j = 0; j < wordLen; j++) {
                wordLower[j] = tolower((unsigned char)wordForFrequency[j]);
            }
            // Add the null terminator to the end of wordLower
            wordLower[wordLen] = '\0';
  
            // Using for loop to traverse each line in the file
            for (int i = 0; i < numberOfLines; i++) {
                // Declare an integer to get the length of the current line
                int lineLen = (int)strlen(lines[i]);
                // Declare an integer to store the number of characters to copy.
                int copyLen;
                // Using if statement to check if the current line's length is less than 99
                if (lineLen < BUFFER_SIZE_OF_LINE - 1) {
                // Set copyLen equal to the length of the current line.
                copyLen = lineLen;
                } 
                else {
                // Set copyLen to 99 to avoid buffer overflow.
                copyLen = BUFFER_SIZE_OF_LINE - 1;
                }
                
                for (int k = 0; k < copyLen; k++) {
                    lineLower[k] = tolower((unsigned char)lines[i][k]);
                }
                // Add the \0 to the end of lineLower
                lineLower[copyLen] = '\0';
  
                // Using if statement to check if the lowercase line contains the lowercase word by using keyCheck
                if (keyCheck(lineLower, wordLower)) {
                    // Assign found to 1
                    found = 1;
                    // Break out of the loop
                    break;
                }
            }
            // If the word was not found in any line
            if (found == 0) {
                // Print an error message
                printf("Error: Cannot find the word '%s'.\n", wordForFrequency);
                // Continue the loop
                continue;
            }
  
            // Declare a SummarizeConfig structure to store summarization parameters
            SummarizeConfig config;
            // Using strcpy to copy the word from the user into the config structure
            strcpy(config.word, wordForFrequency);
  
            // Set the operations function pointer to point to the summarizeLines function
            operations = summarizeLines;
            // Call the summarizeLines function using the operations pointer, passing the arguments
            newLines = operations(lines, numberOfLines, &config, &newNumberOfLines);
  
            // Using writeFile function to write the summary to the output file 
            if (writeFile(outputFile, newLines, newNumberOfLines) == 0)
                // Print a success message
                printf("Summary written to '%s'.\n", outputFile);
            else
                // Print an error message
                printf("Error writing summary to '%s'.\n", outputFile);
            // Free the memory allocated for the new summary lines
            freeLines(newLines, newNumberOfLines);  // from ctype.h
        }
        // If the user entered an invalid option
        else {
            // Print an error message
            printf("Invalid choice.\n");
        }
    }
  
    // Free the memory allocated for the original lines before exiting the program
    freeLines(lines, numberOfLines);  // from ctype.h
    // Return 0 indicates the program runs correctly
    return 0;
}

/* FUNCTION:
    keyCheck
   DESCRIPTION :
    This function is used to check if the provided keyword exists within the given line.
   PARAMETERS:
    const char *line   : The line of text to search.
    const char *keyword: The keyword to find within the line.
   RETURNS :
    int : Returns 1 if the key is found, 0 if the key is not found.
*/
static int keyCheck(const char *line, const char *keyword) {  // Reference: https://www.geeksforgeeks.org/what-are-static-functions-in-c/
    // Declare an integer to get the length of the line
    int lineLen = (int)strlen(line);
    // Declare an integer to get the length of the keyword
    int keyLen = (int)strlen(keyword);
    // Using if statement to check if the keyword is an empty string or not
    if (keyLen == 0)
        return 1;
    // Using for loop over the line
    for (int i = 0; i <= lineLen - keyLen; i++) {
        // Declare a variable for the inner loop index
        int j;
        // Using second for loop to compare the substring of 'line'
        for (j = 0; j < keyLen; j++) {
            // Using if statement to check if any character match or not
            if (line[i + j] != keyword[j])
                // Break out of the loop
                break;
        }
        // Using if statement to check if the inner loop completed
        if (j == keyLen)
            return 1;
    }
    // Return 0 if not found the keyword
    return 0;
}
