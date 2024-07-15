#ifndef PUZZLE_CASE_H
#define PUZZLE_CASE_H
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <utility>


const unsigned puzzleSize = 3; //Used for 8 puzzle since 3 rows and 3 columns, can be easily changed


class puzzleCase
{
private:
   std::vector<std::vector<int> > myPuzzle;
   unsigned int gCost;
   unsigned int hCost;
   unsigned int blankRowNumber;
   unsigned int blankColNumber;
   std::vector<std::vector<int> > goalPuzzle;
   std::map<puzzleCase, puzzleCase> parent;


public:
   puzzleCase();
   puzzleCase(std::vector<std::vector<int> > aPuzzle);
   void printPuzzleCase();
   unsigned int getGCost() const;
   unsigned int getHCost() const;
   void setGCost();
   void setFCost();
   std::vector<std::vector<int> > getMyPuzzle();
   void setHCost(const std::string &algType);
   unsigned int getFCost() const;
   unsigned int getBlankColNumber();
   unsigned int getBlankRowNumber();
   bool operator<(const puzzleCase &aCase) const;
   bool isGoalCase();
   bool isValidMove(int rowNum, int colNum);
   unsigned locateBlankRowNumber();
   unsigned locateBlankColNumber();
   puzzleCase moveBlankUp(puzzleCase);
   puzzleCase moveBlankDown(puzzleCase);
   puzzleCase moveBlankLeft(puzzleCase);
   puzzleCase moveBlankRight(puzzleCase);
   bool isGoalState();
   unsigned getManhattanCost();
   unsigned getMisplacedCost();
   std::vector<puzzleCase> getChildCases(puzzleCase firstCase, puzzleCase secondCase, puzzleCase thirdCase, puzzleCase fourthCase);
   void expandCase(puzzleCase myCase, std::priority_queue<puzzleCase> &cases, std::map<std::vector<std::vector<int> >, bool> &visitedCases, std::string &algType);
};


#endif
