#ifndef GAME_H
#define GAME_H

    typedef struct Node {
        void** data;
        struct Node* prev;
        struct Node* next;
    } Node;
    /* void** was used, instead of void*, for data because it integrated easier with the way the code was written.
     * In this linked list, the struct consists of past versions of the map, not the positions of the car and player.
     * This is also a doubly linked list, which makes it easier to enter data at the end. */


    Node* initializeList(void);
    Node* insertMove(Node* head, void* d, int rows, int cols);
    void freeList(Node* head, int rows);
    Node* deleteLastMove(Node* head, Node* nodeToDelete, int rows);

    char** makeMap(FILE *mapFile, int *rows, int *cols, int **carPos);
    char** makeBlankMap(char** map, int *rows, int* cols);
    void printMap(char** map, int *rows, int *cols);
    int moveConditions(int rows, int cols, int game, char** map, char** blankMap, char move, int condition, int** carPos, Node* list, Node* lastNode);
    void gameCondition(int rows, int cols, int* gamePtr, char** map);

    #define PLAYING 0
    #define EXIT 1
    #define LOSE 2
    #define WIN 3
    /* The game int denotes the current state of the game, using definitions, the code becomes more understandable. */

    #define FALSE 0
    #define TRUE 1
    /* The condition int denotes if a particular change has taken place in the 2d array. Once the condition has been fulfilled,
      it becomes TRUE to prevent unnecessary looping from occurring. */


#endif
