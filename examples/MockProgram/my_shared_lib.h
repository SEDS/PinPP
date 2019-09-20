// -*- C++ -*-
// my_shared_lib.h

/*******************************
 * Dependencies
 *******************************/

#include <string>  
#include "my_shared_lib_export.h"      // include export header



/*******************************
 * Function call
 *******************************/

MY_SHARED_LIB_Export
double fn_fibonacci (int num, bool output);



/*******************************
 * Event and Component class
 *******************************/

/**
 * Event class for inheritance.
 */
class MY_SHARED_LIB_Export Event
{
  // empty class
};

/**
 * Component class for inheritance.
 */
class MY_SHARED_LIB_Export Component
{
  // empty class
};

/**
 * Greeting event class.
 */
class MY_SHARED_LIB_Export Greeting : public Event
{
public:
  Greeting (long time, char * content);
  long time (void);
  char * content (void);

private:
  long time_;
  char * content_;
};

/**
 * Greeting component class.
 */
class MY_SHARED_LIB_Export Layer_Context : public Component
{
public:
  void push_greeting (Greeting * e);
};

/**
 * Hello event class.
 */
class MY_SHARED_LIB_Export Hello : public Event
{
public:
  Hello (int time, wchar_t * content);
  int time (void);
  wchar_t * content (void);

private:
  int time_;
  wchar_t * content_;
};

/**
 * Hello component class.
 */
class MY_SHARED_LIB_Export Component_Servant : public Component
{
public:
  void push_hello (Hello * e);
};

/**
 * Message event class.
 */
class MY_SHARED_LIB_Export Message : public Event
{
public:
  Message (long time, wchar_t * content);
  long time (void);
  wchar_t * content (void);

private:
  long time_;
  wchar_t * content_;
};

/**
 * Laboratory_Application component class.
 */
class MY_SHARED_LIB_Export Laboratory_Application : public Component
{
public:
  void push_message (Message * e);
};

/**
 * Random event class.
 */
class MY_SHARED_LIB_Export Random_Event : public Event
{
public:
  Random_Event (long time);
  long time (void);

private:
  long time_;
};

/**
 * Component_Context component class.
 */
class MY_SHARED_LIB_Export Component_Context : public Component
{
public:
  void push_random (Random_Event * e);
};
