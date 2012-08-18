/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : high_score_handler.h

* Purpose :

* Creation Date : 01-11-2011

* Last Modified : Sat 18 Aug 2012 05:26:00 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef HIGH_SCORE_HANDLER
#define HIGH_SCORE_HANDLER


#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>


#define MAX_SCORES 10

class h_score
{
private:
    std::string name;
    unsigned int score;
public:
    friend bool operator < (h_score,h_score);
    friend std::ostream& operator << (std::ostream& out,h_score& a);
    std::string *to_str();
    h_score(std::string n,unsigned int s);
};
class high_score_handler
{
private:
    std::ofstream *of_score_file;
    std::ifstream *if_score_file;
    std::vector<h_score *> scores;
    char high_scores_path[100];
public:
    friend std::ostream& operator << (std::ostream& out,high_score_handler& a);
    void load_scores();
    void insert_score(std::string n,unsigned int s);
    void save_scores();
    void get_scores(std::vector<std::string *> &myscores);
    high_score_handler();
    ~high_score_handler();

};



#endif
