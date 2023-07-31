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
#include <stack>



//using namespace std;

void buySequence(char input, Map* newMap, Character* player);

void inventorySequence(char input, Character* player);

void drawInventory(Character* player);

void characterMovementValidation(char input, sf::Vector2u& position, uint16_t speed, bool& flipCharacter, sf::Sprite& character,Map*& map, int* mapData);

char menu(sf::RenderWindow& window, sf::Font font);

void characterSelection(char choice, Character*& userChar, sf::RenderWindow& window, sf::Font font);

void setDungeon(Map*& map, Tilemap& tilemap);


int main() {
    PerlinNoise* myPerlin = new PerlinNoise(); //This needs a destructor!!!

    Map* newMap = new Map();
    newMap->createMap(myPerlin);
    newMap->marchingSquares();

    NameGenerator* names = new NameGenerator();

    int* mapData = newMap->returnMapData();
    
    
    bool TownEvent = false;
    bool DungeonEvent = false;
    bool BossEvent = false;
    bool InventoryEvent = false;

    bool winFight = false;

    bool MapEvent = (!TownEvent) && (!DungeonEvent) && (!BossEvent) && (!InventoryEvent)&& (!winFight);
    
    char input = ' ';
    bool flipCharacter = false;

    sf::Font titleFont;
    if (!titleFont.loadFromFile("8BitFont.ttf")) return 0;
   

    ///////////////MENU CODE HERE////////////////////////////
    //show main menu. Player has option to play or quit. 
    Character* userChar = nullptr; //CHANGE Later
    FightScreen fightScreen;
    //If quit, return 0;
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Fantasma");

    char userChoice = menu(window, titleFont);
    characterSelection(userChoice, userChar, window, titleFont);

    vector<Bandit*> enemies;
    
    Tilemap map;
    if (!map.load("Tilemap.png", sf::Vector2u(8, 8), newMap->returnMapData(), 16, 0))  return 0;
    map.setScale(8, 8);

    sf::Texture characterSprite;
    characterSprite.loadFromFile("Tilemap.png", sf::IntRect(144, 0, 8, 8));

    sf::Sprite character;
    sf::Vector2u characterPosition = sf::Vector2u(512,200);
    uint16_t characterSpeed = 1;
    character.setTexture(userChar->getTexture(1));
    character.setScale(8, 8);


    /////////////////////////////////////////////////////////

    ///////////////GAME LOOP ////////////////////////////////
    while(window.isOpen()){
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                input = event.key.code + 65;
            }
            if (event.type == sf::Event::KeyReleased) {
                input = ' ';
            }
            
            
        }
        window.clear();
        
        ///////////////////GAME EVENTS //////////////////////////


        TownEvent = newMap->getEnteredTown();
        BossEvent = newMap->getEnteredBoss();
        MapEvent = (!TownEvent) && (!DungeonEvent) && (!BossEvent) && (!InventoryEvent);

        if (newMap->getEnteredDungeon()) {
            if (!map.load("Tilemap.png", sf::Vector2u(8, 8), newMap->returnDungeon()->returnMapData(), 16, 1))  return 0;
            mapData = newMap->returnDungeon()->returnMapData();
            enemies = newMap->returnDungeon()->returnEnemies();

            newMap->flipEnteredDungeon();
            DungeonEvent = true;

            //SAVES THE PLAYER'S POSITION
            characterPosition = sf::Vector2u(characterPosition.x, characterPosition.y + 30);
            userChar->positionStackPush(characterPosition);
            characterPosition = sf::Vector2u(512, 900);
            /////////////////////////////
        }
        if (newMap->getExit()) {
            if (!map.load("Tilemap.png", sf::Vector2u(8, 8), newMap->returnMapData(), 16, 0))  return 0;
            mapData = newMap->returnMapData();
            newMap->flipExit();
            DungeonEvent = false;
            //SAVES THE PLAYER'S POSITION
            characterPosition = userChar->positionStackPop();
        }

        window.draw(map);
        characterMovementValidation(input, characterPosition, characterSpeed, flipCharacter, character, newMap, mapData);
        uint16_t characterSpriteIndex = ((characterPosition.x / 16) + (characterPosition.y / 16)) % 3;
        character.setPosition(characterPosition.x - (characterPosition.x % 8), characterPosition.y - (characterPosition.y % 8));
        character.setTexture(userChar->getTexture(characterSpriteIndex));
        window.draw(character);

        if (DungeonEvent) {
            
            for (int i = 0; i < enemies.size(); ++i) {
                //enemies[i]->getSprite().setPosition(200, 200 + (i * 50));
                enemies.at(i)->getSprite().setTexture(enemies.at(i)->getTexture(1));
                window.draw(enemies.at(i)->getSprite());
            }
        }

        ////////////////////INPUT VALIDATION///////////////////
        if(TownEvent){
            buySequence(input, newMap, userChar);
        }else if(InventoryEvent){
            cout << "\033[2J\033[1;1H";
            userChar->displayInventory();

            cout << "Press i to leave" << endl;
        }
        
        if ((input & 95) == 'I') { //checks whether uppercase or lowercase has been pressed

            InventoryEvent = !InventoryEvent;
            input = ' ';
        }
        
        
        window.display();
    }
    ////////////////////////////////////////////////////

    //Delete memory allocation
    delete myPerlin;
    delete newMap;
    delete names;
    delete userChar;
    return 0;
}


void characterMovementValidation(char input, sf::Vector2u& position, uint16_t speed, bool& flipCharacter, sf::Sprite& character, Map*& map, int* mapData) {
    char inputCharacter = input & 95;

    int xQuad = ((position.x) / 64);
    int yQuad = ((position.y) / 64);

    int leftadjacentY = ((position.y + 32) / 64);
    int upadjacentX = ((position.x + 32) / 64);
    
    int bound = 1024 - (64 + speed); //Square boundary of character sprite. Replace 64 with dynamic measurements
    
    switch (inputCharacter) {
    case 'W':
        if (mapData[(upadjacentX)+(yQuad * 16)] == 16) {
            position.y -= position.y > speed ? speed : 0;
        }
        else if (mapData[(upadjacentX)+(yQuad * 16)] == 20) {
            //want to go into dungeon. set map to dungeon mapdata and reset player position. HOW TO KNOW WHAT DUNGEON IS WHICH
            map->setDungeonIndex(xQuad, yQuad);
        }
        break;
    case 'A':
        if (mapData[(xQuad) + (leftadjacentY*16)] == 16) { 
            position.x -= position.x > speed ? speed : 0; 
        }
        if (!flipCharacter) {
            character.setTextureRect(sf::IntRect(8, 0, -8, 8));
            flipCharacter = !flipCharacter;
        }
        break;
    case 'S':
        if (mapData[(upadjacentX)+( (yQuad+1) * 16)] == 16) {
            position.y += position.y < bound ? speed : 0;
        }
        else if (mapData[(upadjacentX)+((yQuad+1) * 16)] == 21) {
            //set back to normal map

            map->flipExit();
        }
        break;
    case 'D':
        if (mapData[(xQuad+1)+((leftadjacentY) * 16)] == 16) {
            position.x += position.x < bound ? speed : 0;
        }
        
        if (flipCharacter) { 
            character.setTextureRect(sf::IntRect(0, 0, 8, 8));
            flipCharacter = !flipCharacter;
        }
        break;
    
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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                input = event.key.code + 65;
            }
            if (event.type == sf::Event::KeyReleased) {
                input = ' ';
            }
        }
        
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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                input = event.key.code + 22;
            }
            if (event.type == sf::Event::KeyReleased) {
                input = ' ';
            }

            if (input == '1') {

                userChar = new Fighter;
                Item* fighterStarter = new Item(2, 7, 3, 2, 1, 1, "Basic sword");
                userChar->addItem(fighterStarter);
                return;
                //cout << "You have chosen the way of the fighter. You're given a basic sword when your training concludes." << endl;

            }

            else if (input == '2') {

                userChar = new Bard;
                bardItem* bardStarter = new bardItem(5, 2, 5, 5, 5, 5, "Beat boxing", 5, 3);
                userChar->addItem(bardStarter);
                return;
                //cout << "You have chosen the way of the bard. You've acquired the skillful craft of beat boxing in your training." << endl;

            }

            else if (input == '3') {

                userChar = new Mage;
                mageItem* mageStarter = new mageItem(3, 5, 1, 5, 3, 5, "Wooden staff", 3, 3);
                userChar->addItem(mageStarter);
                return;
                //cout << "You have chosen the way of the mage. Your master grants you with a simple wooden staff to complete your training." << endl;

            }

            else if(input == '4') {

                userChar = new Tank;
                tankItem* tankStarter = new tankItem(4, 3, 5, 3, 1, 1, "Sturdy stick", 3, true);
                userChar->addItem(tankStarter);
                return;
                //cout << "You have chosen the way of the tank. After dominating the mountains to become a monster in human flesh, you salvage a sturdy stick to impose your will on opponents." << endl;
            }
            
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