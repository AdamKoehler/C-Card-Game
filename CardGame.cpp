#include <iostream>
#include <string>
#include <random>
#include <stack> 
#include <ctime>
using namespace std;

struct cardTraits {
    // a card consists of a number, a color and a face
    int number;
    string color;
    string face;
    char altNumber; // this will be used to store the char value of face cards
}; 

void populateDeck(cardTraits *deck){

    // populate the values of each card in the deck by using 4 switch statements
        for(int i=0;i<52;i++){
        switch(i / 13){ // i / 13 will break the deck up into quarters for our 4 cases. from there we can assign values.
            case 0:// array index 0-12
                deck[i].face = "Spades";
                deck[i].color = "Black";
                deck[i].number = (i%13) + 1;
                break;

            case 1: // array index 13-26
                deck[i].face = "Hearts";
                deck[i].color = "Red";
                deck[i].number = (i%13) + 1;
                break;

            case 2: // array index 27-39
                deck[i].face = "Clubs";
                deck[i].color = "Black";
                deck[i].number = (i%13) + 1;
                break;

            case 3: // array index 40-52
                deck[i].face = "Diamonds";
                deck[i].color = "Red";
                deck[i].number = (i%13) + 1;
                break;

        default: // set char values for face cards
        break;
        }
    }
    // set the char values for face cards
    for(int i=0;i<52;i++){
        switch(deck[i].number){
            case 1:
                deck[i].altNumber = 'A';
                break;
            case 11:
                deck[i].altNumber = 'J';
                break;
            case 12:
                deck[i].altNumber = 'Q';
                break;
            case 13:
                deck[i].altNumber = 'K';
                break;
            default:
                break;
        }
    }
    // once we have our deck of cards populated we can pass these cards to a function to shuffle them up
}

void shuffle(cardTraits *deck){
// to shuffle the deck we can swap indexes of our array in a random sequence
    srand(time(NULL)); // seed our random number generator
    int randomIndex;
    cardTraits temp; // we will use this to swap our cards
    for(int i=0;i<52;i++){
        randomIndex = rand() % 52; // generate a random index between 0 and 51
        temp = deck[i]; // store the card at index i in a temp variable
        deck[i] = deck[randomIndex]; // swap the card at index i with the card at the random index
        deck[randomIndex] = temp; // swap the card at the random index with the card at index i
    }
}

void compare(int playerHandScore,int computerHandScore){
    if (playerHandScore > computerHandScore){
        cout << "You win!\n\n";
    }
    else if (playerHandScore < computerHandScore){
        cout << "You lose!\n\n";
    }
    else{
        cout << "It's a tie!\n\n";
    }
}

int computerScore(){
    // generate a random number between 5 and 55 to represent our computer generated hand score
    return rand() % 51 + 5;

}

void deal(cardTraits *playerHand , cardTraits *deck){ // to playerHand from deck
    // deal our player 5 cards using the top 5 cards in our shuffled deck with only one point of access which is the top of the stack
    // no reaching in the middle of the deck to grab a card

    stack<cardTraits> shuffledDeck;
    for(int i=0;i<52;i++){
        shuffledDeck.push(deck[i]);         // add
    }
    for(int i=0;i<5;i++){
        playerHand[i] = shuffledDeck.top(); // copy
        shuffledDeck.pop();                 // remove
    }

    // print
    cout << "\n\nPLAYER HAND: \n\n";
        for (int i=0; i<5; i++){
        if (playerHand[i].number <= 1 || playerHand[i].number >= 11){
            cout << playerHand[i].altNumber <<  " " << playerHand[i].color << " " << playerHand[i].face << "   ";
        }
        else{
        cout << playerHand[i].number <<  " " << playerHand[i].color << " " << playerHand[i].face << "   ";
        }
    }   
}

int calcScore (cardTraits *playerHand) {
    int playerHandScore = 0;
    for(int i=0;i<5;i++){
        if(playerHand[i].number == 1){
            playerHandScore += 12;
        }
        playerHandScore += playerHand[i].number;
    }
    return playerHandScore;
}

int main(){    
    // initialize an empty array of our struct data type
    cardTraits deck[52];
    populateDeck(deck);
    cout << "\n\nNEW DECK: \n\n";
    for (int i=0; i<52; i++){
        if (deck[i].number <= 1 || deck[i].number >= 11){
            cout << deck[i].altNumber <<  " " << deck[i].color << " " << deck[i].face << "   ";
        }
        else{
        cout << deck[i].number <<  " " << deck[i].color << " " << deck[i].face << "   ";
        }
    }

   shuffle(deck); // this will shuffle our cards by placing them in a stack at random indexes.

   cout << "\n\nSHUFFLED DECK: \n\n";
    for (int i=0; i<52; i++){
        if (deck[i].number <= 1 || deck[i].number >= 11){
            cout << deck[i].altNumber <<  " " << deck[i].color << " " << deck[i].face << "   ";
        }
        else{
        cout << deck[i].number <<  " " << deck[i].color << " " << deck[i].face << "   ";
        }
    }

    // we must deal our player 5 cards from the shuffled deck. deal is where our stack data structure is located.
    // create 5 empty slots in memory for our player hand
    cardTraits playerHand[5];
    deal(playerHand,deck);   // deal will also print our cards so that the player can see what they have before scores are calculated
    
    // caluculate the score of our local players hand
    int playerHandScore = calcScore(playerHand);

    // generate a number between 5-55 to represent our computer generated hand score
    int computerHandScore = computerScore();

    cout << "\n\nPLAYER HAND SCORE: " << playerHandScore << "\n\n";
    cout << "\n\nCOMPUTER HAND SCORE: " << computerHandScore << "\n\n";

    // compare the scores of the two hands and determine a winner
    compare(playerHandScore,computerHandScore); // compare will print the winner to the console
    
    return 0;
}