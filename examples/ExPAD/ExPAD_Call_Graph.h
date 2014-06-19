#ifndef _EXPAD_CALL_GRAPH_H_
#define _EXPAD_CALL_GRAPH_H_

#include <string>
#include <map>
#include "pin++/Routine_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "boost/graph/adjacency_list.hpp"

/**
 * Represent the call graph of a program
 *
 * File: ExPAD_Call_Graph.h
 *
 */

//
// Keep details abot a function
//
struct ExPAD_Routine_Info
{
  UINT32 id_;
  std::string name_;
  std::string image_;
  ADDRINT address_;  
};

/// Boost Graph traits
class ExPAD_Call_Graph_Traits
{
public:
  struct routine_info_t
  {
    typedef boost::vertex_property_tag kind;
  };

  typedef
    boost::property <boost::vertex_name_t, UINT32,
    boost::property <routine_info_t, ExPAD_Routine_Info *> >
    vertex_property;

  typedef boost::property <boost::edge_weight_t, int> edge_property;
};

/// Type defintion of the graph type
typedef
  boost::adjacency_list <boost::vecS,
                         boost::vecS,
                         boost::directedS,
                         ExPAD_Call_Graph_Traits::vertex_property,
                         ExPAD_Call_Graph_Traits::edge_property>
                         ExPAD_Call_Graph_Type;

/**
 * @class ExPAD_Call_Graph
 *
 * Dependency graph between the methods in a program
 */
class ExPAD_Call_Graph
{
public:
  /// Type definition to the vertex descriptor
  typedef boost::graph_traits <ExPAD_Call_Graph_Type>::vertex_descriptor vertex_descriptor;

  /// Type definition to the vertex descriptor
  typedef boost::graph_traits <ExPAD_Call_Graph_Type>::vertex_iterator vertex_iterator;

  /// Type definition of the edge descriptor
  typedef boost::graph_traits <ExPAD_Call_Graph_Type>::edge_descriptor edge_descriptor;

  /// Type definition of the adjacency iterator
  typedef boost::graph_traits <ExPAD_Call_Graph_Type>::adjacency_iterator adjacency_iterator;

  /// Default constructor
  ExPAD_Call_Graph (void);

  /**
   * Initializing constructor
   *
   * @param[in]         name        Name of the graph
   */
  ExPAD_Call_Graph (const std::string & name);

  /// Desturctor
  ~ExPAD_Call_Graph (void);

  /**
   * Connect method
   *
   * @param[in]     caller_id    Caller of the function
   * @param[in]     callee_id    Called function
   */
  bool connect (UINT32 caller_id, UINT32 callee_id);

  /**
   * Insert a vertex into the graph
   *
   * @param[in]     func_id    Unique Id represening the fucntion
   * @param[in]     routine_info    Function details
   */
  void insert_vertex (UINT32 func_id, ExPAD_Routine_Info * routine_info);

  /**
   * Get the vertex descriptor for a given function id
   *
   * @param[in]     func_id    Unique Id represening the fucntion
   * @return[out]   vertex_descriptor
   */
  vertex_descriptor find_vertex (UINT32 func_id);

  // Return the name of the graph
  const std::string & name (void) const;

  /**
   * Set the name of the graph
   *
   * @param[in]       name        The new name of the graph
   */
  void name (const std::string & name);

  /// Get the routine info corresponding to a vertex in the grpah
  ExPAD_Routine_Info * get_routine_info (vertex_descriptor vertex) const;

  /// Get the Graph type
  const ExPAD_Call_Graph_Type & graph (void) const;

 
private:

  typedef std::map <UINT32, vertex_descriptor> VERTEX_MAP;

  /// Local cache of the vertices
  VERTEX_MAP vertices_;
  
  /// Name of the graph
  std::string name_;

  /// Type of the graph
  ExPAD_Call_Graph_Type graph_;

};

// A cusom Graph writer which will be used in Graphviz writer
template <class ExPAD_Call_Graph_Type> class ExPAD_Vertex_Writer
{
public:
  ExPAD_Vertex_Writer (ExPAD_Call_Graph_Type g) : g_(g) {}

  template <class VertexOrEdge> void operator () (std::ostream & out, const VertexOrEdge & v) const 
  {
    ExPAD_Routine_Info * ri = boost::get (ExPAD_Call_Graph_Traits::routine_info_t (), g_, v);

    std::string name_;
    out << "[id=\"" << ri->id_ << "\", " 
        <<  "name=\"" << ri->name_  << "\", "
        << "label=\"" << ri->id_ <<"\\n" << ri->name_ <<"\"]";
  }

private:
  ExPAD_Call_Graph_Type g_;
};

#include "ExPAD_Call_Graph.inl"

#endif  // !defined _EXPAD_CALL_GRAPH_H_