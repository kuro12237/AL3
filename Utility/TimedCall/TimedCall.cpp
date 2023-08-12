#include "TimedCall.h"

TimedCall::TimedCall(std::function<void()> f, uint32_t time) {
	f_ = f;
	timer_ = time;
}

TimedCall::~TimedCall() {}

void TimedCall::Update() {

	if (IsTimerFinish_) {
		return;
	}

	timer_--;

	if (timer_ <= 0) {
		IsTimerFinish_ = true;
		f_();
	}
}