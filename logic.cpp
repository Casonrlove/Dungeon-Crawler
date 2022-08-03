#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char **loadLevel(const string &fileName, int &maxRow, int &maxCol, Player &player)
{

    bool hasexit = false, hasdoor = false;
    char hold;
    ifstream filestream;

    //----------open file----------
    filestream.open(fileName);
    if (!filestream.is_open())
    {
        return nullptr;
    }

    //---------------condition checks---------------
    filestream >> maxRow;
    if (filestream.fail() || maxRow <= 0)
    {
        cout << "bad 1";
        return nullptr;
    }
    filestream >> maxCol;
    if (filestream.fail() || maxCol <= 0)
    {
        cout << "bad 2";
        return nullptr;
    }
    filestream >> player.row;
    if (filestream.fail() || player.row < 0 || player.row >= maxRow)
    {
        cout << "bad 3";
        return nullptr;
    }
    filestream >> player.col;
    if (filestream.fail() || player.col < 0 || player.col >= maxCol)
    {
        cout << "bad 4";
        return nullptr;
    }

    //----------checking for tile > INT_32MAX
    if (maxRow >= (INT32_MAX / maxCol))
    {
        cout << "bad 5";
        return nullptr;
    }

    //----------create map----------
    char **map = createMap(maxRow, maxCol);

    //----------check and put in characters----------
    for (int row = 0; row < maxRow; row++)
    {
        for (int col = 0; col < maxCol; col++)
        {
            filestream >> hold;
            if (filestream.fail() || player.row < 0)
            {
                cout << "bad 6";
            }
            if (hold == TILE_TREASURE)
            {
                map[row][col] = TILE_TREASURE;
            }
            else if (hold == TILE_AMULET)
            {
                map[row][col] = TILE_AMULET;
            }
            else if (hold == TILE_MONSTER)
            {
                map[row][col] = TILE_MONSTER;
            }
            else if (hold == TILE_PILLAR)
            {
                map[row][col] = TILE_PILLAR;
            }
            else if (hold == TILE_DOOR)
            {
                map[row][col] = TILE_DOOR;
                hasdoor = true;
            }
            else if (hold == TILE_EXIT)
            {
                map[row][col] = TILE_EXIT;
                hasexit = true;
            }
            else if (hold == TILE_OPEN)
            {
                map[row][col] = TILE_OPEN;
            }
            else
            {
                // check for any character other than allowed
                cout << "bad 7";
                return nullptr;
            }
        }
    }

    //----------check to see if extra thing in file----------
    filestream >> hold;
    if (!filestream.fail())
    {
        cout << "bad 8";
        return nullptr;
    }

    //----------check for whay out----------
    if (!hasdoor && !hasexit)
    {
        cout << "bad 9";
        return nullptr;
    }

    map[player.row][player.col] = TILE_PLAYER;
    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int &nextRow, int &nextCol)
{
    if (input == 'q')
    {
        return;
    }
    else if (input == 'w')
    {
        nextRow--;
    }
    else if (input == 'a')
    {
        nextCol--;
    }
    else if (input == 'd')
    {
        nextCol++;
    }
    else if (input == 's')
    {
        nextRow++;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char **createMap(int maxRow, int maxCol)
{

    char **map = new char *[maxRow]; //fill is all dashes

    for (int row = 0; row < maxRow; row++)
    {
        map[row] = new char[maxCol];
    }

    for (int row = 0; row < maxRow; row++)
    {
        for (int col = 0; col < maxCol; col++)
        {
            map[row][col] = TILE_OPEN;
        }
    }

    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char **&map, int &maxRow)
{
    if (map == nullptr)
    {
        maxRow = 0;
        return;
    }
    for (int row = 0; row < maxRow; row++)
    {
        delete[] map[row];
    }
    delete[] map;
    map = nullptr;
    maxRow = 0;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char **resizeMap(char **map, int &maxRow, int &maxCol)
{
    //check for maxRow/maxCol <= 0;
    //if map is null return nullptr;

    if ((maxRow <= 0) || maxCol <= 0)
    {
        cout << "bad4b";
        return nullptr;
    }
    if (map == nullptr)
    {
        // maxRow *= 2;
        // maxCol *= 2;
        cout << "bad4c";
        return nullptr;
    }

    //----------checking for tile > INT_32MAX----------
    if ((2 * maxRow) >= (INT32_MAX / (2 * maxCol)))
    {
        cout << "bad 5";
        return nullptr;
    }

    int maxrowhold = maxRow;
    //---------------------CREATE NEW MAP-------------------------
    char **newmap = new char *[2 * maxRow]; //fill is all dashes
    for (int row = 0; row < (2 * maxRow); row++)
    {
        newmap[row] = new char[2 * maxCol];
    }

    //-------------------TRANSFER OLD TO NEW MAP-------------------

    //-----------transfer to old to new----------
    for (int row = 0; row < maxRow; row++)
    {
        for (int col = 0; col < maxCol; col++)
        {
            // if(map[row][col] == TILE_PLAYER)
            // {
            //     newmap[row][col] = TILE_OPEN;
            //     continue;
            // }
            newmap[row][col] = map[row][col];
        }
    }
    //----------transfer to right----------
    for (int row = 0; row < maxRow; row++)
    {
        for (int col = 0; col < maxCol; col++)
        {
            if (map[row][col] == TILE_PLAYER)
            {
                newmap[row][col + maxCol] = TILE_OPEN;
                continue;
            }
            newmap[row][col + maxCol] = map[row][col];
        }
    }
    //----------transfer to bottom----------
    for (int row = 0; row < maxRow; row++)
    {
        for (int col = 0; col < maxCol; col++)
        {
            if (map[row][col] == TILE_PLAYER)
            {
                newmap[row + maxRow][col] = TILE_OPEN;
                continue;
            }
            newmap[row + maxRow][col] = map[row][col];
        }
    }
    //----------transfer to diagonal----------
    for (int row = 0; row < maxRow; row++)
    {
        for (int col = 0; col < maxCol; col++)
        {
            if (map[row][col] == TILE_PLAYER)
            {
                newmap[row + maxRow][col + maxCol] = TILE_OPEN;
                continue;
            }
            newmap[row + maxRow][col + maxCol] = map[row][col];
        }
    }
    deleteMap(map, maxRow);

    maxRow = 2 * maxrowhold;
    maxCol *= 2;
    return newmap;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char **map, int maxRow, int maxCol, Player &player, int nextRow, int nextCol)
{

    //-------------------STEP OFF MAP-------------------
    if ((nextRow >= maxRow) || (nextCol >= maxCol) || (nextRow < 0) || (nextCol < 0))
    {
        //-----DOESN'T MOVE-----
        return STATUS_STAY; //return status
    }

    //-------------------MONSTER TILE-------------------
    if (map[nextRow][nextCol] == TILE_MONSTER)
    {
        //-----DOESN'T MOVE-----
        return STATUS_STAY; //return status
    }
    //-------------------PILLAR TILE-------------------
    else if (map[nextRow][nextCol] == TILE_PILLAR)
    {
        //-----DOESN'T MOVE-----
        return STATUS_STAY;
    }
    //-------------------PLAYER TILE-------------------
    else if (map[nextRow][nextCol] == TILE_PLAYER)
    {
        //-----DOESN'T MOVE-----
        return STATUS_STAY;
    }
    //-------------------TREASURE TILE-------------------
    else if (map[nextRow][nextCol] == TILE_TREASURE)
    {
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;

        player.treasure++;
        return STATUS_TREASURE;
    }
    //-------------------AMULET TILE-------------------
    else if (map[nextRow][nextCol] == TILE_AMULET)
    {
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        //resizeMap(map, maxRow, maxCol);
        return STATUS_AMULET;
    }
    //-------------------DOOR TILE-------------------
    else if (map[nextRow][nextCol] == TILE_DOOR)
    {
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;

        return STATUS_LEAVE;
    }
    //-------------------OPEN TILE-------------------
    else if (map[nextRow][nextCol] == TILE_OPEN)
    {
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_MOVE;
    }
    //-------------------EXIT TILE-------------------
    else if (map[nextRow][nextCol] == TILE_EXIT)
    {
        if (player.treasure > 0)
        {
            map[player.row][player.col] = TILE_OPEN;
            player.row = nextRow;
            player.col = nextCol;
            map[player.row][player.col] = TILE_PLAYER;
            return STATUS_ESCAPE;
        }
        else // name - # levels
        {
            return STATUS_STAY;
        }
    }
    return 0;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char **map, int maxRow, int maxCol, const Player &player)
{
    bool eaten = false;

    //--------------------MONSTER RIGHT--------------------
    if ((player.col <= maxCol - 2) && map[player.row][player.col + 1] == TILE_MONSTER)
        {
            map[player.row][player.col] = TILE_MONSTER; //index
            map[player.row][player.col + 1] = TILE_OPEN;
            eaten = true;
            
        }
    for (int colr = player.col + 1; colr <= maxCol - 1; colr++)
    {
        //-----CHECK FOR MONSTER-------
        
        if (map[player.row][colr] == TILE_PILLAR)
        {
            break;
        }
        if (map[player.row][colr] == TILE_MONSTER)
        {
            map[player.row][colr] = TILE_OPEN;          //index
            map[player.row][colr - 1] = TILE_MONSTER;
        }
    }


    //--------------------MONSTER LEFT--------------------
    if ((player.col >= 2) && map[player.row][player.col - 1] == TILE_MONSTER)
        {
            map[player.row][player.col] = TILE_MONSTER;
            map[player.row][player.col - 1] = TILE_OPEN;
            eaten = true;
            
        }
    for (int coll = player.col - 1; coll >= 0; coll--)
    {
        //-----CHECK FOR MONSTER-------
        
        if (map[player.row][coll] == TILE_PILLAR)
        {
            break;
        }
        if (map[player.row][coll] == TILE_MONSTER)
        {
            map[player.row][coll] = TILE_OPEN;
            map[player.row][coll + 1] = TILE_MONSTER;
        }
    }


    //--------------------MONSTER DOWN--------------------
    if ((player.row <= maxRow -2) && map[player.row+1][player.col] == TILE_MONSTER)
        {
            map[player.row][player.col] = TILE_MONSTER;
            map[player.row+1][player.col] = TILE_OPEN;
            eaten = true;
            
        }
    for (int rowu = player.row + 1; rowu <= maxRow - 1; rowu++)
    {

        if (map[rowu][player.col] == TILE_PILLAR)
        {
            break;
        }
        if (map[rowu][player.col] == TILE_MONSTER)
        {
            map[rowu][player.col] = TILE_OPEN;
            map[rowu - 1][player.col] = TILE_MONSTER;
        }
    }


    //--------------------MONSTER UP--------------------
    if ((player.row >= 2) && map[player.row-1][player.col] == TILE_MONSTER)
        {
            map[player.row][player.col] = TILE_MONSTER;
            map[player.row - 1][player.col] = TILE_OPEN;
            eaten = true;  
        }
    for (int rowd = player.row - 1; rowd >= 0; rowd--)
    {
        
        if (map[rowd][player.col] == TILE_PILLAR)  
        {
            break;
        }
        if (map[rowd][player.col] == TILE_MONSTER)
        {
            map[rowd][player.col] = TILE_OPEN;
            map[rowd + 1][player.col] = TILE_MONSTER;  
        }
    }

    return eaten;
}
