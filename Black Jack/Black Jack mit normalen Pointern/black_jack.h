#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum colours {
		KARO = 9,
		HERZ,
		PIK,
		KREUZ
};

enum cardKind {
        ZWEI = 2,
        DREI,
        VIER,
        FUENF,
        SECHS,
		SIEBEN,
		ACHT,
		NEUN,
		ZEHN,
		ASS,
		BUBE,
		DAME,
		KOENIG
};

typedef struct cards* cardPointer;

typedef struct cards {
		enum colours colour;
		enum cardKind name;
		short value;
} card;

typedef struct players {
		char name[32];
		short playerNumber;
		cardPointer handCards[5];
		short cardCounter;
		short actualScore;
		short accountValue;
} player;

void initCardDeck(cardPointer* cardDeckPointer);
short initAllPlayer(player* allPlayerPointer);
player initNewPlayer(char* name);

void gameContinues(cardPointer* cardDeck, short playerCounter, player* allPlayersPointer);

cardPointer* drawCard(cardPointer* cardDeck);
void addCardToHand(player* actualPlayer, cardPointer actualCard);
void resetPlayerHand(player* actualPlayer);

short winning(player actualPlayer);

void cardsToPrint(cardPointer actualCard);
void coloursToPrint(enum colours colour);
void cardKindToPrint(enum cardKind cardTyp);
