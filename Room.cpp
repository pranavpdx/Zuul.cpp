#include "Room.h"
#include <cstring>
#pragma warning(disable : 4996)
// constructor for a room with no objects
Room::Room( char* des,  char* name1){
	name = new char[strlen(name1)+1];
	description = new char[strlen(des)+1];
	strcpy(name, name1);
	strcpy(description, des);
} 
// constructor for room with objects
Room::Room(char* description1, char* name1, char* item) {
	name = new char[strlen(name1)+1];
	description = new char[strlen(description1)+1];
	strcpy(name, name1);
	Object* object = new Object();
	object->name = new char[strlen(item)+1];
	strcpy(object->name, item);
	items.push_back(object);
	strcpy(description, description1);
}
// prints room name
 char* Room::getName() {
	return name;
}

 // adds a direction and a room to a hashmap in java but an unordered map in c++
void Room::setExit(char* dir, Room* room) {
	char* direction = new char[strlen(dir)+1];
	strcpy(direction, dir);
	neighbors.insert(make_pair(direction, room));
}
// removes item from the rooms object vector and returns the object
Object* Room::removeItem(char* item) {
	for (vector<Object*>::iterator it = (items).begin(); it != (items).end(); ++it) {
		if (strcmp((*it)->getName(), item) == 0) {
			Object* ptr = *it;
			items.erase(it);
			return ptr;
			break;
		}
	}
	return NULL;
}
// adds item from users inventory to the rooms object vector
bool Room::addItem(vector<Object*>& vect, char* item) {
	for (vector<Object*>::iterator it = (vect).begin(); it != (vect).end(); ++it) {
		if (strcmp((*it)->getName(), item) == 0) {
			items.push_back(*it);
			vect.erase(it);
			return true;
			break;
		}
	}
	return false;
}
// moves a pointer to the room indicated by direction in map
void Room::move(char* direction, Room* &ptr) {
	bool moved = false;
	for (auto& x : neighbors) {
		if (strcmp(x.first, direction) == 0) {
			ptr = x.second;
			moved = true;
		}
	}
	if (moved == false) {
		cout << "You did not enter a proper direction";
	}
}
// destructer deletes pointers
Room::~Room() {
	if (name != NULL) {
		delete name;
	}
	if (description != NULL) {
		delete description;
	}
	while (!items.empty()) {
		Object* ptr = items.back();
		items.pop_back();
		delete ptr;
	}

}