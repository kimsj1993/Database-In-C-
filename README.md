# csce315project1
application for keeping track of video game players, what games they play, their activity in those games, and friendships between players. The application will also compile some of these data sources to output informative reports. This application will be similar in nature to Valve's Steam service or the website trueVictorys.com.


The application will be implemented as a command-line-interface (CLI) application. All input will be taken from standard input.  The input contains multiple lines. Each non-empty line of input will begin with a command that identifies the type of operation that line describes, followed by all its arguments (if any). The input can also contain empty lines, or lines in which there are only whitespace characters. Your program should ignore these empty or empty-character-only lines.


All output will be written to standard out.  


## The possible line formats are:


### AddPlayer (Player ID, Player Name)

Add player to the data structures. Player ID is a positive integer identifier for the player. Player Name is a string enclosed by double quotes ("Andruid Kerne"). Player Name may contain special characters (excluding double quote).

 

### AddGame (Game ID, Game Name)

Add game to the data structures. Game ID is a positive integer identifier for the game. Game Name is a string enclosed by double quotes (i.e. "Mirror's Edge"). Game Name may contain special characters (excluding double quote).


### AddVictory (Game ID, Victory ID, Victory Name, Victory Points)

Add Victory to the game denoted by Game ID. Victory ID is an integer identifier for the Victory. Victory Name is a string enclosed by double quotes (i.e. "Head over heels"). Victory Name may contain special characters (excluding double quote). Victory Points is an integer indicating how many gamer points the Victory is worth.


### Plays (Player ID, Game ID, Player IGN)

Add entry for player playing a specific game. Player IGN is a string identifier for that player's particular in game name for the specified game, enclosed by double quotes. Player IGN may contain special characters (excluding double quote).


### AddFriends (Player ID1, Player ID2)

Makes players 1 & 2 friends. Friends are mutual.


### WinVictory (Player ID, Game ID, Victory ID)

Adds Victory indicated to Player ID's record. Each Victory can only be achieved by a given player for once.



### FriendsWhoPlay (Player ID, Game ID)

Report which of player's friends play the specified game.


### ComparePlayers (Player ID1, Player ID2, Game ID)

Print report comparing player 1 and player 2's Victory records and total Victory scores for the given game. The given game is guaranteed to have been played by both players.


### SummarizePlayer (Player ID)

Print record of all of player's friends, games the player plays, and gamer point totals.


### SummarizeGame (Game ID)

Print a record of all players who play the specified game and the number of times each of its victories have been accomplished.


### SummarizeVictory (Game ID, Victory ID)

Print a list of all players who have achieved a Victory, and the percentage of players who play that game who have the Victory.


### VictoryRanking

Print a summary ranking all players by their total number of gamer points.


Players, Games, Victories and data relationships are guaranteed to exist before being operated on. IDs are guaranteed to be unique within their scope (i.e. a game's Victories will all have mutually exclusive IDs, but different games may have Victories with the same ID). Note that names can contain spaces and special characters (excluding double quote). The input has been validated to make sure that each non-empty line conforms to one of the specified line formats.
