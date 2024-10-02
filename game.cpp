#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Room {
private:
    string name;
    string description;
    map<string, int> exits;
    bool isFinalRoom;

public:
    Room(string n, string desc, bool isFinal = false) : name(n), description(desc), isFinalRoom(isFinal) {}

    void addExit(string direction, int roomId) {
        exits[direction] = roomId;
    }

    int getExitId(string direction) {
        auto it = exits.find(direction);
        if (it != exits.end()) {
            return it->second;
        }
        return -1;
    }

    string getDescription() {
        return description;
    }

    bool isFinal() {
        return isFinalRoom;
    }

    const map<string, int>& getExits() const {
        return exits;
    }
};

int main() {
    srand(time(0));

    vector<Room> rooms = {
        Room("Entrance Hall", "You are standing in the entrance hall of an old castle."),
        Room("Courtyard", "You find yourself in a courtyard surrounded by towering walls."),
        Room("Library", "You enter a dusty library filled with ancient tomes and scrolls."),
        Room("Dungeon", "You descend into a dark and damp dungeon."),
        Room("Treasure Room", "You've found the treasure room! Congratulations!", true)
    };

    rooms[0].addExit("east", 1);    // Entrance Hall -> Courtyard
    rooms[1].addExit("west", 0);    // Courtyard -> Entrance Hall
    rooms[1].addExit("north", 2);   // Courtyard -> Library
    rooms[2].addExit("south", 1);   // Library -> Courtyard
    rooms[2].addExit("down", 3);    // Library -> Dungeon
    rooms[3].addExit("up", 2);      // Dungeon -> Library
    rooms[3].addExit("east", 4);    // Dungeon -> Treasure Room
    rooms[4].addExit("west", 3);    // Treasure Room -> Dungeon

    int currentRoomId = 0;

    cout << "Welcome to AdventureQuest!" << endl;

    while (true) {
        Room& currentRoom = rooms[currentRoomId];
        cout << "----------------------------------------" << endl;
        cout << "You are in: " << currentRoom.getDescription() << endl;

        if (currentRoom.isFinal()) {
            cout << "Congratulations! You've completed the quest!" << endl;
            break;
        }

        cout << "Exits: ";
        for (auto& exit : currentRoom.getExits()) {
            cout << exit.first << " ";
        }
        cout << endl;

        string direction;
        cout << "Where do you want to go? ";
        cin >> direction;

        int nextRoomId = currentRoom.getExitId(direction);
        if (nextRoomId == -1) {
            cout << "You cannot go that way!" << endl;
        } else {
            currentRoomId = nextRoomId;
        }
    }

    cout << "Thanks for playing AdventureQuest!" << endl;

    return 0;
}
