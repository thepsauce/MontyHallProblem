#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Statistically proving that you have a higher chance of winning when you switch the door!
//
// What the following program reveals is that your chances are ~33% of winning when not switching
// AND twice as high ~66% when switching!

int main(void)
{
    int rnd;
    int i;
    const int sampleSize = 100000000;
    int cntKr = 0;
    int cntKw = 0;
    int cntSr = 0;
    int cntSw = 0;
    _Bool switched;

    int door;
    int validDoor;
    int invalidDoor;
    // picking a seed based on the system time
    srand(time(NULL));

    for(i = 0; i < sampleSize; i++)
    {
        rnd = rand();
        if(rnd < RAND_MAX / 3)
            validDoor = 1;
        else if(rnd < RAND_MAX * 2 / 3)
            validDoor = 2;
        else
            validDoor = 3;

        rnd = rand();
        if(rnd < RAND_MAX / 3)
            door = 1;
        else if(rnd < RAND_MAX * 2 / 3)
            door = 2;
        else
            door = 3;
        //printf("Chose door: %d\n", door);
        //getc(stdin);
        // determine a door to reveal
        switch((door << 4) | (validDoor))
        {
        case (1 << 4) | 2:
        case (2 << 4) | 1:
            invalidDoor = 3;
            break;
        case (3 << 4) | 2:
        case (2 << 4) | 3:
            invalidDoor = 1;
            break;
        case (3 << 4) | 1:
        case (1 << 4) | 3:
            invalidDoor = 2;
            break;
        case (1 << 4) | 1:
            invalidDoor =  2 + rand() % 2;
            break;
        case (2 << 4) | 2:
            invalidDoor =  1 + (rand() % 2) * 2;
            break;
        case (3 << 4) | 3:
            invalidDoor = 1 + rand() % 2;
            break;
        }
        //printf("Door number %d is invalid\n", invalidDoor);
        //printf("Keep or switch?\n");
        // pick a random option (keep or switch)
        rnd = rand();
        switched = rnd % 2 != 0;
        if(!switched)
            ;//printf("Keeping\n");
        else
        {
            //printf("Switching\n");
            door = 6 - (invalidDoor + door);
        }
        // checking result and incrementing respective counter
        if(door == validDoor)
        {
            //printf("Picked the right one! Nice!\n");
            //getc(stdin);
            if(switched)
                cntSr++;
            else
                cntKr++;
        }
        else
        {
            //printf("Picked the wrong one! Bad!\n");
            //getc(stdin);
            if(switched)
                cntSw++;
            else
                cntKw++;
        }

    }
    printf("Results:\n");
    printf("  %d samples were examined where each sample represents one \"Monty Hall cycle\"\n", sampleSize);
    printf("+-------+----------+-----------+\n");
    printf("|       | Switched |    Kept   |\n");
    printf("+-------+----------+-----------+\n");
    printf("| Wrong | %8d | %8d  |\n", cntSw, cntKw);
    printf("| Right | %8d | %8d  |\n", cntSr, cntKr);
    printf("+-------+----------+-----------+\n");
    return 0;
}
