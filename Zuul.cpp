// Zuul.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Program runs a version of the game ZUUL
//Author: Pranav Sharma
// Date: 10/25/20
#pragma warning(disable : 4996)
#include <iostream>
#include "Room.h"
#include <cstring>
using namespace std;
// Our global variables
vector<Room*> vect;
vector<Object*> personalitems;
// Method prints the moves available for a given room
void printMoves(Room* ptr) {
    cout << "( ";
    for (auto& x : ptr->neighbors) {
        cout << x.first << " ";
    }
    cout << ")\n";
}
// Method prints the item avaliable in a given room by iterating over its object vector
void printItems(vector<Object*> vect) {
    for (vector<Object*>::iterator it = (vect).begin(); it != (vect).end(); ++it) {
        cout << (*it)->getName() << endl;
    }
    if ((vect).empty()) {
        cout << "no items\n";
    }
}
// Methods prints the initial description of the room, its exits, and its items
void printInfo(Room* ptr) {
    cout << "\nYou are in room: " << ptr->getName() << endl;
    cout << ptr->description << endl;
    cout << "There are exits: " << endl;
    printMoves(ptr);
    cout << "There are items: " << endl;
    printItems(ptr->items);
}
// Checks to see if the inventory has the right items needed to win the game
bool checkItems(bool &strong) {
    int count = 0;
    bool weak = false;
    for (vector<Object*>::iterator it = personalitems.begin(); it != personalitems.end(); ++it) {
        if (strcmp((*it)->getName(), "Gears") == 0) {
            count++;
        }
        if (strcmp((*it)->getName(), "Voice Modulator") == 0) {
            count++;
        }
        if (strcmp((*it)->getName(), "Stuffed Monkey") == 0) {
            count++;
        }
        if (strcmp((*it)->getName(), "PB&J") == 0) {
            count++;
        }
        if (strcmp((*it)->getName(), "Battery") == 0) {
            count++;
            weak = true;
        }
        if (strcmp((*it)->getName(), "Strong Battery") == 0) {
            count++;
            strong = true;
        }
    }
    // checks if normal battery is held plus the other 4 items, or the strong battery is held with the other 4 items, or if all items are held then
    // secret room becomes available
    if (count > 4 && strong == false && weak == true) {
        return true;
    }else if (count > 4 && strong == true && weak == false) {
        return true;
    }
    else if (count == 6) {
        return true;
    }
    else {
        return false;
    }
}
int main()
{
    // Creates Room Objects and sets their items
    char des[400];
    char name[20];
    char item[20];
    strcpy(des, "This is where all the computer nerds are");
    strcpy(name, "1-20");
    Room* computerlab = new Room(des,name);
    vect.push_back(computerlab);
    // currunt pointer keeps trakc of where you are in a map
    Room* currentptr = computerlab; 
    strcpy(des, "All the students are paying close attention to Ms.Mac");
    strcpy(name, "Math Room");
    strcpy(item, "Gears");
    Room* math = new Room(des, name, item);
    vect.push_back(math);
    strcpy(des, "Los estudiantes están hablando en español con fluidez");
    strcpy(name, "Spanish Room");
    strcpy(item, "Voice Modulator");
    Room* spanish = new Room(des, name, item);
    vect.push_back(spanish);
    strcpy(des, "The janitor is cleaning up! It looks tidy!");
    strcpy(name, "Courtyard");
    strcpy(item, "Racquet");
    Room* courtyard = new Room(des, name, item);
    vect.push_back(courtyard);
    strcpy(des, "The tennis players are doing drills");
    strcpy(name, "Tennis Court");
    strcpy(item, "Tennis Ball");
    Room* tennis = new Room(des, name, item);
    vect.push_back(tennis);
    strcpy(des, "The students are disecting a pig!");
    strcpy(name, "Biology Room");
    strcpy(item, "Battery");
    Room* biology = new Room(des, name, item);
    vect.push_back(biology);
    strcpy(des, "Physicists are shooting particles at each other");
    strcpy(name, "Physics Room");
    strcpy(item, "Strong Battery");
    Room* physics = new Room(des, name, item);
    vect.push_back(physics);
    strcpy(des, "The Janitor's closet is empty... and smells kinda funny.");
    strcpy(name, "Janitor's Closet");
    strcpy(item, "Mop");
    Room* janitor = new Room(des, name, item);
    vect.push_back(janitor);
    strcpy(des, "Reactions! Reactions everywhere!");
    strcpy(name, "Chemistry Room");
    strcpy(item, "Flasks");
    Room* chemistry = new Room(des, name, item);
    vect.push_back(chemistry);
    strcpy(des, "Very loud and heated discussions are happening");
    strcpy(name, "Literature Room");
    strcpy(item, "Ungraded Papers");
    Room* lit = new Room(des, name, item);
    vect.push_back(lit);
    strcpy(des, "Supply and Demand curves are being analyzed");
    strcpy(name, "Economics Room");
    Room* econ = new Room(des, name);
    vect.push_back(econ);
    strcpy(des, "Thoughful and meaningful discussions are happening...jk");
    strcpy(name, "Philosophy Room");
    strcpy(item, "Stuffed Monkey");
    Room* phil = new Room(des, name, item);
    vect.push_back(phil);
    strcpy(des, "Uh Oh! Diploma candidates are stressing over their 50 HL exams! oh well");
    strcpy(name, "TOK Room");
    strcpy(item, "Markers");
    Room* tok = new Room(des, name, item);
    vect.push_back(tok);
    strcpy(des, "Students are furiously munching");
    strcpy(name, "Cafeteria");
    strcpy(item, "PB&J");
    Room* cafeteria = new Room(des, name, item);
    vect.push_back(cafeteria);
    strcpy(des, "Room is empty... Printing materials are available");
    strcpy(name, "Print Room");
    Room* print = new Room(des, name);
    vect.push_back(print);
    Room* secret = NULL;
    
    // Creates Exits 
    char* direction = new char(5);
    strcpy(direction, "WEST");
    computerlab->setExit(direction, print);
    math->setExit(direction, computerlab);
    spanish->setExit(direction, math);
    tennis->setExit(direction, courtyard);
    janitor->setExit(direction, chemistry);
    physics->setExit(direction, biology);
    chemistry->setExit(direction, lit);
    lit->setExit(direction, tok);
    phil->setExit(direction, cafeteria);

    strcpy(direction, "EAST");
    computerlab->setExit(direction, math);
    math->setExit(direction, spanish);
    courtyard->setExit(direction, tennis);
    biology->setExit(direction, physics);
    chemistry->setExit(direction, janitor);
    lit->setExit(direction, chemistry);
    tok->setExit(direction, lit);
    cafeteria->setExit(direction, phil);
    print->setExit(direction, computerlab);

    strcpy(direction, "NORTH");
    math->setExit(direction, courtyard);
    spanish->setExit(direction, tennis);
    biology->setExit(direction, math);
    physics->setExit(direction, spanish);
    chemistry->setExit(direction, biology);
    janitor->setExit(direction, physics);
    lit->setExit(direction, phil);
    tok->setExit(direction, cafeteria);
    econ->setExit(direction, lit);
    cafeteria->setExit(direction, print);

    strcpy(direction, "SOUTH");
    courtyard->setExit(direction, math);
    tennis->setExit(direction, spanish);
    math->setExit(direction, biology);
    spanish->setExit(direction, physics);
    biology->setExit(direction, chemistry);
    physics->setExit(direction, janitor);
    phil->setExit(direction, lit);
    cafeteria->setExit(direction, tok);
    lit->setExit(direction, econ);
    print->setExit(direction, cafeteria);

    // sets local variables
    bool playing = true;
    bool strong = false;
    bool created = false;
    char* input = new char[400];
    // intro
    cout << "Welcome to Zuul! The Mysterious turn-based adventure game. You are at school, ditching C++ class because you don't like coding\n";
    // runs program until user wins or quits the game, each loop is a turn
    while (playing) {
        //at the beggining of each turn, the room description and name are printed out
        printInfo(currentptr);
        // user can move ot a different room, pick up an item, drop an item, or check their inventory
        cout << "What would you like to do?(MOVE, PICK, DROP, PRINT or QUIT)\n";
        cin.getline(input, 80, '\n');
        // if user moves
        if (strcmp(input, "MOVE") == 0) {
            // asks for the direction and prints options
            cout << "Which direction would you like to move? You may move ";
            printMoves(currentptr);
            cin.getline(input, 80, '\n');
            // moves the room pointer
            currentptr->move(input, currentptr);
        }
        // if user picks
        else if (strcmp(input, "PICK") == 0) {
            // only allows 10 items in your inventory
            if (personalitems.size() < 10) {
                // they input the item they want to pick
                cout << "Which item would you like to pick up? The available items are: \n";
                printItems(currentptr->items);
                cin.getline(input, 80, '\n');
                // item gets removed form the Rooms vector and added to your inventory vector
                Object* ptr = currentptr->removeItem(input);
                if (ptr != NULL) {
                    personalitems.push_back(ptr);
                    cout << "In your inventory, you have: \n";
                    // prints items
                    printItems(personalitems);
                }
                else {
                    cout << "This item could not be found\n";
                }
            }
            else {
                cout << "Sorry! You have too many items in your bag. Drop one and try again\n";
            }
        }
        // if user drops item
        else if (strcmp(input, "DROP") == 0) {
            // prints options and asks what user wants to drop
            cout << "Which item would you like to drop? The available items are: \n";
            printItems(personalitems);
            cin.getline(input, 80, '\n');
            bool dropped = currentptr->addItem(personalitems, input);
            if (dropped == true) {
            cout << "You dropped " << input << ". In your inventory, you have: \n";
            printItems(personalitems);
            }
            else {
                cout << "You don't have that item\n";
            }
        }
        // while loop ends if user quits... what a sore loser
        else if (strcmp(input, "QUIT") == 0) {
            playing = false;
        }
        // if user prints inventory.. it is printed
        else if (strcmp(input, "PRINT") == 0) {
            cout << "In your inventory, you have: \n";
            printItems(personalitems);
        }
        // user didnt enter a real command? Seriously?
        else {
            cout << "It looks like you didn't enter a proper command :(\n";
        }
        // if user has the apropriate items to open the secret door, it is created and computerlab has an pathway to it, only runs once not each time a turn happens
        if (checkItems(strong) && created == false) {
            strcpy(direction, "NORTH");
            strcpy(des, "Fog starts apppearing from every direction, it gets warm.. you hear a sound");
            strcpy(name, "Secret ROOM");
            secret = new Room(des, name);
            vect.push_back(secret);
            computerlab->setExit(direction, secret);
            created = true;
        }
        // if user has right items and is in the secret room, ending is displayed, loop ends
        if (checkItems(strong) && currentptr == secret) {
            cout << "THE GHOST OF A CHILD APPEARS\n" << "She whispers \"Thank you for brining me my bear... Oh and hes alive now? Even better!\"\n";
            cout << "\"You deserve a treat! I will send you home now, take the day off, I marked you present in all your classes\" \n";
            if (strong == true) {
                cout << "\"You even gave him a strong battery?? Here take these cookies\"\n ";
            }
            cout << "You are teleported home\n";
            playing = false;
        }
    }
    // thanks user and deletes all pointers
    cout << "Thanks for playing!";
    while (!vect.empty()) {
        Room* ptr = vect.back();
        vect.pop_back();
        delete ptr;
    }

    while (!personalitems.empty()) {
        Object* ptr = personalitems.back();
        personalitems.pop_back();
        delete ptr;
    }
}

