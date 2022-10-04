#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

bool wczytajPlik(std::string nazwaPliku, std::map<std::string, std::set<std::string>>& edges)
{
    std::ifstream plik;
    plik.open(nazwaPliku.c_str());
    if (!plik.good())
        return false;

    std::string linia;


    do {
        getline(plik, linia);
        // std::cout << linia << std::endl; 
        int comma = 0;
        std::string name = "";
        std::string friendname = "";
        std::set<std::string> friends;

        for (size_t i = 0; i < linia.length(); i++)
        {
            if (linia[i] != ',' && comma == 0) {
                name += linia[i];
            }
            else if (linia[i] != ',' && comma > 0) {
                friendname += linia[i];
            }
            if (linia[i] == ',') {
                if (comma > 0)
                    friends.insert(friendname);
                comma++;
                i++;
                friendname = "";
            }
        }
        friends.insert(friendname);
        edges.insert(std::pair < std::string, std::set<std::string> >(name, friends));
    } while (linia != "");


    plik.close();


    return true;
}

void showFriends(std::map<std::string, std::set<std::string>> edges, std::string person) {

    for (auto& e : edges) {
        if (e.first == person) {
            std::cout << person << "'s friends are: " << std::endl;
            for (auto& s : e.second) {
                std::cout << s << std::endl;
            }
        }
    }
}

void show(std::map<std::string, std::set<std::string>> edges) {
    for (auto& e : edges) {
        cout << "Od " << e.first;
        for (auto& v : e.second) {
            cout << "  do " << v << endl;
        }
    }
}

// dla 0, 4 => dziala
// 4,0
bool czyPolaczone(string a, string b, std::map<std::string, std::set<std::string>> edges) {
    if (a > b) return czyPolaczone(b, a, edges);
    if (edges[a].count(b)) return true;
    return false;
}

int przeszukiwanieWszerz(string nodeStart, string nodeEnd, std::map<std::string, std::set<std::string>> edges)
{  // BFS -  breadth-first search, BFS
   // queue< string > toCheckBasic;
    queue<pair<string, int > > toCheck;

    set<string> vis; // odwiedzone

    // 0. inicjalizacja
    toCheck.push(make_pair(nodeStart, 0));

    while (!toCheck.empty()) {
        // 1. wez nastepny z kolejki
        auto cur = toCheck.front();
        toCheck.pop();
        // 2. wez jego sasiadow
        auto neighbours = edges[cur.first];
        for (auto it = neighbours.begin(); it != neighbours.end(); ++it) {
            if (!vis.contains(*it))
            { // jesli ten sasiad nie byl jeszcze odwiedzony
                toCheck.push(make_pair(*it, cur.second + 1));
            }
        }
        // 3. czy to jest ten ktorego szukamy?
        if (cur.first == nodeEnd) {
            return cur.second;
        }
        vis.insert(cur.first);
    }

    return -1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////      TO DO::
map<string,int> givenFriendsAtDist(int n, string nodeStart, std::map<std::string, std::set<std::string>> edges)
{  // BFS -  breadth-first search, BFS
  
    queue<pair<string, int > > toCheck;

    set<string> vis; // odwiedzone

    set<pair<string, int >> friendsOfFriend;//imie i odleglosc

    map<string,int> result;

    // 0. inicjalizacja
    toCheck.push(make_pair(nodeStart, 0));

    while (!toCheck.empty()) {
        // 1. wez nastepny z kolejki
        auto cur = toCheck.front();
        toCheck.pop();
        // 2. wez jego sasiadow
        auto neighbours = edges[cur.first];
        for (auto it = neighbours.begin(); it != neighbours.end(); ++it) {
            if (!vis.contains(*it))
            { // jesli ten sasiad nie byl jeszcze odwiedzony
                toCheck.push(make_pair(*it, cur.second + 1));
                friendsOfFriend.insert(make_pair(*it, cur.second + 1));
            }
        }
       
        vis.insert(cur.first);
    }

    set<pair<string, int >>::iterator itr;
    for (itr = friendsOfFriend.begin(); itr != friendsOfFriend.end(); itr++) {
        if (itr->second == n)
            result.insert(*itr);
    }
    cout << endl;
    return result;
}


//int checkDistans(string a, string b, std::map<std::string, std::set<std::string>>edges) {
//
//
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::map<std::string, std::set<std::string>>edges;

    if (!wczytajPlik("dane.txt", edges))
        std::cout << "Failed to open the file!" << std::endl;

    //LEVEL -1
    std::string person;
    std::cout << "Find friends :";
    std::getline(std::cin, person);
    showFriends(edges, person);

    //LEVEL 1
    std::string person1;
    std::string person2;
    cout << "Minimal distance between two users\n";
    cout << "Users 1:\n";
    std::getline(std::cin, person1);
    cout << "Users 2:\n";
    std::getline(std::cin, person2);
    cout << "Minimal distance between two users:";
    cout << przeszukiwanieWszerz(person1, person2, edges)<<endl;

    
    //LEVEL 0
    map <string,int> FriendsNDistans = givenFriendsAtDist(2, "Naomi Rajah", edges);

    for (auto v: FriendsNDistans) {
    
        cout << v.first<<endl;
    }

    return 0;
}