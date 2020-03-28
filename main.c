#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define SIZE 25
#define N SIZE*SIZE
#define FILENAME "fileName.txt"
struct PROFILE{
	char name[20];
	int score;
};

int ROW = 0, COLUMN = 0;
int END = 0;
int countWin1=0, countWin2 = 0;
char p1name[100], p2name[100];
int x = (SIZE/2)*2-1, y = SIZE/2;
int countP=0;
struct PROFILE profile[100];

void gotoxy(int x, int y)  {
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

void TextColor(int x) {
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

void intro() {
	TextColor(14);
	printf("\t\t\t_________                                \n");
	printf("\t\t\t\\_   ___ \\   _____     _______     ____  \n");
	printf("\t\t\t/    \\  \\/   \\\__  \\\    \\_  __ \\   /  _ \\ \n");
	printf("\t\t\t\\     \\____   / __ \\_   |  | \\/  (  <_> )\n");
	printf("\t\t\t \\______  /  (____  /   |__|      \\____/ \n");
	printf("\t\t\t        \\/        \\/                     \n\n\n");
	printf("\t\tRule: 2 Players, use W,A,S,D to move, press 'o' to end game.\n");
	printf("\t\t\t\tPlayer 1 's name: ");
	gets(p1name);
	printf("\t\t\t\tPlayer 2 's name: ");
	gets(p2name);
}

void printboard(int board[SIZE][SIZE]) {
    int i,j;
    int cl=249;
    TextColor(cl);
    for(i=0;i<SIZE;i++) {
    	for (j=0; j <SIZE; j++) {
    		printf("|");
	        if (board[i][j]==1) {
    	        TextColor(252);
    	        printf("X");
            	TextColor(cl);
			}
        	else if (board[i][j]==2) {
  			TextColor(252);
	         	printf("O");
			TextColor(cl);
			}
        	else
            	printf("_");
    	}
    	printf("|\n");
    }
}

void askPlayer (int player) {
    TextColor(14);
    gotoxy(SIZE*2+4,5);printf("Press o to end game.\n");
    gotoxy(SIZE*2+4,6);
    if (player%2!=0) {
        printf("%s's turn (X tick)\n",p1name);
    }
    else
        printf("%s's turn (O tick)\n",p2name);
}

int checkEnd() {
	return END;
}

int checkAlready(int row, int column, int board[SIZE][SIZE]) {
    //True return 1;
    //False return 0;
    if (board[row][column] == 0)
        return 0;
    else
        return 1;
}

int checkWin(int player, int board[SIZE][SIZE]) {
	//return 1 to win
    int n,on;
    int i,j;
    int row, column;
    int result1,result2,result3,result4;
    if (player%2 == 1)
    	n = 1;
    else
    	n = 2;
    //check horizontal
    i = 0; j = 0; row = ROW; column = COLUMN;
    while (board[row][column-i] == n) i++;
    while (board[row][column+j] == n) j++;
    result1 = i+j;
    //check vertical
    i = 0; j = 0; row = ROW; column = COLUMN;
    while (board[row-i][column] == n) i++;
    while (board[row+j][column] == n) j++;
    result2 = i+j;
    //check duong cheo major
    i = 0; j = 0; row = ROW; column = COLUMN;
    while (board[row+i][column+i] == n) i++;
    while (board[row-j][column-j] == n) j++;
    result3 = i+j;
	//check duong cheo minor
    i = 0; j = 0; row = ROW; column = COLUMN;
    while (board[row+i][column-i] == n) i++;
    while (board[row-j][column+j] == n) j++;
    result4 = i+j;

    if (result1==6 || result2 == 6 || result3 == 6 || result4 == 6)
        {
            return 1;
        }
	return 0;
}

void swap(struct PROFILE *pro1, struct PROFILE *pro2) {
	struct PROFILE temp;
	strcpy(temp.name,pro1->name);
	temp.score=pro1->score;
	strcpy(pro1->name,pro2->name);
	pro1->score=pro2->score;

	strcpy(pro2->name,temp.name);
	pro2->score=temp.score;
	}

void sort(struct PROFILE prof[100],int count) {
	int i, check=0;
	while (check!=1) {
		check=1;
		for(i=0;i<count-1;i++)
			if (prof[i].score<prof[i+1].score){
				check=0;
				swap(&prof[i],&prof[i+1]);
			}
	}
}

char handleName(char str[100], char name[100], struct PROFILE profile[100], int count) {
	char temp[100];
	strncpy(temp,str,strlen(str)-1);
	strcpy(profile[count].name,temp);
	TextColor(0);
	gotoxy(0, SIZE+1);printf("Temp-----: %s|%d|%d|", temp,strlen(temp),strlen(str));
	TextColor(15);
	if (strcmp(temp, name)==0) {
		return 1;
	}
	return 0;
}

void changeLeaderBoard(char name[100]) {
	FILE *fn;

	char str[100];
	int score, newscore,i;
	char temp[100];
	fn=fopen(FILENAME,"r");
	if (fn==NULL) {
		fclose(fn);
		fn=fopen(FILENAME,"w");
		fclose(fn);
	}
	//The file arrange in order of name/score, name/score.
	//Check if the name already have in file or not
	fn = fopen(FILENAME, "r");
	int line = 0, check = 0, pos=-1;
	countP=0;
	while (fgets(str,100,fn)!=NULL) {
		if (line%2==0) {
			if (handleName(str, name, profile, countP)==1) {
				pos = countP;
				check = 1;
			}
		}
		else {
			strncpy(temp,str,strlen(str)-1);
			score=atoi(str);
			profile[countP].score=score;
			countP++;
		}
		line++;
	}
	fclose(fn);

	if (check == 1) {
		profile[pos].score++;
		sort(profile,countP);
		fn=fopen(FILENAME, "w");
		for(i=0;i<countP;i++) {
			fprintf(fn,"%s",profile[i].name);
			fprintf(fn,"\n");
			fprintf(fn,"%d",profile[i].score);
			fprintf(fn,"\n");
		}
		fclose(fn);
	}
	if (check==0) {
		strcpy(profile[countP].name,name);
		profile[countP].score=1;
		countP++;
		sort(profile,countP);
		fn = fopen(FILENAME, "w");
		for(i=0;i<countP;i++) {
			fprintf(fn,"%s",profile[i].name);
			fprintf(fn,"\n");
			fprintf(fn,"%d",profile[i].score);
			fprintf(fn,"\n");
		}
		fclose(fn);
	}
}

void showLeaderBoard() {
	int i;
	int y=2;
	TextColor(14);
	gotoxy(20,y++);printf("Leader Board:\n");
	gotoxy(16,y++);printf("Name\t\tScore\n");
	for(i=0;i<countP;i++) {
		gotoxy(16,y++);printf("%s\t\t%d\n", profile[i].name,profile[i].score);
		if(i==9) break;//Show top 10
	}
}

void input(int count, int board[SIZE][SIZE]) {
	//press W,A,S,D to move cursor and O to quit game.
	char c;
	int n;//turn
	int check = 0;
	int xM=SIZE*2,yM=SIZE-1;
	gotoxy(x, y);
	if (count%2 == 1)
		n=1;
	else
		n=2;
	while (check!=1) {
		c = getch();
		switch(c) {
			case 'w':
				if (y-1<0) break;
				y --;
				gotoxy(x, y);
				break;
			case 's':
				if(y+1>yM) break;
				y ++;
				gotoxy(x, y);
				break;
			case 'a':
				if(x-2<0) break;
				x -= 2;
				gotoxy(x, y);
				break;
			case 'd':
				if(x+2>xM) break;
				x += 2;
				gotoxy(x, y);
				break;
			case 'o':
				END = 1;
				check = 1;
				break;
			case ' ':
				if (checkAlready(y,x/2,board)==1) {
					gotoxy(SIZE*2+5, SIZE/3);
					printf("Already");
					gotoxy(x,y);
					break;
				}
				if (n==1) {
	    	        board[y][x/2] = 1;
				}
	        	else {
	            	board[y][x/2] = 2;
	    		}
	    		ROW = y;
	    		COLUMN = x/2;
	        	check ++;
	        	break;
	        default:
	        	gotoxy(SIZE*2+3, SIZE/3);
	        	printf("Press wrong key.");
	        	gotoxy(x,y);
		}
	}
}

void play() {
	int board[SIZE][SIZE];
    int count, i, j, k, column, row;
    END=0;
    //Creating the board
    for (i=0;i<SIZE;i++)
        for (j=0; j<SIZE; j++)
    		board[i][j] = 0;
    printboard(board);
    //Set the count, count<=SIZE*SIZE
    count=1;
    //Ask player 1 and check the input
    askPlayer(count);
    input(count, board);
    system("cls");

    while (count<=N) {
		count++;
        if(count==N) {
            printf("Run out of place.\n");
            break;
        }
        printboard(board);
        askPlayer(count);
        input(count, board);
        //Check Win Player
        if (checkWin(count, board)==1) {
        	system("cls");
        	printboard(board);
        	gotoxy(SIZE*2+4, SIZE/3);
        	TextColor(14);
        	printf("Player %s win!\n", (count%2==1 ? p1name:p2name));
        	changeLeaderBoard(count%2==1 ? p1name:p2name);
        	break;
		}
        //press o to end game.
        if (checkEnd()) {
        	system("cls");
        	printboard(board);
        	gotoxy(0, SIZE);
        	TextColor(15);
        	gotoxy(SIZE*2+2,SIZE/2-1);
        	printf("OUT GAME.\n");
            break;
        }
        system("cls");
    }
}

int main() {
	char a='y';
	int xpos=SIZE*2+2, ypos=SIZE/2;
	intro();
	while(a!='n') {
		system("cls");
		play();
		gotoxy(xpos,ypos);
		TextColor(14);
		printf("Do you want to play again?(y/n): ");
		a=getch();
		while(a!='y'&&a!='n') {
			ypos++;
			gotoxy(xpos,ypos);
			printf("Wrong key! Do you want to play again?(y/n): ");
			a=getch();
		}
	}
	system("cls");
	showLeaderBoard();
    return 0;
}
