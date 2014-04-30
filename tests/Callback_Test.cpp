// $Id: inscount1.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Callback.h"
#include "pin++/Trace.h"
#include "pin++/Routine.h"

class callback0 : 
  public OASIS::Pin::Callback <callback0 (void)>
{
public:
  callback0 (void) { }
  void handle_analyze (void) { }
};

class callback1 : 
  public OASIS::Pin::Callback <callback1 (OASIS::Pin::ARG_SYSARG_VALUE)>
{
public:
  callback1 (void) { }
  void handle_analyze (param_type1 p1) { }
};

class callback2 : 
  public OASIS::Pin::Callback <callback2 (OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE)>
{
public:
  callback2 (void) { }
  void handle_analyze (param_type1 p1, param_type2 p2) { }
};

class callback3 : 
  public OASIS::Pin::Callback <callback3 (OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE)>
{
public:
  callback3 (void) { }
  void handle_analyze (param_type1 p1, param_type2 p2, param_type3 p3) { }
};

class callback4 : 
  public OASIS::Pin::Callback <callback4 (OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE)>
{
public:
  callback4 (void) { }
  void handle_analyze (param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4) { }
};

class callback5 : 
  public OASIS::Pin::Callback <callback5 (OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE)>
{
public:
  callback5 (void) { }
  void handle_analyze (param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5) { }
};

class callback6 : 
  public OASIS::Pin::Callback <callback6 (OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE,
                                          OASIS::Pin::ARG_SYSARG_VALUE)>
{
public:
  callback6 (void) { }
  void handle_analyze (param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6) { }
};

///

class Conditional_Test : public OASIS::Pin::Conditional_Callback <Conditional_Test (void)>
{
public:
  bool do_next (void)
  {
    return true;
  }
};

template <typename T>
void test_callback (void)
{
  T::pin_type obj_type;
  T obj (obj_type);

  callback0 c0;
  c0.insert (IPOINT_BEFORE, obj);

  callback1 c1;
  c1.insert (IPOINT_BEFORE, obj, 0);

  callback2 c2;
  c2.insert (IPOINT_BEFORE, obj, 0, 0);

  callback3 c3;
  c3.insert (IPOINT_BEFORE, obj, 0, 0, 0);

  callback4 c4;
  c4.insert (IPOINT_BEFORE, obj, 0, 0, 0, 0);

  callback5 c5;
  c5.insert (IPOINT_BEFORE, obj, 0, 0, 0, 0, 0);

  callback6 c6;
  c6.insert (IPOINT_BEFORE, obj, 0, 0, 0, 0, 0 ,0);
}

template <typename T>
void test_conditional_callback (void)
{
  T::pin_type pin_obj;
  T obj (pin_obj);

  Conditional_Test condition;

  callback0 c0;
  c0[condition].insert (IPOINT_BEFORE, obj);

  callback1 c1;
  c1[condition].insert (IPOINT_BEFORE, obj, 0);

  callback2 c2;
  c2[condition].insert (IPOINT_BEFORE, obj, 0, 0);

  callback3 c3;
  c3[condition].insert (IPOINT_BEFORE, obj, 0, 0, 0);

  callback4 c4;
  c4[condition].insert (IPOINT_BEFORE, obj, 0, 0, 0, 0);

  callback5 c5;
  c5[condition].insert (IPOINT_BEFORE, obj, 0, 0, 0, 0, 0);

  callback6 c6;
  c6[condition].insert (IPOINT_BEFORE, obj, 0, 0, 0, 0, 0 ,0);
}

int main (int argc, char * argv [])
{
  test_callback <OASIS::Pin::Ins> ();
  test_callback <OASIS::Pin::Bbl> ();
  test_callback <OASIS::Pin::Trace> ();
  test_callback <OASIS::Pin::Routine> ();

  test_conditional_callback <OASIS::Pin::Ins> ();
  test_conditional_callback <OASIS::Pin::Bbl> ();
  test_conditional_callback <OASIS::Pin::Trace> ();

  return 0;
}
