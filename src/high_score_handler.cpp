/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : high_scores.cpp

* Purpose :

* Creation Date : 01-11-2011

* Last Modified : Tue 01 Nov 2011 02:17:24 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#include "high_score_handler.h"

using namespace std;

h_score::h_score(string n,unsigned int sc)
{
  name = n;
  score = sc;
}

high_score_handler::high_score_handler()
{
  
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
  score_file.open("high_scores.txt");
  unsigned int sc;
  string name;
  while (!score_file.eof())
  {
    score_file >> sc >> name;
    scores.push_back(new h_score(name,sc));
  }
  delete scores.back();
  scores.pop_back();
  score_file.close();
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
}
void high_score_handler::save_scores()
{
  score_file.open("high_scores.txt",ios::out);
  vector<h_score *>::iterator it = scores.begin();
  while(it != scores.end())
  {
    score_file << **it << endl;
    it++;
  }
  score_file.close();
}
