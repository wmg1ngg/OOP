#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

class Room{
public:
    string name;
    Room *N=nullptr, *S=nullptr, *E=nullptr, *W=nullptr, *U=nullptr, *D=nullptr; // Exits in 6 directions（north, south, east, west, up, down)

    Room(const string& n) : name(n){}
    virtual ~Room(){}

    void link(const string& dir, Room* o){ // Link this room to another room in the specified direction
        if (dir=="north"){ N=o; o->S=this;}
        else if (dir=="south") {S=o; o->N=this;}
        else if (dir=="east"){E=o; o->W=this;}
        else if (dir=="west"){W=o; o->E=this;}
        else if (dir=="up"){U=o; o->D=this;}
        else if (dir=="down"){D=o; o->U=this;}
    }

    Room* getExit(const string& dir) const { // Get the room in the specified direction
        if (dir=="north") return N;
        if (dir=="south") return S;
        if (dir=="east")  return E;
        if (dir=="west")  return W;
        if (dir=="up")    return U;
        if (dir=="down")  return D;
        return nullptr;
    }

    virtual void onEnter() const { // Display room information when player enters
        vector<string> ex;
        if (N) ex.push_back("north");
        if (S) ex.push_back("south");
        if (E) ex.push_back("east"); 
        if (W) ex.push_back("west");
        if (U) ex.push_back("up");
        if (D) ex.push_back("down");
        cout << "\n=== " << name << " ===" << endl; // Print room name
        cout << "There are " << ex.size() << " exit(s): "; // Print number of exits
        for (size_t i=0; i<ex.size(); i++){ // Print exit directions
            if (i) cout << (i==ex.size()-1 ? " and " : ", ");
            cout << ex[i];
        }
        cout << "." << endl;
    }
};

class Lobby : public Room { // Special room: Lobby is the exit of the castle
public:
    Lobby() : Room("Lobby"){}
    void onEnter() const override {
        Room::onEnter();
        cout << "[This is the exit of the castle.]" << endl;
    }
};

class Library : public Room { // Special room: Library provides hints about the monster and princess
public:
    int monsterIdx, princessIdx;

    Library() : Room("Library"), monsterIdx(0), princessIdx(0) {}
    void onEnter() const override {
        Room::onEnter();
        cout << "[Type 'spell monster' or 'spell princess' to get a hint.]" << endl;
    }

    string getHint(const string& target) const { // Return a hint based on the target (monster or princess) and the current hint index
        static const vector<string> mh = {"",
            "Harm lurks where steps echo long.",    // 1 Corridor
            "Beware the scent of spice and flame.", // 2 Kitchen
            "Danger drips behind closed doors.",    // 3 Bedroom
            "",                                     // 4 Library
            "Beware the chains beneath your feet.", // 5 Dungeon
            "Shadows guard the steel and arms.",    // 6 Armory
            "Evil hides beneath the open sky.",     // 7 Garden
            "The beast sleeps atop the world.",     // 8 Tower
        };
        static const vector<string> ph = {"",
            "She seeks freedom where paths begin.", // 1 Corridor
            "Her heart beats near the scent of bread.", // 2 Kitchen
            "She hides where silence drips.", // 3 Bedroom
            "Look where dreams rest.", // 4 Library
            "She lingers where banquets once sang.", // 5 Dungeon
            "Freedom whispers where flowers bloom.", // 6 Garden
            "Valor protects her within the iron hall.", // 7 Armory
            "She waits atop the watchful spire.", // 8 Tower
        };
        if (target=="monster"  && monsterIdx  < (int)mh.size()) return mh[monsterIdx];
        if (target=="princess" && princessIdx < (int)ph.size()) return ph[princessIdx];
        return "The magic reveals nothing."; // Return a default message if the target is invalid or the hint index is out of range
    }
};

class Game{
    vector<Room*> rooms;
    Library* lib;
    Room *monsterRoom, *princessRoom;
    Room* current;
    bool hasPrincess = false; // Track if player has found the princess
    bool over = false; // Track if the game is over

    int randIdx(int excl=-1) { // Generate a random index for placing the monster and princess, excluding a specific index if needed
        static mt19937 rng{random_device{}()};
        uniform_int_distribution<> dis(1, 8);
        int r; do { r = dis(rng); }
        while (r==excl);
        return r;
    }

public:
    Game(){
        
        lib = new Library(); // Create the library room first to set monster and princess indices
        rooms = {
            new Lobby(),         
            new Room("Corridor"),
            new Room("Kitchen"),
            new Room("Bedroom"), 
            lib,               
            new Room("Dungeon"),
            new Room("Armory"), 
            new Room("Garden"), 
            new Room("Tower"), 
        };

        // Link rooms together to form the castle layout
        rooms[0]->link("north", rooms[3]);
        rooms[0]->link("east",  rooms[2]);
        rooms[0]->link("south", rooms[1]);
        rooms[0]->link("up",    rooms[4]);
        rooms[1]->link("south", rooms[5]);
        rooms[1]->link("east",  rooms[7]);
        rooms[3]->link("up",    rooms[8]); 
        rooms[6]->link("south", rooms[8]);

        // Randomly place the monster and princess in different rooms (excluding the Lobby)
        int mIdx = randIdx();
        int pIdx = randIdx(mIdx);
        lib->monsterIdx  = mIdx;
        lib->princessIdx = pIdx;
        monsterRoom  = rooms[mIdx];
        princessRoom = rooms[pIdx];
        current = rooms[0];
    }

    ~Game(){
        for (auto r : rooms) delete r;// Clean up dynamically allocated rooms
    }

    void run() { // Main game loop 
        cout << "====== CASTLE ADVENTURE ======" << endl;
        cout << "Find the princess and escape via the Lobby!" << endl;
        cout << "Commands: go <dir> | spell <monster/princess> | look | quit" << endl;
        current->onEnter();

        while (!over) {
            cout << "\n> ";
            string cmd, arg;
            cin >> cmd;
            transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

            if (cmd == "quit"){ // Handle quit command to end the game
                cout << "Farewell, adventurer." << endl;
                break;
            }

            if (cmd == "look"){ // Handle look command to re-display current room information
                current->onEnter();
                continue;
            }

            if (cmd == "go"){ // Handle go command to move to another room in the specified direction
                if (!(cin >> arg)) break; // If no direction is provided, exit the loop (end the game)
                transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
                Room* next = current->getExit(arg);
                if (!next) { cout << "No exit to the " << arg << "." << endl; continue;
                }

                current = next;
                current->onEnter();

                if (current == monsterRoom){ // If player enters the monster's room, the game is over
                    cout << "You found the monster... GAME OVER." << endl;
                    over = true;
                } else if (current == princessRoom && !hasPrincess){// If player finds the princess for the first time, they can now escape with her
                    cout << "Princess: \"You found me! Bring me to the Lobby to escape!\"" << endl;
                    hasPrincess = true;
                } else if (current == rooms[0] && hasPrincess){ // If player reaches the Lobby with the princess, they win the game
                    cout << "You escape the castle with the princess. YOU WIN!" << endl;
                    over = true;
                }
                continue;
            }

            if (cmd == "spell"){ // Handle spell command to get hints about the monster or princess from the Library
                if (!(cin >> arg)) continue;
                transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
                if (current != lib){
                    cout << "You can only cast spells in the Library." << endl; // If player tries to use spell command outside the Library, inform them and continue
                    continue;
                }
                cout << lib->getHint(arg) << endl;
                continue;
            }

            cout << "Unknown command." << endl;
        }
    }
};

int main() {
    Game g; // Create game instance
    g.run(); // Start the game loop
}
