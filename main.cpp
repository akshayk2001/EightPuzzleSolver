#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include "puzzleCase.h"
using namespace std;


vector<int> PuzzleInput(string &myString) // Used for gathering user input for custom puzzle
{
   getline(cin, myString);
   vector<int> puzzleRow;
   for (unsigned i = 0; i < puzzleSize; ++i)
   {
       puzzleRow.push_back(stoi(myString.substr(i, 1), nullptr, 10)); //Convert each user entered row from a string to int and then add it to the row
   };
   return puzzleRow;
};


int main()
{
   vector<vector<int> > puzzle; //puzzle is kept as a vector of vector of ints with each inner vector representing a row in the puzzle
   string userInput;
   bool takingInput = true; //Used to test whether we are done taking input
   string searchType = "";
   priority_queue<puzzleCase> cases;             //Used for selecting the next best case
   map<vector<vector<int> >, bool> visitedCases; //Used to keep track of already visited puzzle cases
   unsigned int numNodesExpanded = 0;
   unsigned int maxQSize = cases.size();
   unsigned int solutionDepth = 0;
   while (takingInput)
   {
       cout << "Enter 1 for first preset puzzle, 2 for second preset puzzle, 3 for third preset puzzle and 4 for custom puzzle " << endl;
       cin >> userInput;
       if (userInput == "1")
       {
           puzzle = {{1, 2, 3}, {5, 0, 6}, {4, 7, 8}};
           takingInput = false; //We are done taking input
       }
       else if (userInput == "2")
       {
           puzzle = {{1, 3, 6}, {5, 0, 7}, {4, 8, 2}};
           takingInput = false;
       }
       else if (userInput == "3")
       {
           puzzle = {{0, 7, 2}, {4, 6, 1}, {3, 5, 8}};
           takingInput = false;
       }
       else if (userInput == "4")
       {
           cin.ignore();
           cout << "Please enter your 8-puzzle where 0 represents the blank " << endl;
           cout << "Please enter the first row without any spaces: " << endl;
           puzzle.push_back(PuzzleInput(userInput));
           cout << "Please enter the second row without any spaces: " << endl;
           puzzle.push_back(PuzzleInput(userInput));
           cout << "Please enter the third row without any spaces: " << endl;
           puzzle.push_back(PuzzleInput(userInput));
           takingInput = false;
       }
       else
       {
           cout << "Input is invalid. Please either enter 1, 2, 3 or 4." << endl;
           userInput.clear();
       }
   }
   while (searchType != "U" && searchType != "MIS" && searchType != "MAN") //Used for detecting which algorithm to use, keep going until valid input
   {
       cout << "Please enter your search type (U for Uniform Cost Search, MIS for A* Misplaced Tile Search, and MAN for A* Manhattan Distance Search:" << endl;
       cin >> searchType;
   }
   puzzleCase newPuzzle = puzzleCase(puzzle); //puzzleCase is a class that handles each puzzle case and includes the necessary operators for each case
   newPuzzle.setHCost(searchType);            //Set h(n) cost depending on algorithm which is passed in as a string
   cases.push(newPuzzle);
   while (cases.size() > 0) //main driver algorithm
   {
       if (cases.size() > maxQSize) //If the queue size is bigger than our set max, we must update our max
       {
           maxQSize = cases.size();
       }
       puzzleCase currentCase = cases.top();
       cases.pop();
       visitedCases[currentCase.getMyPuzzle()] = 1; //We have now visited this case so change its bool map value to 1
       cout << "The best state to expand with a g(n) of " << currentCase.getGCost() << " and h(n) of " << currentCase.getHCost() << " is:" << endl;
       currentCase.printPuzzleCase();
       if (currentCase.isGoalCase())
       {
           //currentCase.printPuzzleCase();
           cout << "Depth of solution was " << currentCase.getGCost() << endl;
           cout << "Number of nodes expanded was " << numNodesExpanded << endl;
           cout << "Max queue size was " << maxQSize << endl;
           return 0;
       }
       currentCase.expandCase(currentCase, cases, visitedCases, searchType); //Expanding the current case to get options for next best case
       numNodesExpanded += 1;                                                //We have now expanded one more node
   }
   cout << "Unsolvable 8-Puzzle" << endl;
   cout << "Number of nodes expanded was " << numNodesExpanded << endl;
   cout << "Max queue size was " << maxQSize << endl;
   return 0;
};





