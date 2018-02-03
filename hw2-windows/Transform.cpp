// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#include <iostream>

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
	const vec3 nAxis = glm::normalize(axis);
	const float radians = glm::radians(degrees);
	return cos(radians) * mat3(1, 0, 0, 0, 1, 0, 0, 0, 1) +
		(1 - cos(radians)) * mat3(
			nAxis.x * nAxis.x, nAxis.x * nAxis.y, nAxis.x * nAxis.z,
			nAxis.x * nAxis.y, nAxis.y * nAxis.y, nAxis.y * nAxis.z,
			nAxis.x * nAxis.z, nAxis.y * nAxis.z, nAxis.z * nAxis.z
		)
		+ sin(radians) * mat3(0, nAxis.z, -nAxis.y, -nAxis.z, 0, nAxis.x, nAxis.y, -nAxis.x, 0);
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	eye = rotate(degrees, up)*eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	vec3 axis = glm::normalize(glm::cross(up, eye));
	eye = rotate(degrees, -axis)*eye;
	up = glm::normalize(glm::cross(eye, axis));
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	vec3& w = glm::normalize(eye);
	vec3& u = glm::normalize(glm::cross(up, w));
	vec3& v = glm::cross(w, u);

	mat4 r = mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0, 0, 0, 1);
	mat4 t = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1);

	return t*r;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.

	float theta = glm::radians(fovy / 2);
	float d = glm::cos(theta) / glm::sin(theta);
	float a = -(zFar + zNear) / (zFar - zNear);
	float b = -(2 * zFar * zNear) / (zFar - zNear);

	mat4 ret = mat4(d / aspect, 0, 0, 0,
		0, d, 0, 0,
		0, 0, a, -1,
		0, 0, b, 0);

    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
	// YOUR CODE FOR HW2 HERE
	mat4 ret = mat4(sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1);

    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
	// YOUR CODE FOR HW2 HERE
    mat4 ret = mat4(1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					tx, ty, tz, 1);
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
