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
    monsterX[NUM_OF_MONSTERS], monstersY[NUM_OF_MONSTERS],
    hasTimeWatch, lives = 3;

void introduction()
{
    system("cls");
    // PlaySoundA(TEXT("C:\\Users\\kk\\Desktop\\project\\intros.wav"), NULL, SND_FILENAME | SND_ASYNC);

    int n;
    printf("\n\n\n\t\tWelcome, Captain Leo Mason...\n");
    printf("\t\tEarth is in grave danger, and humanity's last hope rests on you.\n\n");

    printf("\t\tI am the Commander of Mission Control.\n\t\tWe have entrusted you with a critical task that only you can complete.\n\n");
    printf("\t\t(1. Understood, Commander. What’s the situation? / 2. Just get to the point, Commander!) (1/2): ");
    scanf("%d", &n);

    if (n == 2)
        printf("\n\t\tFair enough, Captain. Let's skip the formalities...\n");
    else
        printf("\n\t\tGlad to see you’re prepared, Captain.\n");

    printf("\n\t\tEarth is suffering from a massive environmental crisis.\n\t\tThe scientists believe that the Solum Sphere, an artifact on the planet Krypton, is our last hope.\n");
    getch();

    printf("\n\t\tThe Solum Sphere has the power to restore balance to our ecosystem.\n\t\tYour mission is simple, but dangerous: retrieve the Sphere and return.\n");
    getch();

    printf("\n\t\tKrypton is not without its perils...\n\t\tYou’ll face three major trials to reach the artifact.\n");
    printf("\n\t\t(1. Trials? Bring them on! / 2. Do I have a choice?) (1/2): ");
    scanf("%d", &n);

    if (n == 2)
        printf("\n\t\tNot really, Captain. Humanity is counting on you.\n");
    else
        printf("\n\t\tThat’s the spirit, Captain!\n");

    printf("\n\t\tFirst, you must navigate the Maze of Shadows, a labyrinth designed to confuse even the most skilled travelers.\n");
    printf("\t\tIf you make it to the end, a mysterious figure may grant you a gift: a Time Watch with three lives.\n");
    getch();

    printf("\n\t\tThe Time Watch will grant you a second chance if things go south. But be careful—once all lives are spent, the mission ends.\n\n");
    printf("\t\t(1. Understood. I’ll be careful. / 2. So, no room for mistakes, huh?) (1/2): ");
    scanf("%d", &n);

    printf("\n\t\tIn the second level, you’ll face a monstrous creature. Your Time Watch may be the only thing standing between you and certain doom.\n");
    getch();

    printf("\n\t\tFinally, the last challenge awaits in the Heart of Krypton—a maze at the core of the planet where the Solum Sphere resides.\n\t\tRetrieve it, and Earth will be saved.\n\n");

    printf("\t\tAre you ready, Captain Leo Mason?\n\t\t(1. For Earth! / 2. Here goes nothing...) (1/2): ");
    scanf("%d", &n);

    printf("\n\t\tGood luck, Captain. Humanity’s fate is in your hands. We'll see you when you return.\n");
    printf("\n\t\tPRESS ANY KEY TO BEGIN YOUR MISSION...");
    getch();
}

void resetConditions()
{ // resets the game conditions and make it ready for new game
    system("cls");
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

void generateMaze(int includeMonsters)
{
    int offsetX = 50; // Horizontal offset to center the maze
    int offsetY = 5;  // Vertical offset to center the maze

    setCoordinates(offsetX, offsetY);
    printf("\033[1;34m+----------------------------------------------------+\033[0m\n");

    for (int i = 0; i < GRID_SIZE; i++) // column-wise
    {
        setCoordinates(offsetX, offsetY + 1 + i); // Offset row positioning for vertical centering
        printf("\033[1;34m| \033[0m");

        for (int j = 0; j < GRID_SIZE; j++) // row-wise
        {
            if (j == playerX && i == playerY) // Check if this position matches player's location
            {
                printf("\033[1;33m%c \033[0m", PLAYER); // Display player
            }
            else if (j == endPointX && i == endPointY) // Check if this position matches end/finish point
            {
                printf("\033[1;33m %c <FINISH>\033[0m", END_POSITION); // Display finish point
            }
            else
            {
                int isObject = 0; // Flag for object presence
                for (int k = 0; k < NUM_OF_OBJECTS; k++)
                {
                    if (j == objectX[k] && i == objectY[k]) // Check if object is at this position
                    {
                        isObject = 1;
                        break;
                    }
                }

                int isMonster = 0; // Flag for monster presence
                if (includeMonsters)
                {
                    for (int k = 0; k < NUM_OF_MONSTERS; k++)
                    {
                        if (j == monsterX[k] && i == monstersY[k]) // Check if monster is at this position
                        {
                            isMonster = 1;
                            break;
                        }
                    }
                }

                if (isObject)
                {
                    printf("\033[1;37m%c \033[0m", OBJECT); // Display object
                }
                else if (isMonster)
                {
                    printf("\033[1;31m%c \033[0m", MONSTER); // Display monster
                }
                else
                {
                    printf("  "); // Display open path
                }
            }
        }
        printf("\033[1;34m |\033[0m\n"); // Right border of maze
    }

    setCoordinates(offsetX, offsetY + GRID_SIZE + 1);
    printf("\033[1;34m+----------------------------------------------------+\033[0m");
}

int riddle()
{
    char *riddles[] = {
        "What has keys but can't open locks?",
        "What has to be broken before you can use it?",
        "What has a ring but no finger?"};
    char *answers[] = {
        "keyboard",
        "egg",
        "telephone"};

    srand(time(0));

    int randomIndex = rand() % (sizeof(riddles) / sizeof(riddles[0]));
    setCoordinates(36, 32);
    printf("\033[1;35mMysterious Figure:\033[0m So Riddle me this O Traveller\n");
    setCoordinates(36, 34);
    printf("%s\n", riddles[randomIndex]);
    char answer[32];
    setCoordinates(36, 36);
    printf("\033[1;33mLeo:\033[0m ");
    scanf("%s", &answer);

    if (strcasecmp(answer, answers[randomIndex]) == 0)
    {
        return 1;
    }
    return 0;
}

int movePlayer(char direction, int includeMonsters)
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

        if (includeMonsters)
        {
            for (int i = 0; i < NUM_OF_MONSTERS; i++)
            {
                if (newX == monsterX[i] && newY == monstersY[i])
                {
                    isAMonster = 1;
                    return isAMonster;
                }
            }
        }

        if (canMove)
        {
            playerX = newX;
            playerY = newY;
        }
    }

    generateMaze(includeMonsters); // generate updated maze with new player position
    return 0;
}

void level1Intro()
{
    system("cls");

    setCoordinates(36, 10);
    printf("\033[1;34m*Leo's Ship Lands on Krypton*\033[0m\n");
    getch();

    setCoordinates(36, 12);
    printf("\033[1;33mLeo:\033[0m So this is Krypton... The atmosphere is heavy, and everything looks ancient.\n");
    getch();

    setCoordinates(36, 14);
    printf("I better keep my guard up. There's no telling what could be lurking around here.\n");
    getch();

    setCoordinates(36, 16);
    printf("\033[1;34m*Suddenly, an eerie maze appears before Leo*\033[0m\n");
    getch();

    setCoordinates(36, 18);
    printf("\033[1;33mLeo:\033[0m Of course, it couldn't be as simple as just walking up to the artifact.\n");
    getch();

    setCoordinates(36, 20);
    printf("Alright, let's do this. Just a maze... how hard could it be?\n");
    getch();

    setCoordinates(36, 22);
    printf("\033[1;34m*You enter the maze, surrounded by towering walls and an eerie silence*\033[0m\n");
    getch();

    setCoordinates(36, 24);
    printf("The air feels colder with each step, and faint whispers seem to echo around you...\n");
    getch();

    setCoordinates(36, 26);
    printf("\033[1;35m*Objective:\033[0m Navigate through the maze to reach the mysterious figure awaiting you at the end.\n");
    getch();

    setCoordinates(64, 28);
    printf("\033[1;31mPRESS ANY KEY TO PROCEED\033[0m");
    getch();

    system("cls");
}

void level1Outro()
{
    system("cls");
    setCoordinates(36, 10);
    printf("\033[1;33mLeo:\033[0m Ohh man, that was something! WOAHH!! what the hell are you?\n");
    getch();

    setCoordinates(36, 12);
    printf("\033[1;35mMysterious Figure:\033[0m It is quite impressive that you've crossed the maze, traveller.\n");
    setCoordinates(36, 13);
    printf("I have been in this godforsaken place for who knows how long\n");
    setCoordinates(36, 14);
    printf("and have never seen anyone come out of this damned maze.\n");
    getch();

    setCoordinates(36, 16);
    printf("\033[1;33mLeo:\033[0m (1. Well, I'm not just anyone; I'm built different / 2. Yeah, I got lucky)\n");
    getch();

    setCoordinates(36, 18);
    printf("\033[1;35mMysterious Figure:\033[0m Certainly.\n");
    getch();

    setCoordinates(36, 20);
    printf("\033[1;35mMysterious Figure:\033[0m But from here, it only gets worse.\n");
    setCoordinates(36, 21);
    printf("However, I can give you something that can save your life.\n");
    getch();

    setCoordinates(36, 24);
    printf("\033[1;33mLeo:\033[0m I'd be glad, but what is that?\n");
    getch();

    setCoordinates(36, 26);
    printf("\033[1;35mMysterious Figure:\033[0m My life's work, my TIME WATCH.\n");
    getch();

    setCoordinates(36, 28);
    printf("\033[1;35mMysterious Figure:\033[0m But I have to make sure that you are worthty of it, are you?");
    getch();

    setCoordinates(36, 30);
    printf("\033[1;33mLeo:\033[0m Try me");
    getch();
    Sleep(400);
    hasTimeWatch = riddle();

    if (hasTimeWatch)
    {
        system("cls");
        setCoordinates(36, 20);
        printf("\033[1;35mMysterious Figure:\033[0m You have answered correctly.");
        setCoordinates(36, 22);
        printf("Here, take this... but use it carefully, for you can only use it a limited number of times.\n");
        getch();
        setCoordinates(40, 24);
        printf("\033[1;32mTIME WATCH: \n");
        setCoordinates(40, 26);
        printf("You can use it only three times.\n");
        setCoordinates(40, 28);
        printf("It can help you reverse time if something happens to you.\033[0m\n");
        getch();
        setCoordinates(36, 30);
        printf("\033[1;33mLeo:\033[0m Thank you, old man, or... whatever you are.\n");
        getch();
        setCoordinates(36, 32);
        printf("\033[1;35mMysterious Figure:\033[0m Good luck, traveller, and if you die, may you have a swift death.\n");
        setCoordinates(36, 34);
        printf("May the Force be with you.\n");
        getch();
    }
    else
    {
        system("cls");
        setCoordinates(36, 20);
        printf("\033[1;35mMysterious Figure:\033[0m Hmm... Not quite, traveller.\n");
        setCoordinates(36, 20);
        printf("\033[1;35mMysterious Figure:\033[0m Perhaps your journey will sharpen your wits... or end them.\n");
        getch();
        setCoordinates(36, 22);
        printf("\033[1;33mLeo:\033[0m Yeah whatever I'm better off without your stupid watch.");
        getch();
        setCoordinates(36, 24);
        printf("\033[1;35mMysterious Figure:\033[0m Good luck, traveller, and if you die, may you have a swift death.\n");
        setCoordinates(36, 26);
        printf("May the Force be with you.\n");
        getch();
    }
    setCoordinates(64, 36);
    printf("\033[1;31mPRESS ANY KEY TO CONTINUE\033[0m");
    getch();
    return;
}
void level2Intro()
{
    system("cls");

    setCoordinates(36, 10);
    printf("\033[1;34m*Leo enters the deeper part of Krypton’s maze*\033[0m\n");
    getch();

    setCoordinates(36, 12);
    printf("\033[1;33mLeo:\033[0m Alright, things just got darker and scarier...\n");
    getch();

    setCoordinates(36, 14);
    printf("\033[1;34m*Monsters are lurking in the shadows*\033[0m\n");
    getch();

    setCoordinates(36, 16);
    printf("Beware! If a monster catches you, you will be sent back to the beginning.\n");
    getch();

    setCoordinates(36, 18);
    printf("\033[1;31mIf you have time remaining, answer the riddle to continue.\033[0m\n");
    getch();

    setCoordinates(36, 30);
    printf("\033[1;31mPRESS ANY KEY TO PROCEED TO LEVEL 3\033[0m");
    getch();

    system("cls");
}

void level1()
{
    resetConditions();
    level1Intro();
    generateMaze(0);

    char input;
    while (1)
    {
        input = getch();
        if (tolower(input) == 'q')
        {
            return;
        }
        movePlayer(input, 0);
        if (playerX == endPointX && playerY == endPointY)
        {
            level1Outro();
            return;
        }
    }
}
void level2()
{
    resetConditions();
    level2Intro();
    printf("THE SHADOW MAZE");
    generateMaze(1);

    char input;
    while (1)
    {
        input = getch();
        if (tolower(input) == 'q')
        {
            return;
        }
        int checkMonster = movePlayer(input, 1);

        if (checkMonster)
        {
            system("cls");
            setCoordinates(29, 18);
            printf("You have been eaten by the monster");
            break;
        }

        if (playerX == endPointX && playerY == endPointY)
        {
            printf("Congratulations! You've reached the endpoint.\n");
            break;
        }
    }
}

int main()
{
    srand(time(NULL));
    introduction();
    system("cls");
    Sleep(500);
    // system("\"C:/Users/Asad Mirza/Desktop/Malicious-Maze-Game/setup.bat\"");
    level1();
    system("cls");
    Sleep(500);
    level2();
    return 0;
}