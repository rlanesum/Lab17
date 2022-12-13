/************
Anesu Mudzingwa
C++
David Busch
Lab 4: Temperature Output
Due Date: 14 October 2022
**************/

#include <iostream>
#include <string>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

const int boardSize = 10;
typedef char grid[boardSize][boardSize];
const char water = '~';
const char ship = '#';

void waterDeployment(grid userGrid);
void outputGrid(grid userGrid);
void startingPoint(int x, int y, grid userGrid);
void userinputSwitch(int shipNumber);
void directionDeployment(int a, int direction, int xcoordinate, int ycoordinate, grid userGrid);
void shipSize(int placement);

void cpuRandom();

enum direction
{
	up,
	down,
	left,
	right,
};

struct plotFleet//All the variables needed to plot the user's Fleet
{
	int xcoordinate;
	int ycoordinate;
	int dir;
	int size;
};


struct Fleet
{
	string Carrier;
	string Battleship;
	string Cruiser;
	string Submarine;
	string Destroyer;

};

plotFleet shipPlot;

grid userGrid;
grid userfireGrid;

grid CPUgrid;
grid CPUfireGrid;


int main()
{
	int placement = 1;// initialised to run the loop 5 times, after every iteration the loop is incremented 

	waterDeployment(userGrid);

	outputGrid(userGrid);

	cout << "Welcome to Battleship!" << endl;
	cout << "Lets have fun!" << endl;
	cout << "\nLet's begin:";

	do
	{

		userinputSwitch(placement);

		cout << "x: " << endl;
		cin >> shipPlot.xcoordinate;
		cout << "y: " << endl;
		cin >> shipPlot.ycoordinate;

		shipPlot.xcoordinate = shipPlot.xcoordinate - 1;
		shipPlot.ycoordinate = shipPlot.ycoordinate - 1;

		startingPoint(shipPlot.xcoordinate, shipPlot.ycoordinate, userGrid);

		cout << "Now please enter the direction:" << endl;
		cout << "0 = up" << endl;
		cout << "1 = down" << endl;
		cout << "2 = left" << endl;
		cout << "3 = right" << endl;

		cin >> shipPlot.dir;

		shipSize(placement);

		directionDeployment(shipPlot.size, shipPlot.dir, shipPlot.xcoordinate, shipPlot.ycoordinate, userGrid);
		placement++;

	} while (placement < 6);

	cpuRandom();
	
	return 0;
}

void cpuRandom() 
{
	int  placement = 1;
	int  astart;

	waterDeployment(CPUgrid);

	outputGrid(CPUgrid);

	srand((unsigned)time(0));

	do 
	{
		if (placement == 1) 
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					userGrid[j][i] = water;
				}
			}
		}

		int randomxcoordinate = (rand() % 10) + 1;
		int randomycoordinate = (rand() % 10) + 1;

		cout << "x:" << randomxcoordinate << endl;
		cout << "y:" << randomycoordinate << endl;

		randomxcoordinate = randomxcoordinate - 1;
		randomycoordinate = randomycoordinate - 1;

		shipSize(placement);


		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (j == randomxcoordinate && i == randomycoordinate && userGrid[j][i] != ship)
				{
					userGrid[j][i] = ship;
				}
			}
		}

		outputGrid(userGrid);



		int randomdirection = (rand() % 3) + 1;
		cout << randomdirection << endl;

		switch (randomdirection)
		{

			int x;
			int j;

		case 0:


			for (x = 0; x < 10; x++)
			{

				for (j = 0; j < 10; j++)
				{
					if (userGrid[j][x] == ship && randomxcoordinate == j && randomycoordinate == x)
					{
						for (astart = 1; astart < shipPlot.size; astart++)
						{
							if (shipPlot.size <= x && userfireGrid[j][x - 1] == water)
							{
								for (int astart2 = 1; astart2 < shipPlot.size; astart2++)
								{
									if (userfireGrid[j][x - astart2] == ship)
									{
										continue;
									}
								}
								userGrid[j][x - astart] = ship;
							}
							else 
							{
								continue;
							}
						}
					}
				}
			}

			for (x = 0; x < 10; x++)
			{
				for (j = 0; j < 10; j++)
				{
					if (userGrid[j][x] == ship && randomxcoordinate == j && randomycoordinate == x)
					{
						for (astart = 1; astart < shipPlot.size; astart++)
						{
							if (x + shipPlot.size < 10)
							{
								for (int astart2 = 1; astart2 < shipPlot.size; astart2++)
								{
									if (userfireGrid[j][x + astart2] == ship)
									{
										continue;
									}
								}
								userGrid[j][x + astart] = ship;
							}
							else 
							{
								continue;
							}
						}
					}
				}
			}
			break;

		case 2:

			for (x = 0; x < 10; x++)
			{
				for (j = 0; j < 10; j++)
				{
					if (userGrid[j][x] == ship && randomxcoordinate == j && randomycoordinate == x)
					{
						for (astart = 1; astart < shipPlot.size; astart++)
						{
							if (shipPlot.size <= j && userfireGrid[j - 1][x] == water)
							{
								for (int astart2 = 1; astart2 < shipPlot.size; astart2++)
								{
									if (userfireGrid[j - astart2][x] == ship)
									{
										continue;
									}
								}
								userGrid[j - astart][x] = ship;
							}
							else 
							{
								continue;
							}
						}
					}
				}
			}
			break;

		case 3:
			for (x = 0; x < 10; x++)
			{
				for (j = 0; j < 10; j++)
				{
					if (userGrid[j][x] == ship && randomxcoordinate == j && randomycoordinate == x)
					{
						for (astart = 1; astart < shipPlot.size; astart++)
						{
							if (j + shipPlot.size < 10)
							{
								for (int astart2 = 1; astart2 < shipPlot.size; astart2++) 
								{
									if (userfireGrid[j + astart2][x] == ship) 
									{
										continue;
									}
								}
								userGrid[j + astart][x] = ship;
							}
							else 
							{
								continue;
							}
						}
					}
				}
			}
			break;
		}
		placement++;

	} while (placement < 6);

	
}

void userinputSwitch(int shipNumber)
{

	switch (shipNumber) 
	{
		case 1:
			cout << endl << "Please enter the coordinates of the beginning of your Carrier(x,y): " << endl;
			break;
		case 2:
			cout << endl << "Please enter the coordinates of the beginning of your Battleship(x,y): " << endl;
			break;

		case 3:
			cout << endl << "Please enter the coordinates of the beginning of your Cruiser(x,y): " << endl;
			break;

		case 4:
			cout << endl << "Please enter the coordinates of the beginning of your Submarine(x,y): " << endl;
			break;

		case 5:
			cout << endl << "Please enter the coordinates of the beginning of your Destroyer(x,y): " << endl;
			break;
	} 
}

void directionDeployment(int a, int direction, int xcoordinate, int ycoordinate, grid userGrid)// change direction to enum later
{

	int astart;
	int x;
	int j;

	switch (direction)
	{
	case 0:

			for (x = 0; x < 10; x++)
			{
				for (j = 0; j < 10; j++)
				{
					if (userGrid[j][x] == ship && xcoordinate == j && ycoordinate == x)
					{
						for (astart = 1; astart < a; astart++)
						{
							if (a <= x)
							{
								userGrid[j][x - astart] = ship;
							}
						}
					}
				}
			}
			break;

	case 1:
			for (x = 0; x < 10; x++)
			{
				for (j = 0; j < 10; j++)
				{
					if (userGrid[j][x] == ship && xcoordinate == j && ycoordinate == x)
					{
						for (astart = 1; astart < a; astart++)
						{
							if (x + a < 10)
							{
								userGrid[j][x + astart] = ship;
							}
						}
					}
				}
			}
			break;

	case 2:
			for (x = 0; x < 10; x++)
			{
				for (j = 0; j < 10; j++)
				{
					if (userGrid[j][x] == ship && xcoordinate == j && ycoordinate == x)
					{
						for (astart = 1; astart < a; astart++)
						{
							if (a <= j)
							{
								userGrid[j - astart][x] = ship;
							}
						}
					}
				}
			}
			break;

	case 3:
			for (x = 0; x < 10; x++)
			{
				for (j = 0; j < 10; j++)
				{
					if (userGrid[j][x] == ship && xcoordinate == j && ycoordinate == x)
					{
						for (astart = 1; astart < a; astart++)
						{
							if (j + a < 10)
							{
								userGrid[j + astart][x] = ship;
							}
						}
					}
				}
			}
			break;
	}



}

void waterDeployment(grid userGrid) // grid x
{
	//j represents the x coordinate
	//i represents the y coordinate

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			userGrid[j][i] = water;
		}
	}
}

void outputGrid(grid userGrid)
{
	int dV = 1;
	int dH = 1;

	cout << endl;
	cout << setw(9);

	for (int z = 1; z < 11; z++) 
	{
		cout << z << setw(5);
	}

	cout << endl;
	cout << setw(9);

	for (int y = 0; y < 46; y++)
	{
		cout << "_";
	}

	cout << endl;

	for (int i = 0; i < 10; i++)
	{
		if (dV == 10)
		{
			cout << setw(4) << dV << setw(3) << "||" << setw(2);
		}
		else
		{
			cout << setw(4) << dV << setw(3) << "||" << setw(2);
		}
		for (int j = 0; j < 10; j++)
		{
			cout << userGrid[j][i] << setw(5);
		}
		cout << endl;
		dV++;
	}

	cout << endl;
}

void startingPoint(int x, int y, grid userGrid)
{

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) 
		{
			if (j == x && i == y && userGrid[j][i] != ship)
			{
				userGrid[j][i] = ship;
			}
		}
	}


}

void shipSize(int placement) 
{
	if (placement == 1)
	{
		shipPlot.size = 5;
	}
	if (placement == 2) 
	{
		shipPlot.size = 4;
	}
	if (placement == 3) 
	{
		shipPlot.size = 3;
	}
	if (placement == 4) 
	{
		shipPlot.size = 3;
	}
	if (placement == 5) 
	{
		shipPlot.size = 2;
	}
}