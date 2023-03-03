#pragma once
#include "fsm/State.h"

class Mother;

//-----------------------------------------------------------------------------
class MotherGlobalState : public State<Mother> {
private:

	MotherGlobalState() {}

	//copy ctor and assignment should be private
	MotherGlobalState(const MotherGlobalState&);
	MotherGlobalState& operator=(const MotherGlobalState&);

public:

	//this is a singleton
	static MotherGlobalState* Instance();

	virtual void Enter(Mother* mother) {}

	virtual void Execute(Mother* mother);

	virtual void Exit(Mother* mother) {}

	virtual bool OnMessage(Mother* mother, const Telegram& msg);
};

//-----------------------------------------------------------------------------
class HouseWork : public State<Mother> {
private:

	HouseWork() {}

	//copy ctor and assignment should be private
	HouseWork(const HouseWork&);
	HouseWork& operator=(const HouseWork&);

public:

	//this is a singleton
	static HouseWork* Instance();

	virtual void Enter(Mother* mother);

	virtual void Execute(Mother* mother);

	virtual void Exit(Mother* mother);

	virtual bool OnMessage(Mother* mother, const Telegram& msg);

};

//-----------------------------------------------------------------------------
class Shopping : public State<Mother> {
private:

	Shopping() {}

	//copy ctor and assignment should be private
	Shopping(const Shopping&);
	Shopping& operator=(const Shopping&);

public:

	//this is a singleton
	static Shopping* Instance();

	virtual void Enter(Mother* mother);

	virtual void Execute(Mother* mother);

	virtual void Exit(Mother* mother);

	virtual bool OnMessage(Mother* mother, const Telegram& msg);

};

//-----------------------------------------------------------------------------
class Cook : public State<Mother> {
private:

	Cook() {}

	//copy ctor and assignment should be private
	Cook(const Cook&);
	Cook& operator=(const Cook&);

public:

	//this is a singleton
	static Cook* Instance();

	virtual void Enter(Mother* mother);

	virtual void Execute(Mother* mother);

	virtual void Exit(Mother* mother);

	virtual bool OnMessage(Mother* mother, const Telegram& msg);

};

//-----------------------------------------------------------------------------
class VisitBathroom : public State<Mother> {
private:

	VisitBathroom() {}

	//copy ctor and assignment should be private
	VisitBathroom(const VisitBathroom&);
	VisitBathroom& operator=(const VisitBathroom&);

public:

	//this is a singleton
	static VisitBathroom* Instance();

	virtual void Enter(Mother* mother);

	virtual void Execute(Mother* mother);

	virtual void Exit(Mother* mother);

	virtual bool OnMessage(Mother* mother, const Telegram& msg);

};