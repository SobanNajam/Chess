#include <stdio.h>

int determine=0;
void move(char** chess, int* Ab, int* Aw,int* big,FILE* name,char* plr1,char* plr2)
{
     int a=0,i,everything=0;
     if (determine==0)
         printf("\nTURN: %s\n",plr1);
     else
         printf("\nTURN: %s\n",plr2);
 char rt,rf;
 int ct=0,cf=0;
 int ans1=0,ans2=0;
     printf("\nEnter the position:\n");
     fflush(stdin);
     scanf("%c%d to %c%d",&rf,&cf,&rt,&ct);
     
     ans1 = decoder(rf,cf); //from
     ans2 = decoder(rt,ct); //to
     fflush(stdin);
     
   for (i=0;i<11;i++)
       if (ans2==i)
          {
           printf("\nIllegal Move.Please re-enter your move\n");
           everything=1;
          }
   
   for (i=90;i<99;i++)
       if (ans2==i)
           {
           printf("\nIllegal Move.Please re-enter your move\n");
           everything=1;
            }
          
   for (i=19;i<90;i+=9)
       {
        if (ans2==i)
           {
            printf("\nIllegal Move.Please re-enter your move\n");
            everything=1;
           }
        else 
           {
            i++;
            if (ans2==i)
               {
               printf("\nIllegal Move.Please re-enter your move\n");
               everything=1;
               }
           }
       }
 if (everything != 1)
     {
      a=the_checker ( Ab,  Aw, ans1, ans2, rf,cf,rt,ct);
     
      if (a==0)
         {
          swap(&chess[ans1],&chess[ans2],Ab,Aw,ans1,ans2);
          check_calculator(Ab,Aw,rf,cf,rt,ct);
          
          if (determine == 1)
             fprintf(name,"%s moved from %c%d to %c%d\n",plr1,rf,cf,rt,ct);
          else
             fprintf(name,"%s moved from %c%d to %c%d\n",plr2,rf,cf,rt,ct);
         }
      else 
         {
          printf("\nIllegal Move.Please re-enter your move\n");
          move(chess,Ab,Aw,big,name,plr1,plr2);        
         }
        
     if (determine == 1)
        *big=checkmateB(Ab,Aw);
     else
        *big=checkmateW(Ab,Aw);
    }
}
void swap(char** a, char** b,int* Ab, int* Aw,int from, int to)
{
     int check=0,count=0,k=0;
     char* t={"    "};
     if (t == *b)
        {
        *b=*a;
        *a=t;
        count=1;
        }
     else
         {
         *b=*a;
         *a=t;
         count=1;
         k=1;
         }
     if (count==1)
        {
        if (determine==0)
           {
            record_keeper(Aw, from, to);
            determine=1;
            if (k==1)
                r(Ab,to,from);
           }
        else
           {
            record_keeper(Ab, from, to);
            determine=0;
            
            if (k==1)
                r(Aw,to,from);
            }
        }
 free(t);
}

int decoder(char row,int col)
{
 int conv=0;
    switch(row)
    {
    case 'A' : conv = 1;
             break;
    case 'B' : conv = 2;
             break;
    case 'C' : conv = 3;
             break;
    case 'D' : conv = 4;
             break;
    case 'E' : conv = 5;
             break;
    case 'F' : conv = 6;
             break;
    case 'G' : conv = 7;
             break;
    case 'H' : conv = 8;
             break;
    default  : break;          
    }
  return conv + (col*10);
}
void record_keeper(int* array, int from, int to)
{
     int i;
     for (i = 0; i < 16; i++)
         {
          if (*(array +i) == from)
             {
               *(array + i) = to;  
               break;
              }     
          } 
}
void r(int* array, int to,int from)
{
 int i=0,j,k;
 for (i=0;i<16;i++)
     {
      if(*(array + i) == to)
        {
         *(array + i) = 0;
          break;
        }
      }
}
int the_checker (int* Ab, int* Aw, int from,int to,char a,int x,char b,int y)
{
 int i,j;
 char clr;
 
 if (from == 0)
   return 1;
 for (i = 0; i < 16; i++)
        {
          if ( *(Ab +i) == from)
             {
               clr = 'b';
               j=i;       
               break;
             }     
          else if (*(Aw +i) == from)
             {
               clr = 'w';
               j=i;
               break;
              }
        }
 if (clr=='w')
    {
     for (i=8;i<16;i++)
         if (j == i)
             return legal_pawn(Ab,Aw,to,from,'w');
     
	 if (j== 0 || j==7 )
        return legal_rook(Ab,Aw,to,from,'w',a,x,b,y);
        
             
	 else if (j== 2 || j==5)
        return legal_bishop(Ab,Aw,to,from,'w');
                
     else if (j==1 || j==6)
          return legal_knight(Ab,Aw,to,from,'w');
                 
     else if (j== 3 )
          return legal_queen(Ab,Aw,to,from,a,x,b,y,'w');   
      
     else if (j== 4)
          return legal_king(Ab,Aw,to,from,'w');
      }
 else if (clr == 'b')
    {
     for (i=0;i<8;i++)
         if (j == i)
             return legal_pawn(Ab,Aw,to,from,'b');
                 
     if (j== 8 || j==15 )
        return legal_rook(Ab,Aw,to,from,'b',a,x,b,y);
                
     else if (j== 10 || j==13)
        return legal_bishop(Ab,Aw,to,from,'b');
                            
     else if (j== 9 || j==14)
       return legal_knight(Ab,Aw,to,from,'b');
     
     else if (j== 11)
          return legal_queen(Ab,Aw,to,from,a,x,b,y,'b');  
             
     else if (j== 12)
          return legal_king(Ab,Aw,to,from,'b');
     }
 else return 1;
}
int legal_pawn(int* black, int* white, int to, int from, char clr)
{
 int i,frst;
    
    for (i=0;i<10;i++)
       if (to==i)
          return 1;
   
   for (i=90;i<99;i++)
       if (to==i)
          return 1;
          
   for (i=19;i<90;i+=9)
       {
        if (to==i)
           return 1;
        else 
           {
            i++;
            if (to==i)
               return 1;
           }
       }
 int ok = from - to,yes=0,no=1;
 
   if (clr == 'w')
      { 
        for (frst=21;frst<29;frst++)
            if (from == frst)
               if ( ok == -20)
                  return yes;
                        
       if (ok == -9 || ok == -10|| ok == -11)
          {
           for (i = 0; i < 16; i++)
               {
                if (*(white + i) == to)
                   return no;           
                else if (*(black + i) == to)
                   {
                    if (to == from + 11 || to == from + 9)
                       return yes;
                    else      
                       return no; 
                    }
                }if (i==16 && to == from +10)return yes;
                 else return no;
           }else return no;
       }
    
   if(clr == 'b')
   { 
    for (frst=71;frst<79;frst++)
            if (from == frst)
               if ( ok == 20)
                  return yes;
                  
    if (ok == 9 || ok == 10|| ok == 11)
          {
           for (i = 0; i < 16; i++)
               {  
               if (*(black + i) == to)
                   return no;           
               else if (*(white + i) == to)
                   {
                    if (to == (from - 11) || to == (from - 9) )
                       return yes;
                   else      
                       return no; 
                   }           
                }if (i==16 && to == from -10)return yes;
                 else return no;
           }else return no;
    }
}
int legal_knight(int* black, int* white, int to, int from, char clr)
{
    int j;
    for (j=0;j<10;j++)
       if (to==j)
          return 1;
   
   for (j=90;j<99;j++)
       if (to==j)
          return 1;
          
   for (j=19;j<90;j+=9)
       {
        if (to==j)
           return 1;
        else 
           {
            j++;
            if (to==j)
               return 1;
           }
       }
    
        int beat, d = from - to,i, no=1, yes=0;
        if (clr == 'b')
           {
            for (i = 0; i< 16; i++)
                {
                  if (*(white + i) == to)
                     {
                      beat = 1;         
                      break;
                     }  
                  else if (*(black + i) == to)
                     return no;        
                 }
            if (i==16)
               beat=1;
           }
        else if (clr == 'w')
           {
            for (i = 0; i< 16; i++)
                {
                 if (*(black + i) == to)
                    {
                     beat = 1;         
                     break;
                    }
                 else if (*(white + i) == to)
                      return no;        
                 }           
            if (i==16)
               beat=1;
           }       
       if (beat == 1)
          {
           if (d == 8 || d == -8 || d == 12 || d == -12|| d == 21 || d== -21 || d == 19 || d == -19)
             return yes;      
           else
             return no;      
           }
}
int legal_rook(int* black, int* white, int to, int from, char clr,char a,int x,char b,int y)
{
    int k;
    for (k=0;k<10;k++)
       if (to==k)
          return 1;
   
   for (k=90;k<99;k++)
       if (to==k)
          return 1;
          
   for (k=19;k<90;k+=9)
       {
        if (to==k)
           return 1;
        else 
           {
            k++;
            if (to==k)
               return 1;
           }
       }
 int distance = to - from,i=1,yes=0,no=1,abc=from;
 
     if ( a == b || x == y)
        {
         if (clr == 'w')
            {
            if (distance > 0)
               {
                if (a == b)
                   {
                    while( (abc)!=to)
                     {
                      for (i=0;i<16;i++)
                          if (abc+10==to)break;                     
                          else if (*(white + i) == (abc+10 ) || *(black + i) == (abc +10))
                             return no;
                          abc += 10; 
                      }for (i=0;i<16;i++)
							{
							if (abc==to && *(black + i) == abc  )return yes;
							else if (abc==to && *(white + i) == abc  )return no;
							}
						if (i==16)return yes;
                   }                    
                else if (x == y)
                        {
                        while((abc)!=to)
                          {
                          for (i=0;i<16;i++)
                             if (abc+1==to)break;
                             else if (*(black + i) == (abc+1 ) || *(white + i) == (abc +1))
                                 return no;
                             
                             abc += 1;             
                          }for (i=0;i<16;i++)
							{
							if (abc==to && *(black + i) == abc  )return yes;
							else if (abc==to && *(white + i) == abc  )return no;
							}
						if (i==16)return yes;    
                        }
               }  
               else if (distance < 0)
                  {
                  if (a == b)
                     {
                     while((abc)!=to){
                      for (i=0;i<16;i++)
                         if (abc-10==to)break;
                         else if (*(white + i) == (abc -10) || *(black + i) == (abc -10))
                             return no;
                                   
                         abc -= 10;             
                      }for (i=0;i<16;i++)
							{
							if (abc==to && *(black + i) == abc  )return yes;
							else if (abc==to && *(white + i) == abc  )return no;
							}
						if (i==16)return yes;
                  }                    
                  else if (x == y)
                        {
                         while ((abc)!=to)
                            {
							 for (i=0;i<16;i++)
							     if (abc-1==to)break;
								 else if (*(black + i) == (abc -1) || *(white + i) == (abc -1))
									return no;
                               
                             abc -=1;             
                            }for (i=0;i<16;i++)
								{
								 if (abc==to && *(black + i) == abc  )return yes;
								 else if (abc==to && *(white + i) == abc  )return no;
								}
						     if (i==16)return yes; 
                        }
                  }
            }  
            if (clr == 'b')
            {
             if (distance > 0)
               {
                if (a == b)
                   {
                     while((abc)!=to)
                     {
                     for (i=0;i<16;i++)
                         if (abc+10==to)break;
                         else if (*(black + i) == (abc +10) || *(white + i) == (abc +10))
                            return no;
                     abc += 10;             
                   }for (i=0;i<16;i++)
							{
							if (abc==to && *(white + i) == abc  )return yes;
							else if (abc==to && *(black + i) == abc  )return no;
							}
						if (i==16)return yes;
                   }
                else if (x == y)
                    {
                        while ((abc)!=to)
                          {
                           for (i=0;i<16;i++)
                             if (abc+1==to)break;
							 if (*(black + i) == (abc+1 ) || *(white + i) == (abc+1 ))
                                return no;
                                
                             abc += 1;             
                          } for (i=0;i<16;i++)
								{
								 if (abc==to && *(white + i) == abc  )return yes;
								 else if (abc==to && *(black + i) == abc  )return no;
								}
						    if (i==16)return yes;
                    }                    
               }  
            else if (distance < 0)
                {
                   if (a == b)
                     {
                      while ((abc)!=to)
                            {
                            for (i=0;i<16;i++)
                                if (abc-10==to)break;
                                else if (*(black + i) == (abc-10 ) || *(white + i) == (abc-10 ))
                                   return no;
                          
                            abc -= 10;             
                            }for (i=0;i<16;i++)
								{
								 if (abc==to && *(white + i) == abc  )return yes;
								 else if (abc==to && *(black + i) == abc  )return no;
								}
						    if (i==16)return yes;
                      }
				    else if (x == y)
                     {
                         while ((abc)!=to)
                           {
                            for (i=0;i<16;i++)
                              if (abc-1==to)break;
                              else if (*(black + i) == (abc-1 ) || *(white + i) == (abc -1))
                                 return no;
                                
                            abc -= 1;             
                           }for (i=0;i<16;i++)
								{
								 if (abc==to && *(white + i) == abc  )return yes;
								 else if (abc==to && *(black + i) == abc  )return no;
								}
							if (i==16)return yes;
                    } 		
                }
            }
        }
        else
            return no;   
}
int legal_bishop(int* black, int* white, int to, int from,char clr)
{  
   int l;
   for (l=0;l<10;l++)
       if (to==l)
          return 1;
   
   for (l=90;l<99;l++)
       if (to==l)
          return 1;
          
   for (l=19;l<90;l+=9)
       {
        if (to==l)
           return 1;
        else 
           {
            l++;
            if (to==l)
               return 1;
           }
       }
   
 int distance = to - from,i=1,yes=0,no=1,abc=from;
 if ( distance%9 ==0 ||  distance%11 ==0 )
    {
		 if (distance > 0 && distance % 11 == 0)
            {
                    while((abc)!=to)
                     {
                       
                       for (i=0;i<16;i++)
                          if ((abc+11)==to)break;
                          else if (*(white + i) == (abc +11) || *(black + i) == (abc +11))
                             return no;
                       abc += 11; 
                      }  if(clr == 'w' )
							{
						     for (i=0;i<16;i++)
								{
                                 if ( abc == to && abc == *(black + i) )return yes;          
                                 else if ( *(white + i) == abc )return no;
                                 }
                             if(i==16)return yes;
							}
						 else
			               {
		     				for (i=0;i<16;i++)
								{
                                 if ( *(white + i) == abc )return yes;          
                                 else if ( *(black + i) == abc )return no;
                                 }          
							 if(i==16)return yes;
							}   
			}
	 else if (distance > 0 && distance %9 == 0)
			{
             while(abc!=to)
				{
				 for (i=0;i<16;i++)
					if ((abc+9)==to)break;
                    else if (*(white + i) == (abc+9) || *(black + i) == (abc+9 ))
						return no;
							         
				 abc += 9;             
				}if(clr == 'w')
							{
						     for (i=0;i<16;i++)
								{
                                 if ( *(black + i) == abc )return yes;          
                                 else if ( *(white + i) == abc )return no;
                                 }
                             if(i==16)return yes;
							}
						 else
			               {
						     for (i=0;i<16;i++)
								{
                                 if ( *(white + i) == abc )return yes;          
                                 else if ( *(black + i) == abc )return no;
                                 }          
							 if(i==16)return yes;
							}
            }   
		else if (distance < 0 && distance %11 == 0)
            {
             while(abc!=to)
                {
                 for (i=0;i<16;i++)
                     if ((abc-11)==to)break;
                     else if (*(white + i) == (abc -11) || *(black + i) == (abc -11))
                        return no;
                 abc -= 11; 
                }if(clr == 'w')
							{
						     for (i=0;i<16;i++)
								{
                                 if ( *(black + i) == abc )return yes;          
                                 else if ( *(white + i) == abc )return no;
                                 }
                             if(i==16)return yes;
							}
						 else
			               {
						     for (i=0;i<16;i++)
						         {
								   if ( *(white + i) == abc )return yes;
                                   else if ( *(black + i) == abc )return no;          
                                  }
                             if(i==16)return yes;
							}        
            } 
		 else if (distance < 0 && distance %9 == 0)
			{
			 while(abc!=to)
				{
                 for (i=0;i<16;i++)
				     if ((abc-9)==to)break;
                     else if (*(white + i) == (abc -9) || *(black + i) == (abc -9))
						 return no;
				 abc -= 9;             
				}if(clr == 'w')
							{
						     for (i=0;i<16;i++)
		         				{
                                if ( *(black + i) == abc )return yes;          
							    else if ( *(white + i) == abc )return no;
                               }
                             if(i==16)return yes;
							}
			    else
			               {
						     for (i=0;i<16;i++)
								{
                                 if ( *(white + i) == abc )return yes;          
                                 else if ( *(black + i) == abc )return no;
                                 }          
							 if(i==16)return yes;
							}
           }   
	}else return no;
}
int legal_queen(int* Ab,int* Aw,int to,int from,char a,int x,char b, int y,char clr)
{
    int m;
    for (m=0;m<10;m++)
       if (to==m)
          return 1;
   
   for (m=90;m<99;m++)
       if (to==m)
          return 1;
          
   for (m=19;m<90;m+=9)
       {
        if (to==m)
           return 1;
        else 
           {
            m++;
            if (to==m)
               return 1;
           }
       }
int distance = to- from;

if (a==b || x==y)
   return legal_rook(Ab,Aw,to,from,clr,a,x,b,y);
else 
   return legal_bishop(Ab,Aw,to,from,clr); 
}
int legal_king(int* black, int* white, int to, int from, char clr)
{
    int n;
    for (n=0;n<10;n++)
       if (to==n)
          return 1;
   
   for (n=90;n<99;n++)
       if (to==n)
          return 1;
          
   for (n=19;n<90;n+=9)
       {
        if (to==n)
           return 1;
        else 
           {
            n++;
            if (to==n)
               return 1;
           }
       }
 int ok = from - to,i,yes=0,no=1;
 
   if (clr == 'w')
      { 
       if (ok == -9 || ok == -10|| ok == -11 || ok == 1 || ok == -1 || ok == 9 || ok == 10|| ok == 11)
          {
           for (i = 0; i < 16; i++)
               {
                if (*(white + i) == to)
                   return no;           
                else if (*(black + i) == to)
                   return yes;
                }
           if (i==16)
              return yes;
              
           }else return no;
       }
    
   if(clr == 'b')
   { 
    if (ok == -9 || ok == -10|| ok == -11 || ok == 1 || ok == -1 || ok == 9 || ok == 10|| ok == 11)
          {
           for (i = 0; i < 16; i++)
               {  
               if (*(black + i) == to)
                   return no;           
               else if (*(white + i) == to)
                   return yes;
               }     
               if (i==16)
                  return yes;
               
           }else return no;
    }
}
void check_calculator(int* Ab, int* Aw, char a,int x,char b,int y)
{
    int black =1,white=1,i,j;
   
   char a1,b2;
   int x1,y2;
   
   recoder(*(Ab+12),&b2,&y2);
   for (j=0;j<16;j++)
             {
              recoder(*(Aw+j),&a1,&x1);               
              if (the_checker(Ab, Aw, *(Aw+j),*(Ab+12), a1, x1, b2, y2) == 0)
                     black = 0;       
                  
             }

   recoder(*(Aw+4),&b2,&y2);               
   for (i = 0; i < 16; i++)
        {
        recoder(*(Ab+i),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Ab+i),*(Aw+4), a, x, b, y) == 0)
            white = 0;
        }
    
    if(white == 0)
         printf("\nWhite under CHECK !!\n"); 
         
    if (black == 0)
        printf("\nBlack Under CHECK!!\n"); 
}
void recoder (int x,char* c,int* a)
{
 switch(x%10)
     {
     case 1 : *c = 65;
                break;
     case 2 : *c = 66;
                break;
     case 3 : *c = 67;
                break;
     case 4 : *c = 68;
                break;
     case 5 : *c = 69;
                break;
     case 6 : *c = 70;
                break;
     case 7 : *c = 71;
                break;
     case 8 : *c = 72;
                break;
     default  : break;
     }
 *a = x/10;
}

int checkmateB(int* Ab,int* Aw)
{
char a,b,a1;
int x,y,j,x1,i;
int count=0,count_2=0,chl=0,chk=0;

recoder(*(Ab+12),&a,&x);

recoder(*(Ab+12)-1,&b,&y);

if (the_checker(Ab,Aw,*(Ab+12),*(Ab+12)-1,a,x,b,y) == 0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Aw+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Aw+j),*(Ab+12)-1, a1, x1, b, y) == 0)
             {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Ab+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 0)
                     return 0;
                  }    
              if (i==16 && chl==1)
                     {count++;chk=1;}
              }
        }
   }
   chl=0;
recoder(*(Ab+12)+1,&b,&y);
if (the_checker(Ab,Aw,*(Ab+12),*(Ab+12)+1,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Aw+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Aw+j),*(Ab+12)+1, a1, x1, b, y) == 0)
             {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Ab+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                  {count++;chk=1;}          
              }
        }
   }
   chl=0;
recoder(*(Ab+12)-10,&b,&y);
if (the_checker(Ab,Aw,*(Ab+12),*(Ab+12)-10,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Aw+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Aw+j),*(Ab+12)-10, a1, x1, b, y) == 0)
            {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Ab+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                  {count++;chk=1;}           
            }     
        }
   }
chl=0;
recoder(*(Ab+12)+10,&b,&y);
if (the_checker(Ab,Aw,*(Ab+12),*(Ab+12)+10,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Aw+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Aw+j),*(Ab+12)+10, a1, x1, b, y) == 0)
              {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Ab+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                  {count++;chk=1;}           
            }            
        }
   }
chl=0;
recoder(*(Ab+12)-11,&b,&y);
if (the_checker(Ab,Aw,*(Ab+12),*(Ab+12)-11,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Aw+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Aw+j),*(Ab+12)-11, a1, x1, b, y) == 0)
              {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Ab+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                  {count++;chk=1;}            
            }        
        }
   }
chl=0;
recoder(*(Ab+12)+11,&b,&y);
if (the_checker(Ab,Aw,*(Ab+12),*(Ab+12)+11,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Aw+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Aw+j),*(Ab+12)+11, a1, x1, b, y) == 0)
              {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Ab+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                  {count++;chk=1;}            
            }            
        }
   }
   chl=0;
recoder(*(Ab+12)-9,&b,&y);
if (the_checker(Ab,Aw,*(Ab+12),*(Ab+12)-9,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Aw+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Aw+j),*(Ab+12)-9, a1, x1, b, y) == 0)
             {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Ab+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                  {count++;chk=1;}           
            }            
        }
   }
   chl=0;
recoder(*(Ab+12)+9,&b,&y);
if (the_checker(Ab,Aw,*(Ab+12),*(Ab+12)+9,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Aw+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Aw+j),*(Ab+12)+9, a1, x1, b, y) == 0)
              {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Ab+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Ab+i),*(Aw+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                  {count++;chk=1;}         
            }            
        }
   }
   
if (chk==1)
   if (count_2 == count)
      return 1;
   else
       return 0;
   
else 
  return 0;
}

int checkmateW(int* Ab,int* Aw)
{
char a,b,a1;
int x,y,j,x1,i;
int count=0,count_2=0,chl=0,chk=0;

recoder(*(Aw+4),&a,&x);

recoder(*(Aw+4)-1,&b,&y);
if (the_checker(Ab,Aw,*(Aw+4),*(Aw+4)-1,a,x,b,y) == 0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Ab+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Ab+j),*(Aw+4)-1, a1, x1, b, y) == 0)
              {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Aw+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                     {count++;chk=1;}      
            }     
        }
   }
   chl=0;
recoder(*(Aw+4)+1,&b,&y);
if (the_checker(Ab,Aw,*(Aw+4),*(Aw+4)+1,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Ab+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Ab+j),*(Aw+4)+1, a1, x1, b, y) == 0)
                           {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Aw+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                     {count++;chk=1;}      
            }      
        }
   }
   chl=0;
recoder(*(Aw+4)-10,&b,&y);
if (the_checker(Ab,Aw,*(Aw+4),*(Aw+4)-10,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Ab+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Ab+j),*(Aw+4)-10, a1, x1, b, y) == 0)
                           {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Aw+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                     {count++;chk=1;}            
            }      
        }
   }
chl=0;
recoder(*(Aw+4)+10,&b,&y);
if (the_checker(Ab,Aw,*(Aw+4),*(Aw+4)+10,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Ab+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Ab+j),*(Aw+4)+10, a1, x1, b, y) == 0)
                           {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Aw+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                    {count++;chk=1;}            
            }       
        }
   }
chl=0;
recoder(*(Aw+4)-11,&b,&y);
if (the_checker(Ab,Aw,*(Aw+4),*(Aw+4)-11,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Ab+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Ab+j),*(Aw+4)-11, a1, x1, b, y) == 0)
                           {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Aw+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                 {count++;chk=1;}            
            }   
        }
   }
chl=0;
recoder(*(Aw+4)+11,&b,&y);
if (the_checker(Ab,Aw,*(Aw+4),*(Aw+4)+11,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Ab+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Ab+j),*(Aw+4)+11, a1, x1, b, y) == 0)
                           {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Aw+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                  {count++;chk=1;}            
            }       
        }
   }
   chl=0;
recoder(*(Aw+4)-9,&b,&y);
if (the_checker(Ab,Aw,*(Aw+4),*(Aw+4)-9,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Ab+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Ab+j),*(Aw+4)-9, a1, x1, b, y) == 0)
                           {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Aw+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                  {count++;chk=1;}            
            }      
        }
   }
   chl=0;
recoder(*(Aw+4)+9,&b,&y);
if (the_checker(Ab,Aw,*(Aw+4),*(Aw+4)+9,a,x,b,y)==0)
   {
    count_2++;
    for (j=0;j<16;j++)
        {
         recoder(*(Ab+j),&a1,&x1);               
         if (the_checker(Ab, Aw, *(Ab+j),*(Aw+4)+9, a1, x1, b, y) == 0)
                           {
              for (i=0;i<16;i++)
                  {
                  recoder(*(Aw+i),&b,&y); 
                  if (the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 1)
                     chl=1;
                  else if(the_checker(Ab, Aw, *(Aw+i),*(Ab+j), b, y, a1, x1) == 0)
                     return 0;
                  }
              if (i==16 && chl==1)
                  {count++;chk=1;}         
            }       
        }
   }
   
if (chk==1)
   if (count_2 == count)
      return -1;
   else
      return 0;
   
else 
  return 0;
}

int stalemate(int* A,char clr)
{
  int i,g,count=16;
    
    if (clr =='w')
        g = clr-115 ;
    else
        g = clr-86;
       
    
    if (A[g] != 0)
       for (i=0;i<16;i++)
           { 
            if (A[i] == 0)
               count--;    
           }
    else
        return 3;
      
    
    if (count == 1)
       {
        return 2;
       }
}
