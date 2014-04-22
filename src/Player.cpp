#include "Player.h"

Player::Player(){
	
}

Player::~Player(){
	
}

void Player::setChallenge(std::string pChallenge){
	mChallenge = pChallenge;
}

void Player::setId(int pId){
	mId = pId;
}

int Player::getId(){
	return mId;
}

std::string Player::getChallenge(){
	return mChallenge;
}
