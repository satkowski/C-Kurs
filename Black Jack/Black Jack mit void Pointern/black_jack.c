#include "black_jack.h"

int main(void)
{
	long sek;
	time(&sek);
	srand((unsigned)sek);

	card originalCardDeck[52];
	card cardDeck[52];
	player allPlayers[9];
	short gameEnd;
	short playerCounter;

	printf("-----------------------------------------------------------\n");
	printf("--------------- Willkommen beim Black Jack! ---------------\n");
	printf("-----------------------------------------------------------\n\n");

	// Initialisierung der Bank als '0' ter Spieler.
	allPlayers[0] = initNewPlayer("Bank");
	allPlayers[0].playerNumber = 0;

	// Initialisierung der benötigten Daten.
	initCardDeck(originalCardDeck);
	playerCounter = initAllPlayer(allPlayers);

	// Schleife für den Spieldurchlauf.
	do {
        short c;
		void* voidCardDeck[52];
        for(c = 0; c < 52; c++)
            cardDeck[c] = originalCardDeck[c];
		for(c = 0; c < 52; c++)
            voidCardDeck[c] = &cardDeck[c];
        for(c = 0; c < playerCounter; c++)
            resetPlayerHand(&allPlayers[c]);
		gameContinues(voidCardDeck, playerCounter, allPlayers);
	}
	while(gameEnd == 0);

	return 0;
}

// Funktion für die Initialisierung des Kartendeckes.
void initCardDeck(card* cardDeckPointer) {
	int colourIndex;
	int nameIndex;
	int cardCounter = 0;
	// Initialisieren der einzelnen Karten.
	for(colourIndex = KARO; colourIndex <= KREUZ; colourIndex++) {
		for(nameIndex = ZWEI; nameIndex <= KOENIG; nameIndex++) {
			card newCard;
			newCard.colour = colourIndex;
			newCard.name = nameIndex;
			// Alles was nach ASS kommt, also BUBE, DAME, KOENIG bekommen den Wert 10.
			if(nameIndex <= ASS)
				newCard.value = nameIndex;
			else
				newCard.value = 10;
			// Hinzufügen der Karten in das Kartendeck.
			cardDeckPointer[cardCounter] = newCard;
			cardCounter++;
		}
	}
}

// Funktion, welche alle Spieler initialisiert.
short initAllPlayer(player* allPlayerPointer) {
	short playerNumber;
	short playerCounter;
	// Eingabe der Spieleranzahl.
	printf("Wieviele Spieler seit ihr? Die maximale Anzahl beträgt 8 Spieler! :\n");
	scanf("%hd", &playerNumber);
	getchar();

	// Initialisierung der verschiedenen Spieler.
	for(playerCounter = 1; playerCounter <= playerNumber; playerCounter++) {
		player newPlayer;
		char name[32];
		// Eingabe des Namen eines Spielers.
		printf("Spieler %hd gib deinen Namen ein! :\n", playerCounter);
		// fgets nimmt nur genau 32 - 1 Zeichen auf und speichert es ab. Es werden überliegenden
		// Wortteile abgeschnitten und auch das '\n’ mit gespeichert.
		fgets(name, 32, stdin);
		// '\n' mit '\0' überschreiben
		size_t p = strlen(name);
		name[p - 1] = '\0';
		newPlayer = initNewPlayer(name);
		newPlayer.playerNumber = playerCounter;
		// Hinzufügen der Spieler.
		allPlayerPointer[playerCounter] = newPlayer;
	}
	short c;
	// Spieler die nicht mit Spielen werden auf -1 gesetzt.
	for(c = playerCounter; c < 9; c++) {
        player newPlayer;
        newPlayer.playerNumber = -1;
        allPlayerPointer[c] = newPlayer;
	}
	return playerCounter;
}

// Funktion zur Initialisierung eines einzelnen Spielers.
player initNewPlayer(char* name) {
	player newPlayer;
	short c;
	// Befüllung der Namens varibale im Struct.
	for(c = 0; c < 32; c++)
		newPlayer.name[c] = name[c];
    newPlayer.actualScore = 0;
	newPlayer.cardCounter = 0;
	newPlayer.accountValue = 500;

	return newPlayer;
}

// Funktion die das Spiel repräsentiert.
void gameContinues(void* cardDeck, short playerCounter, player* allPlayersPointer) {
	short c1, c2;
	short playerIndex;
	printf("Es beginnt eine neue Runde. Die Karten werden ausgeteilt!\n\n");
	// Ausgeben der Karten
	for(c1 = 0; c1 < 2; c1++) {
		for(c2 = 0; c2 < playerCounter; c2++) {
			card* drawenCard = (card*) drawCard(cardDeck);
			addCardToHand(&allPlayersPointer[c2], drawenCard);
		}
	}

	for(playerIndex = 1; playerIndex <= playerCounter; playerIndex++) {
        short turnEnd;
        short choice;
        short winningIndex;
        player actualPlayer = allPlayersPointer[playerIndex];
        // Nicht vorhandene Spieler werden nie betrachtet..
        if(actualPlayer.playerNumber == -1)
            continue;
        // DieBank zieht als letztes
        if(playerIndex == 9) {
            break;
        }
        // Schleife, damit der Spieler sooft ziehen kann bis er nicht mehr kann oder verloren / gewonnen hat.
        do {
            short c;
            turnEnd = 1;
            winningIndex = winning(actualPlayer);
            // Bei verlorenen oder gewonnen Spiel wird die Auswahl verlassen.
            if(winningIndex == -1 || winningIndex == 1)
                break;
            // Ausgabe der Karte der Bank.
            printf("Die Bank hat eine offene Karte:");
            coloursToPrint(allPlayersPointer[0].handCards[0].colour);
            cardKindToPrint(allPlayersPointer[0].handCards[0].name);
            printf("\n");
            // Ausgabe der Karten des jetzigen Spielers.
            printf("Spieler %hd: %s. Du hast folgende Karten", playerIndex, actualPlayer.name);
            for(c = 0; c < allPlayersPointer[playerIndex].cardCounter; c++) {
                coloursToPrint(actualPlayer.handCards[c].colour);
                cardKindToPrint(actualPlayer.handCards[c].name);
                if(c + 1 == actualPlayer.cardCounter)
                    printf(".\n\n");
                else
                    printf(",");
            }
            // Abfrage was der Spieler tun möchte.
            printf("Was möchstest du machen? :\n");
            printf("1 - Eine Karte ziehen?\n");
            printf("2 - Keine Karte mehr ziehen?\n");
            scanf("%hd", &choice);
            // Abfrage der verschiedenen Auswahlmöglichkeiten
            if(choice == 1) {
                card* drawenCard = (card*) drawCard(cardDeck);
                addCardToHand(&allPlayersPointer[playerIndex], drawenCard);
                printf("Du hast eine");
                coloursToPrint(allPlayersPointer[playerIndex].handCards[actualPlayer.cardCounter - 1].colour);
                cardKindToPrint(allPlayersPointer[playerIndex].handCards[actualPlayer.cardCounter - 1].name);
                printf("gezogen1!\n\n");
                turnEnd = 0;
            }
            else if(choice == 2)
                break;
            else
                turnEnd = 0;
        }
        while(!turnEnd);
        // Falls ein Spieler gewonnen hat, bekommt er alles.
        if(winningIndex == 1) {

        }
	}
}

// Funktion welche eine gezogene Karte zu der Hand hinzufügt
void addCardToHand(player* actualPlayer, card* actualCard) {
			short playersCardCounter = (*actualPlayer).cardCounter;
			(*actualPlayer).handCards[playersCardCounter] = *actualCard;
			(*actualPlayer).actualScore += (*actualCard).value;
			(*actualPlayer).cardCounter += 1;
}

// Zurücksetzen der spielerhänder
void resetPlayerHand(player* actualPlayer) {
			(*actualPlayer).actualScore = 0;
			(*actualPlayer).cardCounter = 0;
}

// Funktion die das Kartenziehen regelt.
void* drawCard(void** cardDeck) {
	void* actualCardDeck[52];
	void* drawenCard;
	short actualCardCounter = 0;
	short c;
	short randomCard;

	// Es werden alle Karten aufgezählt die noch im Deck sind.
	for(c = 0; c < 52; c++) {
		if(cardDeck[c] != NULL) {
			actualCardDeck[actualCardCounter] = cardDeck[c];
			actualCardCounter++;
		}
	}
	// Falls es keine Karten mehr im Deck gibt, wird NULL zurückgegeben.
	if(actualCardCounter == 0)
		return NULL;
	// Eine zufällige Karte aus dem übrigen Karten im Deck wird ausgesucht.
	randomCard = rand() % actualCardCounter;
	drawenCard = actualCardDeck[randomCard];
	// Die zufäälig gezogene Karte wird aus dem richtigen Deck herausgenommen.
	actualCardDeck[randomCard] = NULL;
	return drawenCard;
}

// Funktion die prüft ob der jeweilige Spieler gewonnen hat.
short winning(player actualPlayer) {
        // Abfrage nach dem Gewinn.
        if(actualPlayer.actualScore == 22) {
            card* actualCard[5];
            *actualCard = actualPlayer.handCards;
            // Wenn man 2 Ässer hat, hat man gewonnen.
            if((*actualCard[0]).name == ASS && (*actualCard[1]).name == ASS) {
                printf("%s, du hast gewonnen, da du 2 Ässer auf der Hand hast!\n", actualPlayer.name);
                return 1;
            }
            // Falls nicht, hat man bei 22 Punkten verloren.
            else {
                printf("%s, du hast verloren, da du 22 Punkte, aber keine 2 Ässer auf der Hand hast!\n", actualPlayer.name);
                return -1;
            }
        }
        // Bei genau 21 hat man gewonnen.
        else if(actualPlayer.actualScore == 21) {
            printf("%s, du hast gewonnen, da du 21 Punkte erreichst hast!\n", actualPlayer.name);
            return 1;
        }
        // Bei mehr als 21 Punkten hat man verloren.
        else if(actualPlayer.actualScore > 21) {
            printf("%s, du hast verloren, da du %hd Punkte erreichst hast!\n", actualPlayer.name, actualPlayer.actualScore);
            return -1;
        }
        // Man ist noch unter den 21 Punkten.
        else
            return 0;
}

// Wandelt ein colours enum in einen String um.
void coloursToPrint(enum colours colour) {
    switch(colour) {
        case KARO:  printf(" Karo");
                    break;
        case HERZ:  printf(" Herz");
                    break;
        case PIK:   printf(" Pik");
                    break;
        case KREUZ: printf(" Kreuz");
                    break;
    }
}

// Wandelt ein cardKind enum in einen String um.
void cardKindToPrint(enum cardKind cardTyp) {
    switch(cardTyp) {
        case ZWEI:    printf(" Zwei");
                        break;
        case DREI:    printf(" Drei");
                        break;
        case VIER:    printf(" Vier");
                        break;
        case FUENF:   printf(" Fünf");
                        break;
        case SECHS:   printf(" Sechs");
                        break;
        case SIEBEN:  printf(" Sieben");
                        break;
        case ACHT:    printf(" Acht");
                        break;
        case NEUN:    printf(" Neun");
                        break;
        case ZEHN:    printf(" Zehn");
                        break;
        case BUBE:    printf(" Bube");
                        break;
        case DAME:    printf(" Dame");
                        break;
        case KOENIG:  printf(" König");
                        break;
        case ASS:     printf(" Ass");
                        break;
    }
}
