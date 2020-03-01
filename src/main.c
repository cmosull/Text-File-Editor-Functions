//Purpose: The purpose of this project is to read in an Input text file
//and a dicitonay file to perform editor functions on the input file using
//the dictionary. Two editor functions can be performed which are accessed
//via a menu. The user can either search and then replace a word or spell
//check the input document. The user can then save their changed input file
//to an output file.
//
//Assumptions: It is assumed that the user willbe realistic with their inputs when prompted.
//It is also assumed that words entered in will never be longer than 500 characters,
//as this would be very unusual.
//

#include "header.h"

int main(int argc, char *argv[]) {
  FILE *InputFile,*OutputFile,*DPtr;
  int choice,lines,a,b,test = 0,pdcheck = 0,maxlength;
  char pdictname[500];

  testArg(argc);

  InputFile = fopen(argv[1], "r");
  DPtr = fopen(argv[3], "r");

  testFile(InputFile,DPtr);

  lines = LineCounter(InputFile);
  maxlength = MaxLength(InputFile);

  char *strarr[lines];
  for (a = 0; a < lines; a++) {
    strarr[a] = (char *)calloc(maxlength, sizeof(char));
	  fgets(strarr[a], 200,InputFile);
   }

   while (test == 0) {
     choice = menu();

     if (choice == 1) {
       pdcheck = SpellCheck(strarr,DPtr,lines,maxlength,pdcheck,pdictname);
     }
     else if (choice == 2) {
       SearchReplace(strarr,lines,maxlength);
     }
     else if (choice == 3) {
       OutputFile = fopen(argv[2],"w+");
       for (b = 0; b < lines; b++) {
         fprintf(OutputFile,"%s",strarr[b]);
       }
       fclose(OutputFile);
     }
     else if (choice == 4) {
       test = 1;
       fclose(InputFile);
       fclose(DPtr);
     }
   }
   return 0;
}
