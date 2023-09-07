/*Your code here! */ 
#include "maze.h"
#include <sys/time.h>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

//empty maze constructor
SquareMaze::SquareMaze() {}

//created maze, using random function
void SquareMaze::makeMaze(int width, int height)
{
	width_ = width;
	height_ = height;
	size_ = height_ * width_;
	for (int i = 0; i < size_; i++)
	{
		WallD.push_back(1);
		WallR.push_back(1);
	}
	DisjointSets path;
	path.addelements(size_);
	int i = 0;
	while (i < size_ - 1)
	{
		int random_wall = rand() % 2;
		int randX = rand() % width_;
		int randY = rand() % height_;
		if (random_wall)
		{
			if (randX < width_ - 1 && WallR[randX + randY *width_] && path.find(randX + randY *width_) != path.find(randX + randY *width_ + 1))
			{
				WallR[randX + randY *width_] = 0;
				path.setunion(path.find(randX + randY *width_), path.find(randX + randY *width_ + 1));
				i++;
			}
		}
		else
		{
			if (randY < height_ - 1 && WallD[randX + randY *width_] && path.find(randX + randY *width_) != path.find(randX + (randY + 1) *width_))
			{
				WallD[randX + randY *width_] = 0;
				path.setunion(path.find(randX + randY *width_), path.find(randX + (1 + randY) *width_));
				i++;
			}
		}
	}
}
//check to see if there are any walls in the directions of travel, where 0, 1, 2, 3 are right, down, left, up, respectively
bool SquareMaze::canTravel(int x, int y, int dir) const
{
	if (dir == 0)
	{
		return WallR[y *width_ + x] == false;
	}
	else if (dir == 1)
	{
		return WallD[y *width_ + x] == false;
	}
	else if (dir == 2)
	{
		return (x != 0) && (WallR[y *width_ + x - 1] == false);
	}
	else if (dir == 3)
	{
		return (y != 0) && (WallD[y *width_ + x - width_] == false);
	}
	else
	{
		return false;
	}
}

//places wall based off WallR or WallD existing
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	if (dir == 0)
	{
		WallR[y *width_ + x] = exists;
	}
	else if (dir == 1)
	{
		WallD[y *width_ + x] = exists;
	}
}

//using BFS algorithm, send out findingVector to explore possible travel paths, find the maxPath (aka the solution due to not getting stopped), then have solvingVector traceback from endpoint to start, and reverse for solved output
vector<int> SquareMaze::solveMaze()
{
	int x, y, current;
	vector<int> previous;
	vector<int> distance;
	previous.push_back(0);
	distance.push_back(0);
	for (int i = 1; i < width_ * height_; i++)
	{
		previous.push_back(-1);
		distance.push_back(0);
	}
	queue<int> findingVector;
	findingVector.push(0);
	while (!findingVector.empty())
	{
		current = findingVector.front();
		x = current % width_;
		y = current / width_;
		findingVector.pop();
		if (canTravel(x, y, 0))
		{
			while (previous[current + 1] == -1)
			{
				findingVector.push(current + 1);
				previous[current + 1] = current;
				distance[current + 1] = distance[current] + 1;
				break;
			}
		}
		if (canTravel(x, y, 1))
		{
			while (previous[current + width_] == -1)
			{
				findingVector.push(current + width_);
				previous[current + width_] = current;
				distance[current + width_] = distance[current] + 1;
				break;
			}
		}
		if (canTravel(x, y, 2))
		{
			while (previous[current - 1] == -1)
			{
				findingVector.push(current - 1);
				previous[current - 1] = current;
				distance[current - 1] = distance[current] + 1;
				break;
			}
		}
		if (canTravel(x, y, 3))
		{
			while (previous[current - width_] == -1)
			{
				findingVector.push(current - width_);
				previous[current - width_] = current;
				distance[current - width_] = distance[current] + 1;
				break;
			}
		}
	}
	int maxPath = width_ *(height_ - 1);
	for (int j = 0; j < width_; j++)
	{
		if (distance[width_ *(height_ - 1) + j] > distance[maxPath])
		{
			maxPath = width_ *(height_ - 1) + j;
		}
	}
	endpoint = maxPath;
	vector<int> solvingVector;
	current = endpoint;
	while (current != 0)
	{
		if (previous[current] == current - 1)
		{
			solvingVector.push_back(0);
		}
		if (previous[current] == current - width_)
		{
			solvingVector.push_back(1);
		}
		if (previous[current] == current + 1)
		{
			solvingVector.push_back(2);
		}
		if (previous[current] == current + width_)
		{
			solvingVector.push_back(3);
		}
		current = previous[current];
	}
	reverse(solvingVector.begin(), solvingVector.end());

	return solvingVector;
}

//draw maze using PNG class
PNG *SquareMaze::drawMaze() const
{
	PNG *canvas = new PNG(width_ *10 + 1, height_ *10 + 1);
	for (int x = 0; x < width_; x++)
	{
		for (int y = 0; y < height_; y++)
		{
			if (y == 0)
			{
				for (unsigned p = 0; p < 10; p++)
				{
					if ((x *10 + p < 1) || (x *10 + p > 9))
					{
						HSLAPixel &cur_pixel = canvas->getPixel(x *10 + p, 0);
						cur_pixel.l = 0;
					}
				}
			}
			if (x == 0)
			{
				for (unsigned p = 0; p < 10; p++)
				{
					HSLAPixel &cur_pixel = canvas->getPixel(0, y *10 + p);
					cur_pixel.l = 0;
				}
			}
			if (!canTravel(x, y, 0))
			{
				for (unsigned p = 0; p <= 10; p++)
				{
					HSLAPixel &cur_pixel = canvas->getPixel((x + 1) *10, y *10 + p);
					cur_pixel.l = 0;
				}
			}
			if (!canTravel(x, y, 1))
			{
				for (unsigned p = 0; p <= 10; p++)
				{
					HSLAPixel &cur_pixel = canvas->getPixel(x *10 + p, (y + 1) *10);
					cur_pixel.l = 0;
				}
			}
		}
	}
	return canvas;
}

//draw maze with PNG then draw the solution vector from solve maze
PNG *SquareMaze::drawMazeWithSolution()
{
	PNG *solvedCanvas = drawMaze();
	vector<int> solution = solveMaze();
	int x = 5;
	int y = 5;
	for (unsigned i = 0; i < solution.size(); i++)
	{
		if (solution[i] == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				HSLAPixel &pix = solvedCanvas->getPixel(x, y);
				pix.h = 0;
				pix.s = 1;
				pix.l = 0.5;
				pix.a = 1;
				x++;
			}
		}
		if (solution[i] == 1)
		{
			for (int i = 0; i < 10; i++)
			{
				HSLAPixel &pix = solvedCanvas->getPixel(x, y);
				pix.h = 0;
				pix.s = 1;
				pix.l = 0.5;
				pix.a = 1;
				y++;
			}
		}
		if (solution[i] == 2)
		{
			for (int i = 0; i < 10; i++)
			{
				HSLAPixel &pix = solvedCanvas->getPixel(x, y);
				pix.h = 0;
				pix.s = 1;
				pix.l = 0.5;
				pix.a = 1;
				x--;
			}
		}
		if (solution[i] == 3)
		{
			for (int i = 0; i < 10; i++)
			{
				HSLAPixel &pix = solvedCanvas->getPixel(x, y);
				pix.h = 0;
				pix.s = 1;
				pix.l = 0.5;
				pix.a = 1;
				y--;
			}
		}
	}
	HSLAPixel &pix = solvedCanvas->getPixel(x, y);
	pix.h = 0;
	pix.s = 1;
	pix.l = 0.5;
	pix.a = 1;
	x -= 4;
	y += 5;
	for (int i = 0; i < 9; i++)
	{
		HSLAPixel &pix = solvedCanvas->getPixel(x, y);
		pix.h = 0;
		pix.s = 0;
		pix.l = 1;
		pix.a = 1;
		x++;
	}
	return solvedCanvas;
}