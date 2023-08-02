#include"VectorTransform.h"



Vector3 Multiply(Vector3 v1, Vector3 v2) {
	Vector3 result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return result;
}

Vector3 Substract(Vector3 v1, Vector3 v2)
{
	Vector3 Result;

	Result.x=v1.x - v2.x;
	Result.y=v1.y - v2.y;
	Result.z=v1.z - v2.z;

	return Result; 
}
