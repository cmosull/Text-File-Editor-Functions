#include "header.h"

void testArg(int argnum) {
  if (argnum != 4) {
   fprintf(stderr, "\nError: Please enter three files to be read in.");
   fprintf(stderr, "\n./prog5 [Input File] [Output File] [Dictionary]\n\n");
   exit(1);
  }
}

void testFile(FILE *In, FILE *Dict) {
  if (In == NULL || Dict == NULL) {
    fprintf(stderr,"\nError opening File(s).\n\n");
    exit(1);
  }
}

int LineCounter(FILE *In) {
  int linenum = 0;
  char buff[256];

  while (fgets(buff,256,In)!=NULL) {
   linenum++;
  }
  rewind(In);

  return linenum;
}

int MaxLength(FILE *In) {
  int lengthLine, maxlength = 0;
  char buff[256];

  while (fgets(buff,256,In)!=NULL) {
   lengthLine = strlen(buff);
   if (lengthLine > maxlength) {
    maxlength = lengthLine;
   }
  }
  rewind(In);

  return maxlength;
}

//Menu function prints out a menu to the user so that the user can choose which function they want performed
int menu() {

   int numberchoice,check = 0;
   char numstr[3];

   printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
   printf("================================================================================");
   printf("\nPlease choose one of the following options by typing the corresponding number");
   printf("\n1. Check the spelling using the Dictionary");
   printf("\n2. Search and Replace");
   printf("\n3. Save the file to an Output File");
   printf("\n4. Exit the Program");
   printf("\n================================================================================");
   printf("\n\nChoice: ");

   while (check == 0) {
	  fgets(numstr, 3, stdin);
      sscanf(numstr, "%i", &numberchoice);
	  if (numberchoice < 1 || numberchoice > 4) {
		 printf("Please enter in a number between 1 and 4: ");
		 check = 0;
	  }
	  else {
		 check =  1;
	  }
   }

   return numberchoice;
}

//Search and Replace function prompts user for word to search and replace in the file
void SearchReplace(char *arr[], int size, int linelen) {
   int a,b,i,j,k,length,length2,len = 0,lendifference,cnt,checkmatch = 0,test = 0;
   char teststr[128],replacestr[128],ans[3];
   char tempstr1[128],tempstr2[128];

   printf("Please enter the text string to be searched for: ");
   fgets(teststr, sizeof(teststr), stdin);
   length = strlen(teststr) - 1;

   for (i = 0; i < size; i++) {
     for (j = 0; j < linelen; j++) {
       if (memcmp(arr[i] + j,teststr,length) == 0) {
         if (strncmp((arr[i] + j) + length," ",1) == 0) {
           printf("\nFound at line: %i, character #%i", i+1, j+1);
           checkmatch++;
         }
       }
     }
   }

   if (checkmatch > 0) {

	  printf("\n\nPlease enter a string for replacement: ");
	  fgets(replacestr, 128, stdin);
	  length2 = strlen(replacestr) - 1;


	  char finalreplace[length2];
	  strncpy(finalreplace, replacestr, length2);
	  lendifference = length2 - length;


	  for (k = 0; k < size; k++) {
		 cnt = 0;
		 for (a = 0; a < linelen; a++) {

			if(memcmp(arr[k] + a, teststr, length) == 0) {
			   cnt++;

			   arr[k] = (char *)realloc(arr[k],linelen + lendifference*cnt);

			   for (b = 0; b < 128; b++) {
				  tempstr1[b] = '\0';
				  tempstr2[b] = '\0';
			   }

			   strncpy(tempstr1, arr[k], a);
			   strcpy(tempstr2, arr[k] + length + a);
			   strcpy(arr[k], tempstr1);
			   strncat(arr[k], finalreplace,length2);
			   len = strlen(tempstr2);
			   strncat(arr[k], tempstr2,len);
			   a = a + length2 - 1;
			}
		 }
	  }
   }

   if (checkmatch == 0) {
	  printf("\n\nWord not found! Returning to menu...Press 1 to continue: ");

	  while (test == 0) {
		 fgets(ans,3,stdin);
	  	 if (strncmp(ans,"1",1) == 0) {
			test = 1;
		 }
		 else {
			printf("\nPlease enter '1' to continue: ");
		    test = 0;
		 }
	  }
   }
}


//SpellCheck function runs through the enitre string array and checks the spelling of every word against a dictionary/personal
//dictionary if it exists
int SpellCheck(char *arr[], FILE *Dptr, int size, int linelen, int pdict, char* nameofdictionary) {
   int a,b = 0,i,f,m,n,y,length,length2,match,lendif,ans2,check,contin = 0;
   char tempstr[128],buff[128],buff2[128],nameofdict[128],outstr1[128],outstr2[128],replacestr[128],ans[3],finalreplace[128],ans3[3];
   FILE *personaldict;

   if (pdict == 1) {
	  personaldict = fopen(nameofdictionary, "a+");
   }

   for (a = 0; a < size; a++) {
	  b = 0;
	  while (b < linelen) {

		 for (i = 0; i < 128; i++) {
			buff[i] = '\0';
			tempstr[i] = '\0';
		 }

		 while ((*(arr[a] + b) < 'a' || *(arr[a] + b) > 'z') && (*(arr[a] + b) < 'A' || *(arr[a] + b) > 'Z')) {
			b++;
		 }

		 sscanf(arr[a] + b, "%s", buff);
		 length = strlen(buff);

		 for (y = 0; y < length; y++) {
			buff[y] = tolower(buff[y]);
			if (buff[y] < 'a' || buff[y] > 'z') {
			   buff[y] = '\0';
			   length = strlen(buff);
			}
		 }

		 rewind(Dptr);
		 match = 0;

		 while(fgets(tempstr,128,Dptr) != NULL && match == 0)  {
			if (strncmp(tempstr,buff,length) == 0) {

			   match = 1;
			}
		 }

		 length2 = strlen(tempstr) - 1;
		 lendif = length2 - length;

		 if (pdict == 1 && match == 0) {
			rewind(personaldict);
			while(fgets(buff2,128,personaldict) != NULL && match == 0) {
			   if (strncmp(buff,buff2,length) == 0) {

				  match = 1;
			   }
			}
		 }

		 if (match == 0) {

			for (n = 0; n < 3; n++) {
			   ans[n] = '\0';
			}
			for (f = 0; f < 128; f++) {
			   replacestr[f] = '\0';
			   finalreplace[f] = '\0';
			}


			check = 0;

			while (check == 0) {
			   printf("\nThe word %s was not found in the dictionary. Would you like to replace it? [Y/N] ",buff);
			   fgets(ans,3,stdin);
			   if ((strncmp(ans,"Y",1) == 0)) {
				  check = 1;
				  ans2 = 1;
			   }
			   else if (strncmp(ans,"N",1) == 0) {
				  check = 1;
				  ans2 = 2;
			   }
			   else {
				  printf("\nPlease enter either Y or N\n");
			   }
			}

			if (ans2 == 1) {
			   printf("\n\nPlease enter a string for replacement: ");
			   fgets(replacestr, 128, stdin);
			   int cnt = 0;

			   while (replacestr[cnt] != '\n') {
				  finalreplace[cnt] = replacestr[cnt];
				  cnt++;
			   }

			   length2 = strlen(finalreplace);
			   lendif = length2-length;

			   linelen += lendif;

			   arr[a] = (char *)realloc(arr[a], linelen);

			   for (m = 0; m < 128; m++) {
				  outstr1[m] = '\0';
				  outstr2[m] = '\0';
			   }

			   strncpy(outstr1, arr[a], b);
			   strcpy(outstr2, arr[a] + length + b);
			   strcpy(arr[a], outstr1);
			   strcat(arr[a], finalreplace);
			   strcat(arr[a], outstr2);
			   b += lendif;
			}

			if (ans2 == 2) {
			   if (pdict == 0) {

				  printf("\n\nA personal dictionary must be created. Please enter the name: ");
				  fgets(nameofdict,128,stdin);
				  sscanf(nameofdict,"%[^\n]s",nameofdictionary);

				  strcat(nameofdictionary,".txt");
				  personaldict = fopen(nameofdictionary,"w+");
				  fprintf(personaldict, "%s\n", buff);
				  pdict = 1;
			   }
			   else if(pdict == 1){
				  fprintf(personaldict, "%s\n", buff);
			   }
			}
		 }
		 b += length;
	  }
   }

   if (match == 1) {
	  printf("\n\nSpelling Check Complete. No errors found! Please press '1' to menu: ");
	  while (contin == 0) {
		 fgets(ans3,3,stdin);
		 if (strncmp(ans3,"1",1) == 0) {
			contin = 1;
		 }
		 else {
			printf("\nPlease enter '1' to return to menu: ");
			contin = 0;
		 }
	  }
   }

   fclose(personaldict);
   return pdict;
}
