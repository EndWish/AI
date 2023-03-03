#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_SonTakeYourPocketMoney,
  Msg_DinnerIsReady,
  Msg_HiHoneyImHome,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_SonTakeYourPocketMoney:
    
    return "아들, 용돈 계좌로 보내놨다."; 

  case Msg_DinnerIsReady:
      return "저녁식사 준비완료 됐어요.";

  case Msg_HiHoneyImHome:
    return "여보 다녀왔어";

  default:

    return "Not recognized!";
  }
}

#endif