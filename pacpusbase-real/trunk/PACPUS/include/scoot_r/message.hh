#ifndef MESSAGE_H_INCLUDE
#define MESSAGE_H_INCLUDE

#ifndef LANG
#define LANG Fr
#endif

class Message
{
protected:
  char *Fr;
  char *En;
public:
  Message() { 
    Fr = "message non spécifié." ;
    En = "no message.";
  } 
  char *s(){
      return LANG ;
  }
};

#undef FR
#define FR( Y ) Fr = Y;
#undef EN
#define EN( Y ) En = Y ;
#undef MESSAGE
#define MESSAGE( X ,Y) class Message_##X :public Message { public: Message_##X(){ Y } }; extern Message_##X *X;

extern void Create_Messages();
extern void Delete_Messages();

#include "version.mh"
#include "messages.mh"

#endif
