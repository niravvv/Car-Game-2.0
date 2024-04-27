#include <stdio.h> /*Although this program does not require I/O, game.h will not compile when this is not present*/
#include "player.h"
#include "game.h"

/* Note: This game does not support the jumping feature as it was not included in the
 * assignment outline. If the player and car are next to each other and the appropriate
 * key is pressed, the player will lose. */

void w(char** map, char** blankMap, int rows, int cols, int* game, int** carPos)
{
    int i,j;
    int condition = FALSE;
    for(i=0; i<rows+1; i++)
    {
        for(j=0; j<cols+1; j++)
        {
            if(map[i][j] == 'P' && condition == FALSE && map[i-1][j] !='*')
            {
                if(carPos[0][0] == i-1 && carPos[0][1] == j)
                {
                    *game = 2;
                    map[i-1][j] = 'P';
                    map[i][j] = blankMap[i][j];
                }
                else
                {
                    if(map[i-1][j] == 'G')
                    {
                        *game = 3;
                    }
                    map[i-1][j] = 'P';
                    map[i][j] = blankMap[i][j];
                }

                condition = TRUE;
            }
        }
    }
}
/* Causes the player to move one space up and replaces the old position with the appropriate char. */

void s(char** map, char** blankMap, int rows, int cols, int* game, int** carPos)
{
    int i,j;
    int condition = FALSE;
    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols+1; j++)
        {
            if(map[i][j] == 'P' && condition == FALSE && map[i+1][j] != '*')
            {
                if(carPos[0][0] == i+1 && carPos[0][1] == j)
                {
                    *game = 2;
                    map[i+1][j] = 'P';
                    map[i][j] = blankMap[i][j];
                }
                else
                {
                    if(map[i+1][j] == 'G')
                    {
                        *game = 3;
                    }
                    map[i+1][j]='P';
                    map[i][j] = blankMap[i][j];
                }

                condition = TRUE;
            }
        }
    }
}
/* Causes the player to move one space down and replaces the old position with the appropriate char. */

void d(char** map, char** blankMap, int rows, int cols, int* game, int** carPos)
{
    int i,j;
    int condition = FALSE;
    for(i=0; i<rows+1; i++)
    {
        for(j=0; j<cols+1; j++)
        {
            if(map[i][j] == 'P' && condition == FALSE && map[i][j+1] !='*')
            {
                if(carPos[0][1] == j+1 && carPos[0][0] == i)
                {
                    *game = 2;
                    map[i][j+1]='P';
                    map[i][j] = blankMap[i][j];
                }
                else
                {
                    if(map[i][j+1] == 'G')
                    {
                        *game = 3;
                    }
                    map[i][j+1]='P';
                    map[i][j] = blankMap[i][j];
                }

                condition = TRUE;
            }
        }
    }
}
/* Causes the player to move one space right and replaces the old position with the appropriate char. */

void a(char** map, char** blankMap, int rows, int cols, int* game, int** carPos)
{
    int i,j;
    int condition = FALSE;
    for(i=0; i<rows+1; i++)
    {
        for(j=0; j<cols+1; j++)
        {
            if(map[i][j] == 'P' && condition == FALSE && map[i][j-1] !='*')
            {

                if(carPos[0][1] == j-1 && carPos[0][0] == i)
                {
                    *game = 2;
                    map[i][j-1]='P';
                    map[i][j] = blankMap[i][j];
                }
                else
                {
                    if(map[i][j-1] == 'G')
                    {
                        *game = 3;
                    }
                    map[i][j-1]='P';
                    map[i][j] = blankMap[i][j];
                }

                condition = TRUE;
            }
        }
    }

}
/* Causes the player to move one space left and replaces the old position with the appropriate char. */


