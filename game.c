#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define GRID_SIZE 25
#define PLAYER 'U'
#define OBJECT '#'
#define END_POSITION '$'
#define NUM_OF_OBJECTS 150
#define ROWS 28
#define COLS 25

COORD coord = {0, 0}; // set the initial position to (0, 0)
void setCoordinates(int x, int y)
{
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int playerX, playerY,                                 // Players coordinates
    objectX[NUM_OF_OBJECTS], objectY[NUM_OF_OBJECTS], // array of coordinates of all objects in the maze
    endPointX, endPointY;                             // endpoint/finishpoint coordinates

void resetConditions()
{ // resets the game conditions and make it ready for new game
    int i;
    playerX = 0; // resets the position of player
    playerY = 0;

    endPointX = GRID_SIZE - 1;
    endPointY = GRID_SIZE - 1;

    srand(time(NULL)); // ensures that everytime rand() produces random numbers in random order

    for (i = 0; i < NUM_OF_OBJECTS; i++) // looping till NUM_OF_OBJECTS and populating the X and Y coordinate arrays of objects
    {
        objectX[i] = rand() % GRID_SIZE;
        objectY[i] = rand() % GRID_SIZE;
    }
}

void generateMaze()
{
    system("cls");
    printf("+----------------------------------------------------+\n");
    for (int i = 0; i < GRID_SIZE; i++) // column wise
    {
        printf("| ");
        for (int j = 0; j < GRID_SIZE; j++) // row wise
        {
            if (j == playerX && i == playerY) // checks if the current j and i position of the row and column corresponds to the x and y position of the user
            {
                printf("%c ", PLAYER); // if true, it prints the player at that position/coordinate in the maze
            }
            else if (j == endPointX && i == endPointY) // checks if the current j and i position of the row and column corresponds to the x and y position of the endPoint/finishPoint (basically the last position of the maze)
            {
                printf(" %c <FINISH>", END_POSITION); // if true, it prints the end point at that position/coordinate in the maze
            }
            else
            {
                int isObject = 0;                        // flag to check if there should be an object at that position
                for (int k = 0; k < NUM_OF_OBJECTS; k++) // loops through the number of objects i-e; 150
                {
                    if (j == objectX[k] && i == objectY[k]) // checks if the current j and i position of the row and column corresponds to the x and y position of the current index of object in the array
                    {
                        isObject = 1; // if yes, then the flag is raised as true that means that we have to put an object there
                        break;
                    }
                }
                if (isObject)
                {
                    printf("%c ", OBJECT); // printing object if the flag is true
                }
                else
                {
                    printf("  "); // other wise printing spaces which are basically the corridor/paths in the maze
                }
            }
        }
        printf(" |\n");
    }
    printf("+----------------------------------------------------+");
}

int main()
{
    printf("git checking");
    setCoordinates(29, 14);
    printf("Ayan");
    Sleep(800);
    printf(" Mirza");
    getch();
    resetConditions();
    generateMaze();
    // system("\"C:/Users/Asad Mirza/Desktop/Malicious-Maze-Game/setup.bat\"");
    return 0;
}