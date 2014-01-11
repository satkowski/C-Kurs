#include <stdio.h>

int main(void)
{	
	//Arrays für die Speicherung des Spieles in int und char
	short intArray[3][3] = {{-1, -1, -1},
							{-1, -1, -1},
							{-1, -1, -1}};
	char charArray[3][3] = {{' ', ' ', ' '}, 
							{' ', ' ', ' '}, 
							{' ', ' ', ' '}};
	//Array für den Input und die Spielervariable
	short inputArray[2];	
	short player = 0;	
	
	//Veriable zum bestätigen der richtigen Eingabe und die der spielzüge
	int var;
	int turnCounter = 0;

	printf("\033[2J\033[1;1H");
	printf("Tic Tac Toe\n\n");
	
	while(1) {	
		//Ausgabe für das Spielfeld des Tic Tac Toe Spieles
		printf("      0     1     2  \n");
		printf("         |     |     \n");
		printf(" 0    %c  |  %c  |  %c  \n", charArray[0][0], charArray[0][1], charArray[0][2]);
		printf("         |     |     \n");
		printf("    -----------------\n");
		printf("         |     |     \n");
		printf(" 1    %c  |  %c  |  %c  \n", charArray[1][0], charArray[1][1], charArray[1][2]);
		printf("         |     |     \n");
		printf("    -----------------\n");
		printf("         |     |     \n");
		printf(" 2    %c  |  %c  |  %c  \n", charArray[2][0], charArray[2][1], charArray[2][2]);
		printf("         |     |     \n");
		
		if(turnCounter == 8) {
			printf("Es steht unentschieden!\n");   
			break;
		}
		else if(turnCounter == 9)
			break;
		
		printf("\n\nSpieler %hd Eingabe:\n", player + 1);
		scanf("%hd" "%hd", &inputArray[0], &inputArray[1]);
		
		var = 1;

		while(var) {
			var = 0;
			//Prüfung ob die Eingabe negativ ist oder über das Array hinausgeht
			while(inputArray[0] < 0 || inputArray[0] > 2 || inputArray[1] < 0 || inputArray[1] > 2) {
				printf("\n\nDeine eingabe ist größer oder kleiner als das Tic Tac Toe Feld, bitte gib ein neues an:\n");
				scanf("%hd" "%hd", &inputArray[0], &inputArray[1]);
				var = 1;
			}
			//Prüfung ob die Eingabe 
			while(intArray[inputArray[0]][inputArray[1]] != -1) {
				printf("\n\nDas eingegebene Feld ist schon belegt, bitte gib ein neues an:\n");
				scanf("%hd" "%hd", &inputArray[0], &inputArray[1]);
				var = 1;
			}
		}
		
		//Setzen des char und des int Array mit dem entsprechenden Werten
		intArray[inputArray[0]][inputArray[1]] = player;
		charArray[inputArray[0]][inputArray[1]] = (player == 1 ? 'X' : 'O');
				
		//Abfrae nach dem sieg
		if(	(intArray[0][0] == player && intArray[0][1] == player && intArray[0][2] == player) ||
			(intArray[1][0] == player && intArray[1][1] == player && intArray[1][2] == player) ||
			(intArray[2][0] == player && intArray[2][1] == player && intArray[2][2] == player) ||
			(intArray[0][0] == player && intArray[1][0] == player && intArray[2][0] == player) ||
			(intArray[0][1] == player && intArray[1][1] == player && intArray[2][1] == player) ||
			(intArray[0][2] == player && intArray[1][2] == player && intArray[2][2] == player) ||
			(intArray[0][0] == player && intArray[1][1] == player && intArray[2][2] == player) ||
			(intArray[2][0] == player && intArray[1][1] == player && intArray[0][2] == player)) {
				
			printf("Spieler %hd hat gewonnen!\n", player + 1);
			turnCounter = 9;
		}
		//Wechseln des Spielers falls man noch nicht gewonnen hat
		else {
			player = (player + 1) % 2;
			turnCounter++;
//			printf("\033[2J\033[1;1H");
		}
	}
	
	
	return 0;
}

