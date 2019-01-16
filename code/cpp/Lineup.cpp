//
// Created by avliu on 12/28/18.
//

#include <string>
#include <unordered_map>
#include <vector>
#include "Player.cpp"

struct Lineup{
    std::unordered_map<std::string, Player*> players;
    int OR = 0;
    int DR = 0;
    int availOR = 0;
    int availDR = 0;
    int seconds_played = 0;

public:

    Lineup(std::unordered_map<std::string, Player*> input_players){
        players = input_players;
    }

    void add_time(std::string prev_string, std::string new_string){
        seconds_played = seconds_played + (std::stoi(prev_string.substr(0,2))*60 + std::stoi(prev_string.substr(3,5))
                                           - (std::stoi(new_string.substr(0,2))*60 + std::stoi(new_string.substr(3,5))));
    }

    void process_data(std::string name, std::string play){
        if (play.find("defensive rebound") != std::string::npos) {
            //update player that got the rebound
            bool ub = false;
            if (players.count(name)) {
                players.at(name)->my_DR();
                //UB defensive rebound
                ub = true;
                DR++;
                availDR++;
            }
            else{
                availOR++;
            }
            for (std::pair<std::string, Player*> player: players) {
                if (ub) {
                    //if UB got the rebound, update current lineup that got the rebound

                    player.second->team_DR();
                    player.second->avail_DR();
                }
                else{
                    player.second->avail_OR();
                }
            }

        } else if (play.find("offensive rebound") != std::string::npos) {
            //update player that got the rebound
            bool ub = false;
            if (players.count(name)) {
                players.at(name)->my_OR();
                //UB defensive rebound
                ub = true;
                OR++;
                availOR++;
            }else{
                availDR++;
            }
            for (std::pair<std::string, Player*> player: players) {
                if (ub) {
                    //if UB got the rebound, update current lineup that got the rebound
                    player.second->team_OR();
                    player.second->avail_OR();
                }
                else{
                    player.second->avail_DR();
                }
            }
        }
    }

    std::string reportRebounds() {
        std::string answer = "";
        for (std::pair<std::string, Player*> player: players) {
            answer += "\"" + player.first + "\"" + ",";
        }
        answer += std::to_string(seconds_played) + "," + std::to_string(DR) + "," + std::to_string(availDR) + ","
                + std::to_string(OR) + "," + std::to_string(availOR);
        return answer;
    }
};
