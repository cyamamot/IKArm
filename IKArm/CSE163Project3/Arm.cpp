#include "Arm.h"

Arm::Arm() {
	vec3* base = new vec3(0.0f, 0.0f, 0.0f);
	baseCoord = *base;
	vec3* elbow = new vec3(0.0f, 1.0f, 0.0f);
	vec3* wrist = new vec3(0.0f, 1.75f, 0.0f);
	vec3* knuckle = new vec3(0.0f, 2.5f, 0.0f);
	vec3* fingers = new vec3(0.0f, 3.0f, 0.0f);
	E = fingers;
	//create each segment of full arm
	armBase = new ArmSegment(base, elbow);
	upperArm = new ArmSegment(elbow, wrist);
	hand = new ArmSegment(wrist, knuckle);
	finger = new ArmSegment(knuckle, fingers);
	segmentList.push_back(armBase);
	segmentList.push_back(upperArm);
	segmentList.push_back(hand);
	segmentList.push_back(finger);
	totalLength = armBase->getLength() + upperArm->getLength() + hand->getLength() + finger->getLength();
	armBase->setNextSegment(upperArm);
	upperArm->setNextSegment(hand);
	hand->setNextSegment(finger);
	jointList.push_back(base);
	jointList.push_back(elbow);
	jointList.push_back(wrist);
	jointList.push_back(knuckle);
	jointList.push_back(fingers);
}
void Arm::drawObject() {
	glLineWidth(2);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < segmentList.size(); i++) {
		segmentList[i]->draw();
	}
}
void Arm::IKToTarget(float x, float y, float z) {
	D = vec3(x, y, z);
	if (distance(D, baseCoord) > totalLength) {
		return;
	}
	int a = 0;
	while (distance(*E, D) > 0.01 && a < 5) {
		for (int i = segmentList.size() - 1; i >= 0; i--) {
			vec3 R = *(segmentList[i]->getPivotJoint());
			vec3 ER = normalize(*E - R);
			vec3 DR = normalize(D - R);
			vec3 axis = normalize(cross(ER, DR));
			if (glm::isnan(axis[0]) || glm::isnan(axis[1]) || glm::isnan(axis[2])) {
				vec3 temp = vec3(ER[0] - 1.0f, ER[1] - 1.0f, ER[2] - 1.0f);
				axis = cross(ER, temp);
			}
			float theta = (acos(dot(ER, DR)));
			if (glm::isnan(theta)) theta = 1.0f;
			if (axis[2] < 0.0f) {
				theta = -theta;
				axis = -axis;
			}
			mat4x4 rotMat = glm::rotate(theta, axis);
			mat4x4 transMat = glm::translate(mat4x4(1.0f), R);
			segmentList[i]->rotate(R, rotMat, transMat);
		}
		a++;
	}
}
vec3 Arm::getTipDirection() {
	return *jointList[jointList.size() - 1] - *jointList[jointList.size() - 2];
}