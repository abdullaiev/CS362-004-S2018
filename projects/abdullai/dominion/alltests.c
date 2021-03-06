#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "test_utils.h"

int test1() {
    printf("======================= Testing Adventurer Card ===================\n");

    int kingdomCards[10] = {
            adventurer,
            smithy,
            village,
            steward,
            minion,
            mine,
            feast,
            remodel,
            tribute,
            council_room
    };
    int seed = 1000;
    int currentPlayer = 0;
    int topCard, secondTopCard;
    int bonus = 0;
    struct gameState currentGameState, savedGameState;

    initializeGame(2, kingdomCards, seed, &currentGameState);
    memcpy(&savedGameState, &currentGameState, sizeof(struct gameState));


    printf("TEST 1: Current player's has two new cards in hands:");
    cardEffect(adventurer, 0, 0, 0, &currentGameState, 0, &bonus);
    int newCards = 2;
    int discardCards = 1;
    int expected = savedGameState.deckCount[currentPlayer] + newCards - discardCards;
    int actual = currentGameState.handCount[currentPlayer];
    if (actual == expected) {
        success();
    } else {
        printf("\nExpected number of cards in hands: %d\n", expected);
        printf("Actual number of cards in hands: %d.", actual);
        failure();
    }


    printf("TEST 2: Two new cards are of treasure type:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(adventurer, 0, 0, 0, &currentGameState, 0, &bonus);
    topCard = currentGameState.hand[currentPlayer][currentGameState.handCount[currentPlayer] - 1];
    secondTopCard = currentGameState.hand[currentPlayer][currentGameState.handCount[currentPlayer] - 2];
    if ((topCard == copper || topCard == silver || topCard == gold) &&
        (secondTopCard == copper || secondTopCard == silver || secondTopCard == gold)) {
        success();
    } else {
        failure();
    }


    printf("TEST 3: Current player's deck has changed:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(adventurer, 0, 0, 0, &currentGameState, 0, &bonus);
    if (currentGameState.deckCount[currentPlayer] != savedGameState.deckCount[currentPlayer]) {
        success();
    } else {
        failure();
    }

    printf("TEST 4: Other player's state has not changed:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(adventurer, 0, 0, 0, &currentGameState, 0, &bonus);
    otherPlayerNotChanged(&currentGameState, &savedGameState);

    printf("TEST 5: No state change occurred to the victory card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(adventurer, 0, 0, 0, &currentGameState, 0, &bonus);
    victoryCardsNotChanged(&currentGameState, &savedGameState);


    printf("TEST 6: No state change occurred to the kingdom card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(adventurer, 0, 0, 0, &currentGameState, 0, &bonus);
    kingdomCardsNotChanged(&currentGameState, &savedGameState, kingdomCards);


    return 0;
}

int test2() {
    printf("======================= Testing Smithy Card ===================\n");

    int kingdomCards[10] = {
            adventurer,
            smithy,
            village,
            steward,
            minion,
            mine,
            feast,
            remodel,
            tribute,
            council_room
    };
    int seed = 1000;
    int bonus = 0;
    int currentPlayer = 0;
    struct gameState currentGameState, savedGameState;

    initializeGame(2, kingdomCards, seed, &currentGameState);
    memcpy(&savedGameState, &currentGameState, sizeof(struct gameState));


    printf("TEST 1: Current player should receive extra three cards:");
    cardEffect(smithy, 0, 0, 0, &currentGameState, 0, &bonus);
    int newCards = 3;
    int discardCards = 1;
    int expected = savedGameState.handCount[currentPlayer] + newCards - discardCards;
    int actual = currentGameState.handCount[currentPlayer];
    if (expected == actual) {
        success();
    } else {
        printf("\nExpected # of cards in hands: %d\n", expected);
        printf("Actual # of cards in hands: %d.", actual);
        failure();
    }


    printf("TEST 2: Current player's deck should decrease by three cards:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(smithy, 0, 0, 0, &currentGameState, 0, &bonus);
    if (currentGameState.deckCount[currentPlayer] == (savedGameState.deckCount[currentPlayer] - 3)) {
        success();
    } else {
        failure();
    }

    printf("TEST 3: Other player's state has not changed:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(smithy, 0, 0, 0, &currentGameState, 0, &bonus);
    otherPlayerNotChanged(&currentGameState, &savedGameState);


    printf("TEST 4: No state change occurred to the victory card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(smithy, 0, 0, 0, &currentGameState, 0, &bonus);
    victoryCardsNotChanged(&currentGameState, &savedGameState);


    printf("TEST 5: No state change occurred to the kingdom card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(smithy, 0, 0, 0, &currentGameState, 0, &bonus);
    kingdomCardsNotChanged(&currentGameState, &savedGameState, kingdomCards);

    return 0;
}

int test3() {
    printf("======================= Testing Village Card ===================\n");

    int kingdomCards[10] = {
            adventurer,
            smithy,
            village,
            steward,
            minion,
            mine,
            feast,
            remodel,
            tribute,
            council_room
    };
    int seed = 1000;
    int currentPlayer = 0;
    int bonus = 0;
    struct gameState currentGameState, savedGameState;

    initializeGame(2, kingdomCards, seed, &currentGameState);
    memcpy(&savedGameState, &currentGameState, sizeof(struct gameState));


    printf("TEST 1: Current player should receive one extra card:");
    cardEffect(village, 0, 0, 0, &currentGameState, 0, &bonus);
    int newCards = 1;
    int discardCards = 1;
    int expected1 = savedGameState.handCount[currentPlayer] + newCards - discardCards;
    int actual1 = currentGameState.handCount[currentPlayer];
    if (expected1 == actual1) {
        success();
    } else {
        printf("\nExpected # of cards in hands: %d\n", expected1);
        printf("Actual # of cards in hands: %d.", actual1);
        failure();
    }


    printf("TEST 2: Current player should receive two more actions:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(village, 0, 0, 0, &currentGameState, 0, &bonus);
    int newActions = 2;
    int expected2 = savedGameState.numActions + newActions;
    int actual2 = currentGameState.numActions;
    if (expected2 == actual2) {
        success();
    } else {
        printf("\nExpected # of current actions: %d\n", expected2);
        printf("Actual # of current actions: %d.", actual2);
        failure();
    }

    printf("TEST 3: Other player's state has not changed:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(village, 0, 0, 0, &currentGameState, 0, &bonus);
    otherPlayerNotChanged(&currentGameState, &savedGameState);


    printf("TEST 4: No state change occurred to the victory card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(village, 0, 0, 0, &currentGameState, 0, &bonus);
    victoryCardsNotChanged(&currentGameState, &savedGameState);


    printf("TEST 5: No state change occurred to the kingdom card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(village, 0, 0, 0, &currentGameState, 0, &bonus);
    kingdomCardsNotChanged(&currentGameState, &savedGameState, kingdomCards);


    return 0;
}

int test4() {
    printf("======================= Testing Steward Card ===================\n");

    int kingdomCards[10] = {
            adventurer,
            smithy,
            village,
            steward,
            minion,
            mine,
            feast,
            remodel,
            tribute,
            council_room
    };
    int seed = 1000;
    int currentPlayer = 0;
    int bonus = 0;
    struct gameState currentGameState, savedGameState;

    initializeGame(2, kingdomCards, seed, &currentGameState);
    memcpy(&savedGameState, &currentGameState, sizeof(struct gameState));


    printf("TEST 1: Choice A - current user draws two more cards:");
    cardEffect(steward, 1, 0, 0, &currentGameState, 0, &bonus);
    int newCards = 2;
    int discardCards = 1;
    int expected1 = savedGameState.handCount[currentPlayer] + newCards - discardCards;
    int actual1 = currentGameState.handCount[currentPlayer];
    if (expected1 == actual1) {
        success();
    } else {
        printf("\nExpected # of cards in hands: %d\n", expected1);
        printf("Actual # of cards in hands: %d.", actual1);
        failure();
    }


    printf("TEST 2: Choice B - current user gains two coins:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(steward, 2, 0, 0, &currentGameState, 0, &bonus);
    int expected2 = savedGameState.coins + 2;
    int actual2 = currentGameState.coins;
    if (expected2 == actual2) {
        success();
    } else {
        printf("\nExpected # of coins: %d\n", expected2);
        printf("Actual # of coins: %d.", actual2);
        failure();
    }


    printf("TEST 3: Choice C - current user can trash any two cards in the hands:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    int card1Position = 1;
    int card2Position = 2;
    cardEffect(steward, 0, card1Position, card2Position, &currentGameState, 0, &bonus);
    //expect both cards to be removed from player's hands
    if (currentGameState.hand[currentPlayer][card1Position] == -1 && currentGameState.hand[currentPlayer][card2Position] == -1) {
        success();
    } else {
        failure();
    }


    printf("TEST 4: Other player's state has not changed:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(steward, 1, 0, 0, &currentGameState, 0, &bonus);
    otherPlayerNotChanged(&currentGameState, &savedGameState);


    printf("TEST 5: No state change occurred to the victory card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(steward, 1, 0, 0, &currentGameState, 0, &bonus);
    victoryCardsNotChanged(&currentGameState, &savedGameState);


    printf("TEST 6: No state change occurred to the kingdom card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    cardEffect(steward, 1, 0, 0, &currentGameState, 0, &bonus);
    kingdomCardsNotChanged(&currentGameState, &savedGameState, kingdomCards);


    return 0;
}

int test5() {
    printf("=============== Testing handCard Function ================\n");

    int kingdomCards[10] = {
            adventurer,
            smithy,
            village,
            steward,
            minion,
            mine,
            feast,
            remodel,
            tribute,
            council_room
    };
    int seed = 1000;
    int currentPlayer = 0;
    struct gameState currentGameState, savedGameState;

    initializeGame(2, kingdomCards, seed, &currentGameState);
    memcpy(&savedGameState, &currentGameState, sizeof(struct gameState));


    printf("TEST 1: It should return the card by given position:");
    currentGameState.hand[currentPlayer][0] = smithy;
    currentGameState.whoseTurn = currentPlayer;
    if (handCard(0, &currentGameState) == smithy) {
        success();
    } else {
        failure();
    }

    printf("TEST 2: It should not cause side effects such as change to the victory card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    handCard(0, &currentGameState);
    victoryCardsNotChanged(&currentGameState, &savedGameState);


    printf("TEST 3: It should not cause side effects such as change to the kingdom card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    handCard(0, &currentGameState);
    kingdomCardsNotChanged(&currentGameState, &savedGameState, kingdomCards);

    return 0;
}

int test6() {
    printf("=============== Testing isGameOver Function ================\n");

    int kingdomCards[10] = {
            adventurer,
            smithy,
            village,
            steward,
            minion,
            mine,
            feast,
            remodel,
            tribute,
            council_room
    };
    int seed = 1000;
    struct gameState currentGameState, savedGameState;

    initializeGame(2, kingdomCards, seed, &currentGameState);
    memcpy(&savedGameState, &currentGameState, sizeof(struct gameState));


    printf("TEST 1: It should return true if province pile is empty:");
    currentGameState.supplyCount[province] = 0;
    if (isGameOver(&currentGameState) == 1) {
        success();
    } else {
        failure();
    }

    printf("TEST 2: It should return false if there is at least one province card left (and supply piles are full):");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.supplyCount[province] = 1;
    if (isGameOver(&currentGameState) == 0) {
        success();
    } else {
        failure();
    }

    printf("TEST 3: It should return true if at least three supply piles are empty");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.supplyCount[smithy] = 0;
    currentGameState.supplyCount[gold] = 0;
    currentGameState.supplyCount[tribute] = 0;
    if (isGameOver(&currentGameState) == 1) {
        success();
    } else {
        failure();
    }

    printf("TEST 4: It should return false if only two supply piles are empty");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.supplyCount[smithy] = 0;
    currentGameState.supplyCount[gold] = 0;
    if (isGameOver(&currentGameState) == 0) {
        success();
    } else {
        failure();
    }

    printf("TEST 5: It should not cause side effects such as change to the victory card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    isGameOver(&currentGameState);
    victoryCardsNotChanged(&currentGameState, &savedGameState);


    printf("TEST 6: It should not cause side effects such as change to the kingdom card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    isGameOver(&currentGameState);
    kingdomCardsNotChanged(&currentGameState, &savedGameState, kingdomCards);

    return 0;
}

int test7() {
    printf("=============== Testing updateCoins Function ================\n");

    int kingdomCards[10] = {
            adventurer,
            smithy,
            village,
            steward,
            minion,
            mine,
            feast,
            remodel,
            tribute,
            council_room
    };
    int seed = 1000;
    int currentPlayer = 0;
    struct gameState currentGameState, savedGameState;

    initializeGame(2, kingdomCards, seed, &currentGameState);
    memcpy(&savedGameState, &currentGameState, sizeof(struct gameState));


    printf("TEST 1: It should not add new coins if the player does not have treasure cards in hands");
    currentGameState.hand[currentPlayer][0] = village;
    currentGameState.hand[currentPlayer][1] = minion;
    currentGameState.hand[currentPlayer][2] = mine;
    currentGameState.handCount[currentPlayer] = 3;
    updateCoins(currentPlayer, &currentGameState, 0);
    if (currentGameState.coins == 0) {
        success();
    } else {
        failure();
    }

    printf("TEST 2: It should handle all three kinds of treasury cards");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.hand[currentPlayer][0] = copper;
    currentGameState.hand[currentPlayer][1] = silver;
    currentGameState.hand[currentPlayer][2] = gold;
    currentGameState.handCount[currentPlayer] = 3;
    updateCoins(currentPlayer, &currentGameState, 0);
    if (currentGameState.coins == 6) {
        success();
    } else {
        failure();
    }

    printf("TEST 3: It should add given bonus on top of treasure cards");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.hand[currentPlayer][0] = copper;
    currentGameState.hand[currentPlayer][1] = silver;
    currentGameState.hand[currentPlayer][2] = gold;
    currentGameState.handCount[currentPlayer] = 3;
    updateCoins(currentPlayer, &currentGameState, 2);
    if (currentGameState.coins == 8) {
        success();
    } else {
        failure();
    }


    printf("TEST 5: It should not cause side effects such as change to the victory card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    updateCoins(currentPlayer, &currentGameState, 2);
    victoryCardsNotChanged(&currentGameState, &savedGameState);


    printf("TEST 6: It should not cause side effects such as change to the kingdom card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    updateCoins(currentPlayer, &currentGameState, 2);
    kingdomCardsNotChanged(&currentGameState, &savedGameState, kingdomCards);


    return 0;
}

int test8() {
    printf("=============== Testing buyCard Function ================\n");

    int kingdomCards[10] = {
            adventurer,
            smithy,
            village,
            steward,
            minion,
            mine,
            feast,
            remodel,
            tribute,
            council_room
    };
    int seed = 1000;
    int currentPlayer = 0;
    struct gameState currentGameState, savedGameState;

    initializeGame(2, kingdomCards, seed, &currentGameState);
    memcpy(&savedGameState, &currentGameState, sizeof(struct gameState));


    printf("TEST 1: It should buy a card and place it into the discard pile:");
    currentGameState.whoseTurn = currentPlayer;
    currentGameState.numBuys = 1;
    currentGameState.supplyCount[village] = 1;
    currentGameState.coins = 5;
    int status = buyCard(village, &currentGameState);
    int expectedCount =  savedGameState.discardCount[currentPlayer] + 1;
    int actualCount =  currentGameState.discardCount[currentPlayer];
    if (status == 0 && expectedCount == actualCount) {
        success();
    } else {
        printf("\nPurchased card did not appear in discard pile. Expected: %d, Actual %d", expectedCount, actualCount);
        failure();
    }


    printf("TEST 2: It should not allow to purchase cards if number of available buys is less than one:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.whoseTurn = currentPlayer;
    currentGameState.numBuys = 0;
    currentGameState.supplyCount[village] = 1;
    currentGameState.coins = 5;
    if (buyCard(village, &currentGameState) == -1) {
        success();
    } else {
        failure();
    }


    printf("TEST 3: It should not allow to purchase a card if that card ran out of supply:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.whoseTurn = currentPlayer;
    currentGameState.numBuys = 1;
    currentGameState.supplyCount[village] = 0;
    currentGameState.coins = 5;
    if (buyCard(village, &currentGameState) == -1) {
        success();
    } else {
        failure();
    }


    printf("TEST 4: It should not allow to purchase a card if the user doesn't have enough coins:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.whoseTurn = currentPlayer;
    currentGameState.numBuys = 1;
    currentGameState.supplyCount[province] = 1;
    currentGameState.coins = 7;
    if (buyCard(province, &currentGameState) == -1) {
        success();
    } else {
        failure();
    }

    printf("TEST 5: It should decrease number of available coins:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.whoseTurn = currentPlayer;
    currentGameState.numBuys = 1;
    currentGameState.supplyCount[province] = 1;
    currentGameState.coins = 8;
    buyCard(province, &currentGameState);
    if (currentGameState.coins == 0) {
        success();
    } else {
        failure();
    }


    printf("TEST 6: It should decrease number of available buys:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.whoseTurn = currentPlayer;
    currentGameState.numBuys = 1;
    currentGameState.supplyCount[province] = 1;
    currentGameState.coins = 8;
    buyCard(province, &currentGameState);
    if (currentGameState.numBuys == 0) {
        success();
    } else {
        failure();
    }

    printf("TEST 7: It should decrease number of available cards to purchase:");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.whoseTurn = currentPlayer;
    currentGameState.numBuys = 1;
    currentGameState.supplyCount[province] = 2;
    currentGameState.coins = 8;
    buyCard(province, &currentGameState);
    if (currentGameState.supplyCount[province] == 1) {
        success();
    } else {
        failure();
    }


    printf("TEST 8: It should not cause side effects such as change to the victory card piles");
    memcpy(&currentGameState, &savedGameState, sizeof(struct gameState));
    currentGameState.whoseTurn = currentPlayer;
    currentGameState.numBuys = 1;
    currentGameState.supplyCount[village] = 1;
    currentGameState.coins = 5;
    buyCard(province, &currentGameState);
    victoryCardsNotChanged(&currentGameState, &savedGameState);


    return 0;
}


int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    return 0;
}