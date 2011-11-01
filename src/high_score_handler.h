/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : high_score_handler.h

* Purpose :

* Creation Date : 01-11-2011

* Last Modified : Tue 01 Nov 2011 02:17:48 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef HIGH_SCORE_HANDLER
#define HIGH_SCORE_HANDLER


#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>

class h_score
{
  private:
    std::string name;
    unsigned int score;
  public:
    friend bool operator < (h_score,h_score);
    friend std::ostream& operator << (std::ostream& out,h_score& a);
    h_score(std::string n,unsigned int s);
};
class high_score_handler
{
  private:
    std::fstream score_file;
    std::vector<h_score *> scores;
  public:
    friend std::ostream& operator << (std::ostream& out,high_score_handler& a);
    void load_scores();
    void insert_score(std::string n,unsigned int s);
    void save_scores();
    high_score_handler();
    
};



#endif
