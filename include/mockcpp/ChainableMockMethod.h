/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Any.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/Invokable.h>
#include <mockcpp/Result.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

class SelfDescribe;

template <typename RT>
class ChainableMockMethodBase
{
public:
    ChainableMockMethodBase(Invokable* invokable_)
		: invokable(invokable_)
    {}

    RT operator()( const std::string& nameOfCaller
                 , const RefAny& p01 = RefAny()
                 , const RefAny& p02 = RefAny()
                 , const RefAny& p03 = RefAny()
                 , const RefAny& p04 = RefAny()
                 , const RefAny& p05 = RefAny()
                 , const RefAny& p06 = RefAny()
                 , const RefAny& p07 = RefAny()
                 , const RefAny& p08 = RefAny()
                 , const RefAny& p09 = RefAny()
                 , const RefAny& p10 = RefAny()
                 , const RefAny& p11 = RefAny()
                 , const RefAny& p12 = RefAny()
    )
    {
       SelfDescribe* resultProvider = 0;

       Any anyResult = invokable->invoke( nameOfCaller
                                        , p01, p02, p03, p04, p05, p06
                                        , p07, p08, p09, p10, p11, p12
                                        , resultProvider);

       Result result(typeid(RT), TypeString<RT>::value(), resultProvider);

       return getResult(result.getResult(anyResult));
    }

    virtual ~ChainableMockMethodBase() {}

protected:

    virtual RT getResult(const Any& result) = 0;

private:

    Invokable* invokable;
};


//////////////////////////////////////////////////////////////////
template <typename ReturnType>
class ChainableMockMethod : public ChainableMockMethodBase<ReturnType>
{
    ReturnType getResult(const Any& result)
    {
      if (result.empty())
      {
         return value;
      }

      return any_cast<ReturnType>(result);
    }

public:

    ChainableMockMethod(Invokable* invokable)
		: ChainableMockMethodBase<ReturnType>(invokable)
    {}

private:
	
    typedef typename TypeTraits<ReturnType>::Type nonref;

private:
    nonref value;
};

//////////////////////////////////////////////////////////////////
template <>
class ChainableMockMethod<void> : public ChainableMockMethodBase<void>
{
    void getResult(const Any& result)
    {
    }

public:

    ChainableMockMethod(Invokable* invokable)
		: ChainableMockMethodBase<void>(invokable)
    {}
};

//////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif

