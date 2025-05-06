// Used to check if OPERATIONS_H is not defined to prevent multiple inclusion.
 #ifndef OPERATIONS_H    
 // Define OPERATIONS_H to mark that this header file has been included.
 #define OPERATIONS_H    
 
 // Define the maximum length for action strings in transformation operations.
 #define MAX_ACTION_LENGTH 50   
// Define the maximum length for words used in summary operations.
 #define MAX_WORD_LENGTH 100    
 
// Create a structure for filtering operations.
 typedef struct {       
     // Pointer to an array of keyword strings. 
     char **keywords;   
     // The number of keywords contained in the array.
     int numberOfKeywords;  
 } FilterConfig;         
 
// Create a structure for transformation operations.
 typedef struct {
    // Array to hold the transformation action.        
     char action[MAX_ACTION_LENGTH];  
 } TransformConfig;      

// Create a structure for summarizing operations.
 typedef struct {
    // Array to hold the word used for frequency calculation in summary operations.
     char word[MAX_WORD_LENGTH];  
 } SummarizeConfig;      
 
// Prototype of filteringlines.
 char **filterLines(char **lines, int numberOfLines, void *config, int *newNumberOfLines);  // Filters out lines based on specified keywords.
 
// Prototype of transforminglines.
 char **transformLines(char **lines, int numberOfLines, void *config, int *newNumberOfLines);  // Transforms lines based on the specified action.
 
// Prototype of summarizinglines.
 char **summarizeLines(char **lines, int numberOfLines, void *config, int *newNumberOfLines);  // Summarizes lines by computing statistics.
 // End of include guard: OPERATIONS_H.
 #endif  
 