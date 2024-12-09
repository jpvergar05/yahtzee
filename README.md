Description
This program simulates a Yahtzee game with the following features:

Dice Rolling: The player rolls five dice.
Selection: The player can choose which dice to keep and which to reroll.
Scoring: The program calculates scores for various combinations, including:
Ones, Twos, Threes, Fours, Fives, Sixes
Three of a Kind, Four of a Kind, Full House
Small Straight, Large Straight, Chance
Yahtzee
Gameplay: The game progresses until all rows on the scorecard have been filled.
How to Play
Roll the Dice: The game starts with the player rolling five dice.
Keep or Reroll Dice: After each roll, the player is prompted to choose which dice to keep and which to reroll.
Choose a Scoring Row: After the third roll, the player chooses a row on the scorecard to score their dice combination.
Repeat: The game continues until all rows on the scorecard are filled.
Game Over: The final score is displayed when the game is finished.
Game Rules
The game consists of 13 rounds, with each round corresponding to one of the following scoring categories:
Ones: Sum of all dice showing a 1.
Twos: Sum of all dice showing a 2.
Threes: Sum of all dice showing a 3.
Fours: Sum of all dice showing a 4.
Fives: Sum of all dice showing a 5.
Sixes: Sum of all dice showing a 6.
Three of a Kind: At least three dice with the same value, sum of all dice.
Four of a Kind: At least four dice with the same value, sum of all dice.
Full House: A combination of a three-of-a-kind and a pair, 25 points.
Small Straight: A sequence of four consecutive numbers, 30 points.
Large Straight: A sequence of five consecutive numbers, 40 points.
Chance: Sum of all dice, no specific combination required.
Yahtzee: All five dice showing the same value, 50 points.
Bonus: If the sum of scores for Ones to Sixes is 63 or more, the player receives a 35-point bonus.
Classes
Dice
Represents a single die.
Provides methods to roll the die (roll()) and reveal its value (reveal()).
Hand
Represents a player's hand (five dice).
Provides methods to roll and display dice, as well as select which dice to keep.
Game
Manages the game board and keeps track of the score.
Provides methods to calculate and display scores for different combinations, play a round, and check if the game is finished.
