#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "puzzleCase.h"


using namespace std;


puzzleCase::puzzleCase(vector<vector<int> > aPuzzleCase) //Constructor initializing all the necessary member variables
{
   myPuzzle = aPuzzleCase;
   gCost = 0;                               //Keeps track of the g(n) cost
   hCost = 0;                               // Keeps track of the h(n) cost
   blankRowNumber = locateBlankRowNumber(); //Keeps track of where the blank row number is in order to find it when necessary
   blankColNumber = locateBlankColNumber(); //Keeps track of where the blank col number is in order to find it when necessary
   goalPuzzle = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
}


unsigned int puzzleCase::locateBlankColNumber() //Used to find the blank column number
{
   int blankCol;
   for (unsigned i = 0; i < myPuzzle.size(); ++i)
   {
       for (unsigned j = 0; j < myPuzzle.at(i).size(); ++j)
       {
           if (myPuzzle.at(i).at(j) == 0)
           {
               blankCol = j;
           }
       }
   }
   return blankCol;
}


unsigned int puzzleCase::locateBlankRowNumber() //Used to find the blank row number
{
   int blankRow;
   for (unsigned i = 0; i < myPuzzle.size(); ++i)
   {
       for (unsigned j = 0; j < myPuzzle.at(i).size(); ++j)
       {
           if (myPuzzle.at(i).at(j) == 0)
           {
               blankRow = i;
           }
       }
   }
   return blankRow;
}


unsigned int puzzleCase::getBlankColNumber() //getter function for grabbing the blank column number
{
   return blankColNumber;
}
unsigned int puzzleCase::getBlankRowNumber() //getter function for grabbing the blank row number
{
   return blankRowNumber;
}
std::vector<std::vector<int> > puzzleCase::getMyPuzzle() //getter function for grabbing the puzzle
{
   return myPuzzle;
}


puzzleCase puzzleCase::moveBlankUp(puzzleCase myCase) //Used to move the blank tile up by swapping the blank and numbered tiles
{
   if (myCase.blankRowNumber != 0) // meaning we can move up
   {


       int valueSave = myCase.myPuzzle.at(myCase.blankRowNumber - 1).at(myCase.blankColNumber); // save numbered tile
       myCase.myPuzzle.at(myCase.blankRowNumber - 1).at(myCase.blankColNumber) = 0;             // set value of original position of numbered tile to 0
       myCase.myPuzzle.at(myCase.blankRowNumber).at(myCase.blankColNumber) = valueSave;         // insert the value of the numbered tile where the original blank was
       myCase.blankRowNumber--;                                                                 // blank is now one more tile up
   }


   return myCase;
}
puzzleCase puzzleCase::moveBlankDown(puzzleCase myCase) //Used to move the blank tile down by swapping the blank and numbered tiles
{
   if (myCase.blankRowNumber != puzzleSize - 1) // meaning we can move down
   {
       int valueSave = myCase.myPuzzle.at(myCase.blankRowNumber + 1).at(myCase.blankColNumber);
       myCase.myPuzzle.at(myCase.blankRowNumber + 1).at(myCase.blankColNumber) = 0;
       myCase.myPuzzle.at(myCase.blankRowNumber).at(myCase.blankColNumber) = valueSave;
       myCase.blankRowNumber++; // blank is now one more tile down
   }
   return myCase;
}
puzzleCase puzzleCase::moveBlankLeft(puzzleCase myCase) //Used to move the blank tile left by swapping the blank and numbered tiles
{
   if (myCase.blankColNumber != 0) // meaning we can move left
   {
       int valueSave = myCase.myPuzzle.at(myCase.blankRowNumber).at(myCase.blankColNumber - 1);
       myCase.myPuzzle.at(myCase.blankRowNumber).at(myCase.blankColNumber - 1) = 0;
       myCase.myPuzzle.at(myCase.blankRowNumber).at(myCase.blankColNumber) = valueSave;
       myCase.blankColNumber--; // blank is now one more tile to the left
   }
   return myCase;
}
puzzleCase puzzleCase::moveBlankRight(puzzleCase myCase) //Used to move the blank tile right by swapping the blank and numbered tiles
{
   if (myCase.blankColNumber != puzzleSize - 1) // meaning we can move right
   {
       int valueSave = myCase.myPuzzle.at(myCase.blankRowNumber).at(myCase.blankColNumber + 1);
       myCase.myPuzzle.at(myCase.blankRowNumber).at(myCase.blankColNumber + 1) = 0;
       myCase.myPuzzle.at(myCase.blankRowNumber).at(myCase.blankColNumber) = valueSave;
       myCase.blankColNumber++; // blank is now one more tile to the right
   }
   return myCase;
}


unsigned int puzzleCase::getMisplacedCost() //Used to calculate h(n) for Misplaced Tile heuristic
{
   unsigned int cost = 0;
   unsigned int comparisonValue = 1; // Used to check if the tile value matches the tile value of the goal case
   for (unsigned int i = 0; i < myPuzzle.size(); i++)
   {
       for (unsigned int j = 0; j < myPuzzle.at(i).size(); j++)
       {
           if (myPuzzle.at(i).at(j) == 0) // Skip the blank tile
           {
               comparisonValue++;
               continue;
           }
 if (myPuzzle.at(i).at(j) != comparisonValue) //If a tile is misplaced then...
           {
               cost++; //We have one more misplaced tile
               comparisonValue++;
           }
           else
           {
               comparisonValue++;
           }
       }
   }
   return cost;
}


unsigned int puzzleCase::getManhattanCost() //Used to calculate h(n) for Manhattan Distanceheuristic
{
   unsigned int overallCost = 0;
   unsigned int currentCost = 0;
   unsigned int tileValue;
   int goalX;
   int goalY;
   int incrementor = -1; // Used for calculating the current position; has to be -1 because incremented in beginning to 0
   int currentX;
   int currentY;
   for (unsigned int i = 0; i < myPuzzle.size(); i++)
   {
       for (unsigned int j = 0; j < myPuzzle.at(i).size(); j++)
       {
           incrementor++;
           tileValue = myPuzzle.at(i).at(j);
           if (tileValue == 0) //Skip blank space
           {
               continue;
           }
           tileValue--;                                                 // Subtract because each tile's value is the index + 1
           goalX = tileValue % puzzleSize;                              //Calculates the goal column
           goalY = tileValue / puzzleSize;                              // Calculates the goal row
           currentX = incrementor % puzzleSize;                         // Calculates the current column
           currentY = incrementor / puzzleSize;                         // Calculates the goal row
           currentCost = abs(currentX - goalX) + abs(currentY - goalY); //Calculates displacement of tile from goal position (Manhattan Distance) for this tile
           overallCost += currentCost;
       }
   }
   return overallCost; //Returns sum of all the distances
}
void puzzleCase::setGCost() // Used to increase g(n) cost when expanding case
{
   gCost++;
}
unsigned int puzzleCase::getGCost() const // getter function for grabbing g(n) cost
{
   return gCost;
}


void puzzleCase::setHCost(const string &algType) //Used to distinguish between which algorithm as h(n) changes based on algorithm type
{
   if (algType == "MIS")
   {
       hCost = getMisplacedCost();
   }
   else if (algType == "MAN")
   {
       hCost = getManhattanCost();
   }
   else
   {
       hCost = 0; // We have Uniform Cost Search in this case
   }
}
unsigned int puzzleCase::getHCost() const //getter function for grabbing the h(n) cost
{
   return hCost;
}


unsigned int puzzleCase::getFCost() const //getter function for grabbing the f(n) cost
{
   return getGCost() + getHCost();
}


bool puzzleCase::isGoalCase() //Used to test whether current case is indeed the goal case
{
   for (unsigned i = 0; i < myPuzzle.size(); ++i)
   {
       for (unsigned j = 0; j < myPuzzle.at(i).size(); ++j)
       {
           if (myPuzzle.at(i).at(j) != goalPuzzle.at(i).at(j)) //if current element is not the same as the goal element
           {
               return false;
           }
       }
   }
   return true;
}


void puzzleCase::printPuzzleCase() //Used to print puzzle case for debugging and testing purposes
{


   for (unsigned i = 0; i < myPuzzle.size(); ++i)
   {
       for (unsigned j = 0; j < myPuzzle.at(i).size(); ++j)
       {
           if (j == myPuzzle.size() - 1)
           {
               cout << myPuzzle.at(i).at(j); //Edge numbers don't require commas
           }
           else
           {
               cout << myPuzzle.at(i).at(j) << ", ";
           }
       }
       cout << endl;
   }
}


bool puzzleCase::isValidMove(int rowNum, int colNum) //Tests whether new blank position is on the puzzle board
{
   if (rowNum < 0 || rowNum >= puzzleSize || colNum < 0 || colNum >= puzzleSize) //If we are not on the board anymore then...
   {
       return false;
   }
   else
   {
       return true;
   }
}


bool puzzleCase::operator<(const puzzleCase &aCase) const //Used to override priority queue comparison
{
   int firstCost = getFCost();
   int secondCost = aCase.getFCost();
   return firstCost < secondCost ? false : true; //Used to find the element in queue with the lowest f(n) cost
}


vector<puzzleCase> puzzleCase::getChildCases(puzzleCase firstCase, puzzleCase secondCase, puzzleCase thirdCase, puzzleCase fourthCase) //Grabs all the possible 
       childCases.push_back(secondCase.moveBlankDown(secondCase)); //Move the blank down and add the new case to the child cases
   }
   if (isValidMove(thirdCase.blankRowNumber, thirdCase.blankColNumber + 1)) //If we can move right then...
   {
       childCases.push_back(thirdCase.moveBlankRight(thirdCase)); //Move the blank right and add the new case to the child cases
   }
   if (isValidMove(fourthCase.blankRowNumber, fourthCase.blankColNumber - 1)) //If we can move left then...
   {
       childCases.push_back(fourthCase.moveBlankLeft(fourthCase)); //Move the blank left and add the new case to the child cases
   }
 return childCases;
}


void puzzleCase::expandCase(puzzleCase aCase, priority_queue<class puzzleCase> &cases, map<vector<vector<int> >, bool> &visitedCases, string &algType) //Handles the expansion of new cases that may lead to solution
{
   vector<puzzleCase> children = getChildCases(aCase, aCase, aCase, aCase); // passes the current case to grab all the possible neighboring cases
   for (int i = 0; i < children.size(); i++)
   {


       if (visitedCases[children.at(i).myPuzzle] == 0) //If we haven't seen this case before...
       {
           children.at(i).setGCost();        //Calculate g(n) for this case
           children.at(i).setHCost(algType); //Calculate h(n) for this case given the algorithm type that we received as a string parameter
           cases.push(children.at(i));       //Add this case to the priority queue as a possible way to reach the solution
       }
   }
}cases where 0 can move to
{
   vector<puzzleCase> childCases;
   if (isValidMove(firstCase.blankRowNumber - 1, firstCase.blankColNumber)) //If we can move up then...
   {
       childCases.push_back(firstCase.moveBlankUp(firstCase)); //Move the blank up and add the new case to the child cases
   }
   if (isValidMove(secondCase.blankRowNumber + 1, secondCase.blankColNumber)) //If we can move down then...
   {
       childCases.push_back(secondCase.moveBlankDown(secondCase)); //Move the blank down and add the new case to the child cases
    }
  if (isValidMove(thirdCase.blankRowNumber, thirdCase.blankColNumber - 1)) //If we can move down then...
   {
       childCases.push_back(thirdCase.moveBlankLeft(thirdCase)); //Move the blank down and add the new case to the child cases
    }
  if (isValidMove(fourthCase.blankRowNumber, fourthCase.blankColNumber + 1)) //If we can move down then...
   {
       childCases.push_back(fourthCase.moveBlankRight(fourthCase)); //Move the blank down and add the new case to the child cases
    }
}


