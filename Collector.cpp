//
// Created by avliu on 12/28/18.
//

#include "Lineup.cpp"
#include <set>
#include <unordered_map>
#include <fstream>
#include <iostream>

class Collector{

    std::unordered_map<std::string, Player> roster;
    std::set<std::string> currentLineup;
    std::unordered_map<int, Lineup> lineup_map;
    std::unordered_map<std::string, int> id_map;
    std::unordered_map<int, std::string> number_map;

public:
    Collector(std::vector<std::string> roster_names){
        int id = 1;
        for(std::string n : roster_names){
            roster.insert(std::pair<std::string, Player> (n, Player(n)));
            id_map.insert(std::pair<std::string, int> (n, id));
            id = id * 2;
        }
    }

    int get_id(std::set<std::string> lineup){
        int answer = 0;
        for(std::string s : lineup){
            answer += id_map.at(s);
        }
        return answer;
    }

    //insert the previous lineup if it doesn't already exist
    void store_new_lineup(){
        int id = get_id(currentLineup);
        if(lineup_map.find(id)==lineup_map.end()) {
            std::unordered_map<std::string, Player *> players;
            for (std::string n : currentLineup) {
                players.insert(std::pair<std::string, Player *>(n, &roster.at(n)));
            }
            lineup_map.insert(std::pair<int, Lineup> (get_id(currentLineup), Lineup(players)));
        }
    }

    void update_old_lineup(std::string prev_time, std::string new_time){
        int id = get_id(currentLineup);
        lineup_map.at(id).add_time(prev_time,new_time);
    }

    void swap_lineup(std::set<std::string> new_names, std::string prev_time, std::string new_time){
        update_old_lineup(prev_time, new_time);

        currentLineup.clear();
        currentLineup = new_names;
        store_new_lineup();
    }

    void sub_lineup(std::set<std::string> entering, std::set<std::string> leaving, std::string prev_time, std::string new_time){
        update_old_lineup(prev_time, new_time);

        for(std::string s : entering){
            currentLineup.insert(s);
        }
        for(std::string s : leaving){
            currentLineup.erase(s);
        }
        store_new_lineup();
    }

    void process_game(std::string filename, std::set<std::string> starters1, std::set<std::string> starters2, std::set<std::string> starters3){
        std::ifstream in_file (filename);
        std::string line;
        std::string delim = ";";
        currentLineup = starters1;
        store_new_lineup();
        std::string prev_time = "20:00";
        std::string time = "20:00";
        bool ot_ready = false;
        bool ignore = false; //change to false
        bool substitutions = false; //change to false
        std::set<std::string> entering;
        std::set<std::string> leaving;

        if (in_file.is_open()) {
            while (getline(in_file, line)) {
                if (substitutions) {
                    if (line.substr(0, line.find(delim)) != time) {
                        if (std::stoi(line.substr(0, 2)) > std::stoi(time.substr(0, 2))) {
                            sub_lineup(entering, leaving, prev_time, "00:00");
                        } else {
                            sub_lineup(entering, leaving, prev_time, time);
                        }
                        entering.clear();
                        leaving.clear();
                        prev_time = time;
                        substitutions = false;
                        if (currentLineup.size() != 5) {
                            std::cout << "problem" << std::endl;
                        }
                    }
                }
                //20:00 has useless lineup changes, so wait until they are over
                if (ignore) {
                    if (line.substr(0, line.find(delim)) != "20:00") {
                        if (!ot_ready) {
                            ot_ready = true;
                            swap_lineup(starters2, prev_time, "00:00");
                            prev_time = "20:00";
                        } else {
                            swap_lineup(starters3, prev_time, "00:00");
                            prev_time = "05:00";
                        }
                        ignore = false;
                    }
                }
                std::string time_string = (line.substr(0, line.find(delim)));
                line.erase(0, line.find(delim) + delim.length());
                std::string name = (line.substr(0, line.find(delim)));
                line.erase(0, line.find(delim) + delim.length());
                std::string play = (line.substr(0, line.find(delim)));
                if (!ignore ) {
                    if (std::stoi(time_string.substr(0, 2)) > std::stoi(time.substr(0, 2))) {
                        ignore = true;
                    }
                    else if ((play.find("enters the game") != std::string::npos && roster.count(name))) {
                        substitutions = true;
                        entering.insert(name);
                    }
                    else if ((play.find("goes to the bench") != std::string::npos && roster.count(name))) {
                        substitutions = true;
                        leaving.insert(name);
                    }
                    else {
                        lineup_map.at(get_id(currentLineup)).process_data(name, play);
                    }
                }
                time = time_string;
            }
            update_old_lineup(prev_time, "00:00");
        }

    }
    void write_out_lineups(std::string filename){
        std::ofstream out_file (filename);
        out_file << "player1,player2,player3,player4,player5,minutes played,DR,available DR,OR, available OR" << std::endl;
        for(std::pair<int, Lineup> p : lineup_map){
            if( true ){
                out_file << p.second.reportRebounds() << std::endl;
            }
        }
    }


};

