#include <stdlib.h>
#include "../prototypes/gameEntity.h"
#include "../prototypes/map.h"


int SELECTED_MAP_1[5][9] = {
        {0, 0, 0,  0, 0, 0, 0, 0, 0},
        {0, 5, -7, 2, 1, 1, 1, 1, 0},
        {0, 2, 0,  1, 0, 1, 0, 2, 0},
        {0, 1, 1,  1, 1, 1, 2, 6, 0},
        {0, 0, 0,  0, 0, 0, 0, 0, 0}
};

int SELECTED_MAP_2[13][15] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 5, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 6, 0},
        {0, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 0},
        {0, 7, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 8, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

Player createPlayer(char *name, int bombCount) {
    Player myPlayer;
    myPlayer.name = name;
    myPlayer.bombCount = bombCount;
    myPlayer.life = 1;
    Inventory inventory;
    //inventory.bombUp = 0;
    //inventory.bombDown = 0;
    inventory.yellowFlame = 0;
    inventory.blueFlame = 0;
    inventory.redFlame = 0;
    inventory.bombPass = 0;
    inventory.bombKick = 0;
    inventory.invincibility = 0;
    inventory.invincibleTimer = 0;
    inventory.heart = 0;
    inventory.life = 0;
    inventory.pickHeart = 0;

    myPlayer.inventory = inventory;
    return myPlayer;
}

Map createBaseMap(int selectedMap) {
    Map myMap;
    switch (selectedMap) {
        case 1:
            myMap.row = 5;
            myMap.column = 9;
            myMap.map = calloc(myMap.row + 1, sizeof(int *));
            for (int i = 0; i < myMap.row; i++) {
                myMap.map[i] = malloc(sizeof(int) * myMap.column + 1);
            }
            for (int i = 0; i < myMap.row; i++) {
                for (int j = 0; j < myMap.column; j++) {
                    myMap.map[i][j] = SELECTED_MAP_1[i][j];
                }
            }
            break;
        case 2:
            myMap.row = 13;
            myMap.column = 15;
            myMap.map = calloc(myMap.row + 1, sizeof(int *));
            for (int i = 0; i < myMap.row; i++) {
                myMap.map[i] = malloc(sizeof(int) * myMap.column + 1);
            }
            for (int i = 0; i < myMap.row; i++) {
                for (int j = 0; j < myMap.column; j++) {
                    myMap.map[i][j] = SELECTED_MAP_2[i][j];
                }
            }
            break;
        default:
            break;
    }
    return myMap;
}

Game createGameWithDefaultMap(int playerCount, Player playerList[], int mapSelected, int soloGame) {
    Game myGame;
    Map myMap;
    myGame.soloGame = soloGame;
    myGame.playerCount = playerCount;
    myGame.mapSelected = mapSelected;
    myGame.WhoPlay = 1;
    myMap = createBaseMap(mapSelected);
    myGame.gameMap = purgeMapFromUselessPlayers(myMap, playerCount);
    myGame.posedBomb = malloc(sizeof(Bomb) * 100);
    myGame.posedBombCount = 0;
    myGame.players = malloc(sizeof(Player) * playerCount);
    for (int i = 0; i < playerCount; i++) {
        myGame.players[i] = playerList[i];
    }
    return myGame;
}

Game createGameWithImportedMap(int playerCount, Player playerList[], Map myMap, int soloGame) {
    Game myGame;
    myGame.soloGame = soloGame;
    myGame.playerCount = playerCount;
    myGame.mapSelected = 0;
    myGame.WhoPlay = 1;
    myGame.gameMap = purgeMapFromUselessPlayers(myMap, playerCount);
    myGame.posedBomb = malloc(sizeof(Bomb) * 100);
    myGame.posedBombCount = 0;
    myGame.players = malloc(sizeof(Player) * playerCount);
    for (int i = 0; i < playerCount; i++) {
        myGame.players[i] = playerList[i];
    }
    return myGame;
}
