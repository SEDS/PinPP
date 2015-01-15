// -*- C++ -*-
// my_shared_lib.cpp



/*******************************
 * Dependencies
 *******************************/

#include "my_shared_lib.h"
#include <iostream>



/*******************************
 * Function call
 *******************************/

//
// fn_fibonacci
//
double fn_fibonacci (int num, bool output)
{
  if (num <= 2)
  {
    return 1.0;
  }
  double prev2 = 1.0;
  double prev1 = 1.0;
  double fibonacci = 0.0;
  if (output)
  {
    std::cout << "1: 1" << std::endl;
    std::cout << "2: 1" << std::endl;
  }
  for (int j = 0; j < num-2; ++j)
  {
    fibonacci = prev1 + prev2;
    prev2 = prev1;
    prev1 = fibonacci;
    if (output)
    {
      std::cout << j + 3 << ": " << fibonacci << std::endl;
    }
  }
  return fibonacci;
}


/*******************************
 * Event class
 *******************************/

//
// Greeting (long, char *)
//
Greeting::Greeting (long time, char * content)
  : time_ (time),
    content_ (content)
{
  // do nothing
}

//
// time
//
long Greeting::time (void)
{
  std::cout << "Time (long): " << time_ << std::endl;
  return time_;
}

//
// content
//
char * Greeting::content (void)
{
  std::cout << "Content (char *): " << *content_ << std::endl;
  return content_;
}

//
// push_greeting (Greeting *)
//
void Layer_Context::push_greeting (Greeting * e)
{
  std::cout << "-- Context layer push: Greeting." << std::endl;
}

//
// Hello (long, char *)
//
Hello::Hello (int time, wchar_t * content)
  : time_ (time),
    content_ (content)
{
  // do nothing
}

//
// time
//
int Hello::time (void)
{
  std::cout << "Time (int): " << time_ << std::endl;
  return time_;
}

//
// content
//
wchar_t * Hello::content (void)
{
  std::cout << "Content (wchar_t *): " << *content_ << std::endl;
  return content_;
}

//
// push_hello (Hello *)
//
void Component_Servant::push_hello (Hello * e)
{
  std::cout << "-- Servant layer push: Hello." << std::endl;
}

//
// Message (long, std::string)
//
Message::Message (long time, wchar_t * content)
  : time_ (time),
    content_ (content)
{
  // do nothing
}

//
// time
//
long Message::time (void)
{
  std::cout << "Time (long): " << time_ << std::endl;
  return time_;
}

//
// content
//
wchar_t * Message::content (void)
{
  std::cout << "Content (wchar_t *): " << content_ << std::endl;
  return content_;
}

//
// push_message (Message *)
//
void Laboratory_Application::push_message (Message * e)
{
  std::cout << "-- Application layer push: Message." << std::endl;
}

//
// Random_Message (long)
//
Random_Event::Random_Event (long time)
  : time_ (time)
{
  
}

//
// time
//
long Random_Event::time (void)
{
  std::cout << "Time (long): " << time_ << std::endl;
  return time_;
}

//
// push_random (Random_Message *)
//
void Component_Context::push_random (Random_Event * e)
{
  std::cout << "-- Context layer push: Random_Event." << std::endl;
}
