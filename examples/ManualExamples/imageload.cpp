// $Id: imageload.cpp 2266 2013-09-10 14:08:35Z hillj $

#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"

#include <fstream>

class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  Instrument (std::ofstream & fout)
    : fout_ (fout)
  {

  }

  void handle_instrument (const OASIS::Pin::Image & img)
  {
    this->fout_ << "Loading " << img.name () << ", Image id = " << img.id () << std::endl;
  }

private:
  std::ofstream & fout_;
};

class imageload : public OASIS::Pin::Tool <imageload>
{
public:
  imageload (void)
    : fout_ ("imageload.out"),
      inst_ (fout_)
  {
    this->enable_unload_callback ();
    this->enable_fini_callback ();
  }

  void handle_unload (const OASIS::Pin::Image & img)
  {
    this->fout_ << "Unloading " << img.name () << std::endl;
  }

  void handle_fini (INT32)
  {
    this->fout_.close ();
  }

private:
  std::ofstream fout_;
  Instrument inst_;
};

DECLARE_PINTOOL (imageload);
