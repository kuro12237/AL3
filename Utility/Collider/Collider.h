#pragma once


class Collider {
public:


	float GetRadious() { return radious_; }

	void SetRadious(float radious) { radious_ = radious; }

	virtual Vector3 GetWorldPosition() = 0;

	virtual void OnCollision()=0;

private:


	float radious_ = 3.0f;

};
