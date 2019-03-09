-- PROCEDURE --
First I scrape the website for data using a Python script, splitting each row into these attributes: time, player name, and phrase relating to the action (rebound, makes two points, player enters/leaves, etc.). 

After creating the CSV file of plays, I use C++ to iterate through the file and find three things: 

First, the rebounding percentages of each player on the roster. This includes the rebounds made by player x divided by the available rebounds while he is playing; It also includes the rebounds that player x’s team gets while he is on the court divideed by the available rebounds while he is playing (the reason being that some players help their team a rebound without individually getting one). 

Second, the rebounding percentages that every group of five players that are on the court (known as a lineup) earns collectively. In other words, it is the rebounds that the team gets divided by rebounding opportunities, when a given lineup is on the court. 

Lastly, the total time played by each lineup. This is important because out of the hundred-plus lineups that our coach has put on the court, not only are we only interested in the numbers of the lineups that he uses the most, those numbers are also more reliable. Overall, each stat we find is aggregated across multiple games so that we can find meaningful pattern.


-- ANALYSIS --
Reading the website occurs in O(n) time, where n is the number of rows in the play-by-play log. Although for some of the games in the beginning of the season, there were a few errors made by the person entering the data. These were corrected manually by watching game film. Reading the CSV and then calculating and writing the stats also occurs in O(n) time.


-- DESIGN CONSIDERATIONS --
Flexibility- Our coach will likely ask for different stats in the future which can be easily found by reading the play-by-play log on our website. Instead of stats for the groups of five on the court, maybe he will ask which pair of players performss best, or maybe which triplet. He might ask for assists or scoring related numbers. The project should be easily adapted to find answers to these questions

Speed/Space- Project should take advantage of data structures recently learned in CS class in order to make operations occur in linear time, and should also take as little space as possible.

Clarity- Results should be clear enough for the coach- who has a small statistics background and zero computer science background- to understand with little to no editing.


-- IMPLEMENTATION DETAILS -- 
Each player is associated with an ID; the first player with id 2^0=1, the second with id 2^1=2, ... , the fifteenth 2^15=32768. Every unique combination of five will thus have a unique sum of ID's; In addition, lineups ABCDE, ACDEB, BECDA... which all represent the same lineup, will have an equivalent sum of ID's. Each lineup is then stored in a map, where the key is the sum of the player ID's in that lineup, and the value is a custom data structure representing the lineup (called Lineup). A Lineup object contains an std::set of REFERENCES to another custom data structure representing a player (called Player... creative am I right), along with the lineup's rebounding numbers. 

Such an implmentation allows two things. First: excpected constant time lookup to see if a given lineup already exists- if it does, we can just update that and if it doesn't we insert a new Lineup into the map. Second: the references to Player objects allows us to update the players' stats directly from any lineup containing that player.   

The Collector class houses the map of Lineup objects as well as a map of the actual Player objects (not the references). It reads a CSV file, which represents actions in a game, given a starting lineup and second-half starting lineup that is input manually. While reading the file row-by-row (in time-order), Collector keeps track of the current lineup in the game. Whenever an action relating to that lineup happens, it sums this lineup's player ID's in order to find the key which maps to the Lineup object we want to update. Whenever a substitution happens, the lineup previously on the court essentially stops playing in the game. Again, Collector finds the key of this old lineup. This time, Collector will just update the amount of time that the old lineup has played. The new lineup in the game will be inserted into the map ONLY if it's associated key did not previously exist in the map.
