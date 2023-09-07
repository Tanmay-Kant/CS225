/* Your code here! */
#pragma once
#include "dsets.h"
#include "cs225/PNG.h"
#include<iostream>
#include<math.h>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<vector>


using namespace std;
using namespace cs225;
class SquareMaze{
public:
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  vector<int> solveMaze();
  PNG* drawMaze() const;
  PNG* drawMazeWithSolution();

  int width_, height_, size_, endpoint;
  DisjointSets mazeSets;
  vector<bool> WallR;
  vector<bool> WallD;

};