#pragma once

#include <iostream>
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glew/glew.h"
#include "Dependencies/glut/glut.h"
#include <vector>
#include "Dependencies/glm/ext.hpp"


typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat4x4 mat4x4;
typedef glm::mat3x3 mat3x3;

const float pi = 3.14159265359;

class ArmSegment {
private:
	float length; //length of arm segment
	vec3* pivotJoint;
	vec3* endJoint;
	ArmSegment* nextSegment;
	std::vector<vec3*> points;
	std::vector<int> indices;

public:
	ArmSegment(vec3*& pivot, vec3*& end);
	void setNextSegment(ArmSegment*& next);
	float getLength();
	vec3* getPivotJoint();
	vec3* getEndJoint();
	void rotate(vec3 R, mat4x4& rotMat, mat4x4& transMat);
	void draw();
};
