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
