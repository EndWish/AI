#ifndef STATE_H
#define STATE_H
//------------------------------------------------------------------------
//
//  Name:   State.h
//
//  Desc:   abstract base class to define an interface for a state
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
 
// 기존에는 Miner밖에 못섰기 때문에 템플릿을 이용하였다.
// 전역 상태 : 어느 때라도 발생할 수 있는 상태
// Miner::Update에 넣거나 모든 상태에 복사된 조건 논리를 추가하는 것은 안좋은 방법
// FSM이 갱신될 때마다 호출되는 전역 상태를 생성
// 
template <class entity_type>
class State
{
public:

  virtual ~State(){}

  //this will execute when the state is entered
  virtual void Enter(entity_type*)=0;

  //this is the states normal update function
  virtual void Execute(entity_type*)=0;

  //this will execute when the state is exited. (My word, isn't
  //life full of surprises... ;o))
  virtual void Exit(entity_type*)=0;
};

#endif