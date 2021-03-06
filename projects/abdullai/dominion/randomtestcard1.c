//
// Created by Illia Abdullaiev on 5/7/18.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "test_utils.h"


int main() {
    printf("======================= Testing Smithy Card ===================\n");

    int kingdomCards[10];
    memcpy(kingdomCards, getRandomKingdomCards(), sizeof(kingdomCards));
    int iterations = 0;
    int ITERATIONS_LIMIT = 1000;
    int NOISY = 0;
    int tests = 0;
    int failures = 0;
    int successes = 0;
    struct gameState currentGameState, savedGameState;


    while (iterations < ITERATIONS_LIMIT) {
        iterations++;

        if (NOISY == 1) {
            printf("************* ITERATION %d ****************\n", iterations);
        }

        //Generate random input params for the game and the smithy card function
        int numOfPlayers = generateRandomNumber(2, 4);
        int choice1 = generateRandomNumber(0, 1);
        int choice2 = generateRandomNumber(0, 1);
        int choice3 = generateRandomNumber(0, 1);
        int bonus = generateRandomNumber(0, 5);
        int seed = generateRandomNumber(10, 1000);
//        int currentPlayer = generateRandomNumber(0, numOfPlayers - 1);
//        currentGameState.whoseTurn = currentPlayer;
        int currentPlayer = 0;

        //Initialize the game with random inputs
        initializeGame(numOfPlayers, kingdomCards, seed, &currentGameState);

        //set hand, deck, and discard piles to random number bounded above by limits from dominion.h
        currentGameState.handCount[currentPlayer] = generateRandomNumber(1, MAX_HAND);
        currentGameState.deckCount[currentPlayer] = generateRandomNumber(1, MAX_DECK);
        currentGameState.discardCount[currentPlayer] = generateRandomNumber(1, MAX_DECK);

        memcpy(&savedGameState, &currentGameState, sizeof(struct gameState));

        //Run the smithy card function with random input
        cardEffect(smithy, choice1, choice2, choice3, &currentGameState, 0, &bonus);


        //Perform all checks that indicate that the function performs as expected
        tests++;
        int newCards = 3;
        int discardCards = 1;
        int expected = savedGameState.handCount[currentPlayer] + newCards - discardCards;
        int actual = currentGameState.handCount[currentPlayer];
        if (expected == actual) {
            if (NOISY == 1) {
                printf("TEST 1: Current player should receive extra three cards:");
                success();
            }
            successes++;
        } else {
            printf("Iteration %d. TEST 1: Current player should receive extra three cards:\n", iterations);
            printf("\nExpected # of cards in hands: %d\n", expected);
            printf("Actual # of cards in hands: %d.\n", actual);
            printf("SEED: %d.\n", seed);
            failure();
            failures++;
        }


        tests++;
        if (currentGameState.deckCount[currentPlayer] == (savedGameState.deckCount[currentPlayer] - 3)) {
            if(NOISY == 1) {
                printf("TEST 2: Current player's deck should decrease by three cards:");
                success();
            }
            successes++;
        } else {
            printf("Iteration %d. TEST 2: Current player's deck should decrease by three cards:\n", iterations);
            printf("SEED: %d.\n", seed);
            failure();
            failures++;
        }

        if (NOISY == 1) {
            printf("TEST 3: Other player's state has not changed:");
        }
        tests++;
        if (otherPlayerNotChanged(&currentGameState, &savedGameState, NOISY) == 1) {
            successes++;
        } else {
            failures++;
        }

        if (NOISY == 1) {
            printf("TEST 4: No state change occurred to the victory card piles");
        }
        tests++;
        if (victoryCardsNotChanged(&currentGameState, &savedGameState, NOISY) == 1) {
            successes++;
        } else {
            failures++;
        }

        if (NOISY == 1) {
            printf("TEST 5: No state change occurred to the kingdom card piles");
        }
        tests++;
        if (kingdomCardsNotChanged(&currentGameState, &savedGameState, kingdomCards, NOISY) == 1) {
            successes++;
        } else {
            failures++;
        }
    }

    printf("\n********************************\n");
    printf("Smithy card tests completed.\n");
    printf("Total Iterations: %d\n", iterations);
    printf("Total Tests: %d\n", tests);
    printf("Tests Failed: %d\n", failures);
    printf("Tests Succeeded: %d\n\n", successes);

    return 0;
}

