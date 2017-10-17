/*
Class defining the target point on the grid which the IKArm attempts to reach on the canvas
Colored Red if unreachable, Green if reachable
Shows target in 3D space as well as its corresponding 2D location
*/
#pragma once

#include <iostream>
#include "../IKArm/Dependencies/glm/glm.hpp"
#include "../IKArm/Dependencies/glew/glew.h"
#include "../IKArm/Dependencies/glut/glut.h"
#include <vector>

typedef glm::vec3 vec3;

class TargetPoint 
{
private:
	//actual position in 3D space
	vec3* currPos;
	//position overlaid on 2D grid
	vec3* gridPos;
	//amount to move by
	float moveAmount;

public:
	TargetPoint();
	float getPos(int i);
	//movement of point in 3D using specified controls
	void plusX();
	void minusX();
	void plusY();
	void minusY();
	void plusZ();
	void minusZ();
	void draw();
	void set(vec3 pos);
};
