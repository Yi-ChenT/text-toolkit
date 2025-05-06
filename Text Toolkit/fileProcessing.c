#include <stdio.h>
// Import the stdlib.h to use functions such as malloc(), free(), exit() and so on.
#include <stdlib.h>
// Import the string.h to use string manipulation functions such as strlen(), strcpy() and so on.
#include <string.h>
// Import the fileProcessing.h to use file processing functions such as readFile, writeFile, freeLines.
#include "fileProcessing.h"

// Declare a constant to store the maximum buffer length
#define MAX_BUFFER_LENGTH 100

/* 
    FUNCTION:
    readFile
   DESCRIPTION:
    This function is used to read a file line by line and returns an array of strings.
   PARAMETERS:
    const char *fileName : The name of the file to read.
    int *numOfLines    : A pointer to an integer that will store the number of lines read.
   RETURNS:
    char**: A pointer to an array of strings containing the lines from the file, or NULL if an error occurs.
*/
char **readFile(const char *fileName, int *numOfLines) {
    // Using fopen to open the file in read mode.
    FILE *file = fopen(fileName, "r");
    // Using if statement to check if the file was opened successfully.
    if (file == NULL) {
        // Print an error message if the file could not be opened.
        fprintf(stderr, "Error opening file '%s'\n", fileName);
        // Return NULL to indicate failure.
        return NULL;
    }
    // Initialize the pointer for storing lines to NULL.
    char **lines = NULL;
    // Initialize the number of lines to zero.
    *numOfLines = 0;
    // Declare a buffer array to temporarily store each line read from the file.
    char buffer[MAX_BUFFER_LENGTH];

    // Using while loop traverse the file and using fgets to get the user input.
    while (fgets(buffer, MAX_BUFFER_LENGTH, file) != NULL) {
        // Declare an integer to get the length of the current line stored in the buffer.
        int len = strlen(buffer);
        // Check if the line ends with a newline character.
        if (len > 0 && buffer[len - 1] == '\n')
            // Replace the newline character with a null terminator.
            buffer[len - 1] = '\0';
        // Reallocate memory for the array of lines to include the new line.
        char **temp = realloc(lines, ((*numOfLines) + 1) * sizeof(char *));  // Reference: https://www.geeksforgeeks.org/g-fact-66/
        // Using if statement to check if the memory allocation was successful.
        if (temp == NULL) {
            // Print an error message if memory allocation fails.
            fprintf(stderr, "Memory allocation error.\n");
            // Close the file
            fclose(file);
            // Return NULL to indicate failure.
            return NULL;
        }
        // Update the lines pointer with the newly allocated memory.
        lines = temp;
        // Allocate memory for the new line, including space for the null terminator.
        lines[*numOfLines] = malloc(strlen(buffer) + 1);
        // Using if statement to check if the memory allocation for the new line was successful.
        if (lines[*numOfLines] == NULL) {
            // Print an error message error if memory allocation fails.
            fprintf(stderr, "Memory allocation error.\n");
            // Close the file before returning.
            fclose(file);
            // Return NULL to indicate failure.
            return NULL;
        }
        // Using strcpy to copy the contents of the buffer into the allocated memory for the new line.
        strcpy(lines[*numOfLines], buffer);
        // Increment the number of lines read.
        (*numOfLines)++;
    }
    // Close the file
    fclose(file);
    // Return the array of lines read from the file.
    return lines;
}

/* 
   FUNCTION:
    writeFile
   DESCRIPTION:
    This function writes an array of strings to a file, with each string on a new line.
   PARAMETERS:
    const char *fileName : The name of the file to write to.
    char **lines         : The array of strings to write to the file.
    int numOfLines       : The number of lines in the array.
   RETURNS:
    int : Returns 0 if the file is written successfully, -1 if an error occurs.
*/
int writeFile(const char *fileName, char **lines, int numOfLines) {
    // Using fopen to open the file in write mode.
    FILE *file = fopen(fileName, "w");
    // Using if statement to check if the file was opened successfully.
    if (file == NULL) {
        // Print an error message if the file could not be opened.
        fprintf(stderr, "Error opening output file '%s'\n", fileName);
        // Return -1 to indicate failure.
        return -1;
    }
    // Using for loop through each line in the array.
    for (int i = 0; i < numOfLines; i++) {
        // Using fprintf to write the current line to the file followed by a newline character.
        fprintf(file, "%s\n", lines[i]);
    }
    // Close the file
    fclose(file);
    // Return 0 to indicate success.
    return 0;
}

/* 
   FUNCTION:
    freeLines
   DESCRIPTION:
    This function frees the memory allocated for an array of strings.
   PARAMETERS:
    char **lines   : The array of strings to free.
    int numOfLines : The number of lines in the array.
   RETURNS:
    No return
*/
void freeLines(char **lines, int numOfLines) {
    // Using if statement to check if the lines pointer is NULL.
    if (lines == NULL)
        // Return nothing if it is NULL
        return;
    // Using for loop to traverse each line in the array.
    for (int i = 0; i < numOfLines; i++)
        // Free the memory allocated for the current line.
        free(lines[i]);
    // Free the memory allocated for the array of pointers.
    free(lines);
}