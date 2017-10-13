#pragma once

#include <iostream>
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glew/glew.h"
#include "Dependencies/glut/glut.h"
#include <vector>

typedef glm::vec3 vec3;

class TargetPoint {
private:
	vec3* currPos;
	vec3* gridPos;
	float moveAmount;

public:
	TargetPoint();
	float getPos(int i);
	void plusX();
	void minusX();
	void plusY();
	void minusY();
	void plusZ();
	void minusZ();
	void draw();
	void set(vec3 pos);
};
