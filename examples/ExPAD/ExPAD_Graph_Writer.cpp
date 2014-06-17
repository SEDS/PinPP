#include "ExPAD_Graph_Writer.h"

void ExPAD_Simple_Graph_Writer::
write_graph (std::ostream & ostr, const ExPAD_Call_Graph & cg)
{
  ExPAD_Call_Graph::vertex_iterator iter, iter_end;

  boost::tie (iter, iter_end) = boost::vertices (cg.graph ());

  for (; iter != iter_end; iter++)
  {
    ExPAD_Call_Graph::adjacency_iterator ai_iter, ai_iter_end;

    boost::tie (ai_iter, ai_iter_end) = boost::adjacent_vertices (*iter, cg.graph ());

    for (; ai_iter != ai_iter_end; ai_iter++)
    {
      ExPAD_Call_Graph::vertex_descriptor src, dst;
      src = *iter;
      dst = *ai_iter;
      
      bool found;
      ExPAD_Call_Graph::edge_descriptor e;
      boost::tie (e, found) = boost::edge (src, dst, cg.graph ());
      int weight = boost::get (boost::edge_weight_t (), cg.graph (), e);
      ostr << src << " " << dst << " " << weight << std::endl;
    }
  }
}