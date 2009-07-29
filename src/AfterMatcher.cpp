
#include <AfterMatcher.h>
#include <InvocationMocker.h>
#include <Asserter.h>
#include <Invocation.h>
#include <InvocationId.h>
#include <ChainableMockMethodCore.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////
AfterMatcher::AfterMatcher( InvocationMocker* previous)
		: previousCall(previous)
{
}

//////////////////////////////////////////////////////
bool AfterMatcher::matches(const Invocation& inv) const
{
    return previousCall? previousCall->hasBeenInvoked() : false;
}

//////////////////////////////////////////////////////
void AfterMatcher::increaseInvoked(const Invocation& inv)
{
}

//////////////////////////////////////////////////////
std::string AfterMatcher::toString() const
{
    return "after";
}

//////////////////////////////////////////////////////
void AfterMatcher::verify() 
{
}

//////////////////////////////////////////////////////
bool AfterMatcher::isCompleted(void) const
{
    return previousCall != 0;
}

//////////////////////////////////////////////////////
void AfterMatcher::setOrderingInvocationMocker(InvocationMocker* mocker)
{
    previousCall = mocker;
}

MOCKCPP_NS_END

