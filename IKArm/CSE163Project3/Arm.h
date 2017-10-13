#pragma once

#include <iostream>
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glew/glew.h"
#include "Dependencies/glut/glut.h"
#include <vector>
#include "ArmSegment.h"


typedef glm::vec3 vec3;
typedef glm::mat4x4 mat4x4;

class Arm {
private:
	std::vector<vec3*> jointList;
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
	void drawObject();
	void IKToTarget(float x, float y, float z);
	vec3 getTipDirection();
};