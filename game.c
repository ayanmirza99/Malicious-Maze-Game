#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

#define GRID_SIZE 25
#define PLAYER 'U'
#define OBJECT '#'
#define END_POSITION '$'
#define NUM_OF_OBJECTS 150
#define NUM_OF_MONSTERS 24
#define MONSTER 'M'
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
    endPointX, endPointY,                             // endpoint/finishpoint coordinates
    monsterX[NUM_OF_MONSTERS], monstersY[NUM_OF_MONSTERS];

void resetConditions()
{                // resets the game conditions and make it ready for new game
    playerX = 0; // resets the position of player
    playerY = 0;

    endPointX = GRID_SIZE - 1;
    endPointY = GRID_SIZE - 1;

    srand(time(NULL)); // ensures that everytime rand() produces random numbers in random order

    for (int i = 0; i < NUM_OF_OBJECTS; i++) // looping till NUM_OF_OBJECTS and populating the X and Y coordinate arrays of objects
    {
        objectX[i] = rand() % GRID_SIZE;
        objectY[i] = rand() % GRID_SIZE;
    }
    for (int i = 0; i < NUM_OF_MONSTERS; i++) // looping till NUM_OF_OBJECTS and populating the X and Y coordinate arrays of objects
    {
        monsterX[i] = rand() % GRID_SIZE;
        monstersY[i] = rand() % GRID_SIZE;
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

                int isMonster = 0;                        // flag to check if there should be a monster at that position
                for (int k = 0; k < NUM_OF_MONSTERS; k++) // loops through the number of monsters i-e; 24
                {
                    if (j == monsterX[k] && i == monstersY[k]) // checks if the current j and i position of the row and column corresponds to the x and y position of the current index of monter in the array
                    {
                        isMonster = 1; // if yes, then the flag is raised as true that means that we have to put a monster there
                        break;
                    }
                }

                if (isObject)
                {
                    printf("%c ", OBJECT); // printing object if the flag is true
                }
                else if (isMonster)
                {
                    printf("%c ", MONSTER); // printing monster if the flag is true
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

int movePlayer(char direction)
{
    int newX = playerX;
    int newY = playerY;

    switch (tolower(direction))
    {
    case 'w':
        newY--;
        break;
    case 's':
        newY++;
        break;
    case 'a':
        newX--;
        break;
    case 'd':
        newX++;
        break;
    }
    if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE) // cheks if the new X and Y coordinates of player are greater than or equal to zero as they can't be negative and whether they are within the grid
    {
        int canMove = 1, isAMonster = 0; // Flag to indicate if the move is valid

        for (int i = 0; i < NUM_OF_OBJECTS; i++)
        {
            if (newX == objectX[i] && newY == objectY[i])
            {
                canMove = 0;
                break;
            }
        }

        for (int i = 0; i < NUM_OF_MONSTERS; i++)
        {
            if (newX == monsterX[i] && newY == monstersY[i])
            {
                isAMonster = 1;
                return isAMonster;
            }
        }

        if (canMove)
        {
            playerX = newX;
            playerY = newY;
        }
    }

    generateMaze(); // generate updated maze with new player position
    return 0;
}

void level1()
{
    resetConditions();
    generateMaze();

    char input;
    while (1)
    {
        input = getch();
        if (tolower(input) == 'q')
        {
            return;
        }
        int checkMonster = movePlayer(input);

        if (checkMonster)
        {
            system("cls");
            break;
        }

        if (playerX == endPointX && playerY == endPointY)
        {
            printf("Congratulations! You've reached the endpoint.\n");
            break;
        }
    }
    setCoordinates(29, 18);
    printf("You have been eaten by the monster");
}

int main()
{
    setCoordinates(29, 14);
    printf("WELCOME LAD THERE ARE THREE LEVELS TO THIS GAME WANNA PLAY [Y/y]: ");
    char input;
    scanf("%c", &input);
    if (tolower(input) == 'y')
    {
        level1();
    }
    else
    {
        setCoordinates(29, 18);
        printf("THEN BE ON YOUR WAY");
    }
    // system("\"C:/Users/Asad Mirza/Desktop/Malicious-Maze-Game/setup.bat\"");
    return 0;
}