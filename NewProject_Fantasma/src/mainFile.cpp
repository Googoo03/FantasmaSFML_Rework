#include "../header/PerlinNoise.h"
#include "../header/Map.h"
#include "../header/NameGenerator.h"
#include "../header/Character.h"
#include "../header/FightScreen.h"
#include "../header/Fighter.h"
#include "../header/Mage.h"
#include "../header/Tank.h"
#include "../header/Item.hpp"
#include "../header/fighterItem.hpp"
#include "../header/mageItem.hpp"
#include "../header/tankItem.hpp"
#include "../header/bardItem.hpp"
#include "../header/Bard.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "conio.h"
#include "../header/Tilemap.h"
#include <cmath>
#include <algorithm>
#include <stack>
#include <queue>



//using namespace std;



void buySequence(char input, Map* newMap, Character* player);

void inventorySequence(char input, Character* player);

void drawInventory(Character* player);

void characterMovementValidation(char input, Character*& player, Map*& map, int* mapData);

char menu(sf::RenderWindow& window, sf::Font font);

void characterSelection(char choice, Character*& userChar, sf::RenderWindow& window, sf::Font font);

void setDungeon(Map*& map, Tilemap& tilemap);

void pollEvent(sf::RenderWindow& window, char& input);

void eventStateMachine(sf::RenderWindow& window, Map* newMap, int*& mapData, Character* player, queue<sf::Sprite>& drawSequence, char input);

void drawElements(sf::RenderWindow& window, queue<sf::Sprite>& drawSequence);

void characterMovementStateMachine(int currentTile, Character*& player, Map*& map, vector<int>& walkableTiles);

int main() {
    
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Fantasma"); //Non-negotiable I think; keep in main
    queue<sf::Sprite> drawSequence;

    Map* newMap = new Map();
    newMap->createMap();

    NameGenerator* names = new NameGenerator();

    int* mapData = newMap->returnMapData();

    bool TownEvent = false;
    bool DungeonEvent = false;
    bool BossEvent = false;
    bool InventoryEvent = false;

    bool winFight = false;

    bool MapEvent = (!TownEvent) && (!DungeonEvent) && (!BossEvent) && (!InventoryEvent) && (!winFight);

    char input = ' ';
    bool flipCharacter = false;

    sf::Font titleFont;
    if (!titleFont.loadFromFile("8BitFont.ttf")) return 0;
   

    ///////////////MENU CODE HERE////////////////////////////
    //show main menu. Player has option to play or quit. 
    Character* userChar = nullptr; //CHANGE Later
    char userChoice = menu(window, titleFont);
    characterSelection(userChoice, userChar, window, titleFont);
    /////////////////////////////////////////////////////////

    ///////////////GAME LOOP ////////////////////////////////
    while(window.isOpen()){
        
        pollEvent(window, input); // checks for keypress and assigns input accordingly
        
        ///////////////////GAME EVENTS //////////////////////////
        TownEvent = newMap->getEnteredTown();
        BossEvent = newMap->getEnteredBoss();
        MapEvent = (!TownEvent) && (!DungeonEvent) && (!BossEvent) && (!InventoryEvent);

        window.clear();
        eventStateMachine(window, newMap, mapData, userChar, drawSequence, input);
        drawElements(window, drawSequence);
    }
    ////////////////////////////////////////////////////
    delete newMap;
    delete names;
    delete userChar;
    return 0;
}

void eventStateMachine(sf::RenderWindow& window, Map* newMap, int*& mapData, Character* player, queue<sf::Sprite>& drawSequence, char input) {
    vector<Bandit*> enemies;
    sf::Vector2i characterPosition = player->getCharacterPosition();
    bool DungeonEvent = false;

    if (newMap->getEnteredDungeon()) {

        newMap->loadTilemap(newMap->returnDungeon()->returnMapData(), 1);
        mapData = newMap->returnDungeon()->returnMapData();
        enemies = newMap->returnDungeon()->returnEnemies();

        newMap->flipEnteredDungeon();
        DungeonEvent = true;

        //SAVES THE PLAYER'S POSITION
        characterPosition = sf::Vector2i(characterPosition.x, characterPosition.y + 30);
        player->positionStackPush(characterPosition);
        characterPosition = sf::Vector2i(512, 900);
        /////////////////////////////
    }
    if (newMap->getExit()) {
        newMap->loadTilemap(newMap->returnMapData(), 0);
        mapData = newMap->returnMapData();
        newMap->flipExit();
        DungeonEvent = false;
        //SAVES THE PLAYER'S POSITION
        characterPosition = player->positionStackPop();
    }
    player->setCharacterPosition(characterPosition);
    window.draw(newMap->returnTilemap()); //tilemap cant be passed into drawSequence, therefore window has to draw it here, any way to optimize?

    characterMovementValidation(input, player, newMap, mapData);

    player->updateCharacter();

    drawSequence.push(player->getCharacterSprite());

    if (DungeonEvent) {

        for (int i = 0; i < enemies.size(); ++i) {
            //enemies[i]->getSprite().setPosition(200, 200 + (i * 50));
            enemies.at(i)->getSprite().setTexture(enemies.at(i)->getTexture(1));
            drawSequence.push(enemies.at(i)->getSprite());
        }
    }
}

void pollEvent(sf::RenderWindow& window, char& input) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) { //Checks for keypress and assigns necessary ASCII Value
            input = event.key.code + 65;
            //input = event.key.code;
        }
        if (event.type == sf::Event::KeyReleased) { //Resets ASCII value if key is released
            input = ' ';
        }
    }
    
}

void drawElements(sf::RenderWindow& window, queue<sf::Sprite>& drawSequence) {
    while (!drawSequence.empty()) {
        window.draw(drawSequence.front());
        drawSequence.pop();
    }
    window.display();
}

void characterMovementValidation(char input, Character*& player, Map*& map, int* mapData) {
    char inputCharacter = input & 95;

    sf::Vector2i position = player->getCharacterPosition();
    int currentTile = player->getTilePos();
    int size = map->getSize();
    
    if (!(player->getCanMove())) { //is currently moving
        player->interpolatePosition();
        return;
    }

    switch (inputCharacter) {
    case 'W':
        if (currentTile / size > 0 && player->getCanMove()) { //Each key checks if within bounds and canMove, if so, set movement.
            characterMovementStateMachine(currentTile - size, player, map, player->getWalkableTiles());
        }
        break;
    case 'A':
        if (currentTile % size > 0 && player->getCanMove()) {
            
            player->setCharacterDirection(false);
            characterMovementStateMachine(currentTile - 1, player, map, player->getWalkableTiles());
        }
        break;
    case 'S':
        if (currentTile / size < map->getSize()-1 && player->getCanMove()) {
            characterMovementStateMachine(currentTile + size, player, map, player->getWalkableTiles());
        }
        break;
    case 'D':
        if (currentTile % size < map->getSize()-1 && player->getCanMove()) {
            
            player->setCharacterDirection(true);
            characterMovementStateMachine(currentTile + 1, player, map, player->getWalkableTiles());
        }
        break;
    
    }
}

void characterMovementStateMachine(int currentTile, Character*& player, Map*& map, vector<int>& walkableTiles) {
    
    for (int i = 0; i < walkableTiles.size(); ++i) {
        if (map->getTileValue(currentTile) == walkableTiles.at(i)) { //Player class should have a list of traversable tiles
            player->setCanMove(false);
            player->setNewTile(currentTile);
            break; //or return?
        }
    }
    
}

void inventorySequence(char input, Character* player){
    int choice = (input - 48);

    
    if(choice > player->getInventorySize() || choice <= 0) return;

    if(player->getEquipped() == player->getInventoryItem(choice-1)){ 
        //unequip
        player->UnequipItem();

    }else{
        //equip
        player->equipItem( player->getInventoryItem(choice-1)  );
    }
}

void buySequence(char input, Map* newMap, Character* player){
    if(player->isInventoryFull() && input != 'l'){
        cout << endl << "your inventory is full! Lose items to pickup more!" << endl;
        return;
    }
    Town* town = newMap->returnTown();

    switch(input){
        case 'l':
            //newMap->movementValidation('d');
            break;
        case '1':
            //if inventory isn't full, then remove item from shop and add to player inventory
            if(town->getShopSize() >= 1){
                Item* shopItem = town->getItem(0);
                player->addItem(shopItem);
                town->removeShopItem(0);
                //delete shopItem;
            }
            break;
        case '2':
            //if inventory isn't full, then remove item from shop and add to player inventory
            if(town->getShopSize() >= 2){
                Item* shopItem = town->getItem(1);
                player->addItem(shopItem);
                town->removeShopItem(1);
                //delete shopItem;
            }
            break;
        case '3':
            //if inventory isn't full, then remove item from shop and add to player inventory
            if(town->getShopSize() >= 3){
                Item* shopItem = town->getItem(2);
                player->addItem(shopItem);
                town->removeShopItem(2);
                //delete shopItem;
            }
            break;
        case '4':
            //if inventory isn't full, then remove item from shop and add to player inventory   
            if(town->getShopSize() >= 4){      
                Item* shopItem = town->getItem(3);
                player->addItem(shopItem);
                town->removeShopItem(3);
                //delete shopItem;
            }
            break;
        case '5':
            //if inventory isn't full, then remove item from shop and add to player inventory
            if(town->getShopSize() >= 5){
                Item* shopItem = town->getItem(4);
                player->addItem(shopItem);
                town->removeShopItem(4);
                delete shopItem;
            }
            break;

        default:
            break;
            }
}

char menu(sf::RenderWindow& window, sf::Font titleFont){

    sf::Text title;
    title.setFont(titleFont);
    title.setString("FANTASMA");
    title.setCharacterSize(64);
    
    title.setPosition(384, 300);

    sf::Text startOption;
    startOption.setFont(titleFont);
    startOption.setString("S to Start");
    startOption.setCharacterSize(48);

    startOption.setPosition(420, 400);

    sf::Text exitOption;
    exitOption.setFont(titleFont);
    exitOption.setString("Q to Quit");
    exitOption.setCharacterSize(48);

    exitOption.setPosition(420, 500);

    window.clear();
    window.draw(title);
    window.draw(startOption);
    window.draw(exitOption);
    window.display();

    char input = ' ';

    while (window.isOpen()) {
        pollEvent(window, input);

        if (input == 'S') {
            window.clear();
            return 's';
        }
        else if (input == 'Q') { exit(0); }
    }
}







void characterSelection(char userChoice, Character*& userChar, sf::RenderWindow& window, sf::Font font){

    sf::Text decisionText;
    decisionText.setFont(font);
    decisionText.setPosition(50, 50);
    decisionText.setCharacterSize(24);
    decisionText.setString("The land of Fantasma used to be a prosperous nation with a friendly\nand loving population, until their peaceful ways were usurped and \ntheir land seized by the ever - powerful Nardwar, an ancient being\nwho roams across the globe and toys with the lives of the innocents\nfor his own amusement.Fantasma yearns for the improbable arrival of \ntheir savior, and here you have arrived.You have chosen to challenge\nthe timeless devil Nardwar, now you must choose how you will approach\nthis epic showdown.");

    sf::Text FighterText;
    FighterText.setFont(font);
    FighterText.setPosition(200, 600);
    FighterText.setCharacterSize(24);
    FighterText.setString("Fighter");

    sf::Texture FighterTexture;
    FighterTexture.loadFromFile("Tilemap.png", sf::IntRect(176, 8, 8, 8));
    sf::Sprite FighterSprite;
    FighterSprite.setTexture(FighterTexture);
    FighterSprite.setScale(8, 8);
    FighterSprite.setPosition(200, 500);

    sf::Text BardText;
    BardText.setFont(font);
    BardText.setPosition(400, 600);
    BardText.setCharacterSize(24);
    BardText.setString("Bard");

    sf::Texture BardTexture;
    BardTexture.loadFromFile("Tilemap.png", sf::IntRect(184, 8, 8, 8));
    sf::Sprite BardSprite;
    BardSprite.setTexture(BardTexture);
    BardSprite.setScale(8, 8);
    BardSprite.setPosition(400, 500);

    sf::Text MageText;
    MageText.setFont(font);
    MageText.setPosition(600, 600);
    MageText.setCharacterSize(24);
    MageText.setString("Mage");

    sf::Texture MageTexture;
    MageTexture.loadFromFile("Tilemap.png", sf::IntRect(192, 8, 8, 8));
    sf::Sprite MageSprite;
    MageSprite.setTexture(MageTexture);
    MageSprite.setScale(8, 8);
    MageSprite.setPosition(600, 500);

    sf::Text TankText;
    TankText.setFont(font);
    TankText.setPosition(800, 600);
    TankText.setCharacterSize(24);
    TankText.setString("Tank");

    sf::Texture TankTexture;
    TankTexture.loadFromFile("Tilemap.png", sf::IntRect(200, 8, 8, 8));
    sf::Sprite TankSprite;
    TankSprite.setTexture(TankTexture);
    TankSprite.setScale(8, 8);
    TankSprite.setPosition(800, 500);

    char input = ' ';

    while (window.isOpen()) {
        pollEvent(window, input);
        char choice = input - 43;
        
        switch (choice) {
            case '1':
            {
                userChar = new Fighter;
                Item* fighterStarter = new Item(2, 7, 3, 2, 1, 1, "Basic sword");
                userChar->addItem(fighterStarter);
                return; //bad practice. is there a better way to exit the while loop and the switch case?
            }
            case '2':
            {
                userChar = new Bard;
                bardItem* bardStarter = new bardItem(5, 2, 5, 5, 5, 5, "Beat boxing", 5, 3);
                userChar->addItem(bardStarter);
                return;
            }
                
            case '3':
            {
                userChar = new Mage;
                mageItem* mageStarter = new mageItem(3, 5, 1, 5, 3, 5, "Wooden staff", 3, 3);
                userChar->addItem(mageStarter);
                return;
            }
                
            case '4':
            {
                userChar = new Tank;
                tankItem* tankStarter = new tankItem(4, 3, 5, 3, 1, 1, "Sturdy stick", 3, true);
                userChar->addItem(tankStarter);
                return;
            }
            default:
                break;
        }
        window.clear();
        window.draw(decisionText);
        window.draw(FighterText);
        window.draw(FighterSprite);
        window.draw(BardText);
        window.draw(BardSprite);
        window.draw(MageText);
        window.draw(MageSprite);
        window.draw(TankText);
        window.draw(TankSprite);
        window.display();
    }
}