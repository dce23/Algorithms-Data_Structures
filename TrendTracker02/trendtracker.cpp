#include "trendtracker.h"

Trendtracker::Trendtracker(string filename)
{
	string lines;
	ifstream file;
	getline(file, lines);
	file.open(filename);

	if (file) {
		while (file >> lines) {
			Entry trends;
			//getline(file, lines);
			trends.hashtag = lines;
			trends.pop = 0;
			E.push_back(trends);
		}
	}
	/*
	file.open("tiny.txt");
	file.open("small.txt");
	file.open("hashtags.txt");
	file.open("tweeted.txt");*/

	file.close();
}

int Trendtracker::size()
{
	return E.size();
}

void Trendtracker::tweeted(string ht)
{
	Entry tweet;

	tweet.pop = 0;

	for (int i = 0; i < E.size(); i++) {
		if (ht == E[i].hashtag) {
			E[i].pop++;
			break; 	
		}
	}
}

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
	string FT = E[topT].hashtag;

	search(FT);

	//return FT;

	return E[topT].hashtag;
}

void Trendtracker::top_three_trends(vector<string>& T)
{
	vector<Entry> E;
	int num1;
	int num2;
	int num3;

	T.clear();

	if (E.size() == 0) {
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
		if (E[num1].pop < E[i].pop) {
			num3 = num2;
			num2 = num1;
			num1 = i;
		}
		else if (E[num2].pop < E[i].pop) {
			num3 = num2;
			num2 = i;
		}
		else if (E[num3].pop < E[i].pop) {
			num3 = i;
		}
	}

	T.push_back(E[num1].hashtag);

	if (num2 != size && num2 != num1) {
		T.push_back(E[num2].hashtag);
	}

	if (num3 != size && num3 != num2) {
		T.push_back(E[num3].hashtag);
	}

	E.pop_back();
}

// Returns the index of E containing an Entry with hashtag ht.
// If no such hashtag is found, returns -1.

int Trendtracker::search(string ht)
{
	Entry searchTT;
	searchTT.pop = 0;
	searchTT.hashtag = ht;

	if (E.empty()) {
		E.push_back(searchTT);
		S.push_back(0);
	}

	int left, mid, right;
	left = 0;
	right = S.size() - 1;

	while (left < right) {
		mid = (left + right) / 2;
		if (E[S[mid]].hashtag == ht) { //found #1
			return E[mid].pop;
		}
		else if (E[S[mid]].hashtag < ht) {		//Searches right
			left = mid + 1;
		}
		else {
			right = mid - 1;				//Searches left
		}
	}

	if (left == right && E[S[left]].hashtag == searchTT.hashtag) {	// found #2
		return E[left].pop;
	}
	E.push_back(searchTT);

	//if hashtag still hasent been found this is the lowest
	if (left == 0 && ht < E[S[left]].hashtag) {
		//S[0]= E.size()-1;
		S.insert(S.begin(), E.size() - 1);
	}

	//if hashtag has not be been found you but is higher then the rest of the hashtags
	else if (left == S.size() - 1 && E[S[left]].hashtag < ht) {
		S.push_back(E.size() - 1);
	}

	// if new hashtag goes in the second index
	else if (left == 0 && right == 0 && E[S[right]].hashtag< ht) {
		S.insert(S.begin() + 1, E.size() - 1);
	}

	//left and right are somewhere in the middle
	else {
		S.insert(S.begin() + left, E.size() - 1);
	}
	
	return -1;
}