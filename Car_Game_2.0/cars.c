#include <stdio.h>
#include "cars.h"
#include "game.h"

void carMove(char** map, int rows, int cols, int** carPos)
{
    int i, j;
    int Xcondition, Ycondition;
    /* Two conditions required for the X and Y directions to accommodate for all directions of
     * car movement. */

    Ycondition = FALSE;
    for (i = 0; i < rows + 2; i++)
    {
        Xcondition = FALSE;
        for (j = 0; j < cols + 2; j++)
        {
            /* if > */
            if(map[i][j] == '>' && Xcondition == FALSE && map[i][j+1] == '.')
            {
                map[i][j + 1] = '>';
                map[i][j]='.';
                Xcondition = TRUE;
            }
            else if(map[i][j] == '>' && Xcondition == FALSE && map[i][j+1] == ' ')
            {
                if(map[i+1][j] == '.')
                {
                    map[i+1][j] = 'v';
                    map[i][j]='.';
                    Xcondition = TRUE;
                    Ycondition = TRUE;
                    /* Ycondition needs to be true otherwise it moves an extra step when it turns*/
                }
                else if (map[i-1][j] == '.')
                {
                    map[i-1][j] = '^';
                    map[i][j]='.';
                    Xcondition = TRUE;
                }
            }

            /* if v */
            else if(map[i][j] == 'v' && Ycondition == FALSE && map[i+1][j] == '.')
            {
                map[i+1][j] = 'v';
                map[i][j]='.';
                Ycondition = TRUE;
            }
            else if (map[i][j] == 'v' && Ycondition == FALSE && map[i+1][j] == ' ')
            {
                if(map[i][j+1] == '.')
                {
                    map[i][j+1] = '>';
                    map[i][j]='.';
                    Ycondition = TRUE;
                    Xcondition = TRUE;
                }
                else if (map[i][j-1] == '.')
                {
                    map[i][j-1] = '<';
                    map[i][j]='.';
                    Ycondition = TRUE;
                    Xcondition = TRUE;
                }
            }

            /* if ^ */
            else if(map[i][j] == '^' && Ycondition == FALSE && map[i-1][j] == '.')
            {
                map[i-1][j] = '^';
                map[i][j]='.';
                Ycondition = TRUE;
            }
            else if (map[i][j] == '^' && Ycondition == FALSE && map[i-1][j] == ' ')
            {
                if(map[i][j+1] == '.')
                {
                    map[i][j+1] = '>';
                    map[i][j]='.';
                    Ycondition = TRUE;
                    Xcondition = TRUE;
                }
                else if (map[i][j-1] == '.')
                {
                    map[i][j-1] = '<';
                    map[i][j]='.';
                    Ycondition = TRUE;
                    Xcondition = TRUE;
                }
            }

            /* if < */
            if(map[i][j] == '<' && Xcondition == FALSE && map[i][j-1] == '.')
            {
                map[i][j - 1] = '<';
                map[i][j]='.';
                Xcondition = TRUE;
            }
            else if(map[i][j] == '<' && Xcondition == FALSE && map[i][j-1] == ' ')
            {
                if(map[i+1][j] == '.')
                {
                    map[i+1][j] = 'v';
                    map[i][j]='.';
                    Xcondition = TRUE;
                    Ycondition = TRUE;
                }
                else if (map[i-1][j] == '.')
                {
                    map[i-1][j] = '^';
                    map[i][j]='.';
                    Xcondition = TRUE;
                }
            }
        }
    }

    for (i = 0; i < rows + 2; i++)
    {
        for (j = 0; j < cols + 2; j++) {
            if (map[i][j] == '>' || map[i][j] == '<' || map[i][j] == 'v' || map[i][j] == '^')
            {
                (*carPos)[0] = i;
                (*carPos)[1] = j;
            }
        }
    }
    /* Sets the carPos pointer. */

}
/* Causes all cars to move one space. */
