// Used to check if FILEPROCESSING_H is not defined to avoid multiple inclusion.
 #ifndef FILEPROCESSING_H
// Define FILEPROCESSING_H to mark that this file has been included.
 #define FILEPROCESSING_H  
 
// Prototype of readFile
 char **readFile(const char *fileName, int *numOfLines);  // Function prototype for readFile.
 // Prototype of writeFile
 int writeFile(const char *fileName, char **lines, int numOfLines);  // Function prototype for writeFile.
 // Prototype of freeLines
 void freeLines(char **lines, int numOfLines);  // Function prototype for freeLines.
 // End of include guard: FILEPROCESSING_H.
 #endif  
 