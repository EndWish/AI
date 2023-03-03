#pragma once
#include "fsm/State.h"

class Child;

//-----------------------------------------------------------------------------
class ChildGlobalState : public State<Child> {
private:

	ChildGlobalState() {}

	//copy ctor and assignment should be private
	ChildGlobalState(const ChildGlobalState&);
	ChildGlobalState& operator=(const ChildGlobalState&);

public:

	//this is a singleton
	static ChildGlobalState* Instance();

	virtual void Enter(Child* child) {}

	virtual void Execute(Child* child);

	virtual void Exit(Child* child) {}

	virtual bool OnMessage(Child* child, const Telegram& msg);
};

//-----------------------------------------------------------------------------
class SleepOrRest : public State<Child> {
private:

	SleepOrRest() {}

	//copy ctor and assignment should be private
	SleepOrRest(const SleepOrRest&);
	SleepOrRest& operator=(const SleepOrRest&);

public:

	//this is a singleton
	static SleepOrRest* Instance();

	virtual void Enter(Child* child);

	virtual void Execute(Child* child);

	virtual void Exit(Child* child);

	virtual bool OnMessage(Child* child, const Telegram& msg);

};

//-----------------------------------------------------------------------------
class Study : public State<Child> {
private:

	Study() {}

	//copy ctor and assignment should be private
	Study(const Study&);
	Study& operator=(const Study&);

public:

	//this is a singleton
	static Study* Instance();

	virtual void Enter(Child* child);

	virtual void Execute(Child* child);

	virtual void Exit(Child* child);

	virtual bool OnMessage(Child* child, const Telegram& msg);

};

//-----------------------------------------------------------------------------
class PlayInThePCRoom : public State<Child> {
private:

	PlayInThePCRoom() {}

	//copy ctor and assignment should be private
	PlayInThePCRoom(const PlayInThePCRoom&);
	PlayInThePCRoom& operator=(const PlayInThePCRoom&);

public:

	//this is a singleton
	static PlayInThePCRoom* Instance();

	virtual void Enter(Child* child);

	virtual void Execute(Child* child);

	virtual void Exit(Child* child);

	virtual bool OnMessage(Child* child, const Telegram& msg);

};

//-----------------------------------------------------------------------------
class Sick : public State<Child> {
private:

	Sick() {}

	//copy ctor and assignment should be private
	Sick(const Sick&);
	Sick& operator=(const Sick&);

public:

	//this is a singleton
	static Sick* Instance();

	virtual void Enter(Child* child);

	virtual void Execute(Child* child);

	virtual void Exit(Child* child);

	virtual bool OnMessage(Child* child, const Telegram& msg);

};