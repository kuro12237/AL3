#pragma once

#include"Vector3.h"
#include"Matrix4x4.h"
#include<cmath>
#include<cassert>

Vector3 Add(const Vector3 v1, const Vector3 v2);
Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2);

Matrix4x4 MakeScaleMatrix(const Vector3 scale);
Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

float Dot(const Vector3& v1, const Vector3& v2);

float Length(const Vector3& v);

Vector3 Normalize(const Vector3& v);

Matrix4x4 Inverse(const Matrix4x4& m);



/// <summary>
/// 4x4正射影行列
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="right"></param>
/// <param name="bottom"></param>
/// <param name="neaCrlip"></param>
/// <param name="farClip"></param>
/// <returns></returns>

Matrix4x4 MakeOrthographicMatrix(
    float left, float top, float right, float bottom, float neaCrlip, float farClip);
    /// <summary>
/// 4x4ビューポート行列
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="minDepth"></param>
/// <param name="maxDepth"></param>
/// <returns></returns>
Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);