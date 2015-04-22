// -*- C++ -*-

//==============================================================================
/**
 *  @file        TLS.h
 *
 *  $Id: TLS.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_TLS_H_
#define _OASIS_PIN_TLS_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class TLS
 *
 * Wrapper class for Thread local storage, also known as Thread-specific
 * storage on most systems.
 *
 * The TLS class is typed to the object type that is stored in the thread
 * local storage. The client has the option of registering a destruction
 * function with the TLS class. This allows the client to destroy any data
 * stored in TLS when the thread terminates.
 *
 * The copy constructor and assignment operator for this class are disabled.
 * If you need to pass this object around, then you must pass it around by
 * reference. Otherwise, the key for the object type will be destroyed, prevent
 * the client from being able store data in the TLS for this type.
 */
template <typename T>
class TLS
{
public:
  /// Default constructor.
  TLS (DESTRUCTFUN destructor = 0);

  /// Destructor.
  ~TLS (void);

  /// Get the object for the current thread.
  T * operator -> (void) const;
 
  /// Get the object for the current thread.
  T * get (void) const;
  
  /**
   * Get the object for a thread from thread-local storage.
   *
   * @param[in]     thr_id        Target thread
   */
  T * get (THREADID thr_id) const;
  
  /**
   * Get the object for the thread from its local storage. If the object
   * does exists, then the factory object will be used to create a new one.
   *
   * The factory is a functor object. This allows developers to use C++11
   * lambda objects when calling this method. The lambda object can capture
   * the state of the caller, and be used to initialize the local data object.
   * The FACTORY should have void -> T * function type signature.
   */
  template <typename FACTORY>
  T * get_with_create (FACTORY factory);
  
  /**
   * Get the object for the thread from its local storage. If the object
   * does exists, then the factory object will be used to create a new one.
   *
   * The factory is a functor object. This allows developers to use C++11
   * lambda objects when calling this method. The lambda object can capture
   * the state of the caller, and be used to initialize the local data object.
   * The FACTORY should have void -> T * function type signature.
   */
  template <typename FACTORY>
  T * get_with_create (THREADID thr_id, FACTORY factory);

  /// Set the data for the current thread.
  void set (T * data);
  
  /**
   * Set the data for a thread.
   *
   * @param[in]     thr_id        Target thread
   */
  void set (THREADID thr_id, T * data);

  /// Test if the value for the current thread is set.
  bool is_set (void) const;
  
  /**
   * Test if the value of a thread is set.
   *
   * @param[in]     thr_id        Target thread
   */
  bool is_set (THREADID thr_id) const;
  
private:
  /// The registered key for the thread-local data object.
  TLS_KEY key_;
  
  // prevent the following operations
  const TLS & operator = (const TLS &);
  TLS (const TLS & rhs);
};

} // namespace OASIS
} // namespace Pin

#include "TLS.inl"

#endif  // _OASIS_PIN_TLS_H_
