#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <pthread.h>

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

void heading()
{
    system("cls");
    setCoordinates(70, 10);
    printf("\033[1;31m QUEST FOR SOLEM SPHERE\n\033[0m");
    getch();
    setCoordinates(70, 12);
    printf("THIS");
    Sleep(800);
    setCoordinates(74, 12);
    printf(" GAME");
    Sleep(800);
    setCoordinates(79, 12);
    printf(" IS");
    Sleep(800);
    setCoordinates(82, 12);
    printf(" BROUGHT");
    Sleep(800);
    setCoordinates(90, 12);
    printf(" T0");
    Sleep(800);
    setCoordinates(93, 12);
    printf(" YOU");
    Sleep(800);
    setCoordinates(97, 12);
    printf(" BY");
    setCoordinates(50, 18);
    printf("\033[1;34mAYAN MIRZA\t\t\tM.SAAD BAIG\t\t\tSYED AZAN\n\033[0m");
    getch();
}
void introduction()
{
    system("cls");
    // PlaySoundA(TEXT("C:\\Users\\kk\\Desktop\\project\\intros.wav"), NULL, SND_FILENAME | SND_ASYNC);

    int n;
    printf("\n\n\n\t\t\033[1;32mCommander:\033[0m Welcome, Captain Leo Mason...\n");
    printf("\t\t\033[1;32mCommander:\033[0m Earth is in grave danger, and humanity's last hope rests on you.\n\n");

    printf("\t\t\033[1;32mCommander:\033[0m I am the Commander of Mission Control.\n\t\tWe have entrusted you with a critical task that only you can complete.\n\n");
    printf("\t\t\033[1;33mLeo:\033[0m (1. Understood, Commander. What's the situation? / 2. Just get to the point, Commander!) (1/2): ");
    scanf("%d", &n);

    if (n == 2)
        printf("\n\t\t\033[1;32mCommander:\033[0m Fair enough, Captain. Let's skip the formalities...\n");
    else
        printf("\n\t\t\033[1;32mCommander:\033[0m Glad to see you're prepared, Captain.\n");

    printf("\n\t\t\033[1;32mCommander:\033[0m Earth is suffering from a massive environmental crisis.\n\t\tThe scientists believe that the Solum Sphere, an artifact on the planet Krypton, is our last hope.\n");
    getch();

    printf("\n\t\t\033[1;32mCommander:\033[0m The Solum Sphere has the power to restore balance to our ecosystem.\n\t\tYour mission is simple, but dangerous: retrieve the Sphere and return.\n");
    getch();

    printf("\n\t\t\033[1;32mCommander:\033[0m Krypton is not without its perils...\n\t\tYou'll face three major trials to reach the artifact.\n");
    printf("\n\t\t\033[1;33mLeo:\033[0m (1. Trials? Bring them on! / 2. Do I have a choice?) (1/2): ");
    scanf("%d", &n);

    if (n == 2)
        printf("\n\t\t\033[1;32mCommander:\033[0m Not really, Captain. Humanity is counting on you.\n");
    else
        printf("\n\t\t\033[1;32mCommander:\033[0m That's the spirit, Captain!\n");

    printf("\n\t\t\033[1;32mCommander:\033[0m First, you must navigate the Maze of Shadows, a labyrinth designed to confuse even the most skilled travelers.\n");
    printf("\n\t\t\033[1;32mCommander:\033[0m If you make it to the end, a mysterious figure may grant you a gift: a Time Watch with three lives.\n");
    getch();

    printf("\n\t\t\033[1;32mCommander:\033[0m The Time Watch will grant you a second chance if things go south. But be careful once all lives are spent, the mission ends.\n\n");
    printf("\t\t\033[1;33mLeo:\033[0m (1. Understood. I'll be careful. / 2. So, no room for mistakes, huh?) (1/2): ");
    scanf("%d", &n);

    printf("\n\t\t\033[1;32mCommander:\033[0m In the second level, you'll face a monstrous creature. Your Time Watch may be the only thing standing between you and certain doom.\n");
    getch();

    printf("\n\t\t\033[1;32mCommander:\033[0m Finally, the last challenge awaits in the Heart of Krypton maze at the core of the planet where the Solum Sphere resides.\n\t\tRetrieve it, and Earth will be saved.\n\n");

    printf("\t\tAre you ready, Captain Leo Mason?");
    printf("\n\t\t\033[1;33mLeo:\033[0m (1. For Earth! / 2. Here goes nothing...) (1/2): ");
    scanf("%d", &n);

    printf("\n\t\t\033[1;32mCommander:\033[0m Good luck, Captain. Humanity's fate is in your hands. We'll see you when you return.\n");
    printf("\033[1;31m\n\t\tPRESS ANY KEY TO PROCEED\033[0m");
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
        int xCoordinate = rand() % GRID_SIZE;
        int yCoordinate = rand() % GRID_SIZE;
        if ((xCoordinate != 1 || yCoordinate != 1) && (xCoordinate != 24 || yCoordinate != 24))
        {
            objectX[i] = rand() % GRID_SIZE;
            objectY[i] = rand() % GRID_SIZE;
        }
    }
    for (int i = 0; i < NUM_OF_MONSTERS; i++) // looping till NUM_OF_OBJECTS and populating the X and Y coordinate arrays of objects
    {
        int xCoordinate = rand() % GRID_SIZE;
        int yCoordinate = rand() % GRID_SIZE;
        if ((xCoordinate != 1 || yCoordinate != 1) && (xCoordinate != 24 || yCoordinate != 24))
        {
            monsterX[i] = xCoordinate;
            monstersY[i] = yCoordinate;
        }
    }
}

void generateMaze(int includeMonsters)
{
    int offsetX = 55; // Horizontal offset to center the maze
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
                printf("\033[1;33m%c <FINISH>\033[0m", END_POSITION); // Display finish point
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
void displayInstructions()
{
    system("cls");
    printf("\033[1;34m");
    setCoordinates(50, 5);
    printf("+----------------------------------------------------+\n");
    setCoordinates(50, 6);
    printf("|                    INSTRUCTIONS                    |\n");
    setCoordinates(50, 7);
    printf("|                    W: Up                           |\n");
    setCoordinates(50, 8);
    printf("|                    S: Down                         |\n");
    setCoordinates(50, 9);
    printf("|                    A: Left                         |\n");
    setCoordinates(50, 10);
    printf("|                    D: Right                        |\n");
    setCoordinates(50, 11);
    printf("+----------------------------------------------------+\n");
    printf("\033[0m");

    setCoordinates(64, 14);
    printf("\033[1;31mPRESS ANY KEY TO CONTINUE\033[0m");
    getch();
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
    printf("\033[1;33mLeo:\033[0m Of course, it couldn't be as simple as just walking up to the artifact.");
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
    int d;
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
    printf("\033[1;33mLeo:\033[0m (1. Well, I'm not just anyone; I'm built different / 2. Yeah, I got lucky) 1/2):  ");
    scanf("%d", &d);

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
    printf("\033[1;35mMysterious Figure:\033[0m But I have to make sure that you are worthty of it, are you?\n");
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
void level1()
{
    resetConditions();
    system("cls");
    level1Intro();
    system("cls");
    setCoordinates(74, 2);
    printf("\033[1;33mThe Vortex Vault\033[0m");
    generateMaze(0);

    char input;
    while (1)
    {
        input = getch();
        if (tolower(input) == 'q')
        {
            exit(0);
            exit(0);
        }
        movePlayer(input, 0);
        if (playerX == endPointX && playerY == endPointY)
        {
            level1Outro();
            return;
        }
    }
}

void level2Intro()
{
    system("cls");

    setCoordinates(36, 10);
    printf("\033[1;34m*Leo's journey continues as he ventures deeper into Krypton*\033[0m\n");
    getch();

    setCoordinates(36, 12);
    printf("\033[1;33mLeo:\033[0m These mountains feel like they are closing in. I need to hurry...\n");
    getch();

    setCoordinates(36, 14);
    printf("\033[1;34m*Suddenly, a voice echoes through the valley*\033[0m\n");
    getch();

    setCoordinates(36, 16);
    printf("\033[1;37mVoice:\033[0m Leo... is that you?\n");
    getch();

    setCoordinates(36, 18);
    printf("\033[1;33mLeo:\033[0m Who's there? Who are you?\n");
    getch();

    setCoordinates(36, 20);
    printf("\033[1;37mVoice:\033[0m It's me... Kaden. Your old mentor... You don't remember me?\n");
    getch();

    setCoordinates(36, 22);
    printf("\033[1;33mLeo:\033[0m Kaden...? How... how is this possible?\n");
    getch();

    setCoordinates(36, 24);
    printf("\033[1;37mKaden:\033[0m I was sent here years ago. The Solum Sphere... it trapped me here. I can help you... but only if you help me escape.\n");
    getch();

    setCoordinates(36, 26);
    printf("\033[1;33mLeo:\033[0m What do I need to do?\n");
    getch();

    setCoordinates(36, 28);
    printf("\033[1;37mKaden:\033[0m Trust me, Leo. But beware, the next level is filled with monsters that feed on fear. \n");
    getch();

    setCoordinates(36, 30);
    printf("They can sense your fear, and it makes them stronger. They won't just kill you; they can take everything from you.\n");
    getch();

    setCoordinates(36, 32);
    printf("\033[1;33mLeo:\033[0m I won’t give in to fear!\n");
    getch();

    setCoordinates(36, 34);
    printf("\033[1;37mKaden:\033[0m Stay strong, Leo. If you solve the puzzle ahead, you can free me. Let's finish this, once and for all.\n");
    getch();

    setCoordinates(64, 36);
    printf("\033[1;31mPRESS ANY KEY TO PROCEED\033[0m");
    getch();
    system("cls");
}

void level2Outro()
{
    system("cls");

    setCoordinates(36, 12);
    printf("\033[1;33mLeo:\033[0m I can't believe I made it through those monsters...\n");
    getch();

    setCoordinates(36, 14);
    printf("\033[1;35mKaden:\033[0m You did well, Leo. But we must stay alert. Only one level remains.\n");
    getch();

    setCoordinates(36, 16);
    printf("\033[1;33mLeo:\033[0m What happens in the last level?\n");
    getch();

    setCoordinates(36, 18);
    printf("\033[1;35mKaden:\033[0m The Solum Sphere is waiting for us there. I am trapped, but if you can reach it, we can finally go home and save Earth.\n");
    getch();

    setCoordinates(36, 20);
    printf("\033[1;33mLeo:\033[0m I won't let you down, Kaden.\n");
    getch();

    setCoordinates(36, 22);
    printf("\033[1;35mKaden:\033[0m Then let's finish this, once and for all.\n");
    getch();

    setCoordinates(64, 24);
    printf("\033[1;31mPRESS ANY KEY TO CONTINUE TO THE NEXT LEVEL\033[0m");
    getch();
    system("cls");
}

void level2()
{
    resetConditions();
    level2Intro();
    system("cls");
    setCoordinates(74, 2);
    printf("\033[1;33mTHE SHADOW MAZE\033[0m");
    generateMaze(1);

    char input;
    while (1)
    {
        input = getch();
        if (tolower(input) == 'q')     // press q to abort the game means exit the game
            if (tolower(input) == 'q') // press q to abort the game means exit the game
            {
                exit(0);
            }
        int checkMonster = movePlayer(input, 1);

        if (checkMonster)
        {
            system("cls");
            setCoordinates(36, 14);
            printf("You have been killed by the monster");

            if (hasTimeWatch && lives > 0)
            {
                setCoordinates(36, 16);
                printf("TimeWatch - remaining charges: %d.", lives);
                setCoordinates(36, 18);

                char choice;
                do
                {
                    setCoordinates(36, 20);
                    printf("Press q to abort your mission\n");
                    setCoordinates(36, 21);
                    printf("Do you want to use the TimeWatch [y/n]: ");
                    scanf(" %c", &choice);
                    if (tolower(choice) == 'q')
                    {
                        return; // Abort mission if 'q' is pressed
                    }
                } while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

                if (tolower(choice) == 'y')
                {
                    lives--;  // Decrement lives when using TimeWatch
                    level2(); // Restart level
                    return;   // Exit current level execution
                }
            }
            else
            {
                break;
            }
        }

        if (playerX == endPointX && playerY == endPointY)
        {
            level2Outro();
            system("cls");
            break;
        }
    }
}
int timerExpired = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for thread safety

void *timerFunction(void *arg)
{
    int timeLeft = 40; // Set the timer duration

    while (timeLeft > 0 && !timerExpired)
    {
        while (timeLeft > 0 && !timerExpired)
        {
            Sleep(1000); // Wait for 1 second
            timeLeft--;

            // Print the timer at a fixed position without affecting the maze
            pthread_mutex_lock(&mutex);
            setCoordinates(2, 2);                                          // Choose a position away from the maze
            setCoordinates(2, 2);                                          // Choose a position away from the maze
            printf("\033[1;31mTime Left: %d seconds   \033[0m", timeLeft); // Print timer with padding
            fflush(stdout);
            pthread_mutex_unlock(&mutex);

            if (timeLeft == 0)
            {
                if (timeLeft == 0)
                {
                    timerExpired = 1;
                    pthread_mutex_lock(&mutex);
                    setCoordinates(36, 14);
                    printf("\n\033[1;31mTime's up! You failed to complete the maze.\033[0m");
                    fflush(stdout);
                    pthread_mutex_unlock(&mutex);
                    return NULL;
                }
            }
            return NULL;
        }
    }
}

void level3()
{
    pthread_t timerThread;

    // Create the timer thread
    pthread_create(&timerThread, NULL, timerFunction, NULL);

    resetConditions();
    system("cls");
    setCoordinates(74, 2);
    printf("\033[1;33mTHE SHADOW MAZE - Level 3\033[0m");
    generateMaze(2);

    char input;
    while (!timerExpired)
    {
        input = getch();
        if (tolower(input) == 'q')
        {
            if (tolower(input) == 'q')
            {
                timerExpired = 1;
                exit(0);
            }

            // Locking mutex for safe player movement
            pthread_mutex_lock(&mutex);
            int checkMonster = movePlayer(input, 2);
            pthread_mutex_unlock(&mutex);

            if (checkMonster)
            {
                system("cls");
                setCoordinates(36, 14);
                printf("You have been killed by the monster, Better luck Next Time ");
                exit(0);
                if (playerX == endPointX && playerY == endPointY)
                {
                    timerExpired = 1; // Stop the timer
                    system("cls");
                    break;
                }
            }
            if (playerX == endPointX && playerY == endPointY)
            {
                timerExpired = 1; // Stop the timer
                system("cls");
                break;
            }
        }

        // pthread_join(timerThread, NULL); // Wait for the timer thread to finish
    }
}

int main()
{
    // ShellExecute(NULL, "open", "setup.bat", NULL, NULL, SW_MINIMIZE);
    // heading();
    // system("cls");
    // introduction();
    // system("cls");
    // Sleep(500);
    // displayInstructions();
    // level1();
    // system("cls");
    // Sleep(500);
    // level2();
    // system("cls");
    level3();
    return 0;
}
