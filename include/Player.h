#pragma once
#include <string>

class Player{
private:
	int mId;
	std::string mChallenge;
public:
	Player();
	~Player();
	
	int getId();
	void setId(int pId);
	std::string getChallenge();
	void setChallenge(std::string pChallenge);
};
