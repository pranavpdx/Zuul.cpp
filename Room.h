#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstring>
using namespace std; 
// struct of objects
struct Object {
public:
	char* name;
	char* getName() {
		return name;
	}
};
class Room
{
public:
	// Room variables
	char* name;
	char* description;
	unordered_map<char*, Room*> neighbors;
	// room functions
	char* getName();
	Object* removeItem(char* item);
	bool addItem(vector<Object*> &vect, char* item);
	void setExit(char* direction, Room* room);
	virtual void move(char* direction, Room* &ptr);
	vector<Object*> items;
	Room(char* des,  char* name);
	Room(char* description, char* name, char* item);
	~Room();
};


