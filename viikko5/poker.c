#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3
} Suit;

char input[] = {'c', 'd', 'h', 's'};
char* output[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
char card_values[] = {' ', ' ', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
char* value_output[] = {" ", " ", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

typedef struct {
    Suit card_suit;
    int value;
} Card;

void get_hand(Card* hand) {
    char value, suit;
    for (int i = 0; i < 5; i++) {
        printf("Pick card #%i: ", i+1);
        scanf("%c%c", &value, &suit);
        getchar();
        for (int j = 0; j < 4; j++)
            if (tolower(suit) == input[j]) {
                hand[i].card_suit = j;
                break;
            }
        for (int k = 2; k < 14; k++)
            if (toupper(value) == card_values[k]) {
                hand[i].value = k;
                break;
            }
    }
}

void sort_hand(Card* hand) {
    Card *cardpi, *cardpj;
    Card *card = malloc(sizeof(card));
    for (cardpi = hand + 1; cardpi - hand < 5; cardpi++) {
        *card = *cardpi;
        cardpj = cardpi - 1;
        while (cardpj - hand >= 0 && cardpj->value > card->value) {
            *(cardpj + 1) = *cardpj;
            cardpj--;
        }
        *(cardpj + 1) = *card;
    }
    free(card);
}

void print_hand(Card* hand) {
    for (int i = 0; i < 5; i++)
        printf("%s of %s\n", value_output[hand[i].value], output[hand[i].card_suit]);
}

int main(void) {
    Card* hand = calloc(5, sizeof(hand));
    if (!hand) {
        fprintf(stderr, "Ran out of memory.\n");
        exit(1);
    }

    get_hand(hand);
    print_hand(hand);
    sort_hand(hand);
    print_hand(hand);

    free(hand);
    exit(0);
}
