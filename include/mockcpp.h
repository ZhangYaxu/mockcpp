
#ifndef __MOCKCPP_H
#define __MOCKCPP_H

#include <assert.h>
#include <sstream>

#if !defined(MOCKCPP_NO_NAMESPACE)
# define MOCKCPP_NS mockcpp
# define MOCKCPP_NS_START namespace MOCKCPP_NS{
# define MOCKCPP_NS_END }
#else
# define MOCKCPP_NS 
# define MOCKCPP_NS_START 
# define MOCKCPP_NS_END 
#endif

#define MOCKCPP_ASSERT(expr) assert(expr)

typedef std::ostringstream oss_t;

#endif // __MOCKCPP_H

