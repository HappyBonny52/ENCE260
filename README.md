
# SHOOT & DODGE
"SHOOT & DODGE" is a shooting game for 2 players with 2 UCFK4s.\
This README file is to help you how to run and play this shooting game.


<br /> 

## Goal

This is a shooting game for two players, each player can shoot and dodge bullets at the same time.\
The goal of this game is
to shoot the other opponent as many as possible within three matches.

<br /> 

<br /> 

## How to run the game

1. Open the terminal
2. Navigate the path which contains the source file of this game.
3. Type "make program" into the terminal as following:
```
make program
```
4. Do 'make program' for both funkits.

<br /> 



<br /> 

## How to play the game

Three components are related for playing game and consists of three rounds to complete the game.\
This will help you understand what these components do and each phase of playing game.

<br /> 


<br /> 

### **Components**

<br />

<img src="./Images/Components%20in%20UCFK4.png" width="400" height="300" >



<br /> 

#### ***1) Display***


Display consists of 4 states in matrix (5 rows and 7 columns for game).
1. Starts with Introduction display
2. Display of player moving and shooting bullets 
3. Shows each player's score in each round
4. Display result to inform who is a winner / loser.

<br /> 

#### ***2) Navigation Switch***

<br /> 

<img src="./Images/Navigation%20switch%20related%20to%20player.png" width="400" height="300" >

Each player use the allocated `navigation switch` for moving player.\
Player moves around from the navigation switch perspective.\
Player can move anywhere within matrix boundary.
- `Press the navigation switch` is for shooting bullets,
- `Push up` to make the player moves one up, 
- `Push down` to make the player moves one down,
- `Push left` to make the player moves one left, 
- `Push right` to make the player moves one right. \
\
*Note  that when player reach the end of the matrix,*\
*going farther will spawn the player to the opposite column in the same row.*\
*The bullet is going out in a same direction from where the player was when the player shot.*
<br /> 


#### ***3) LED***  

- LED1 : (Blue light) It is on when showing each states as well as result. 
- LED2 : (Yellow light) It is on when power is on for UCFK4

<br /> 

***4) Reset Button***
- This button is for turning off the game.
- You can play it again by following [How to run the game](#how-to-run-the-game) process. 

<br /> 


<br /> 


### **Game Phases** 

<br /> 

Align two funkits in this manner as shown below.\
(so the each row is matched between two funkits)\
After `make program` both funkit, \
it starts with introduction display, and display will be shown on the matrix.
<br /> 

<img src="./Images/How%20to%20play.png" width="400" height="300" >

<br />

#### ***Steps :***
<br /> 

- **Step 1** : Press navigation switch down to start the game
- **Step 2** : Game is started immediately, \
 &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp; &nbsp; &nbsp; try to shoot the other player while trying to avoid bullets coming from the other player.
- **Step 3** : Whoever shoot the other player successfully obtain one score.
- **Step 4** : Check the score and press the button to continue the game.
- **Step 5** : Step 2, 3 and 4 will be repeated until all rounds are completed. (There are 3 rounds)
- **Step 6** : Whoever gains more score than the other player within 3 rounds wins the game.

<br /> 


## Contributers

- `Aaron Sevilla, ase89 `
- `Bonghyun Kwon, bkw31
`