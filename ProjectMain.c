#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define SIZE 20
#include <string.h>

/* Variables */

int ROW = 0, COLUMN = 0;
int END = 0;
int countWin1=0, countWin2 = 0;
char name1[100], name2[100];
int x = (SIZE/2)*2-1, y = SIZE/2;
int countP=0;




/* Functions */
void gotoxy(int x, int y)  {
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

void TextColor(int x) {
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color,x);
}

void introgaming()
{
    TextColor(14);
    printf("\t_          _	_______     __          ________      _____     __      __   _______    \n");
	printf("\t\\\\        //   ||      \\\    ||         /   _____\\    /  _  \\    ||\\    /||   ||     \\\ \n");
	printf("\t \\\\  __  //    ||______     ||        /   /         /  / \\  \\   ||\\\\  //||   ||_____     \n");
	printf("\t  \\\\//\\\\//     ||           ||        \\   \\_____    \\  \\_/  /   || \\\\// ||   ||         \n");
	printf("\t   \\/  \\/      ||______/    (|_____/   \\________/    \\_____/    ||      ||   ||_____/     \n");
	printf("\t\t\t\t  ___________ \n");
	printf("\t\t\t\t |_____  ____|  _____   \n");
	printf("\t\t\t\t      | |      /  _  \\  \n");
	printf("\t\t\t\t      | |     /  / \\  \\\n");
	printf("\t\t\t\t      | |     \\  \\_/  /                     * *     * *	   \n");
	printf("\t\t\t\t      |_|      \\_____/                    *     * *     * \n");
	printf("\t\t\t_________                                        *       *       *  \n");
	printf("\t\t\t\\    ___ \\   _____      ______     ____           *             * \n");
	printf("\t\t\t/    \\  \\/   \\\__  \\\    \\_  __ \\   /  _ \\           *           *  \n");
	printf("\t\t\t\\     \\____   / __ \\_   |  | \\/  (  <_> )            *       *   \n");
	printf("\t\t\t \\_________/ (______/   |__|      \\____/                * * \n\n\n");


}
void DrawingBoard( int board[SIZE][SIZE])
{
	int i,j;
	TextColor(252);
	for ( i=0;i<SIZE;i++)
        { for( j=0;j<SIZE;j++)
            {
                printf("|");
                if (board[i][j]==1)
                {
                    TextColor(241);
                    printf("X");
                    TextColor(252);
                }
                else if (board[i][j]==2)
                {
                    TextColor(241);
                    printf("O");
                    TextColor(252);
                }
                else
                printf("_");
            }
			printf("|\n");
        }
        TextColor(249);

}
int checkEnd()
{
    return END;
}
int checkAlready(int row, int column, int board[SIZE][SIZE])
{
    if (board[row][column] == 0)
        return 0; /* False */
    else
        return 1; /* True */
}
int checkWin(int player, int board[SIZE][SIZE])
{
    int n,i=0,j=0;
    int result1,result2,result3,result4;
    if(player%2 == 1)
        n = 1;
    else
        n = 2;
    int row = ROW , column = COLUMN;
    /* Checking horizontal line */
    while (board[row][column-i] == n)
        i++;
    while (board[row][column+j] == n)
        j++;
    result1 = i + j;
    /*Checking verticle line */
    i=0;j=0; row = ROW;column = COLUMN;
    while(board[row-i][column] == n)
        i++;
    while(board[row+j][column] == n)
        j++;
    result2 = i + j;
    /*Checking major diagonal */
    i=0;j=0; row = ROW;column = COLUMN;
    while(board[row+i][column+i]==n)
        i++;
    while(board[row-j][column-j]==n)
        j++;
    result3 = i + j;
    /*Checking minor diagonal*/
    i=0;j=0; row = ROW;column = COLUMN;
    while(board[row+i][column-i]==n)
        i++;
    while(board[row-j][column+j]==n)
        j++;
    result4 = i + j;


    if(result1==6||result2==6||result3==6||result4==6)
        return 1; /* 1: Player win*/
    else
        return 0;
}
void askPlayer (int player)
{
    int i;
    TextColor(158);
    gotoxy(SIZE*2+4,5);
    printf("Press b to end game.\n");
    gotoxy(SIZE*2+4,6);
    TextColor(158);
    if (player%2!=0)
    {   for(i=0;i<strlen(name1);i++)
        printf(name1)

        printf("%s 's turn (X tick)\n",name1);
    }
    else
        printf("%s 's turn (O tick)\n",name2);
}
void input(int count, int board[SIZE][SIZE])
{
	char c;
	int check = 0;
	int n;
	gotoxy(x,y);
	if ( count%2==1)
		n=1;                /* turn 1 */
	else
		n=2;                 /* turn 2 */
	while(check !=1)
    {
		c = getch();
		switch (c){

			case 'w':
                if (y<1)
                    break;
            /* set upper limit of the cursor */
                y--;
                gotoxy(x,y);
                break;

			case 's':
                if ( y > SIZE-2)
                    break;
	/* set lower limit of the cursor, explain: yMax = SIZE-1 because y-coordinate starts from 0,
	similar to upper limit: y +1 > yMax <=> y > SIZE-2 */
			y++;
			gotoxy(x,y);
			break;

			case 'a':
                if ( x-2<0)
                    break;
	/* set left limit of the cursor, because the default cursor at x is set = (SIZE/2)*2-1 ,
	so the last case'a' when x =3 will be implemented and move cursor to x=1, then it breaks.*/
  			x-=2; 	// for every square, the cursor moves to left 2 units horizontally
			gotoxy(x,y);
			break;

			case 'd':
			if( x > SIZE*2-2)
                break;
        /* set right limit of the cursor, similar to left limit */
			x+=2;
			gotoxy(x,y);
			break;

			case 'b':
                END =1;
                check =1; // ignore the while loop
                break;

			case ' ':
				if (checkAlready(y,x/2,board) == 1)
                    {
                        gotoxy(SIZE*2+4,SIZE/3+1);
                        printf("Already ticked");
                        gotoxy(x,y);// This command is needed to move cursor to default position when users double-tick.
                        break;
                    }
				if ( n==1)
					board[y][x/2]=1;
				else
					board[y][x/2]=2;
				ROW =y;
				COLUMN =x/2;
				check ++;
				break;
			default:
			gotoxy(SIZE*2+4,SIZE/3+2);
			printf("Wrong key");
			gotoxy(x,y);
		}
	}
}

void play()
{
	int board[SIZE][SIZE];
    int count, i, j, k, column, row;
    END=0;
    /* Printing the board */
    for (i=0;i<SIZE;i++)
        for (j=0; j<SIZE;j++)
    		board[i][j] = 0;
    DrawingBoard(board);

    //Set the count, count<=SIZE*SIZE
    count=1;                      /* Player 1 and check the input */
    input(count,board);
    system("cls");

    while (count<= SIZE * SIZE)
        {
            count++;
            if(count== SIZE * SIZE )
            {
                printf("Run out of place.\n");
                break;
            }
        DrawingBoard(board);
        askPlayer(count);
        input(count, board);
        TextColor(158);

        //Check Win Player
        if (checkWin(count, board)==1)
        {
        	system("cls");
        	DrawingBoard(board);
        	gotoxy(SIZE*2+4, SIZE/3);
        	TextColor(14);
        	printf("CONGRATULATIONS!!!!! ");
        	gotoxy(SIZE*2+4, SIZE/3 + 1);
            printf("YOU WIN!!");
        	break;
		}
        //press b to end game.
        if (checkEnd()) {
        	system("cls");
        	DrawingBoard(board);
        	gotoxy(0, SIZE);
        	TextColor(14);
        	gotoxy(SIZE*2+2,SIZE/2-1);
        	printf("OUT GAME.\n");
            break;
        }
        system("cls");
    }
}
int main()
{
	char a='y';
	int xpos=SIZE*2+2, ypos=SIZE/2;
	introgaming();
    char name1[20];
    char name2[20];
    printf("\t\tUser1: Input your name: ");
    gets(name1);
    printf("\t\tUser2: Input your name: ");
    gets(name2);
    printf("User1 play first\n");

	while(a!='n')
    {
		system("cls");
		play();
		gotoxy(xpos,ypos);
		TextColor(158);
		printf("Do you want to play again?(y/n): ");
		a=getch();
		while(a!='y'&&a!='n')
            {
                ypos++;
                gotoxy(xpos,ypos);
                printf("Wrong key! Do you want to play again?(y/n): ");
                a=getch();
            }
	}
	system("cls");
    return 0;

}








