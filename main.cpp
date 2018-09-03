//
// Created by 김승진 on 8/30/18.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//data structures

struct Victory {

    int ID;
    string name;
    int points;
    int gameID;
    int nVictoryAchieved;

    vector<int> playersWhoGotVictory;
    Victory(int gameID, int ID ,string name, int points) {
        this->gameID = gameID;
        this->ID = ID;
        this->name = name;
        this->points = points;
        this->nVictoryAchieved = 0;
    }
    Victory(){}
};

struct Player {

    int ID;
    string name;
    vector<int> friendIDs;
    vector<Victory> victoryHistory;
    int userScore ;

    Player(){}

    Player(int ID, string name){
        this->ID = ID;
        this->name = name;
        this->userScore =0;
    }
};

struct Game {

    int ID;
    string name;
    //take userID and in game name
    map <int, string> gameHistory;
    vector<Victory> victorys;
    Game(int ID, string name)
    {
        this->ID = ID;
        this->name = name;
    }

    Game(){}
};

//global variables which functions as tables of database
vector<Player> playerList;
vector<Game> gameList;
vector<Victory> victoryList;



vector<Player>::iterator findPlayer(int playerID)
{
    for(vector<Player>:: iterator it=playerList.begin(); it != playerList.end(); it++)
    {
        if(it->ID == playerID)
            return it;
    }
    cout << "Player is not found " << endl;
}

vector<Game>::iterator findGame(int gameID)
{
    for(vector<Game>:: iterator it=gameList.begin(); it != gameList.end(); it++)
    {
        if(it->ID == gameID)
            return it;
    }
    cout << "game is not found " << endl;
}

/* -------------------------------------------------------------- */

void addPlayer(int playerID, string playerName)
{
    Player player(playerID, playerName);
    playerList.push_back(player);
}
void addGame(int gameID, string gameName)
{
    Game game(gameID, gameName);
    gameList.push_back(game);

}
void addVictory(int gameID, int victoryID, string victoryName, int victoryPoint)
{
    //create Victory object from inputs and put it into victory vector in game object
    Victory victory(gameID, victoryID, victoryName, victoryPoint);
    vector<Game>::iterator it = findGame(gameID);
    it->victorys.push_back(victory);
    victoryList.push_back(victory);


}
void plays(int playerID, int gameID, string inGameName)
{
    vector<Game>::iterator it = findGame(gameID);
    it->gameHistory.insert(pair<int, string>(playerID, inGameName));

}
void addFriends(int playerID1, int playerID2)
{
    vector<Player>::iterator it1, it2;
    it1 = findPlayer(playerID1);
    it1->friendIDs.push_back(playerID2);

    it2 = findPlayer(playerID2);
    it2->friendIDs.push_back(playerID1);

}
void winVictory(int playerID, int gameID, int victoryID)
{

    vector<Player>::iterator player;
    vector<Victory>::iterator victory;
    player = findPlayer(playerID);


    for(vector<Victory>::iterator it = victoryList.begin(); it != victoryList.end(); it++)
    {
        if(it->gameID == gameID && it->ID == victoryID)
        {
            victory = it;
        }
    }

    bool isAlreadyWin = false;
    for(vector<int>::iterator it = victory->playersWhoGotVictory.begin(); it != victory->playersWhoGotVictory.end(); it++)
    {
        if(*it == playerID)
        {
            isAlreadyWin = true;
        }
    }

    if(!isAlreadyWin)
    {
        player->userScore += victory->points;
        player->victoryHistory.push_back(*victory);
        victory->playersWhoGotVictory.push_back(playerID);
        victory->nVictoryAchieved ++;
    }

}

void friendsWhoPlay(int playerID, int gameID)
{
    Player player = *findPlayer(playerID);
    Game game = *findGame(gameID);



    for(vector<int>::iterator it1 = player.friendIDs.begin(); it1 != player.friendIDs.end(); it1 ++)
    {
        map<int, string>::iterator it2 = game.gameHistory.find(*it1);
        if(it2 != game.gameHistory.end())
        {
            vector<Player>::iterator it = findPlayer(*it1);
                cout << "Player ID: " << it->ID << "\tPlayer name : " << it->name << " plays " << game.name << " using " << game.gameHistory.find(*it1)->second << "as a in game name" << endl;

        }
    }
}

void comparePlayers(int playerID1, int playerID2, int gameID)
{
    Player player1 = * findPlayer(playerID1);
    int gameSCore = 0;
    vector<Game>::iterator gIt1 = findGame(gameID);

    cout << "Game Name : " << gIt1->name << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Victorys that " << player1.name << " achieved " << "In " << gIt1->name <<  "(" << gIt1->ID << ") :" << endl;

    for(vector<Victory>::iterator it = player1.victoryHistory.begin(); it != player1.victoryHistory.end(); it++)
    {
        if(it->gameID == gameID)
        {
            cout << it->name << ", which is " << it->points << "Point"<< endl;
            gameSCore += it->points;
        }

    }
    cout << "Total game Score : " << gameSCore << endl;
    cout << "----------------------------------------------------------" << endl;


    Player player2 = * findPlayer(playerID2);
    gameSCore = 0;
    cout << "Victorys that " << player2.name << " achieved " << "In " << gIt1->name <<  "(" << gIt1->ID << ") :" << endl;

    for(vector<Victory>::iterator it = player2.victoryHistory.begin(); it != player2.victoryHistory.end(); it++)
    {
        if(it->gameID == gameID)
        {
            cout << it->name << ", which is " << it->points << "Point"<< endl;
            gameSCore += it->points;
        }

    }
    cout << "Total game Score : " << gameSCore << endl;
    cout << "----------------------------------------------------------" << endl;

}
void summarizePlayer(int playerID)
{
    int nVictory = 0;
    int gameScore = 0;
    Player player = *findPlayer(playerID);
    cout << "Player: " << player.name <<endl;
    cout << "Total Gamerscore: " << player.userScore << " pts" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Game\t\t\t Victories \t GameScore \t IGN" << endl;
    for(vector<Game>::iterator it1 = gameList.begin(); it1 != gameList.end(); it1++)
    {
        gameScore = 0;
        nVictory = 0;

        for(vector<Victory>::iterator it3 = player.victoryHistory.begin(); it3 != player.victoryHistory.end(); it3++)
        {
            if(it1->ID == it3->gameID)
            {
                nVictory++;
                gameScore += it3->points;
            }
        }

        for(map<int, string>::iterator it2 = it1->gameHistory.begin(); it2 != it1->gameHistory.end(); it2++)
        {
            if(it2->first == playerID)
            {
                cout<< it1->name << "\t\t" << nVictory<<"/" << it1->victorys.size() <<"\t\t"<< gameScore << " pts \t"   <<  it2->second <<endl;

            }
        }
    }
    cout << "----------------------------------------------------------" << endl;
    cout << "Frined\t\t GameScore" << endl;
    for(vector<int>::iterator it = player.friendIDs.begin(); it != player.friendIDs.end(); it++)
    {
        Player p = *findPlayer(*it);
        cout << p.name << "\t" << p.userScore << endl;
    }




}
void summarizeGame(int gameID)
{
    Game game = *findGame(gameID);

    cout << "Game Name : " << game.name << "\n------------------\n";
    cout << "Players: "<< endl;


    for(map<int, string>::iterator it = game.gameHistory.begin(); it != game.gameHistory.end(); it++)
    {
        Player player = *findPlayer(it->first);
        cout << player.name << "played the game "<< endl;

    }

    for(vector<Victory> ::iterator it1 = victoryList.begin(); it1 != victoryList.end(); it1++)
    {
        if(it1->gameID == gameID)
            cout << "Victory: " << it1->name << " completed" << it1->nVictoryAchieved << " times" << endl;
    }
}

void summarizeVictory(int gameID, int victoryID)
{
    int counter = 0;
    Game game = *findGame(gameID);

    for(vector<Victory>::iterator it = victoryList.begin(); it!= victoryList.end(); it++)
    {
        if(it->ID == victoryID && it->gameID == gameID)
        {
            cout << "Players who have achieved a " << it->name << ": " << endl;
            for(vector<int>::iterator it2 = it->playersWhoGotVictory.begin(); it2 != it->playersWhoGotVictory.end(); it2++)
            {
                Player player = *findPlayer(*it2);
                cout << player.name << endl;
                counter ++;
            }
            cout << "the percentage of players who play this game who have the Victory : " << (counter * 100) / game.gameHistory.size() << "% " << endl;

        }
    }



}



int getCommands() {
    //depends on the first string of the input it call different function so that It can work properly.
    //util user enter quit, it keep alive

    string command;

    cin >> command;

    if(command == "AddPlayer"){
        int tempPlayerID;
        string tempName;
        cin >> tempPlayerID;
        getline(cin, tempName,'"');
        getline(cin, tempName,'"');
        addPlayer(tempPlayerID, tempName);
        return 1;



    } else if(command == "AddGame"){
        int tempGameID;
        string tempName;
        cin >> tempGameID;
        getline(cin, tempName,'"');
        getline(cin, tempName,'"');
        addGame(tempGameID, tempName);
        return 1;


    } else if(command == "AddVictory"){
        int tempGameID, tempVictoryID, tempScore;
        string tempName;
        cin >> tempGameID >> tempVictoryID;
        getline(cin, tempName,'"');
        getline(cin, tempName,'"');
        cin >> tempScore;

        addVictory(tempGameID, tempVictoryID, tempName, tempScore);
        return 1;





    } else if(command == "Plays"){
        int tempPlayerID, tempGameID;
        string tempInGameName;
        cin >> tempPlayerID >> tempGameID;
        getline(cin, tempInGameName,'"');
        getline(cin, tempInGameName,'"');

        plays(tempPlayerID,tempGameID,tempInGameName);
        return 1;



    } else if(command == "AddFriends"){
        int tempPlayerID1, tempPlayerID2;

        cin >> tempPlayerID1 >> tempPlayerID2;
        addFriends(tempPlayerID1, tempPlayerID2);
        return 1;




    } else if(command == "WinVictory"){
        int tempPlayerID, tempGameID, tempVictoryID;

        cin >> tempPlayerID >> tempGameID >> tempVictoryID;

        winVictory(tempPlayerID, tempGameID, tempVictoryID);
        return 1;



    } else if(command == "FriendsWhoPlay"){
        int tempPlayerID, tempGameID;
        cin  >> tempPlayerID >> tempGameID;

        friendsWhoPlay(tempPlayerID, tempGameID);
        return 1;



    } else if(command == "ComparePlayers"){
        int tempPlayerID1, tempPlayerID2, tempGameID;

        cin >> tempPlayerID1 >> tempPlayerID2 >> tempGameID;

        comparePlayers(tempPlayerID1, tempPlayerID2, tempGameID);
        return 1;




    } else if(command == "SummarizePlayer"){
        int tempPlayerID ;

        cin >> tempPlayerID;
        summarizePlayer(tempPlayerID);
        return 1;

    } else if(command == "SummarizeGame"){
        int tempGameID;
        cin >> tempGameID;
        summarizeGame(tempGameID);

        return 1;
    } else if(command == "SummarizeVictory"){
        int tempGameID, tempVictoryID;

        cin >> tempGameID >> tempVictoryID;
        summarizeVictory(tempGameID, tempVictoryID);
        return 1;

    } else if(command == "VictoryRanking"){
        return 1;

    } else if (command == "quit"){
        return 0;
    }
}

int main() {

    int temp = 1;

    cout << "Enter quit to stop this program " << endl;
    while(temp != 0)
    {
        getCommands();
    }






}