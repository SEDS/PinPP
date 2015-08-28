// -*- C++ -*-

namespace OASIS
{
  namespace Pin
  {
    inline
    Constant_Sampling::Constant_Sampling (size_t iters)
    : iters_ (iters),
      curr_iter_ (0)
    {
      
    }
    
    inline
    Constant_Sampling::~Constant_Sampling (void)
    {
      
    }
    
    inline
    size_t Constant_Sampling::current_iteration (void) const
    {
      return this->curr_iter_;
    }
    
    inline
    size_t Constant_Sampling::iterations (void) const
    {
      return this->iters_;
    }
    
    inline
    void Constant_Sampling::iterations (size_t iters)
    {
      this->iters_ = iters;
    }
  }
}