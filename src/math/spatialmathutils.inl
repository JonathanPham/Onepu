// Onepu: Featherstone's Articulated Body Algorithm implementation
// Written by Yining Karl Li
//
// File: spatialmathutils.inl
// Implements some helpful utility functions for spatial math stuff

#ifndef SPATIALMATHUTILS_INL
#define SPATIALMATHUTILS_INL

#include <Eigen/Core>
#include "spatialmath.inl"
#include "../utilities/utilities.h"

#define EIGEN_DEFAULT_TO_ROW_MAJOR

using namespace std;
using namespace Eigen;

namespace spatialmathCore {
//====================================
// Function Declarations
//====================================

//Forward declarations for externed inlineable methods
extern inline stransform6 createSpatialTranslate(const vec3& t);
extern inline stransform6 createSpatialRotate(const float& angle, const int& axisID);
extern inline stransform6 createSpatialRotate(const float& angle, const vec3& axis);

//====================================
// Function Implementations
//====================================

stransform6 createSpatialTranslate(const vec3& t){
	return stransform6(mat3::Identity(), t);
}

//angle is in degrees
stransform6 createSpatialRotate(const float& angle, const vec3& axis){
	float s = sin(angle*PI/180.0f);
	float c = cos(angle*PI/180.0f);
	mat3 r  = createMat3(axis[0] * axis[0] * (1.0f - c) + c,
						 axis[1] * axis[0] * (1.0f - c) + axis[2] * s,
						 axis[0] * axis[2] * (1.0f - c) - axis[1] * s,
						 axis[0] * axis[1] * (1.0f - c) - axis[2] * s,
						 axis[1] * axis[1] * (1.0f - c) + c,
						 axis[1] * axis[2] * (1.0f - c) + axis[0] * s,
						 axis[0] * axis[2] * (1.0f - c) + axis[1] * s,
						 axis[1] * axis[2] * (1.0f - c) - axis[0] * s,
						 axis[2] * axis[2] * (1.0f - c) + c);
	return stransform6(r, vec3(0,0,0));
}

//for axis, 0 = x-axis, 1 = y-axis, 2 = z-axis, angle is in degrees
stransform6 createSpatialRotate(const float& angle, const int& axisID){
	int rotationAxis = max(min(2, axisID),0);
	float s = sin(angle*PI/180.0f);
	float c = cos(angle*PI/180.0f);
	stransform6 result;
	if(rotationAxis==0){
		result = stransform6(createMat3(1.0f, 0.0f, 0.0f, 
									    0.0f,    c,    s, 
									    0.0f,   -s,    c), vec3(0,0,0));
	}else if(rotationAxis==1){
		result = stransform6(createMat3(   c, 0.0f,   -s, 
									    0.0f, 1.0f, 0.0f, 
									       s, 0.0f,    c), vec3(0,0,0));
	}else if(rotationAxis==2){
		result = stransform6(createMat3(   c,    s, 0.0f, 
									      -s,    c, 0.0f, 
									    0.0f, 0.0f, 1.0f), vec3(0,0,0));
	}
	return result;
}
}

#endif
