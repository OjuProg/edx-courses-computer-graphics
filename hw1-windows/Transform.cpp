// Transform.cpp: implementation of the Transform class.
#include <iostream>

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
		return cos(glm::radians(degrees)) * mat3(1, 0, 0, 0, 1, 0, 0, 0, 1) +
				(1 - cos(glm::radians(degrees))) * mat3(
						axis.x * axis.x, axis.x * axis.y, axis.x * axis.z,
						axis.x * axis.y, axis.y * axis.y, axis.y * axis.z,
						axis.x * axis.z, axis.y * axis.z, axis.z * axis.z
				)
				+ sin(glm::radians(degrees)) * mat3(0, axis.z, -axis.y, -axis.z, 0, axis.x, axis.y, -axis.x, 0);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	eye = rotate(degrees, up)*eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 axis = glm::normalize(glm::cross(up, eye));
	eye = rotate(degrees, -axis)*eye;
	up = glm::normalize(glm::cross(eye, axis));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	vec3& w = glm::normalize(eye);
	vec3& u = glm::normalize(glm::cross(up, w));
	vec3& v = glm::cross(w, u);

	mat4 r = mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0, 0, 0, 1);
	mat4 t = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1);

	return t*r;
}