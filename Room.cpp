#include "room.h"

Room::Room(String name):RemotlyControlled(name) {
  //this->name = name;
  points = 0;
  for(int i = 0; i < ROOM_MAX_POINTS; i++){
    pointsTable[i] = NULL;
  } 
}

Room::~Room() {
  for(int i = 0; i < points; i++){
    delete pointsTable[i];
    pointsTable[i] = NULL;
  }
  points = 0;
}

void Room::addPoint(Point* point) {
  point->setParent(this);
  pointsTable[points] = point;
  points++;
}

void Room::initialize() {
  Serial.println("Init points...");
  for(int i = 0; i < points; i++) {
    Serial.print("Init points ");
    Serial.println(i);
    pointsTable[i]->initialize();
  }
  Serial.println("Init points. Done. Room initialized.");
}

void Room::verifyControlPoints() {  
  for(int i = 0; i < points; i++){
    pointsTable[i]->verifyControlPoint();
  }
}

String Room::createCommand() {
  return getRemoteName();
}


void Room::executeCommand(String roomCommand) {
  String pointRemoteName = getNextRemotlyControlled(roomCommand);
  String pointAction = getSubCommand(roomCommand);
  bool find = false;
 
  for(int i = 0; i < points && !find; i++) {
    if (pointsTable[i]->getRemoteName() == pointRemoteName) {
      pointsTable[i]->executeCommand(pointAction);
      find = true;
    }
  }
  if (!find) {
    Serial.println("There is no point in rooms from command " + roomCommand);
  }
}

