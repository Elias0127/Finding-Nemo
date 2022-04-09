#include"player.h"
#include"actor.h"
#include"stack.h"
#include"dllist.h"
#include"point.h"
#include"maze.h"
#include<iostream>

//  Player( ... )
//		Constructs and initializes the Player/Actor and its member variables
//		Remembers and discovers the starting point.
Player::Player(Maze* maze, Point p, std::string name, char sprite, const bool tbacktrack)
	:Actor(maze, p, name, sprite),
	m_lookingPaper(),
	m_discoveredRooms(),
	m_btQueue(),
	m_btStack(),
	m_backtrackingEnabled(tbacktrack) {

	// Discover the starting point
	m_discoveredRooms.insert_front(p);
	m_lookingPaper.push(p);
}

//  stuck() 
//		See if the player is stuck in the maze (no solution)
bool Player::stuck() const {
	return Actor::getState() == State::STUCK;
}

//  foundExit()
//		See if the player has found the exit
bool Player::foundExit() const {
	return Actor::getState() == State::FREEDOM;
}

//  getTargetPoint()
//		Get the point the player wants to look around next.
//      If m_lookingPaper is empty then return an invalid point.
Point Player::getTargetPoint() const {
	if (m_lookingPaper.empty()) return Point(-1, -1);
	return m_lookingPaper.peek();
}

// discovered
//		returns true if the item is in the list
bool Player::discovered(const Point &p) const {
	return (m_discoveredRooms.find(p) != -2);
}



// say()
//		What does the player say?
//		Already Implemented, nothing to do here
void Player::say() {

	// Freedom supercedes being eaten
	if (getState() == State::FREEDOM) {
		std::cout << getName() << ": WEEEEEEEEE!";
		return;
	} 
 
	// Being eaten supercedes being lost
	switch (getInteract()) {
	case Interact::ATTACK:
		std::cout << getName() << ": OUCH!";
		break;
	case Interact::GREET:
		break;
	case Interact::ALONE:
	default:
		switch (getState()) {
		case State::LOOK:
			std::cout << getName() << ": Where is the exit?";
			break;
		case State::STUCK:
			std::cout << getName() << ": Oh no! I am Trapped!";
			break;
		case State::BACKTRACK:
			std::cout << getName() << ": Got to backtrack...";
			break;
		default:
			break;
		}

		break;
	}
}


//  update() 
//		This function implements an algorithm to look through the maze
//      for places to move (STATE::LOOK). update also handles moving the 
//		player as well, if there is an open undiscovered cell to move to the  
//		player just moves there.  However, there will be cases in the next 
//		desired point to look around is not adjacent (more than one cell away), 
//		at this point the player must backtrack (State::BACKTRACK) to a point 
//		that is adjacent to the next point the player was planning to visit
//
//		The player can only do one thing each call, they can either LOOK or 
//		BACKTRACK not both.  Nor should the player move more than one cell per
//		call to update.  If you examine the function calls for the entire game
//		you should observe that this is already be called within a loop. Your
//		Implementation should NOT have any loops that pertain to actual movement 
//		of the player.  
//
//		Backtracking is challenging, save it for the very very very last thing.
//		Make sure the STATE::LOOK aspect compiles and works first.
void Player::update() {

	int index = 0;
	Point p, newPosition;

	if (getState() == State::LOOK)
	{
		m_btStack.push(currentRoom());
		newPosition = m_lookingPaper.peek();
		move(newPosition);
		m_lookingPaper.pop();
		p = currentRoom();

		if (this->currentRoom() == this->getMaze()->foundExit())
		{
			this->changeState(State::FREEDOM);
			return;
		}

	Point west = Point(p.getX() - 1, p.getY());
   
		if (!discovered(west) && this->getMaze()->open(west))
		{
			newPosition = west;
			m_lookingPaper.push(west);
			m_discoveredRooms.insert_front(west);
		}

	Point east = Point(p.getX() + 1, p.getY());
		if (!discovered(east) && this->getMaze()->open(east))
		{
			newPosition = east;
			m_lookingPaper.push(east);
			m_discoveredRooms.insert_front(east);
		}

	Point north = Point(p.getX(), p.getY() - 1);
		if (!discovered(north) && this->getMaze()->open(north))
		{
			newPosition = north;
			m_lookingPaper.push(north);
			m_discoveredRooms.insert_front(north);
		}

	Point south = Point(p.getX(), p.getY() + 1);
		if (!discovered(south) && this->getMaze()->open(south))
		{
			newPosition = south;
			m_lookingPaper.push(south);
			m_discoveredRooms.insert_front(south);
		}

		if (m_lookingPaper.peek() != north && m_lookingPaper.peek() != south && m_lookingPaper.peek() != west && east != m_lookingPaper.peek())
		{
			changeState(State::BACKTRACK);
			return;
		}	
	}
	else
	{
		p = currentRoom();
		Point south = Point(p.getX(), p.getY() + 1);
		Point east = Point(p.getX() + 1, p.getY());
		Point north = Point(p.getX(), p.getY() - 1);
		Point west = Point(p.getX() - 1, p.getY());

		while (m_btStack.empty())
		{
			if (north != m_lookingPaper.peek() && m_lookingPaper.peek() != west && m_lookingPaper.peek() != east && m_lookingPaper.peek() != south)
			{
				changeState(State::STUCK);
				return;
			}
			else
			{
				if (south == m_lookingPaper.peek())
					newPosition = south;
				if (north == m_lookingPaper.peek())
					newPosition = north;
				if (east == m_lookingPaper.peek())
					newPosition = east;
				if (west == m_lookingPaper.peek())
					newPosition = west;

				changeState(State::LOOK);
				return;
			}
		}

		while (south == m_lookingPaper.peek() || north == m_lookingPaper.peek() || east == m_lookingPaper.peek() || west ==m_lookingPaper.peek())
		{
			if (south == m_lookingPaper.peek())
				newPosition = south;
			if (north == m_lookingPaper.peek())
				newPosition = north;
			if (east == m_lookingPaper.peek())
				newPosition = east;
			if (west == m_lookingPaper.peek())
				newPosition = west;

			changeState(State::LOOK);
			return;
		}

		newPosition = m_btStack.peek();
		m_btStack.pop();
		changeState(newPosition);
		
	}





	// Set by the settings file, if m_backtrackingEnabled is false, then
	// your program should behave exactly as seen in the slides or
	// example executables (with teleporting).
	// if(m_backtrackingEnabled) { ... code relating to backtracking 
	if (m_backtrackingEnabled) {
		

	}


}