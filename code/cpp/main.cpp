#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include "Collector.cpp"

int main() {


    std::vector<std::string> files;
    files.push_back("/home/avliu/Desktop/basketball/20181106.csv"); //0
    files.push_back("/home/avliu/Desktop/basketball/20181109.csv"); //1
    files.push_back("/home/avliu/Desktop/basketball/20181112.csv"); //2
    files.push_back("/home/avliu/Desktop/basketball/20181121.csv"); //3
    files.push_back("/home/avliu/Desktop/basketball/20181124.csv"); //4
    files.push_back("/home/avliu/Desktop/basketball/20181130.csv"); //5
    files.push_back("/home/avliu/Desktop/basketball/20181201.csv"); //6
    files.push_back("/home/avliu/Desktop/basketball/20181205.csv"); //7
    files.push_back("/home/avliu/Desktop/basketball/20181208.csv"); //8
    files.push_back("/home/avliu/Desktop/basketball/20181215.csv"); //9
    files.push_back("/home/avliu/Desktop/basketball/20181218.csv"); //10
    files.push_back("/home/avliu/Desktop/basketball/20181221.csv"); //11


    std::vector<std::string> ros = {"MCRAE,MONTELL", "HARRIS,JEREMY", "GRAVES,JAYVON", "JORDAN,DAVONTA", "MASSINBURG,CJ", "SEGU,RONALDO",
                         "WILLIAMS,JEENATHAN", "CARUTHERS,DONTAY", "FAGAN,TRA'VON", "PERKINS,NICK", "BERTRAM,BROCK"};
    Collector collector(ros);

    //first half starters

    //all but 3,4, secondhalf-5
    std::set<std::string> start1;
    start1.insert(ros[0]);
    start1.insert(ros[1]);
    start1.insert(ros[2]);
    start1.insert(ros[3]);
    start1.insert(ros[4]);

    //3,4
    std::set<std::string> start2;
    start2.insert(ros[0]);
    start2.insert(ros[1]);
    start2.insert(ros[2]);
    start2.insert(ros[3]);
    start2.insert(ros[7]);

    //second half starters

    //0,1,2,4,6,8,11
    std::set<std::string> start3;
    start3.insert(ros[9]);
    start3.insert(ros[1]);
    start3.insert(ros[2]);
    start3.insert(ros[3]);
    start3.insert(ros[4]);

    //3
    std::set<std::string> start4;
    start4.insert(ros[0]);
    start4.insert(ros[1]);
    start4.insert(ros[2]);
    start4.insert(ros[3]);
    start4.insert(ros[7]);

    //7,9
    std::set<std::string> start5;
    start5.insert(ros[9]);
    start5.insert(ros[1]);
    start5.insert(ros[7]);
    start5.insert(ros[3]);
    start5.insert(ros[4]);

    //10
    std::set<std::string> start6;
    start6.insert(ros[9]);
    start6.insert(ros[1]);
    start6.insert(ros[7]);
    start6.insert(ros[3]);
    start6.insert(ros[4]);

    std::set<std::string> start0;

    collector.process_game(files[0], start1, start3, start0);
    collector.process_game(files[1], start1, start3, start3);
    collector.process_game(files[2], start1, start3, start0);
    collector.process_game(files[3], start2, start4, start0);
    collector.process_game(files[4], start2, start3, start0);
    collector.process_game(files[5], start1, start1, start0);
    collector.process_game(files[6], start1, start3, start0);
    collector.process_game(files[7], start1, start5, start0);
    collector.process_game(files[8], start1, start3, start0);
    collector.process_game(files[9], start1, start5, start0);
    collector.process_game(files[10], start1, start6, start0);
    collector.process_game(files[11], start1, start3, start0);

    collector.write_out_lineups("/home/avliu/Desktop/basketball/OUTPUT_LINEUPS.csv");
    collector.write_out_players("/home/avliu/Desktop/basketball/OUTPUT_PLAYERS.csv");

}
