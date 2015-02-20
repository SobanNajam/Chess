#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "chess.h"
#include "chess.c"

int main()
{
  FILE* output=NULL;
  FILE* input=NULL;
  FILE* summary=NULL;

char* b[99]={
"    ","A","B","C","D","E","F","G","H","    ",
"01","ROOKw", "KNIGHTw", "BISHOPw", "QUEENw", "KINGw", "BISHOPw", "KNIGHTw", "ROOKw","01",
"02","PAWNw", "PAWNw", "PAWNw", "PAWNw", "PAWNw", "PAWNw", "PAWNw", "PAWNw","02",
"03","    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ","03",
"04","    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ","04",
"05","    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ","05",
"06","    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ","06",
"07","PAWNb", "PAWNb", "PAWNb", "PAWNb", "PAWNb", "PAWNb", "PAWNb", "PAWNb","07",
"08","ROOKb", "KNIGHTb", "BISHOPb", "QUEENb", "KINGb", "BISHOPb", "KNIGHTb", "ROOKb","08",
"    ","A","B","C","D","E","F","G","H"};

 int Aw[16] =  {11,12,13,14,15,16,17,18,21,22,23,24,25,26,27,28};
 int Ab[16] =  {71,72,73,74,75,76,77,78,81,82,83,84,85,86,87,88}; 
 
 int j=0,i,a=0;
 char ch,ch1;
 
  printf("\t\t\t\t \"GAME RULES\"\n\n");
  
  input = fopen("match summary.txt","w");       
  output = fopen("Game rules.txt","r");
          
  while ( fscanf(output,"%c",&ch) != EOF )
        printf("%c",ch);
          
  printf("\n\n\n");
               
  fclose(output);
  
 FILE* rules;
       rules = fopen("Chess Intro.txt","r");
 
 fflush(stdin);
 printf("Would you like to see the pattern of movement of elements (Y/N) ?");
 scanf(" %c",&ch);
 printf("\n\n");
 
 switch (ch)
        {
         case 'Y' : while(fscanf(rules,"%c",&ch1) != EOF )
                    printf("%c",ch1);
                    break;       
         case 'N' :break;
        }
  fclose(rules);      
 
 fflush(stdin);
 printf("\n\n");
 char plr1[50],plr2[50];
 printf ("Press \"ENTER\" to start the game:");
        getch();
 printf("\n\n");
 
 printf ("Enter 1st player's name:");
        gets(plr1);
 printf ("Enter 2nd player's name:");
        gets(plr2);
 
 printf("\n\n");

for (i=0;i<99;i++)
           {
           printf("%7.7s ",b[i]);
           if (i == 9 || i == 19 || i == 29 || i == 39 ||i == 49 || i == 59 || i == 69 || i == 79 || i == 89)
              printf("\n\n");
           }
while (1)   
      {
       move(b,Ab,Aw,&a,input,plr1,plr2);
       fflush(stdin);
       
       if (Aw[4]== 0 )
          {
           for (i=0;i<99;i++)
               {
               printf("%7.7s ",b[i]);
               if (i == 9 || i == 19 || i == 29 || i == 39 ||i == 49 || i == 59 || i == 69 || i == 79 || i == 89)
                  printf("\n\n");
               }
           printf("\nBLACK WINS!!\n");
           break;
          }
       if (Ab[12]== 0 )
          {
          for (i=0;i<99;i++)
              {
              printf("%7.7s ",b[i]);
              if (i == 9 || i == 19 || i == 29 || i == 39 ||i == 49 || i == 59 || i == 69 || i == 79 || i == 89)
                 printf("\n\n");
              }
           printf("\nWHITE WINS!!\n");
           break;
          }
       if (stalemate(Aw,'w') == 2 || stalemate(Ab,'b')== 2 )
          {
          printf("\nIt's a Stalemate, the Game is drawn\n");
          fprintf(input,"\nIt's a Stalemate, the Game is drawn\n");
          break;
          }
       if (a==0)
          {
           for (i=0;i<99;i++)
               {
               printf("%7.7s ",b[i]);
               if (i == 9 || i == 19 || i == 29 || i == 39 ||i == 49 || i == 59 || i == 69 || i == 79 || i == 89)
                  printf("\n\n");
               }
           }
      else if (a  == 1)
           {
           for (i=0;i<99;i++)
               {
               printf("%7.7s ",b[i]);
               if (i == 9 || i == 19 || i == 29 || i == 39 ||i == 49 || i == 59 || i == 69 || i == 79 || i == 89)
                  printf("\n\n");
               }
           printf("\n%s Is checkmated\n%s WINS!!\n",plr2,plr1);
           fprintf(input,"\n%s Is checkmated\n%s WINS!!\n",plr2,plr1);
           break;
           }
      else if (a  == -1)
           {
           for (i=0;i<99;i++)
               {
               printf("%7.7s ",b[i]);
               if (i == 9 || i == 19 || i == 29 || i == 39 ||i == 49 || i == 59 || i == 69 || i == 79 || i == 89)
                  printf("\n\n");
               }
           printf("\n%s Is checkmated\n%s WINS!!\n",plr1,plr2);
           fprintf(input,"\n%s Is checkmated\n%s WINS!!\n",plr1,plr2);
           break;
           }
      j++;   
      }        
             
fclose(input); 
free(b);
getch();
return 0;
}
