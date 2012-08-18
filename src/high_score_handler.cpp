/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : high_scores.cpp

* Purpose :

* Creation Date : 01-11-2011

* Last Modified : Sat 18 Aug 2012 05:44:09 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#include "high_score_handler.h"

using namespace std;

h_score::h_score(string n,unsigned int sc)
{
    name = n;
    score = sc;
}

string *h_score::to_str()
{
    char formatedS[101];
    snprintf(formatedS, 100, "%d %s", score, name.c_str());
    return new string(formatedS);
}

high_score_handler::~high_score_handler()
{
    if(of_score_file)
    {
        of_score_file->close();
        delete of_score_file;
    }
}
high_score_handler::high_score_handler()
{
    const char *home_dir = getenv("HOME");
    snprintf(high_scores_path, 100, "%s/.config/PewPew/", home_dir);
    of_score_file = NULL;
    mkdir(high_scores_path, 0777);
    snprintf(high_scores_path, 100, "%s/.config/PewPew/high_scores", home_dir);
    if_score_file = new ifstream(high_scores_path);
    if(if_score_file->good())
    {
        load_scores();
        if_score_file->close();
        delete if_score_file;
    }
}

ostream& operator << (ostream& out,h_score& a)
{
    out << a.score << " " << a.name;
    return out;
}
bool operator < (h_score a,h_score b)
{
    return a.score < b.score;
}
ostream& operator << (ostream& out,high_score_handler& a)
{
    vector<h_score *>::iterator it = a.scores.begin();
    while(it != a.scores.end())
    {
        out<< **it << endl;
        it++;
    }
    return out;
}

void high_score_handler::load_scores()
{
    unsigned int sc;
    string name;
    while (!if_score_file->eof())
    {
        *if_score_file >> sc >> name;
        if(if_score_file->fail())
        {
            break;
        }
        scores.push_back(new h_score(name,sc));
    }
}
void high_score_handler::get_scores(vector<string *> &myscores)
{
    for(unsigned int i=0; i< scores.size(); i++)
    {
        myscores.push_back(scores[i]->to_str());
    }
}
void high_score_handler::insert_score(string n,unsigned int s)
{
    vector<h_score *>::iterator it = scores.begin();
    h_score * ns = new h_score(n,s);
    while(it != scores.end())
    {
        if ((**it) < (*ns))
        {
            scores.insert(it,ns);
            break;
        }
        it++;
    }
    if(scores.size() > MAX_SCORES)
    {
        delete scores.back();
        scores.pop_back();
    }
}
void high_score_handler::save_scores()
{
    of_score_file = new ofstream(high_scores_path);
    for(unsigned int i=0; i<scores.size(); i++)
    {
        *of_score_file << *(scores[i]->to_str()) << endl;
    }
}


