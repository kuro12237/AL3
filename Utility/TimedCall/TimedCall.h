#pragma once

#include <functional>
#include <stdint.h>
#include <stdio.h>

class TimedCall {
public:
	
	TimedCall(std::function<void()> f, uint32_t time);

	~TimedCall();

	void Update();

	bool GetIsTimefinish() { return IsTimerFinish_; }

private:
	std::function<void()> f_;
	uint32_t timer_;

	bool IsTimerFinish_ = false;
};