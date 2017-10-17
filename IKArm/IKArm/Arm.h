/*
Class defining the full IKArm
Contains all joints and arm segments comprising the arm
Segments are parented bottom up so rotation along one segment moves all child segments
*/
#pragma once

#include <iostream>
#include "../IKArm/Dependencies/glm/glm.hpp"
#include "../IKArm/Dependencies/glew/glew.h"
#include "../IKArm/Dependencies/glut/glut.h"
#include <vector>
#include "ArmSegment.h"


typedef glm::vec3 vec3;
typedef glm::mat4x4 mat4x4;

class Arm 
{
private:
	//List of all joints in arm
	std::vector<vec3*> jointList;
	//List of segments of arm
	std::vector<ArmSegment*> segmentList;
	vec3* E; //endpoint of arm
	vec3 D; //targetpoint
	vec3 baseCoord; //base of arm
	ArmSegment* armBase;
	ArmSegment* upperArm;
	ArmSegment* hand;
	ArmSegment* finger;
	float totalLength; //longest total length of arm

public:
	Arm();
	//Draws object on canvas
	void drawObject();
	//Performs Cyclic Coordinate Descent to reach a target point using Inverse Kinematics
	void IKToTarget(float x, float y, float z);
	//Returns direction tip of arm is pointing in
	vec3 getTipDirection();
};