#include "TargetPoint.h"

TargetPoint::TargetPoint() {
	currPos = new vec3(0.0f, 3.0f, 0.0f);
	gridPos = new vec3(0.0f, 0.0f, 0.0f);
}
float TargetPoint::getPos(int i) {
	return (*currPos)[i];
}
void TargetPoint::plusX() {
	*currPos = *currPos + vec3(0.05, 0.0, 0.0);
	*gridPos = *gridPos + vec3(0.05, 0.0, 0.0);
}
void TargetPoint::minusX() {
	*currPos = *currPos - vec3(0.05, 0.0, 0.0);
	*gridPos = *gridPos - vec3(0.05, 0.0, 0.0);
}
void TargetPoint::plusY() {
	*currPos = *currPos + vec3(0.0, 0.05, 0.0);
}
void TargetPoint::minusY() {
	*currPos = *currPos - vec3(0.0, 0.05, 0.0);
}
void TargetPoint::plusZ() {
	*currPos = *currPos + vec3(0.0, 0.0, 0.05);
	*gridPos = *gridPos + vec3(0.0, 0.0, 0.05);
}
void TargetPoint::minusZ() {
	*currPos = *currPos - vec3(0.0, 0.0, 0.05);
	*gridPos = *gridPos - vec3(0.0, 0.0, 0.05);
}
void TargetPoint::draw() {
	glPointSize(10);
	glColor3f(0.0, 1.0, 0.0);
	if (distance(*currPos, vec3(0, 0, 0)) > 3.0f) glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f((*currPos)[0], (*currPos)[1], (*currPos)[2]);
	glEnd();
	glBegin(GL_POINTS);
	glVertex3f((*gridPos)[0], (*gridPos)[1], (*gridPos)[2]);
	glEnd();
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex3f((*currPos)[0], (*currPos)[1], (*currPos)[2]);
	glVertex3f((*gridPos)[0], (*gridPos)[1], (*gridPos)[2]);
	glEnd();
}
void TargetPoint::set(vec3 pos) {
	*currPos = pos;
	*gridPos = vec3(pos[0], 0.0f, pos[2]);
}