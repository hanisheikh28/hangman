#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h> // for toupper() and isalpha()

#define MAX_WORD_LENGTH 20
#define MAX_GUESSES 4

// Function to draw the hangman figure
void drawHangman(int guesses) {
    switch (guesses) {
        case 6:
            printf(" +---+\n |   |\n     |\n     |\n     |\n     |\n");
            break;
        case 5:
            printf(" +---+\n |   |\n O   |\n     |\n     |\n     |\n");
            break;
        case 4:
            printf(" +---+\n |   |\n O   |\n |   |\n     |\n     |\n");
            break;
        case 3:
            printf(" +---+\n |   |\n O   |\n/|   |\n     |\n     |\n");
            break;
        case 2:
            printf(" +---+\n |   |\n O   |\n/|\\  |\n     |\n     |\n");
            break;
        case 1:
            printf(" +---+\n |   |\n O   |\n/|\\  |\n/    |\n     |\n");
            break;
        case 0:
            printf(" +---+\n |   |\n O   |\n/|\\  |\n/ \\  |\n     |\n");
            break;
    }
}
char wrongGuesses[26];
int wrongCount = 0;

// When a guess is incorrect
if (!guessCorrect) {
    guesses--;
    wrongGuesses[wrongCount++] = guess;
    wrongGuesses[wrongCount] = '\0'; // keep it a valid string
    printf("INCORRECT! Wrong guesses: %s\n", wrongGuesses);
    printf("YOU HAVE %d GUESSES LEFT.\n", guesses);
}

int main() {
    char word[MAX_WORD_LENGTH];
    char guess;
    int wordLength;
    int guesses = MAX_GUESSES;
    int i;
    int correctGuesses = 0;
    int alreadyGuessed = 0;

    // Choose a random word
    srand(time(NULL));
    char *words[] = {"APPLE", "BANANA", "CHERRY", "DATE", "STRAWBERRY"};
    strcpy(word, words[rand() % 5]);
    wordLength = strlen(word);

    // Initialize guessed word
    char guessedWord[wordLength + 1];
    for (i = 0; i < wordLength; i++) {
        guessedWord[i] = '_';
    }
    guessedWord[wordLength] = '\0'; // null-terminate

    printf("WELCOME TO HANGMAN!\n");
    printf("I'M THINKING OF A WORD THAT IS %d LETTERS LONG.\n", wordLength);

    while (guesses > 0 && correctGuesses < wordLength) {
        printf("\n%s\n", guessedWord);
        drawHangman(guesses);

        printf("GUESS A LETTER: ");
        scanf(" %c", &guess);

        // Convert to uppercase and validate
        guess = toupper((unsigned char)guess);
        if (!isalpha(guess)) {
            printf("PLEASE ENTER A LETTER (A-Z).\n");
            continue;
        }

        // Check if already guessed
        alreadyGuessed = 0;
        for (i = 0; i < wordLength; i++) {
            if (guessedWord[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }
        if (alreadyGuessed) {
            printf("YOU'VE ALREADY GUESSED THAT LETTER. TRY AGAIN!\n");
            continue;
        }

        // Check if guess is correct
        int guessCorrect = 0;
        for (i = 0; i < wordLength; i++) {
            if (word[i] == guess && guessedWord[i] == '_') {
                guessedWord[i] = guess;
                correctGuesses++;
                guessCorrect = 1;
            }
        }

        if (!guessCorrect) {
            guesses--;
            printf("INCORRECT! YOU HAVE %d GUESSES LEFT.\n", guesses);
        }
    }

    // Win or lose message
    if (correctGuesses == wordLength) {
        printf("\nCONGRATULATIONS! YOU GUESSED THE WORD: %s\n", word);
    } else {
        printf("\nSORRY, YOU DIDN'T GUESS THE WORD. THE CORRECT ANSWER WAS: %s\n", word);
    }

    return 0;
}
