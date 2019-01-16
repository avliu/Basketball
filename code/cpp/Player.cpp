//
// Created by avliu on 12/28/18.
//

#include <string>

struct Player {

    std::string name;
    int myOR = 0;
    int myDR = 0;
    int teamOR = 0;
    int teamDR = 0;
    int availOR = 0;
    int availDR = 0;

public:

    Player(std::string input_name){
        name = input_name;
    }

    void my_OR(){
        myOR++;
    }
    void my_DR(){
        myDR++;
    }
    void team_OR(){
        teamOR++;
    }
    void team_DR(){
        teamDR++;
    }
    void avail_OR(){
        availOR++;
    }
    void avail_DR(){
        availDR++;
    }

    std::string reportRebounds(){
        std::string answer = "\"" + name + "\"" + "," +
                             std::to_string(myDR * 100.0 / availDR) + "," + std::to_string(myOR * 100.0 / availOR) + "," +
                             std::to_string(teamDR * 100.0 / availDR) + "," + std::to_string(teamOR * 100.0 / availOR);
        return answer;
    }

};
