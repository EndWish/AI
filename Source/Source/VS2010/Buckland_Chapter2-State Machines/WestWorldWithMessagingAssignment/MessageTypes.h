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
    
    return "�Ƶ�, �뵷 ���·� ��������."; 

  case Msg_DinnerIsReady:
      return "����Ļ� �غ�Ϸ� �ƾ��.";

  case Msg_HiHoneyImHome:
    return "���� �ٳ�Ծ�";

  default:

    return "Not recognized!";
  }
}

#endif