#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

// Constants for board size and different scoring categories in Yahtzee
const int BOARD_SIZE = 13;
const int ONES = 0;
const int TWOS = 1;
const int THREES = 2;
const int FOURS = 3;
const int FIVES = 4;
const int SIXES = 5;
const int THREE_OF_KIND = 6;
const int FOUR_OF_KIND = 7;
const int FULL_HOUSE = 8;
const int SMALL_STRAIGHT = 9;
const int LARGE_STRAIGHT = 10;
const int CHANCE = 11;
const int YAHTZEE = 12;

// Dice class to represent a single die
class Dice {
private:
    int value;  // Stores the value of the die (1 to 6)

public:
    // Roll the die, setting the value to a random number between 1 and 6
    void roll() {
        value = rand() % 6 + 1;
    }

    // Reveal the current value of the die
    int reveal() {
        return value;
    }

    // Set the value of the die (used for setting predefined values)
    void setValue(int value) {
        this->value = value;
    }
};

// Hand class to represent a collection of 5 dice
class Hand {
private:
    vector<Dice> dice;  // Vector to store 5 dice
    string selection;    // String to store the dice numbers that the user wants to keep

public:
    // Constructor to initialize the dice and selection string
    Hand() {
        dice.resize(5);  // Resize the dice vector to hold 5 dice
        selection = "";
    }

    // Display the values of all 5 dice
    void show() {
        for (int i = 0; i < 5; ++i) {
            cout << "Dice " << (i + 1) << ": " << dice[i].reveal() << endl;
        }
    }

    // Set the selection string (which dice to keep)
    void setSelection(string selection) {
        this->selection = selection;
    }

    // Roll the dice based on the user's selection (keeps selected dice, rolls others)
    void play() {
        for (int i = 0; i < 5; ++i) {
            if (selection.find(to_string(i + 1)) == string::npos) {
                dice[i].roll();  // Roll the die if not selected to keep
            }
        }
    }

    // Return a pointer to a specific die
    Dice* getDice(int diceNum) {
        return &dice[diceNum];
    }
};

// Game class to represent the Yahtzee game
class Game {
private:
    vector<int> board;     // Vector to store the scores for each category on the board
    bool played[BOARD_SIZE];  // Array to track whether a category has been played

public:
    // Constructor to initialize the board and played array
    Game() {
        board.resize(BOARD_SIZE);  // Resize the board to 13 categories
        fill_n(played, BOARD_SIZE, false);  // Mark all categories as not played
    }

    // Calculate the score for a given hand and category (row)
    int calcScore(Hand* hand, int row) {
        vector<int> counts(7, 0);  // Array to count occurrences of each die face (1-6)
        int sum = 0;  // Variable to sum the values of the dice

        // Count the occurrences of each die face and calculate the sum
        for (int i = 0; i < 5; ++i) {
            int value = hand->getDice(i)->reveal();
            counts[value]++;
            sum += value;
        }

        // Scoring rules for different categories (based on the row)
        switch (row) {
            case ONES:  return counts[1] * 1;
            case TWOS:  return counts[2] * 2;
            case THREES: return counts[3] * 3;
            case FOURS: return counts[4] * 4;
            case FIVES: return counts[5] * 5;
            case SIXES: return counts[6] * 6;

            case THREE_OF_KIND:
                for (int i = 1; i <= 6; ++i) {
                    if (counts[i] >= 3) return sum;  // If 3 or more of any number, return the sum
                }
                return 0;

            case FOUR_OF_KIND:
                for (int i = 1; i <= 6; ++i) {
                    if (counts[i] >= 4) return sum;  // If 4 or more of any number, return the sum
                }
                return 0;

            case FULL_HOUSE:
                if ((counts[1] == 2 || counts[2] == 2 || counts[3] == 2 || counts[4] == 2 || counts[5] == 2 || counts[6] == 2) &&
                    (counts[1] == 3 || counts[2] == 3 || counts[3] == 3 || counts[4] == 3 || counts[5] == 3 || counts[6] == 3)) {
                    return 25;  // Full house gives 25 points
                }
                return 0;

            case SMALL_STRAIGHT:
                // Small straight condition: at least 4 consecutive numbers
                if ((counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1) ||
                    (counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1) ||
                    (counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1 && counts[6] >= 1)) {
                    return 30;  // Small straight gives 30 points
                }
                return 0;

            case LARGE_STRAIGHT:
                // Large straight condition: exactly 5 consecutive numbers
                if ((counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && counts[5] == 1) ||
                    (counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && counts[5] == 1 && counts[6] == 1)) {
                    return 40;  // Large straight gives 40 points
                }
                return 0;

            case CHANCE:
                return sum;  // Chance gives the total sum of the dice

            case YAHTZEE:
                for (int i = 1; i <= 6; ++i) {
                    if (counts[i] == 5) return 50;  // Yahtzee gives 50 points for five of a kind
                }
                return 0;

            default:
                return 0;  // Default case (should not occur)
        }
    }

    // Display the current status of the board
    void show() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            cout << "Row " << i << ": " << (played[i] ? to_string(board[i]) : "Not Played") << endl;
        }
    }

    // Calculate the score for the upper section (categories 1 to 6)
    int getUpperScore() {
        int upperScore = 0;
        for (int i = 0; i <= SIXES; ++i) {
            if (played[i]) {
                upperScore += board[i];  // Add score if the category has been played
            }
        }
        return upperScore;
    }

    // Calculate the score for the lower section (categories 6 to 12)
    int getLowerScore() {
        int lowerScore = 0;
        for (int i = THREE_OF_KIND; i <= YAHTZEE; ++i) {
            if (played[i]) {
                lowerScore += board[i];  // Add score if the category has been played
            }
        }
        return lowerScore;
    }

    // Calculate the bonus score (35 points for upper section score >= 63)
    int getBonusScore() {
        if (getUpperScore() >= 63) return 35;  // Bonus for achieving >= 63 in the upper section
        return 0;
    }

    // Calculate the total score (upper + lower + bonus)
    int getTotalScore() {
        return getUpperScore() + getLowerScore() + getBonusScore();
    }

    // Play a turn, assigning a score to a category if it has not been played
    void play(Hand* hand, int row) {
        if (!played[row]) {
            int score = calcScore(hand, row);
            board[row] = score;  // Store the score in the respective row
            played[row] = true;  // Mark the row as played
        }
    }

    // Check if a category has been played
    bool isPlayed(int row) {
        return played[row];
    }

    // Check if the game is finished (all categories have been played)
    bool isFinished() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (!played[i]) return false;  // If any category is not played, the game is not finished
        }
        return true;
    }
};

// Function to run the game
void run() {
    srand(time(nullptr));  // Seed the random number generator with the current time
    Game game;  // Create a new game
    Hand hand;  // Create a new hand of dice

    // Loop until the game is finished
    while (!game.isFinished()) {
        cout << "Rolling the dice..." << endl;
        hand.play();  // Roll the dice
        hand.show();  // Display the dice values

        // Prompt the user to select which dice to keep
        cout << "Enter the dice numbers to keep (e.g., '12345' to keep all): ";
        string selection;
        cin >> selection;
        hand.setSelection(selection);  // Set the dice selection

        // Allow two more rolls
        for (int i = 0; i < 2; ++i) {
            cout << "Rolling again..." << endl;
            hand.play();
            hand.show();

            cout << "Enter the dice numbers to keep: ";
            cin >> selection;
            hand.setSelection(selection);  // Update the dice selection
        }

        // Prompt the user to select a category (row) to play
        cout << "Select a row to play: ";
        int row;
        cin >> row;
        game.play(&hand, row);  // Play the selected row in the game
        game.show();  // Show the updated board
        cout << "Total Score: " << game.getTotalScore() << endl;  // Display the total score

        cout << endl;
    }

    // End of the game
    cout << "Game Over!" << endl;
}

// Main function to start the game
int main() {
    run();  // Call the run function to start the game
    return 0;  // Exit the program
}
