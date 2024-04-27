/* Nirav Pathania
 * 21497502
 * COMP1000 - UCP Assignment Two
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"
#include "player.h"
#include "cars.h"
#include "game.h"
/* import all necessary files for the program. */

int main(int argc, char* argv[])
{
    int rows = 0;
    int cols = 0;
    int i;
    int condition = FALSE;
    char move;
    char** map = NULL;
    char** blankMap = NULL;
    int game = PLAYING;
    int* gamePtr;
    FILE *mapFile;
    int *carPos = NULL;

    Node * list = initializeList();
    Node * lastNode = list;
    /*creates the linked list for the undo and sets the
     * last node to be accessed easily. */

    if (argc != 2)
    {
        printf("Invalid command line argument.\n"
               "Entered: %s \n"
               "Required: <rows> <columns>\n", argv[0]);
    }
        /* Requires proper command line argument for the program to run. */
    else
    {
        mapFile = fopen(argv[1], "r");
        map = makeMap(mapFile, &rows, &cols, &carPos);
        blankMap = makeBlankMap(map, &rows, &cols);
        list = insertMove(list, (void*)map, rows, cols);

        /* Creates the map and node for the linked list. */
    }

    printMap(map, &rows, &cols);

    do
    {
        condition = FALSE;

        disableBuffer();
        scanf(" %c", &move);
        enableBuffer();

        game = moveConditions(rows, cols, game, map, blankMap, move, condition, &carPos, list, lastNode);

        gamePtr = &game;
        /* Takes the pointer from player.c */

        gameCondition(rows, cols, gamePtr, map);

    } while (game == PLAYING);
    /* This function is responsible for the gameplay. */

    /* Free the allocated memories. */
    for (i = 0; i < rows + 2; i++)
    {
        free(map[i]);
    }
    free(map);

    for (i = 0; i < rows + 2; i++)
    {
        free(blankMap[i]);
    }
    free(blankMap);

    free(carPos);

    freeList(list, rows);

    return 0;
}
/* Main function that takes command line input and reads the user input. It calls to other functions. */

Node* initializeList(void)
{
    return NULL;
}
/* Initialises the linked list. */

Node* insertMove(Node* head, void* d, int rows, int cols)
{
    Node* current;
    int i;
    Node* newNode = (Node*)malloc(sizeof(Node));
    /* Malloc the node. */
    char** prevMap = (char**)d;

    newNode->data = (void**)malloc((rows + 2) * sizeof(char*));
    for (i = 0; i < rows + 2; i++)
    {
        newNode->data[i] = (void*)malloc((cols + 2) * sizeof(char));
        strncpy(newNode->data[i], prevMap[i], cols+2);
    }
    /* Malloc the data and copy from the map. strncpy needs to be used as assigning values with
     * a loop results in issues with types. */

    newNode->next = NULL;

    if (head != NULL)
    {
        current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = newNode;
        newNode->prev = current;
    }
    /* Sets the node to point to the previous and next nodes. */

    return newNode;
}
/* Adds a node to the end of the linked list. */


Node* deleteLastMove(Node* head, Node* nodeToDelete, int rows)
{
    int i;

    nodeToDelete->prev->next = nodeToDelete->next;

    for ( i = 0; i < rows + 2; i++)
    {
        free(nodeToDelete->data[i]);
    }
    free(nodeToDelete->data);
    free(nodeToDelete);

    return head;
}
/* Deletes the last node of the linked list.*/

int moveConditions(int rows, int cols, int game, char** map, char** blankMap, char move, int condition, int** carPos, Node* list, Node* lastNode)
{
    int i, j;
    char** prevMap; /* Previous version of the map. */

    switch (move)
    {
        case 'e':
            game = 1;
            break;
        case 'u':
            lastNode = list;
            while (lastNode->next != NULL)
            {
                lastNode = lastNode->next;
            }
            prevMap = (char**)lastNode->data;
            for (i = 0; i < rows + 2; i++)
            {
                for (j = 0; j < cols + 2; j++)
                {
                    if (lastNode->data != NULL)
                    {
                        map[i][j] = prevMap[i][j];
                    }
                }
            }
            /* Uses the previous version of the map from the linked list to
             * assign values to the new map. */

            if(list->next != NULL)
            {
                list = deleteLastMove(list, lastNode, rows);
            }
            /* Checks to see if there is a node to delete, then deletes it.
             * If statement avoids segmentation fault from deleting the first node. */
            break;
        case 'w':
            for (i = 0; i < rows + 2; i++)
            {
                for (j = 0; j < cols + 2; j++)
                {
                    if(map[i][j] == 'P')
                    {
                        if(map[i-1][j] != '*' && condition == FALSE)
                        {
                            list = insertMove(list, map, rows, cols);
                            if (carPos[0][0] != i-1 && carPos[0][0] != i-2)
                            {
                                w(map, blankMap, rows, cols, &game, carPos);
                                carMove(map, rows, cols, carPos);
                                condition = TRUE;
                            }
                            else
                            {
                                carMove(map, rows, cols, carPos);
                                w(map, blankMap, rows, cols, &game, carPos);
                                condition = TRUE;
                            }
                        }
                    }
                }

            }
            break;
        case 's':
            for (i = 0; i < rows + 2; i++)
            {
                for (j = 0; j < cols + 2; j++)
                {
                    if (condition == 0)
                    {
                        if(map[i][j] == 'P')
                        {
                            if(map[i + 1][j] != '*')
                            {
                                list = insertMove(list, map, rows, cols);
                                if (carPos[0][0] != i+1 && carPos[0][0] != i+2)
                                {
                                    s(map, blankMap, rows, cols, &game, carPos);
                                    carMove(map, rows, cols, carPos);
                                    condition = TRUE;
                                }
                                else
                                {
                                    carMove(map, rows, cols, carPos);
                                    s(map, blankMap, rows, cols, &game, carPos);
                                    condition = TRUE;
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 'd':
            for (i = 0; i < rows + 2; i++)
            {
                for (j = 0; j < cols + 2; j++)
                {
                    if(map[i][j+1] != '*')
                    {
                        if (map[i][j] == 'P' && carPos[0][1] != j+1 && carPos[0][1] != j+2 && condition == FALSE)
                        {
                            list = insertMove(list, map, rows, cols);
                            d(map, blankMap, rows, cols, &game, carPos);
                            carMove(map, rows, cols, carPos);
                            condition = TRUE;
                        }
                        else if (map[i][j] == 'P' && condition == FALSE)
                        {
                            list = insertMove(list, map, rows, cols);
                            carMove(map, rows, cols, carPos);
                            d(map, blankMap, rows, cols, &game, carPos);
                            condition = TRUE;
                        }
                    }
                }
            }
            break;
        case 'a':
            for (i = 0; i < rows + 2; i++)
            {
                for (j = 0; j < cols + 2; j++)
                {
                    if(map[i][j-1] != '*')
                    {
                        if (map[i][j] == 'P' && carPos[0][1] != j-1 && carPos[0][1] != j-2 && condition == FALSE)
                        {
                            list = insertMove(list, map, rows, cols);
                            a(map, blankMap, rows, cols, &game, carPos);
                            carMove(map, rows, cols, carPos);
                            condition = TRUE;
                        }
                        else if (map[i][j] == 'P' && condition == FALSE)
                        {
                            list = insertMove(list, map, rows, cols);
                            carMove(map, rows, cols, carPos);
                            a(map, blankMap, rows, cols, &game, carPos);
                            condition = TRUE;
                        }
                    }
                }
            }
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
    }
    return game;
}
/* A few conditions need to be checked before the move can be executed.
 * This includes checking where the player and car. This stops bugs from
 * happening, such as the player going on top of the car and deleting it
 * from the game. It is also responsible for the undo. */

void gameCondition(int rows, int cols, int* gamePtr, char** map)
{
    printMap(map, &rows, &cols);

    if(*gamePtr == EXIT)
    {
        printf("You exited.\n");
        /* Used exit during testing to end the game quickly. */
    }
    else if (*gamePtr == LOSE)
    {
        printf("You lose.\n");
    }
    else if (*gamePtr == WIN)
    {
        printf("You win.\n");
    }
}
/* Used to call the printMap function, and it checks whether the game has ended,
 * the player has lost or the player has won. */

char** makeMap(FILE *mapFile, int *rows, int *cols, int **carPos)
{
    char **map = NULL;
    int i, j;

    if (mapFile == NULL)
    {
        printf("Error opening file.\n");
    }
    else
    {
        fscanf(mapFile, "%d %d", rows, cols);

        map = (char **)malloc((*rows + 2) * sizeof(char *));

        for (i = 0; i < *rows + 2; i++)
        {
            map[i] = (char *)malloc((*cols + 2) * sizeof(char));
        }
        /* mallocs the 2D array based on the 2 integers at the top of the page. */

        *carPos = (int *)malloc(2 * sizeof(int));
        /* mallocs the array for the car position. */

        for (i = 0; i < *rows; i++)
        {
            for (j = 0; j < *cols; j++)
            {
                fscanf(mapFile, " %c", &map[i + 1][j + 1]);

                if (map[i + 1][j + 1] == '0')
                {
                    map[i + 1][j + 1] = ' ';
                }
                else if (map[i + 1][j + 1] == '1')
                {
                    map[i + 1][j + 1] = '.';
                }
                else if (map[i + 1][j + 1] == '2')
                {
                    map[i + 1][j + 1] = '>';
                    (*carPos)[0] = i + 1;
                    (*carPos)[1] = j + 1;
                }
                else if (map[i + 1][j + 1] == '3')
                {
                    map[i + 1][j + 1] = 'P';
                }
                else if (map[i + 1][j + 1] == '4')
                {
                    map[i + 1][j + 1] = 'G';
                }
                else
                {
                    printf("Unknown character.\n");
                }
            }
        }
        /* Replaces the values of the text file with the corresponding
         * game sprite. */

        fclose(mapFile);

        for (j = 0; j < *cols + 2; j++)
        {
            map[0][j] = '*';
            map[*rows + 1][j] = '*';
        }
        for (i = 0; i < *rows + 2; i++)
        {
            map[i][0] = '*';
            map[i][*cols + 1] = '*';
        }

        /* Adds border around the map. */
    }

    return map;
}

/* Creates the map based on the text file with malloc and randomly sets the car positions and direction */

char** makeBlankMap(char** map, int *rows, int* cols)
{
    int i, j;
    char** blankMap = NULL;

    blankMap = (char **)malloc((*rows + 2) * sizeof(char *));

    for (i = 0; i < *rows + 2; i++)
    {
        blankMap[i] = (char *)malloc((*cols + 2) * sizeof(char));
    }

    for (i = 0; i < *rows + 2; i++)
    {
        for (j = 0; j < *cols + 2; j++)
        {
            if(map[i][j] == 'P' || map[i][j] == 'G')
            {
                blankMap[i][j] = ' ';
            }
            else if(map[i][j] == '>')
            {
                blankMap[i][j] = '.';
            }
            else
            {
                blankMap[i][j] = map[i][j];
            }
        }
    }

    return blankMap;
}


void freeList(Node* head, int rows)
{
    int i;
    while (head != NULL)
    {
        Node* temp = head;
        head = head->next;
        for ( i = 0; i < rows+2; i++)
        {
            free(temp->data[i]);
        }
        free(temp->data);
        free(temp);
    }
}
/* Frees the linked list when called */

void printMap(char** map, int* rows, int* cols)
{
    int i, j;

    system("clear");

    for (i = 0; i < *rows + 2; i++)
    {
        for (j = 0; j < *cols + 2; j++)
        {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }

    printf("Press w to move up\n"
           "Press s to move down\n"
           "Press a to move left\n"
           "Press d to move right\n"
           "Press u to undo\n"
           "Press e to exit\n");
}

/* Prints map when called. */
