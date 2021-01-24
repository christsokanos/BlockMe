
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

//struct
typedef struct
{
char name[15];
int type;
char kinhsh[4];
}players;
players *pl;
//sinartiseis
void show_table(int N,int **table);
void empodio(int **table,int N);
void add_more(int **table,int x1,int y1,int N);
void kane_kinhsh(int **table,int N,char pawns);
void vale_empodio(int **table,int N);
//int pagideumenos(int **table,int N,int countpl);
//Global metavlhtes
char ch=97;
int N;
int kinhsh=1;
int countpl;

int main(void)
{
	//dhlwse metavlhtwn
    srand(time(NULL)); //gia oles rand
	int **table,i,j,flag,choice,obs;
	int x,y;	//stin sunartisi gia ta empodia
	int *empodia,answer=0,flag1=-1;

	char *pawn;//apothikefsi pioniwn
	char *onoma=NULL;
    onoma=(char*)malloc(sizeof(char)*15);

    if (onoma==NULL)
		{
		printf("No memory available!\n");
		return 1;
		}

	printf("\n    ~ Welcome to Block Me ~ \n \n");
	printf("Choose the default dimension (10) by pressing '1' or choose dimension between 5-26!)\n");    //5-26 gia ta agglika grammata

	while(1)
	{
		scanf("%d",&N);
		if (N==1)				//epilogi '1' gia default
		{
			N=10;					//arxikopoihsh tou N
			break;
		}
		else if (N>=5 && N<=26)
			break;
		else
			printf("Caution the dimension must be between 5-26 or the default!\n");
	}
	table=(int **)malloc(N*sizeof(int *)); 			//desmeusi pinaka
	if (table==NULL)
	{
		printf("No memory available!\n");
		return 1;
	}

	for(i=0;i<N;i++)							//desmeusi upo-pinaka
	{
		table[i]=(int *)malloc(N*sizeof(int));
		if(table[i]==NULL)
		{
			printf("No memory available!\n");
			return 1; //return 0 means all gone good
		}
	}
	//eisagogi teleias se kathe keli
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			table[i][j]='.';

	printf("How many players? (2 or 4!)\n");
	while(1)
	{
		scanf("%d",&countpl);
		if (countpl==2 || countpl==4)
		break;
		else
		printf("The players must be 2 or 4!\n");
	}
	pl=(players *)malloc(countpl*sizeof(players));
	pawn=(char*)malloc(sizeof(char)*countpl+1);//malloc to store pawns
	for (i=0;i<countpl;i++)
	{
		if(i==0)
		{
			printf("The first player will be controlled by the user!\n");
			printf("Give name for player %d!\n",i+1);
			pl[i].type=1;
			scanf("%s",&pl[i].name);
		}
		else
		{
			do
	    {
	      printf("What type of %d player? ('1' for user or '2' for bot)\n", i+1);
	      scanf("%d",&pl[i].type);
	      if(pl[i].type!=1 && pl[i].type!=2)
	      printf("You must choose '1' or '2'!\n");
	    }while(pl[i].type!=1 && pl[i].type!=2 );

      while(1)
		 	{
		    printf("Give name for player %d!\n",i+1);
				scanf("%s",onoma);
				strcpy(pl[i].name,onoma); //pedio onomatos(ekei poy ginetai h apothikeusi onomatos)
				for(j=0;j<i;j++)
				{
					if(strcmp(pl[i].name,pl[j].name)==0)
					{
						printf("Name is already exists!\n");
						flag1=0;
						break;
					}
					else
					{
						flag1=1;
					}
				}
					if(flag1!=0)
					break;	
			}
		}
	}//for loop end here

		printf("Press '1' for table with obstacles and '2' without!\n");
		float pososto;
		int akmeros,monos=0,zugos=0;			//Pososto aritmou gia tin ekxorisi obstacle
		pososto=N*N*0.05;       //pososto apo olo to table
		akmeros=(int)pososto;  //pairnw to akeraio meros tou posostou
		if(akmeros%2==0)      //zugos
		zugos=akmeros;
		else                  //monos
		{
			monos=akmeros;
			monos++;         // an einai monos o arithos tou pros8etw ena gia na vgainei empodio!
		}
		while(1)
		{
			scanf("%d",&choice);
			if (choice==1 || choice==2)
			{
				if(choice==1)
				{
					if (zugos!=0 && monos==0)
					{
						for(i=0;i<zugos/2;i++)
	          			empodio(table,N);
	          		break;
					}
					else
					{
						for(i=0;i<monos/2;i++)
         				 empodio(table,N);
          			break;
					}
				}
				else if(choice==2)
				break;
			}
			else
				printf("You must choose between '1' or '2'!\n");
		}

///////////ekxorisi pionion
  if(countpl==2)
    {
        if(N%2==0) //elegxos gia zigo
        {
          if(rand()%2==0)     //tixaia epilogi tis 2hs stilis/grammis
        	{
           	table[N/2][0]='@';
           	table[N/2][N-1]='#';
      		}
     			else                   //tixaia epilogi tis 1hs stilis/grammis
       		{
           	table[N/2-1][0]='@';
           	table[N/2-1][N-1]='#';
       		}
        }
        else                //ektelesi gia mona
        {
           table[N/2][0]='@';
            table[N/2][N-1]='#';
        }
    }
    else
        {
            if(N%2==0)
        {
            if(rand()%2==0) //tixaia epilogi tis 2hs stilis/grammis
        {
            table[N/2][0]='@';
            table[N/2][N-1]='#';
            table[0][N/2]='*';
            table[N-1][N/2]='&';
        }
        else            //tixaia epilogi tis 2hs stilis/grammis
        {
            table[N/2-1][0]='@';
            table[N/2-1][N-1]='#';
            table[0][N/2-1]='*';
            table[N-1][N/2-1]='&';
        }
        }
        else        //ektelesi gia mona
        {
            table[N/2][0]='@';
            table[N/2][N-1]='#';
            table[0][N/2]='*';
            table[N-1][N/2]='&';
        }
        }
        if(countpl==2)
		{
			pawn[0]='#';
			pawn[1]='@';
			pawn[2]='\0';
		}
		else
		{
			pawn[0]='#';
			pawn[1]='*';
			pawn[2]='@';
			pawn[3]='&';
			pawn[4]='\0';

		}
		show_table(N,table);
	
		empodia=(int*)malloc(countpl*(sizeof (int)));
		for(i=0;i<countpl;i++)
		empodia[i]=5;
		int move;
		while(1)
		{		
			for(i=0;i<countpl;i++)
       		{
       			do
       			{
				printf("\nGive your move for %c pawn,'1' for move or '2' for obstacle! \n", pawn[i]);
       			scanf("%d",&answer);
       			if(answer!=1 && answer!=2)
       			printf("You must choose between '1' or '2'!\n");
				}while(answer!=1 && answer!=2);
               	if(pl[i].type==1 && answer==1)
								{
									kane_kinhsh(table,N,pawn[i]);
									if(kinhsh==0)
									return 0;
								}
								else if (pl[i].type==1 && answer==2)
               	{
               		if(empodia[i]==0)
               		{
					   				printf("You dont have more obstacles! \nMake a move!\n");
										kane_kinhsh(table,N,pawn[i]);
										if(kinhsh==0)
										return 0;
									}
						else
						{
							printf("You have still %d obstacles!\n",empodia[i]);
							empodia[i]--;
							vale_empodio(table,N);
							if(kinhsh==0)
							return 0;
              show_table(N,table);
        		}
								}
					}
		}	
		
	
				
				

///////////////free//////////////////////
for(i=0;i<N;i++)
	free(table[i]);

	free(table);
	free(pl);
	free(onoma);
	free(pawn);
	free(empodia);

	return 0;
}////////////////////////////////////////////////////////////telos int main/////////////////////////////////



/////////////sinartisis///////////
void show_table(int N,int **table)
{
	int i,j;

	printf("     ");
	for(i=0;i<N;i++) //1h grammh
	{
		printf("%c",ch+i);
		printf(" ");
	}
	printf("\n");
	printf(" ");
	for(i=0;i<(N*2)+3;i++) //2h grammh
	printf("-");
	printf("\n");
	for(j=0;j<N;j++) //1-4 sthlh pinaka
	{
		if (j==0)
		printf("%2.d | ",j+1);
		if (j>0)
		{
		printf("\n");
		printf("%2.d | ",j+1);
		}
		for(i=0;i<N;i++)
		{
		printf("%c ",table[i][j]);
		}
	}
}
/////////////////////////////////////////////////////////////////////
void empodio(int **table,int N)
{
		int x1,x2,y1,y2;
        do
        {
            x1=rand()%(N-2)+1;//times apo 0-(N-1)
            y1=rand()%(N-2)+1;//times apo 0-(N-1)
        }while(table[x1][y1]!='.');
        table[x1][y1]='X';
        add_more(table,x1,y1, N);   //klisi synartisis gia prosthiki 2o x gi na exo 1 empodio
	}//telos sinartisis empodio
////////////////////////////////////////////////////////////////////////
	void add_more(int **table,int x1,int y1,int N)
	{
        int k;
        k=rand()%4;
        if(k==0)
        {
            if(table[x1+1][y1]=='.' && x1+1<=N-1)
            {
                table[x1+1][y1]='X';
            }
            else
                return add_more(table,x1,y1,N); //an den isxiei h sinthiki 3ana kalo tin sinartisi gia n aparo allo tixaio k
        }
        else if(k==1)
        {
            if(table[x1-1][y1]=='.' && x1-1>=0)
            {
                table[x1-1][y1]='X';
            }
            else
                return add_more(table,x1,y1,N);
        }
        else if(k==2)
        {
            if(table[x1][y1+1]=='.' && y1+1<=N-1)
            {
                table[x1][y1+1]='X';
            }
            else
                return add_more(table,x1,y1,N);
        }
        else
        {
            if(table[x1][y1-1]=='.' && y1-1>=0)
            {
                table[x1][y1-1]='X';
            }
            else
              return  add_more(table,x1,y1,N);
        }

}//telos sinartisis add_more
////////////////////////////////////////////////////////////
void kane_kinhsh(int **table,int N,char pawns)
{
	int x,y;
  char move[4];
	int i,k,l;
	int h;
	int pawn_position_x,pawn_position_y;                //  mov[0]=gramma mov[1]=1os arithmos mov[2]=2os arithmos
	
		for(k=0;k<N;k++)// i for afti me tin emfolevmeni paei kai vriskei tis sidetagmenes tou antistixou pioniou oste na tsekarei egurotita kinisis
		{
			for(l=0;l<N;l++)
			{
				if(table[k][l]==pawns)
				{
					pawn_position_x=k;
					pawn_position_y=l;
				}
			}
		}
	do
 	{
 	printf("\nGive your move for %c pawn!(px b3)\n",pawns);
  scanf("%s",move);
 	}while(strlen(move)!=2 && strlen(move)!=3 && (strlen(move)!=4 && strncmp(move,"exit",4)==0));
 		if(strncmp(move,"exit",4)==0)
		{
			kinhsh=0;
			return;
		}		
		if(strlen(move)==2) // 1 gramma kai 1psifios arithmos
		{
	    	x=(int)move[0];
	    	x-=97;
	    	y=move[1]-48;
		}
		else // 1 gramma kai 2psifios arithmos
		{
    		x=(int)move[0];
    		x-=97;
   			y=move[1]-48;
    		y*=10;
    		h=move[2]-48;
    		y+=h;
		}
		y--;
		printf("\nmove-> x=%d,y=%d\n",y,x);
	if(((x>=0 && x<=N-1) && (y>=0 && y<=N-1)) && table[x][y]=='.' && (((x-pawn_position_x==1 || x-pawn_position_x==-1)&& y==pawn_position_y) || ((y-pawn_position_y==1 || y-pawn_position_y==-1)&& x==pawn_position_x)))
    {
        table[pawn_position_x][pawn_position_y]='.';
        if(pawns=='@')
        table[x][y]='@';
        else if(pawns=='#')
        table[x][y]='#';
        else if(pawns=='*')
        table[x][y]='*';
        else
        table[x][y]='&';
        show_table(N,table);
    }
     else
     {
    		printf("Watch your move..it's not valid\n");
     	  show_table(N,table);
       	return kane_kinhsh(table,N,pawns);
     }
}
///////////////////////////////////////////////////////////
void vale_empodio(int **table,int N)
{
	int x1,y1,h1,x2,y2,h2;
	int flag=0;
    char obstacle[6];
	
	while(flag==0){
		flag=1;
		do
		{
			printf("Give coordinates for the obstacle!\n"); //syntetagmenes tou empodiou
    		scanf("%s",obstacle);
    		if(strncmp(obstacle,"exit",4)==0)
    		{
					kinhsh=0;
    			return;
				}
			if(strlen(obstacle)==4)  // px c3c4
			{
	    		x1=(int)obstacle[0];
	    		x1-=97;
	    		y1=obstacle[1]-48-1;
	    		x2=(int)obstacle[2];
	    		x2-=97;
	    		y2=obstacle[3]-48-1;
			}
			else if(strlen(obstacle)==5)// px c10c9 h c9c10
			{
    			if(obstacle[2]>=49 && obstacle[2]<=57) //px c10c9
				{
					x1=(int)obstacle[0];
	    			x1-=97;
		    		y1=obstacle[1]-48;
		    		y1*=10;
		    		h1=obstacle[2]-48;
	    			y1+=h1-1;
	    			x2=(int)obstacle[3];
	    			x2-=97;
	    			y2=obstacle[4]-48-1;
				}
				else                             //px c9c10
				{
				x1=(int)obstacle[0];
		    	x1-=97;
	    		y1=obstacle[1]-48-1;
	    		x2=(int)obstacle[2];
	    		x2-=97;
	    		y2=obstacle[3]-48;
	    		y2*=10;
	    		h1=obstacle[4]-48;
	    		y2+=h2-1;
	    		}
			}
			else if(strlen(obstacle)==6)    // px c10c11  
			{
				x1=(int)obstacle[0];
	    		x1-=97;
	  	  		y1=obstacle[1]-48;
	    		y1*=10;
	    		h1=obstacle[2]-48;
	    		y1+=h1-1;
	    		x2=(int)obstacle[3];
	    		x2-=97;
	    		y2=obstacle[4]-48;
	    		y2*=10;
	    		h2=obstacle[5]-48;
	    		y2+=h2-1;
			}
		}while(strlen(obstacle)!=4 && strlen(obstacle)!=5 && strlen(obstacle)!=6);
		do
		{	
			if(table[x1][y1]=='.' && table[x2][y2]=='.')
			{
				if(x2==x1 && y2==y1+1)
				{
					table[x1][y1]='X';
					table[x2][y2]='X';
					
	
				}
				else if(x2==x1 && y2==y1-1)
				{
					table[x1][y1]='X';
					table[x2][y2]='X';	
					

				}
				else if(x2==x1-1 && y2==y1)
				{
					table[x1][y1]='X';
					table[x2][y2]='X';
					

				}
				else if(x2==x1+1 && y2==y1)
				{
					table[x1][y1]='X';
					table[x2][y2]='X';
					

				}
				else
				{
					printf("The posistion of the obstacle must be contiguous\n");
					flag = 0;			
				}
			}
			else
			{
				printf("There is already an obstacle,try again! \n");
				printf("\n");
				flag = 0;
				//return vale_empodio;
			}
		}while(x1>=N && y1>=N-1 && x2>=N && y2>=N-1);
	}
}


//////////////////////////////////////////////////////
/*int pagideumenos(int **table,int N,int countpl)
{
	
}
*/
