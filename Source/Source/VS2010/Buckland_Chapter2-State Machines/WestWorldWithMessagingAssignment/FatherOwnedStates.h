#pragma once
#include "fsm/State.h"

class Father;

//-----------------------------------------------------------------------------
class FatherGlobalState : public State<Father> {
private:

	FatherGlobalState() {}

	//copy ctor and assignment should be private
	FatherGlobalState(const FatherGlobalState&);
	FatherGlobalState& operator=(const FatherGlobalState&);

public:

	//this is a singleton
	static FatherGlobalState* Instance();

	virtual void Enter(Father* father) {}

	virtual void Execute(Father* father);

	virtual void Exit(Father* father) {}

	virtual bool OnMessage(Father* father, const Telegram& msg);
};

//-----------------------------------------------------------------------------
class GoHomeAndSsleep : public State<Father> {
private:

	GoHomeAndSsleep() {}

	//copy ctor and assignment should be private
	GoHomeAndSsleep(const GoHomeAndSsleep&);
	GoHomeAndSsleep& operator=(const GoHomeAndSsleep&);

public:

	//this is a singleton
	static GoHomeAndSsleep* Instance();

	virtual void Enter(Father* father);

	virtual void Execute(Father* father);

	virtual void Exit(Father* father);

	virtual bool OnMessage(Father* father, const Telegram& msg);

};

//-----------------------------------------------------------------------------
class WorkForACompany : public State<Father> {
private:

	WorkForACompany() {}

	//copy ctor and assignment should be private
	WorkForACompany(const WorkForACompany&);
	WorkForACompany& operator=(const WorkForACompany&);

public:

	//this is a singleton
	static WorkForACompany* Instance();

	virtual void Enter(Father* father);

	virtual void Execute(Father* father);

	virtual void Exit(Father* father);

	virtual bool OnMessage(Father* father, const Telegram& msg);

};

//-----------------------------------------------------------------------------
class Eat : public State<Father> {
private:

	Eat() {}

	//copy ctor and assignment should be private
	Eat(const Eat&);
	Eat& operator=(const Eat&);

public:

	//this is a singleton
	static Eat* Instance();

	virtual void Enter(Father* father);

	virtual void Execute(Father* father);

	virtual void Exit(Father* father);

	virtual bool OnMessage(Father* father, const Telegram& msg);

};

//-----------------------------------------------------------------------------
class BusinessTrip : public State<Father> {
private:

	BusinessTrip() {}

	//copy ctor and assignment should be private
	BusinessTrip(const BusinessTrip&);
	BusinessTrip& operator=(const BusinessTrip&);

public:

	//this is a singleton
	static BusinessTrip* Instance();

	virtual void Enter(Father* father);

	virtual void Execute(Father* father);

	virtual void Exit(Father* father);

	virtual bool OnMessage(Father* father, const Telegram& msg);

};