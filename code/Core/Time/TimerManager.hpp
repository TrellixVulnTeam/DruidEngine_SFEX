#pragma once

#include "Core/Time/TimeUtils.hpp"
#include "Core/Core.hpp"
#include "Core/Functor.hpp"

enum class TimerDurationType
{
	NONE,
	TIME_AMOUNT,
	NEXT_FRAME
};

CLASS(Timer, ObjectBase)
{
	PRI(Duration, GET, f32)
	PRI(TimeCounter, GET_SET, f32)
	PRI(DurationType, GET, TimerDurationType)
	PUB(Functor, NONE, FunctorVoid)

public:
	void init(f32 duration, TimerDurationType durationType, SFun<void()> callback);
};

CLASS(TimerHandle, ObjectBase)
{
	friend class TimerManager;

	PRI(TimerReference, NONE, Timer *)

public:
	void init(Timer * timerReference)
	{
		mTimerReference = timerReference;
	}

	COPY(TimerHandle)
	{
		DO_COPY(TimerReference)
	}
};

CLASS(TimerManager, ObjectBase), SINGLETON(TimerManager)
{
	PRI(Timers, NONE, SLst<Timer *>);

	void endTimer(Timer * timer);

public:
	~TimerManager() OVR;
	void init();
	TimerHandle setTimer(f32 duration, TimerDurationType durationType, SFun<void()> callback);
	void cancelTimer(CNS TimerHandle &timerHandle);
	void update();
	void terminate();
};