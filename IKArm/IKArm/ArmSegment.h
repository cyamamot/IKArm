/*
Class defining a single arm segment comprising the full IKArm
Contains list of joints, involved points, and child segments
Responsible for drawing itself onto the canvas
*/
#pragma once

#include <iostream>
#include "../IKArm/Dependencies/glm/glm.hpp"
#include "../IKArm/Dependencies/glew/glew.h"
#include "../IKArm/Dependencies/glut/glut.h"
#include <vector>
#include "../IKArm/Dependencies/glm/ext.hpp"


typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat4x4 mat4x4;
typedef glm::mat3x3 mat3x3;

const float pi = 3.14159265359;

class ArmSegment {
private:
	float length; //length of arm segment
	vec3* pivotJoint; //point around which segment rotates
	vec3* endJoint;
	ArmSegment* nextSegment; //pointer to next segment
	std::vector<vec3*> points; //list of vertices of component
	std::vector<int> indices; //list of indices in points list

public:
	ArmSegment(vec3*& pivot, vec3*& end);
	void setNextSegment(ArmSegment*& next);
	float getLength();
	vec3* getPivotJoint();
	vec3* getEndJoint();
	void rotate(vec3 R, mat4x4& rotMat, mat4x4& transMat);
	void draw();
};
