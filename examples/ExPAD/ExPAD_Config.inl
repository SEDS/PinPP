inline 
ExPAD_Config::ExPAD_Config (void)
{

}

inline 
ExPAD_Config::~ExPAD_Config (void)
{

}

inline 
void ExPAD_Config::insert_to_dll_includes (std::string & dll_name)
{
  this->dll_includes_.insert (dll_name);
}