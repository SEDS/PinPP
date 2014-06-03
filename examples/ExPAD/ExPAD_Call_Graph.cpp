#include "ExPAD_Call_Graph.h"
#include "boost/bind.hpp"
// #include "ace/CORBA_macros.h"


ExPAD_Call_Graph::ExPAD_Call_Graph (void)
{

}

ExPAD_Call_Graph::ExPAD_Call_Graph (const std::string & name)
  : name_ (name)
{
}

ExPAD_Call_Graph::~ExPAD_Call_Graph (void)
{

}

//
// connect
//
bool ExPAD_Call_Graph::
connect (UINT32 caller_id, UINT32 callee_id)
{
  vertex_descriptor src = 0, dst = 0;

  VERTEX_MAP::iterator it1 = this->vertices_.find (caller_id);
  VERTEX_MAP::iterator it2 = this->vertices_.find (callee_id);

  if (it1 != this->vertices_.end () &&
    it2 != this->vertices_.end ())
  {
    src = it1->second;
    dst = it2->second;

    edge_descriptor e;
    bool found;
    boost::tie (e, found) = boost::edge (src, dst, this->graph_);

    if (!found)
    {
      boost::add_edge (src, dst, 1, this->graph_);
    }
    else
    {
      int weight = boost::get (boost::edge_weight_t (), this->graph_, e) + 1;
      boost::put (boost::edge_weight_t (), this->graph_, e, weight);
    }
    return true;  
  }
  
  return false;
}

//
// insert_vertex
//
void ExPAD_Call_Graph::
insert_vertex (UINT32 func_id, ExPAD_Routine_Info * routine_info)
{
  // We need to insert the vertex only if it is not in the graph
  
  vertex_descriptor vertex = 0;
  if (this->vertices_.find (func_id) == this->vertices_.end ())
  {
    vertex = boost::add_vertex (this->graph_);
    this->vertices_.insert (std::pair <UINT32, vertex_descriptor> (func_id, vertex));
    boost::put (boost::vertex_name_t (), this->graph_, vertex, func_id);
    boost::put (ExPAD_Call_Graph_Traits::routine_info_t (),
              this->graph_,
              vertex,
              routine_info);
  }
}

//
// Find the vertex descriptor
//

ExPAD_Call_Graph::vertex_descriptor 
ExPAD_Call_Graph::find_vertex (UINT32 func_id)
{
  VERTEX_MAP::iterator it = this->vertices_.find (func_id);

  if (it == this->vertices_.end ())
    return -1;
  else
    return it->second;
}

//
// name
//
const std::string & ExPAD_Call_Graph::name (void) const
{
  return this->name_;
}

//
// name
//

void ExPAD_Call_Graph::name (const std::string & name)
{
  this->name_ = name;
}

//
// get_routine_info
//
ExPAD_Routine_Info *
ExPAD_Call_Graph::get_routine_info (vertex_descriptor vertex) const
{
  return boost::get (ExPAD_Call_Graph_Traits::routine_info_t (),
                     this->graph_,
                     vertex);
}

const ExPAD_Call_Graph_Type & ExPAD_Call_Graph::graph () const
{
  return this->graph_;
}
