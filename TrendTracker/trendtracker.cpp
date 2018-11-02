#include "trendtracker.h"

Trendtracker::Trendtracker()
{
  vector<Entry> E;
	Entry first;
	first.hashtag = "";
	first.pop = 0;
}


// Inserts a hashtag (tweeted 0 times) into the Trendtracker.
// If the hashtag already is in Trendtracker, does nothing.
void Trendtracker::insert(string ht)
{
  Entry insert;
  int check; 
  insert.hashtag = ht;
  insert.pop = 0;

  for (check = 0; check < E.size(); ++check) {
    if (ht == E[check].hashtag) {
      break;
    }
  }

  if (E.empty()) {
		E.push_back(insert);
	}

  if(check == E.size()) {
    E.push_back(insert);
  }
  
  //Push the element only if i is equal to n, that is there was no instance of the hastag to be inserted
}


// Return the number of hashtags in the Trendtracker.
int Trendtracker::size()
{
  return E.size();
}


// Inserts a hashtag (tweeted 0 times) into the Trendtracker.
// If the hashtag already is in Trendtracker, does nothing.
void Trendtracker::tweeted(string ht) 
{
  Entry tweet;

  tweet.pop = 0;

  for (int i = 0; i < E.size(); i++) {
	  if (ht == E[i].hashtag) {
	    E[i].pop++;
	    break; 	// Breaks if required match found
	  } 
  }
}


// Returns the number of times a hashtag has been tweeted.
// If the hashtag does not exist in Trendtracker, returns -1.
int Trendtracker::popularity(string name)
{
  Entry popularNum;

	for (int i = 0; i < E.size(); i++) {
    if (name == E[i].hashtag) {
      return E[i].pop;
    }
		
	}

  return -1;
}


// Returns a most-tweeted hashtag.
// If the Trendtracker has no hashtags, returns "".
string Trendtracker::top_trend()
{
	int topT, i;
	for (i = 1, topT = 0; i < E.size(); i++) {
		if (E[i].pop > E[topT].pop) {
			topT = i;
		}
	}

  if (E.size() == 0) {
		return "";
	}

  return E[topT].hashtag;
}


// Fills the provided vector with the 3 most-tweeted hashtags,
// in order from most-tweeted to least-tweeted.
//
// If there are fewer than 3 hashtags, then the vector is filled
// with all hashtags (in most-tweeted to least-tweeted order).
void Trendtracker::top_three_trends(vector<string>& T)
{
  int num1;
	int num2;
	int num3;

  T.clear();
  
  if(E.size() == 0) {
    return;
  }

	int i;

  int size = E.size();

  Entry Top3;

  //A new entry to check if its the largest value
	Top3.hashtag = "";
	Top3.pop = -1;
  
	E.push_back(Top3);
  
  for (i = 0, num1 = num2 = num3 = size; i < size; i++) {
    if(E[num1].pop < E[i].pop) { 
      num3 = num2;
      num2 = num1;
      num1 = i;
    } 
    else if(E[num2].pop < E[i].pop) {
      num3 = num2;
      num2 = i;
    } 
    else if(E[num3].pop < E[i].pop) {
      num3 = i;
    }
  } 
  
  T.push_back(E[num1].hashtag);

  if(num2 != size && num2 != num1){
    T.push_back(E[num2].hashtag);
  }
  
  if(num3 != size && num3 != num2) {
    T.push_back(E[num3].hashtag);
  }
  
  
  E.pop_back();
  
}