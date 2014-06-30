#ifndef _EXPAD_GRAPH_WRITER_H_
#define _EXPAD_GRAPH_WRITER_H_

#include <iostream>
#include "ExPAD_Call_Graph.h"
#include "boost/graph/graphviz.hpp"

/// Base class for any graph writer
class ExPAD_Graph_Writer
{
public :
  /// constructor
  ExPAD_Graph_Writer (void);

  /// Destructor
  ~ExPAD_Graph_Writer (void);

  /**
   * Graph writting method
   *
   * @param[in]     ostr  Stream need to nbe output.
   * @param[in]     cg    The graph
   */
  virtual void write_graph (std::ostream & ostr, const ExPAD_Call_Graph & cg) = 0;

};

/// Graphviz graph writer
class ExPAD_Graphviz_Writer : public ExPAD_Graph_Writer
{
public :
  ExPAD_Graphviz_Writer (void);

  ~ExPAD_Graphviz_Writer (void);

  virtual void write_graph (std::ostream & ostr, const ExPAD_Call_Graph & cg);
};

/// A Simple Graph writer
class ExPAD_Simple_Graph_Writer : public ExPAD_Graph_Writer
{
public :

  ExPAD_Simple_Graph_Writer (void);

  ~ExPAD_Simple_Graph_Writer (void);

  virtual void write_graph (std::ostream & ostr, const ExPAD_Call_Graph & cg);
};

#include "ExPAD_Graph_Writer.inl"


#endif