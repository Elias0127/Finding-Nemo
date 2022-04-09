#include"actor.h"
#include"point.h"
#include"maze.h"
#include<string>							
Actor::Actor(Maze* maze, Point p, std::string name, char sprite)
	:m_maze(maze), m_currPos(p),m_name(name),
	m_sprite(sprite), m_currState(State::LOOK), m_interact(Interact::ALONE) {
}
Actor::~Actor() {}
void Actor::move(Point p) {
	m_currPos = p;
}
Point Actor::currentRoom() const {
	return m_currPos;
}
void Actor::changeState(State s) {
	m_currState = s;
}
State  Actor::getState() const {
	return m_currState;
}
char Actor::draw() const {
	return m_sprite;
}
Maze* Actor::getMaze() const {
	return m_maze;
}
std::string Actor::getName() {
	return m_name;
}

void Actor::changeInteract(Interact i) {
	m_interact = i;
}
Interact Actor::getInteract() const {
	return m_interact;
}
