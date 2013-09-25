#include<iostream>
#include<cstdio>
#include<cctype>
#include<cmath>
char chess[8][8];//large case characters denote white chess players and small case characters denote black characters
//----------------------------------------------------------------------------------------
void initialize_game(char chess[8][8])
{int i=0,j=0;
 for(i=0;i<=7;i++)
 chess[1][i]='P';//pawns at the white side have been initialised
 chess[0][0]=chess[0][7]='R';
 chess[0][1]=chess[0][6]='N';
 chess[0][2]=chess[0][5]='B';
 chess[0][3]='K';
 chess[0][4]='Q';
 for(i=0;i<=7;i++)
 chess[6][i]='p';//pawns at the black side have been initialised    
 chess[7][0]=chess[7][7]='r';    
 chess[7][1]=chess[7][6]='n';
 chess[7][2]=chess[7][5]='b';
 chess[7][3]='k';
 chess[7][4]='q';
 for(i=2;i<=5;i++)
 {for(j=0;j<=7;j++)
  chess[i][j]=' ';//empty spaces have been initialised as white spaces
 }
 printf("Initialising CHESS...\n");
 printf("Get ready players.Game starts in 3,2,1\n");
 printf("  01234567\n");
 printf(" ##########\n");
 for(i=0;i<8;i++)
 {printf("%d#",i);
  for(j=0;j<8;j++)
  printf("%c",chess[i][j]);
  printf("#\n");
 }
}
//------------------------------------------------------------------------
void displayboard(char chess[8][8])
{int i,j;
printf("  01234567\n");
printf(" ##########\n");
 
for(i=0;i<8;i++)
{printf("%d#",i);
 for(j=0;j<8;j++)
 printf("%c",chess[i][j]);
 printf("#\n");
} 
}
//-------------------------------------------------------------------------
int pawn(int isel,int jsel,int flag,char player[])
{int i,j;
 start:
 printf("Enter the position where you want to move the pawn\n");
 scanf("%d%d",&i,&j);
 if(i<0||j<0||i>7||j>7)
 {printf("You're trying to move the piece out of the chessboard\n");
  goto start;
 }
 else
 {
  if(flag==0)//the move is for the white pawn
  {if(i==isel-1)
   {printf("You can't move the piece backwards\n");
   goto start;
   }
   if(i==isel)
   {printf("You gotta move ur pawn forward\n");
    goto start;
   }
   if(isel==1)//when the pawn is moved from its starting position it has 2 types of moves
   {switch(i)
    {case 2:if((j==jsel&&chess[i][j]==' ')||((j==jsel+1||j==jsel-1)&&islower(chess[i][j])))//this is when the white pawn's first move is 1 step forward... 
             {if(chess[i][j]=='k')
              {printf("Checkmate.%s wins\n",player);
               return 1;}
			  chess[isel][jsel]=' ';
              chess[i][j]='P';}
     break;
     case 3:if(j==jsel&&chess[i][jsel]==' '&&chess[2][jsel]==' ')//a pawn can't jump over pieces.this is when the white pawn's first move is 2 steps forward
            {chess[isel][jsel]=' ';
             chess[i][j]='P';}
     break;
     default:printf("Invalid move\n");
             return 3;
    }
   }
   else
   {if((i==isel+1&&j==jsel&&chess[i][j]==' ')||((j==jsel+1||j==jsel-1)&&islower(chess[isel+1][j])))
    {if(chess[i][j]=='k')
      {printf("Checkmate.%s wins\n",player);
       return 1;}
     chess[isel][jsel]=' ';
     chess[i][j]='P';}
    else
    {printf("Invalid move\n"); 
     return 3;
     }
    }
   }
else//the move is for the black pawn                      
   {if(i==isel+1)
   {printf("You can't move the piece backwards\n");
   goto start;
   }
   if(i==isel)
   {printf("You gotta move ur pawn forward\n");
    goto start;
   }
   if(isel==6)
   {switch(i)
    {case 5:if((j==jsel&&chess[i][j]==' ')||((j==jsel+1||j==jsel-1)&&isupper(chess[i][j])))
             {if(chess[i][j]=='K')
              {printf("Checkmate.%s wins",player);
               return 1;} 
              chess[isel][jsel]=' ';
              chess[i][j]='p';}
     break;
     case 4:if(j==jsel&&chess[i][jsel]==' '&&chess[5][jsel]==' ')//a pawn can't jump over a piece
            {chess[isel][jsel]=' ';
             chess[i][j]='p';}
     break;
     default:printf("Invalid move\n");
             return 4;
    }
   }
   else
   {if((i==isel-1&&j==jsel&&chess[i][j]==' ')||((j==jsel+1||j==jsel-1)&&isupper(chess[isel-1][j])))
    {if(chess[i][j]=='K')
      {printf("Checkmate.%s wins\n",player);
       return 1;}
     chess[isel][jsel]=' ';
     chess[i][j]='p';}
    else
    {printf("Invalid move\n"); 
     return 4;
     }
    }
   }
}
return 0;}   
   

//-------------------------------------------------------------------------
int rook(int isel,int jsel,int flag,char player[])
{int i,j,count;
start:
printf("Enter the position where you want to move the rook\n");
scanf("%d%d",&i,&j);
 if(i<0||j<0||i>7||j>7)
 {printf("You're trying to move the piece out of the chessboard\n");
  goto start;
 }
 else
 {if(flag==0)//white rook      
  { 
   if(i==isel&&(chess[i][j]==' '||islower(chess[i][j])))//when motion of rook is horizontal 
    {if(j>jsel)//if movin right
	{for(count=jsel+1;count<j;count++)
     {if(chess[isel][count]!=' ')
      {printf("Rook is trying to cross over a piece in its path\n");
       return 3;}}}
	 else if(j<jsel)//if movin left  
     {for(count=jsel-1;count>j;count--)
     {if(chess[isel][count]!=' ')
      {printf("Rook is trying to cross over a piece in its path\n");
       return 3;}}}
	 
	 if(chess[i][j]=='k')
      {printf("Checkmate.%s wins\n",player);
       return 1;}
     chess[isel][jsel]=' ';
     chess[i][j]='R';}
   else if(j==jsel&&(chess[i][j]==' '||islower(chess[i][j])))//when motion of rook is vertical
   {if(i>isel)//if moving down
    {for(count=isel+1;count<i;count++)
     {if(chess[count][jsel]!=' ')
      {printf("Rook is trying to cross over a piece in its path\n");
       return 3;}}}
    else if(i<isel)//if moving up 
	 {for(count=isel-1;count>i;count--)
     {if(chess[count][jsel]!=' ')
      {printf("Rook is trying to cross over a piece in its path\n");
       return 3;}}}
	 if(chess[i][j]=='k')
      {printf("Checkmate.%s wins\n",player);
       return 1;}
     chess[isel][jsel]=' ';
     chess[i][j]='R';}
else
   {printf("Invalid move\n");
    return 3;
    }
   }
  else//black rook                      
  {if(i==isel&&(isupper(chess[i][j])||chess[i][j]==' '))//when motion of rook is horizontal
    {if(j>jsel)//movin right
	{for(count=jsel+1;count<j;count++)
     {if(chess[isel][count]!=' ')
      {printf("Rook is trying to cross over a piece in its path\n");
       return 4;}}}
	 else if(j<jsel)//movin left
     {for(count=jsel-1;count>j;count--)
	  {if(chess[isel][count]!=' ')
      {printf("Rook is trying to cross over a piece in its path\n");
       return 4;}}
	 }	 
     if(chess[i][j]=='K')
      {printf("Checkmate.%s wins\n",player);
       return 1;}
     chess[isel][jsel]=' ';
     chess[i][j]='r';}
   else if(j==jsel&&(isupper(chess[i][j])||chess[i][j]==' '))   
   {if(i>isel)
   {for(count=isel+1;count<i;count++)
     {if(chess[count][jsel]!=' ')
      {printf("Rook is trying to cross over a piece in its path\n");
       return 4;}}
   }
   else if(i<isel)
   {for(count=isel-1;count>i;count--)
   {if(chess[count][jsel]!=' ')
      {printf("Rook is trying to cross over a piece in its path\n");
       return 4;}}}   
	 
	 if(chess[i][j]=='K')
      {printf("Checkmate.%s wins\n",player);
       return 1;}
     
     chess[isel][jsel]=' ';
     chess[i][j]='r';}
else
   {printf("Invalid move\n");
    return 4;
    }
   }
}
return 0;}   
//------------------------------------------------------------------------- 
int knight(int isel,int jsel,int flag,char player[])
{int i,j;
start:
printf("Enter the position where you want to move the knight\n");
scanf("%d%d",&i,&j);
 if(i<0||j<0||i>7||j>7)
 {printf("You're trying to move the piece out of the chessboard\n");
  goto start;
 }
 else
{if(flag==0)//white knight   
 {if(((i==isel+2||i==isel-2)&&(j==jsel+1||j==jsel-1)&&(chess[i][j]==' '||islower(chess[i][j])))||((j==jsel+2||j==jsel-2)&&(i==isel+1||i==isel-1)&&(chess[i][j]==' '||islower(chess[i][j]))))
  {if(chess[i][j]=='k')
    {printf("Checkmate.%s wins\n",player);
     return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='N';
     }
   else
   {printf("Invalid move\n");
    return 3;
    }
  }
else//black knight
{if(((i==isel+2||i==isel-2)&&(j==jsel+1||j==jsel-1)&&((chess[i][j]==' ')||isupper(chess[i][j])))||((j==jsel+2||j==jsel-2)&&(i==isel+1||i==isel-1)&&((chess[i][j]==' ')||isupper(chess[i][j]))))
  {if(chess[i][j]=='K')
    {printf("Checkmate.%s wins\n",player);
     return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='n';
     }
 else
  {printf("Invalid move\n");
   return 4;
   }
}
}
return 0;}   
//------------------------------------------------------------------------- 
int bishop(int isel,int jsel,int flag,char player[])
{int i,j,counti,countj;
start:
printf("Enter the position where you want to move the bishop\n");
scanf("%d%d",&i,&j);
 if(i<0||j<0||i>7||j>7)
 {printf("You're trying to move the piece out of the chessboard\n");
  goto start;
 }
 else
{if(flag==0)//white bishop   
 {if(fabs(i-isel)==fabs(j-jsel)&&(chess[i][j]==' '||islower(chess[i][j])))//if i and j are along the diagonal
  {if(i-isel>0&&j-jsel>0)//right bottom diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti++,countj++)
    {if(chess[i][j]!=' ')
     {printf("The bishop can't cross over the piece\n");
      return 3;
      }
     }
    if(chess[i][j]=='k')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='B';
    }
   else if(i-isel<0&&j-jsel<0)//left top diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti--,countj--)
    {if(chess[i][j]!=' ')
     {printf("The bishop can't cross over the piece\n");
      return 3;
      }
     }
    if(chess[i][j]=='k')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='B';
    } 
   else if(i-isel>0&&j-jsel<0)//left bottom diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti++,countj--)
    {if(chess[i][j]!=' ')
     {printf("The bishop can't cross over the piece\n");
      return 3;
      }
     }
    if(chess[i][j]=='k')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='B';
    }
   else//right top diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti--,countj++)
    {if(chess[i][j]!=' ')
     {printf("The bishop can't cross over the piece\n");
      return 3;
      }
     }
    if(chess[i][j]=='k')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='B';
    }
   }
   
  else
  {printf("Invalid move\n");
   return 3;
   }
}
 else//black bishop
 {if(fabs(i-isel)==fabs(j-jsel)&&(chess[i][j]==' '||isupper(chess[i][j])))//if i and j are along the diagonal
  {if(i-isel>0&&j-jsel>0)//right bottom diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti++,countj++)
    {if(chess[i][j]!=' ')
     {printf("The bishop can't cross over the piece\n");
      return 4;
      }
     }
    if(chess[i][j]=='K')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='b';
    }
   else if(i-isel<0&&j-jsel<0)//left top diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti--,countj--)
    {if(chess[i][j]!=' ')
     {printf("The bishop can't cross over the piece\n");
      return 4;
      }
     }
    if(chess[i][j]=='K')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='b';
    } 
   else if(i-isel>0&&j-jsel<0)//left bottom diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti++,countj--)
    {if(chess[i][j]!=' ')
     {printf("The bishop can't cross over the piece\n");
      return 4;
      }
     }
    if(chess[i][j]=='K')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='b';
    }
   else//right top diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti--,countj++)
    {if(chess[i][j]!=' ')
     {printf("The bishop can't cross over the piece\n");
      return 4;
      }
     }
    if(chess[i][j]=='K')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='b';
    }
   }
   
  else
  {printf("Invalid move\n");
   return 4;
   }
  }
}return 0;}   
//------------------------------------------------------------------------- 
int queen(int isel,int jsel,int flag,char player[])
{int i,j,count,counti,countj;
start:
printf("Enter the position where you want to move the queen\n");
scanf("%d%d",&i,&j);
if(i<0||j<0||i>7||j>7)
{printf("You're trying to move the piece out of the chessboard\n");
 goto start;
 }
else
{if(flag==0)//white queen   
 {if(i==isel&&(chess[i][j]==' '||islower(chess[i][j])))//when queen moves horizontal
  {if(j>jsel)
   {for(count=jsel+1;count<j;count++)
     {if(chess[isel][count]!=' ')
      {printf("Queen is trying to cross over a piece in its path\n");
       return 3;}
      }}
   else if(j<jsel)
   {for(count=jsel-1;count>j;count--)
     {if(chess[isel][count]!=' ')
      {printf("Queen is trying to cross over a piece in its path\n");
       return 3;}
      }}
   if(chess[i][j]=='k')
    {printf("Checkmate.%s wins\n",player);
     return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='Q';
   }
  else if(j==jsel&&(chess[i][j]==' '||islower(chess[i][j])))//when queen moves vertical
  {if(i>isel)
  {for(count=isel+1;count<i;count++)
     {if(chess[count][jsel]!=' ')
      {printf("Queen is trying to cross over a piece in its path\n");
       return 3;}
      }}
   else if(i<isel)
   {for(count=isel-1;count>i;count--)
     {if(chess[count][jsel]!=' ')
      {printf("Queen is trying to cross over a piece in its path\n");
       return 3;}
      }}
   if(chess[i][j]=='k')
    {printf("Checkmate.%s wins\n",player);
     return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='Q';
   }
  else if(((i==isel+2||i==isel-2)&&(j==jsel+1||j==jsel-1)&&(chess[i][j]==' '||islower(chess[i][j])))||((j==jsel+2||j==jsel-2)&&(i==isel+1||i==isel-1)&&(chess[i][j]==' '||islower(chess[i][j]))))//moves like a knight
  {if(chess[i][j]=='k')
    {printf("Checkmate.%s wins\n",player);
     return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='Q';
     }
   
  else if(fabs(i-isel)==fabs(j-jsel)&&(chess[i][j]==' '||islower(chess[i][j])))//when queen moves diagonally
  {if(i-isel>0&&j-jsel>0)//right bottom diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti++,countj++)
    {if(chess[i][j]!=' ')
     {printf("The queen can't cross over the piece\n");
      return 3;
      }
     }
    if(chess[i][j]=='k')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='Q';
    }
   else if(i-isel<0&&j-jsel<0)//left top diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti--,countj--)
    {if(chess[i][j]!=' ')
     {printf("The queen can't cross over the piece\n");
      return 3;
      }
     }
    if(chess[i][j]=='k')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='Q';
    } 
   else if(i-isel>0&&j-jsel<0)//left bottom diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti++,countj--)
    {if(chess[i][j]!=' ')
     {printf("The queen can't cross over the piece\n");
      return 3;
      }
     }
    if(chess[i][j]=='k')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='Q';
    }
   else//right top diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti--,countj++)
    {if(chess[i][j]!=' ')
     {printf("The queen can't cross over the piece\n");
      return 3;
      }
     }
    if(chess[i][j]=='k')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='Q';
    }
   }
  else
  {printf("Invalid move\n");
   return 3;
   }
  }
else//black queen
{if(i==isel&&(chess[i][j]==' '||isupper(chess[i][j])))//when queen moves horizontal
  {if(j>jsel)
   {for(count=jsel+1;count<j;count++)
     {if(chess[isel][count]!=' ')
      {printf("Queen is trying to cross over a piece in its path\n");
       return 4;}
      }}
	else if(j<jsel)
	{for(count=jsel-1;count>j;count--)
     {if(chess[isel][count]!=' ')
      {printf("Queen is trying to cross over a piece in its path\n");
       return 4;}
      }}
   if(chess[i][j]=='K')
    {printf("Checkmate.%s wins\n",player);
     return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='q';
   }
 else if(j==jsel&&(chess[i][j]==' '||isupper(chess[i][j])))//when queen moves vertical
  {if(i>isel)
   {for(count=isel+1;count<i;count++)
     {if(chess[count][jsel]!=' ')
      {printf("Queen is trying to cross over a piece in its path\n");
       return 4;}
      }}
	else if(i<isel)
   {for(count=isel-1;count>i;count--)
     {if(chess[count][jsel]!=' ')
      {printf("Queen is trying to cross over a piece in its path\n");
       return 4;}
      }}	
   if(chess[i][j]=='K')
    {printf("Checkmate.%s wins\n",player);
     return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='q';
   }
 //-----------------------------------------------------------------------------------------------------------
 else if(((i==isel+2||i==isel-2)&&(j==jsel+1||j==jsel-1)&&(chess[i][j]==' '||isupper(chess[i][j])))||((j==jsel+2||j==jsel-2)&&(i==isel+1||i==isel-1)&&(chess[i][j]==' '||isupper(chess[i][j]))))
  {if(chess[i][j]=='K')
    {printf("Checkmate.%s wins\n",player);
     return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='q';
     }
   
//------------------------------------------------------------------------------------------------------------ 
 else if(fabs(i-isel)==fabs(j-jsel)&&(chess[i][j]==' '||isupper(chess[i][j])))//when queen moves diagonally
  {if(i-isel>0&&j-jsel>0)//right bottom diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti++,countj++)
    {if(chess[i][j]!=' ')
     {printf("The queen can't cross over the piece\n");
      return 4;
      }
     }
    if(chess[i][j]=='K')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='q';
    }
   else if(i-isel<0&&j-jsel<0)//left top diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti--,countj--)
    {if(chess[i][j]!=' ')
     {printf("The queen can't cross over the piece\n");
      return 4;
      }
     }
    if(chess[i][j]=='K')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='q';
    } 
   else if(i-isel>0&&j-jsel<0)//left bottom diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti++,countj--)
    {if(chess[i][j]!=' ')
     {printf("The queen can't cross over the piece\n");
      return 4;
      }
     }
    if(chess[i][j]=='K')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='q';
    }
   else//right top diagonal
   {for(counti=isel,countj=jsel;counti<=i,countj<=j;counti--,countj++)
    {if(chess[i][j]!=' ')
     {printf("The queen can't cross over the piece\n");
      return 4;
      }
     }
    if(chess[i][j]=='K')
     {printf("Checkmate.%s wins\n",player);
      return 1;}
    chess[isel][jsel]=' ';
    chess[i][j]='q';
    }
   }
 else
  {printf("Invalid move\n");
   return 4;
   }
 }
   

}return 0;
}  
//------------------------------------------------------------------------- 
int king(int isel,int jsel,int flag,char player[])
{int i,j;
start:
printf("Enter the position where you want to move the king\n");
scanf("%d%d",&i,&j);
 if(i<0||j<0||i>7||j>7)
 {printf("You're trying to move the piece out of the chessboard\n");
  goto start;
 }
 else
{if(flag==0)//white king
 {if((i==isel||i==isel+1||i==isel-1)&&(j==jsel||j==jsel+1||j==jsel-1)&&(chess[i][j]==' '||islower(chess[i][j])))
  {if(chess[i][j]=='k')
   {printf("Checkmate.%s wins\n",player);
     return 1;}
   chess[isel][jsel]=' ';
   chess[i][j]='K';
   }
  else
  {printf("Invalid move.\n");
   return 3;
  }
 }
 else//black king
 {if((i==isel||i==isel+1||i==isel-1)&&(j==jsel||j==jsel+1||j==jsel-1)&&(chess[i][j]==' '||isupper(chess[i][j])))
  {if(chess[i][j]=='K')
   {printf("Checkmate.%s wins\n",player);
     return 1;}
   
   chess[isel][jsel]=' ';
   chess[i][j]='K';
   }
  else
  {printf("Invalid move.\n");
   return 4;
  }
 }
}return 0;
 }   
//------------------------------------------------------------------------- 
int main()
{char player1[10],player2[10],ch;
 int isel,jsel,win=0;//isel and jsel are used to enter the coordinates of the chess piece to move.win=3 means invalid move,win=1 some player has won and the game ends immediately
 printf("Enter the name of the player1-plays white-large case characters\n");
 scanf("%s",player1);//white
 printf("Enter the name of the player-2-plays black-small case characters\n"); 
 scanf("%s",player2);//black
 initialize_game(chess);//the chess board is initialised
 while(1)//keep on playing till one wins
 {
 printf("%s enter the coordinates of the piece to move\n",player1);
  scanf("%d%d",&isel,&jsel);
  if(isel<0||isel>7||jsel<0||jsel>7)
  {printf("You've selected out of the chessboard\n");
   continue;}
  else//if the selection for the white piece isn't out of the chessboard 
  {ch=chess[isel][jsel];//ch is the piece on the chessboard which is selected
  switch(ch)
  {case 'P':win=pawn(isel,jsel,0,player1);
         if(win==3)
         continue;
         displayboard(chess);   
   break;
   case 'R':win=rook(isel,jsel,0,player1);
            if(win==3)
         continue;
            displayboard(chess);
   break;
   case 'K':win=king(isel,jsel,0,player1);
if(win==3)
         continue;
   displayboard(chess);
   break;
   case 'B':win=bishop(isel,jsel,0,player1);
   if(win==3)
         continue;
displayboard(chess);
   break;
   case 'Q':win=queen(isel,jsel,0,player1);
if(win==3)
         continue;   
displayboard(chess);
   break;
   case 'N':win=knight(isel,jsel,0,player1);
if(win==3)
         continue;   
displayboard(chess);
   break;
   case ' ':printf("The position which you selected doesn't contain the chess piece.Try again");
   continue;
   default:printf("You selected the opposition's piece.");
   continue;
  }
}
if(win==1)
break;  
start2:
  printf("%s enter the coordinates of the piece to move\n",player2);
  scanf("%d%d",&isel,&jsel);
  if(isel<0||isel>7||jsel<0||jsel>7)
  {printf("You are out of the chessboard\n");
   goto start2;
  }
  else
  {ch=chess[isel][jsel];
  switch(ch)
  {
  case 'p':win=pawn(isel,jsel,1,player2);
  printf("win returned %d\n",win);
if(win==4)
         goto start2;   
displayboard(chess);
   break;
   case 'r':win=rook(isel,jsel,1,player2);
if(win==4)
         goto start2;   

   displayboard(chess);
   break;
   case 'k':win=king(isel,jsel,1,player2);
if(win==4)
         goto start2;   

   displayboard(chess);
   break;
   case 'b':win=bishop(isel,jsel,1,player2);
if(win==4)
         goto start2;   

   displayboard(chess);
   break;
   case 'q':win=queen(isel,jsel,1,player2);
if(win==4)
         goto start2;   

   displayboard(chess);
   break;
   case 'n':win=knight(isel,jsel,1,player2);
if(win==4)
         goto start2;   

   displayboard(chess);
   break;
   case ' ':printf("The position which you selected doesn't contain the chess piece.Try again");
   goto start2;
   break;
   default:printf("You selected the opposition's piece.");
   goto start2;
  }
}
if(win==1)
break;
}

return 0;
} 
//Created by:Jaskaran Singh Virdi-2011CS1012

   
  
 
 
