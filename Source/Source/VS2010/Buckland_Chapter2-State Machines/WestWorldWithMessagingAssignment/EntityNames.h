#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
    ent_Child,
    ent_Father,
    ent_Mother,
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Child:
    return "Child ";

  case ent_Father:
    return "Father"; 

  case ent_Mother:
      return "Mother";

  default:
    return "UNKNOWN!";
  }
}

#endif