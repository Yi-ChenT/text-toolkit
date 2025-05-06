#include <stdio.h>
// Import the stdlib.h to use functions such as malloc(), free(), exit() and so on.
#include <stdlib.h>
// Import the string.h to use string manipulation functions such as strlen(), strcpy() and so on.
#include <string.h>
// Import the ctype.h to use character conversion functions such as tolower(), toupper() and so on.
#include <ctype.h>
// Import the operations.h to use operations functions such as filterLines, transformLines, summarizeLines.
#include "operations.h"

// Decalre a constant to store the max size of buffer
#define MAX_SIZE_OF_BUFFER 100

/* 
   FUNCTION:
    keyCheck
   DESCRIPTION:
    Checks if the given keyword exists within the specified line.
   PARAMETERS:
    const char *line    : The line in which to search for the keyword.
    const char *keyword : The keyword to search for.
   RETURNS:
    int: 1 if the keyword is found in the line, 0 otherwise.
*/
static int keyCheck(const char *line, const char *keyword) {  // Reference: https://www.geeksforgeeks.org/what-are-static-functions-in-c/
    // Get the length of the input line.
    int lineLen = strlen(line);
    // Get the length of the keyword.
    int keyLen = strlen(keyword);
    // Using if statement to check if the keyword is empty or not
    if (keyLen == 0)
        return 1;

    // Using for loop to traverse the line such that there are enough characters left for the keyword.
    for (int i = 0; i <= lineLen - keyLen; i++) {
        // Declare an index for comparing each character in the keyword.
        int j;
        // Using second for loop over each character of the keyword.
        for (j = 0; j < keyLen; j++) {
            // Using if statement to check if the current character match or not
            if (line[i + j] != keyword[j])
                // Break out of the loop
                break;
        }
        // Using if statement to check if the inner loop completed or not
        if (j == keyLen)
            return 1;
    }
    // Return 0 if the keyword was not found
    return 0;
}

/* 
   FUNCTION:
    countkeyword
   DESCRIPTION:
    Counts the number of times the specified keyword occurs in the given line.
   PARAMETERS:
    const char *line    : The line in which to count occurrences.
    const char *keyword : The keyword to count.
   RETURNS:
    int: The total count of keyword occurrences in the line.
*/
static int countkeyword(const char *line, const char *keyword) {  // Reference: https://www.geeksforgeeks.org/what-are-static-functions-in-c/
    // Declare an integer to initialize the count of keyword occurrences to zero.
    int count = 0;
    // Declare an integer to get the length of the input line.
    int lineLen = strlen(line);
    // Declare an integer to get the length of the keyword.
    int keyLen = strlen(keyword);
    // Using if statement to check if the keyword is empty or not
    if (keyLen == 0)
        return 0;
    // Using for loop through the line ensuring enough characters remain for a full keyword match.
    for (int i = 0; i <= lineLen - keyLen; i++) {
        // Declare an index for comparing characters of the keyword.
        int j;
        // Using second for loop to compare the segment of the line with the keyword.
        for (j = 0; j < keyLen; j++) {
            // Using if statement to check if any character match or not
            if (line[i + j] != keyword[j])
                // Break out of the loop
                break;
        }
        // If a complete match is found
        if (j == keyLen) {
            // Increment the count.
            count++;
            // Skip ahead by the length of the keyword to prevent overlapping matches.
            i += keyLen - 1;
        }
    }
    // Return the total count of keyword occurrences.
    return count;
}

/* 
   FUNCTION:
    filterLines
   DESCRIPTION:
    Filters out lines that contain any of the specified keywords.
   PARAMETERS:
    char **lines         : The array of strings representing the lines to filter.
    int numberOfLines    : The number of lines in the array.
    void *config         : The configuration settings containing keywords and their count.
    int *newNumberOfLines: Pointer to store the number of filtered lines.
   RETURNS:
    char**: A pointer to a new array of strings containing the filtered lines.
*/
char **filterLines(char **lines, int numberOfLines, void *config, int *newNumberOfLines) {
    // Cast the configuration pointer to a FilterConfig structure.
    FilterConfig filterConfig = *(FilterConfig *)config;
    // Initialize the pointer for the filtered lines array to NULL.
    char **filtered = NULL;
    // Set the new number of lines to zero.
    *newNumberOfLines = 0;

    // Using for loop through each line in the input array.
    for (int i = 0; i < numberOfLines; i++) {
        // Declare an integer to initialize a flag indicating whether the current line contains a keyword.
        int contains = 0;
        // Using for loop to traverse each keyword specified in the configuration.
        for (int j = 0; j < filterConfig.numberOfKeywords; j++) {
            // Using if statement to check if the current line contains the current keyword.
            if (keyCheck(lines[i], filterConfig.keywords[j])) {
                // Set the flag to true.
                contains = 1;
                // Break out of the loop
                break;
            }
        }
        // If the current line does not contain any of the keywords...
        if (!contains) {
            // Reallocate memory for the filtered array to add space for one more line.
            char **temp = realloc(filtered, ((*newNumberOfLines) + 1) * sizeof(char *));  // Reference: https://www.geeksforgeeks.org/g-fact-66/
            // Using if statement to check if reallocation fails or not
            if (temp == NULL) {
                fprintf(stderr, "Memory allocation error.\n");
                exit(1);
            }
            // Update the filtered array with the new memory.
            filtered = temp;
            // Allocate memory for a copy of the current line (including the null terminator).
            filtered[*newNumberOfLines] = malloc(strlen(lines[i]) + 1);
            // Using if statement to check if allocation fails or not
            if (filtered[*newNumberOfLines] == NULL) {
                fprintf(stderr, "Memory allocation error.\n");
                exit(1);
            }
            // Copy the current line into the newly allocated memory.
            strcpy(filtered[*newNumberOfLines], lines[i]);
            // Increment the count of filtered lines.
            (*newNumberOfLines)++;
        }
    }
    // Return the array containing the filtered lines.
    return filtered;
}

/* 
   FUNCTION:
    toUppercase
   DESCRIPTION:
    Converts a string to uppercase.
   PARAMETERS:
    const char *string : The string to convert.
   RETURNS:
    char*: A pointer to a newly allocated string that is the uppercase version of the input.
*/
static char *toUppercase(const char *string) {  // Reference: https://www.geeksforgeeks.org/what-are-static-functions-in-c/
    // Declare an integer to store the length of the input string.
    int len = strlen(string);
    // Allocate memory for the resulting uppercase string (plus one for the null terminator).
    char *result = (char *)malloc(len + 1);
    // Using if statement to check if memory allocation fails or not
    if (result == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }
    // Using for loop over each character in the input string.
    for (int i = 0; i < len; i++)
        // Convert the current character to uppercase and store it in the result.
        result[i] = toupper((unsigned char)string[i]);
    // Append the null terminator at the end of the result string.
    result[len] = '\0';
    // Return the newly created uppercase string.
    return result;
}

/* 
   FUNCTION:
    reverseString
   DESCRIPTION:
    Reverses the given string.
   PARAMETERS:
    const char *string : The string to reverse.
   RETURNS:
    char*: A pointer to a newly allocated string that is the reversed version of the input.
*/
static char *reverseString(const char *string) {  // Reference: https://www.geeksforgeeks.org/what-are-static-functions-in-c/
    // Declare an integer to store the length of the input string.
    int len = strlen(string);
    // Allocate memory for the reversed string (plus one for the null terminator).
    char *result = (char *)malloc(len + 1);
    // Using if statement to check if memory allocation fails or not
    if (result == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }
    // Using for loop over each character in the input string.
    for (int i = 0; i < len; i++)
        // Set the corresponding character in the result from the end of the input string.
        result[i] = string[len - i - 1];
    // Append the null terminator to the reversed string.
    result[len] = '\0';
    // Return the reversed string.
    return result;
}

/* 
   FUNCTION:
    transformLines
   DESCRIPTION:
    Transforms each line based on the specified action.
   PARAMETERS:
    char **lines         : The array of strings representing the lines to transform.
    int numberOfLines    : The number of lines in the array.
    void *config         : The configuration settings specifying the transformation action.
    int *newNumberOfLines: Pointer to store the number of transformed lines.
   RETURNS:
    char**: A pointer to a new array of strings containing the transformed lines.
*/
char **transformLines(char **lines, int numberOfLines, void *config, int *newNumberOfLines) {
    // Cast the configuration pointer to a TransformConfig structure.
    TransformConfig transformConfig = *(TransformConfig *)config;
    // Allocate memory for the array of transformed lines.
    char **transformed = (char **)malloc(numberOfLines * sizeof(char *));
    // Using if statement to check if memory allocation fails or not
    if (transformed == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }
    // Set the new number of lines to be equal to the input number of lines.
    *newNumberOfLines = numberOfLines;

    // Using if statement to check if the transformation action is "U" or not
    if (strcasecmp(transformConfig.action, "U") == 0) {
        // Using for loop over each line in the input array.
        for (int i = 0; i < numberOfLines; i++) {
            // Convert the current line to uppercase.
            transformed[i] = toUppercase(lines[i]);
        }
    }
    // Else if the transformation action is "R".
    else if (strcasecmp(transformConfig.action, "R") == 0) {
        // Using for loop over each line in the input array.
        for (int i = 0; i < numberOfLines; i++) {
            // Reverse the current line.
            transformed[i] = reverseString(lines[i]);
        }
    }
    else {
        // Using for loop over each line in the input array.
        for (int i = 0; i < numberOfLines; i++) {
            // Allocate memory for a copy of the current line.
            transformed[i] = malloc(strlen(lines[i]) + 1);
            // Using if statement to check if memory allocation fails or not
            if (transformed[i] == NULL) {
                fprintf(stderr, "Memory allocation error.\n");
                exit(1);
            }
            // Using strcpy to copy the original line into the allocated memory.
            strcpy(transformed[i], lines[i]);
        }
    }
    // Return the array of transformed lines.
    return transformed;
}

/* 
   FUNCTION:
    summarizeLines
   DESCRIPTION:
    Summarizes the given lines by providing statistics like total lines, frequency of a word, and average line length.
   PARAMETERS:
    char **lines         : The array of strings representing the lines to summarize.
    int numberOfLines    : The number of lines in the array.
    void *config         : The configuration settings containing the word to count.
    int *newNumberOfLines: Pointer to store the number of summary lines (always 3).
   RETURNS:
    char**: A pointer to a new array of strings containing the summary information.
*/
char **summarizeLines(char **lines, int numberOfLines, void *config, int *newNumberOfLines) {
    // Cast the configuration pointer to a SummarizeConfig structure.
    SummarizeConfig summarizeConfig = *(SummarizeConfig *)config;
    // Declare an integer and initialize the total frequency count
    int totalFrequency = 0;
    // Declare an integer and initialize the total number of characters.
    int totalChars = 0;

    // Using for loop over each line in the input array.
    for (int i = 0; i < numberOfLines; i++) {
        // Add the length of the current line to the total character count.
        totalChars += strlen(lines[i]);
        // Convert the current line to uppercase.
        char *upperLine = toUppercase(lines[i]);
        // Convert the target word to uppercase.
        char *upperWord = toUppercase(summarizeConfig.word);

        // Count the occurrences of the target word in the current line and add to totalFrequency.
        totalFrequency += countkeyword(upperLine, upperWord);
        // Free the memory allocated for the uppercase version of the current line.
        free(upperLine);
        // Free the memory allocated for the uppercase version of the target word.
        free(upperWord);
    }

    // Calculate the average line length.
    double avgLength = (numberOfLines > 0) ? ((double)totalChars / numberOfLines) : 0.0;

    // Set the number of summary lines to 3.
    *newNumberOfLines = 3;
    // Allocate memory for the array of summary strings.
    char **summary = (char **)malloc(3 * sizeof(char *));
    // Using if statement to check if memory allocation fails or not
    if (summary == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }

    // Declare a buffer for creating the summary strings.
    char buffer[MAX_SIZE_OF_BUFFER];
    // Format the summary string for the total number of lines.
    snprintf(buffer, sizeof(buffer), "Total Number of Lines: %d", numberOfLines);  // Reference: https://www.geeksforgeeks.org/snprintf-c-library/
    // Allocate memory for the first summary string.
    summary[0] = malloc(strlen(buffer) + 1);
    // Using if statement to check if memory allocation fails or not
    if (summary[0] == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }
    // Using strcpy to copy the formatted summary string into the allocated memory.
    strcpy(summary[0], buffer);

    // Format the summary string for the frequency of the specified word.
    snprintf(buffer, sizeof(buffer), "Frequency of '%s': %d", summarizeConfig.word, totalFrequency);  // Reference: https://www.geeksforgeeks.org/snprintf-c-library/
    // Allocate memory for the second summary string.
    summary[1] = malloc(strlen(buffer) + 1);
    // Using if statement to check if memory allocation fails or not
    if (summary[1] == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }
    // Using strcpy to copy the formatted summary string into the allocated memory.
    strcpy(summary[1], buffer);

    // Format the summary string for the average line length.
    snprintf(buffer, sizeof(buffer), "Average Line Length: %.2f", avgLength);  // Reference: https://www.geeksforgeeks.org/snprintf-c-library/
    // Allocate memory for the third summary string.
    summary[2] = malloc(strlen(buffer) + 1);
    // Using if statement to check if memory allocation fails or not
    if (summary[2] == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }
    // Using strcpy to copy the formatted summary string into the allocated memory.
    strcpy(summary[2], buffer);

    // Return the array containing the three summary strings.
    return summary;
}
