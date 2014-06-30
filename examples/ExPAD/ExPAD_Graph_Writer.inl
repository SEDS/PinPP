inline 
ExPAD_Graph_Writer::ExPAD_Graph_Writer (void)
{

}

inline 
ExPAD_Graph_Writer::~ExPAD_Graph_Writer (void)
{

}

inline 
ExPAD_Graphviz_Writer::ExPAD_Graphviz_Writer (void)
{

}

inline 
ExPAD_Graphviz_Writer::~ExPAD_Graphviz_Writer (void)
{

}

inline void ExPAD_Graphviz_Writer::
write_graph (std::ostream & ostr, const ExPAD_Call_Graph & cg)
{
  ExPAD_Vertex_Writer<ExPAD_Call_Graph_Type> vw(cg.graph ());
  boost::write_graphviz (ostr, cg.graph (), vw); 
}

inline 
ExPAD_Simple_Graph_Writer::ExPAD_Simple_Graph_Writer (void)
{

}

inline 
ExPAD_Simple_Graph_Writer::~ExPAD_Simple_Graph_Writer (void)
{

}