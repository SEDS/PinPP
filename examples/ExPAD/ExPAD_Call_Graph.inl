inline 
ExPAD_Call_Graph::ExPAD_Call_Graph (void)
{

}

inline 
ExPAD_Call_Graph::ExPAD_Call_Graph (const std::string & name)
  : name_ (name)
{
}

inline 
ExPAD_Call_Graph::~ExPAD_Call_Graph (void)
{

}

//
// name
//
inline 
const std::string & ExPAD_Call_Graph::name (void) const
{
  return this->name_;
}

//
// name
//

inline 
void ExPAD_Call_Graph::name (const std::string & name)
{
  this->name_ = name;
}

//
// get_routine_info
//
inline 
ExPAD_Routine_Info *
ExPAD_Call_Graph::get_routine_info (vertex_descriptor vertex) const
{
  return boost::get (ExPAD_Call_Graph_Traits::routine_info_t (),
                     this->graph_,
                     vertex);
}

//
// graph
//
inline 
const ExPAD_Call_Graph_Type & ExPAD_Call_Graph::graph () const
{
  return this->graph_;
}
