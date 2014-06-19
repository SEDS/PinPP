#include "ExPAD_Graph_Writer.h"

/// A simple graph writer
// src dest weight
void ExPAD_Simple_Graph_Writer::
write_graph (std::ostream & ostr, const ExPAD_Call_Graph & cg)
{
  auto iter = boost::vertices (cg.graph ());

  std::for_each (iter.first, iter.second,
    [&](ExPAD_Call_Graph::vertex_descriptor v) 
    {
      auto ai_iter = boost::adjacent_vertices (v, cg.graph ());

      std::for_each (ai_iter.first, ai_iter.second, 
        [&, v](ExPAD_Call_Graph::vertex_descriptor u)
        {
           bool found;
           ExPAD_Call_Graph::edge_descriptor e;
           boost::tie (e, found) = boost::edge (v, u, cg.graph ());
           int weight = boost::get (boost::edge_weight_t (), cg.graph (), e);
           ostr << v << " " << u << " " << weight << std::endl;
        } );
     } );
}