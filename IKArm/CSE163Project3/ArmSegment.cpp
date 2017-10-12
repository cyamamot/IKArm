#include "ArmSegment.h"


ArmSegment::ArmSegment(vec3*& pivot, vec3*& end) {
	pivotJoint = pivot;
	endJoint = end;
	length = distance(*endJoint, *pivotJoint);
	vec3 midpoint = (*endJoint + *pivotJoint) * 0.5f;
	vec3* m1 = new vec3(midpoint[0] + 0.1f, midpoint[1], midpoint[2]);
	vec3* m2 = new vec3(midpoint[0] - 0.1f, midpoint[1], midpoint[2]);
	vec3* m3 = new vec3(midpoint[0], midpoint[1], midpoint[2] + 0.1f);
	vec3* m4 = new vec3(midpoint[0], midpoint[1], midpoint[2] - 0.1f);
	points.push_back(pivotJoint);
	points.push_back(endJoint);
	points.push_back(m1);
	points.push_back(m2);
	points.push_back(m3);
	points.push_back(m4);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(5);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(4);
	indices.push_back(4);
	indices.push_back(3);
	indices.push_back(3);
	indices.push_back(5);
	indices.push_back(5);
	indices.push_back(2);
}
void ArmSegment::setNextSegment(ArmSegment*& next) {
	nextSegment = next;
}
float ArmSegment::getLength() {
	return length;
}
vec3* ArmSegment::getPivotJoint() {
	return pivotJoint;
}
vec3* ArmSegment::getEndJoint() {
	return endJoint;
}
void ArmSegment::rotate(vec3 R, mat4x4& rotMat, mat4x4& transMat) {
	for (int i = 1; i < points.size(); i++) {
		vec3 temp = (transMat * rotMat * inverse(transMat) * vec4(*points[i], 1));
		*points[i] = { temp[0], temp[1], temp[2] };
	}
	length = distance(*endJoint, *pivotJoint);
	if (nextSegment != NULL) nextSegment->rotate(R, rotMat, transMat);
}
void ArmSegment::draw() {
	for (int i = 0; i < indices.size() - 1; i++) {
		glBegin(GL_LINES);
		vec3 bottom = *points[indices[i]];
		vec3 top = *points[indices[i + 1]];
		glVertex3f(bottom[0], bottom[1], bottom[2]);
		glVertex3f(top[0], top[1], top[2]);
		glEnd();
	}
}
