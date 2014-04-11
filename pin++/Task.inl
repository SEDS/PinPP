namespace OASIS
{
namespace Pin
{

template <typename T>
inline
Task <T>::Task ()
{
}

template <typename T>
inline
Task <T>::~Task (void)
{
}

template <typename T>
inline
std::list <PIN_THREAD_UID> Task <T>::threads (void)
{
	return ids_;
}

} // namespace OASIS
} // namespace Pin