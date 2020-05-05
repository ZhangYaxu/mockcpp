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

#include <mockcpp/MethodIndiceChecker.h>
#include <mockcpp/MethodInfoReader.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/VirtualTableUtils.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////////////////
namespace
{

////////////////////////////////////////////////////////////////////////
struct DummyType {};

const unsigned int invalidIndex = 0xFFFFFFFF;

////////////////////////////////////////////////////////////////////////
struct Indices
{
   unsigned int indexOfVPTR;
   unsigned int indexOfVTBL;

   Indices()
      : indexOfVPTR(invalidIndex)
      , indexOfVTBL(invalidIndex)
   {}
};

///////////////////////////////////////////////////////////////////////
struct VTBL
{
    VTBL();
   ~VTBL();

   void** table;
};

////////////////////////////////////////////////////////////////////////
struct FakeObject
{
   void* vptr[MOCKCPP_MAX_INHERITANCE];
   Indices* indices;

   FakeObject(const std::type_info& info, Indices* ind);

   Indices& getIndices() 
   {
      return *indices;
   }

   ~FakeObject();

   static VTBL vtbl;
};

////////////////////////////////////////////////////////////////////////
VTBL FakeObject::vtbl;

////////////////////////////////////////////////////////////////////////
FakeObject*
getFakeObject(void* caller, unsigned int vptrIndex)
{
   void** vptr = &((void**)caller)[-(int)vptrIndex];
   return (FakeObject*)vptr;
}

////////////////////////////////////////////////////////////////////////
template <int IndexOfVptr, int IndexOfVtbl, typename T>
struct Method
{
   void check(void*)
   {
      FakeObject* fakeObj = getFakeObject(this, IndexOfVptr);
      fakeObj->getIndices().indexOfVPTR = IndexOfVptr;
      fakeObj->getIndices().indexOfVTBL = IndexOfVtbl;
   }
};

///////////////////////////////////////////////////////////////////////
#define MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(I, J) do{ \
   table[getRealVtblIndex(I,J)] = getAddrOfMethod(&Method<I,J,DummyType>::check); \
}while(0)

////////////////////////////////////////////////////////////////////////
VTBL::VTBL()
{
   table = createVtbls(MOCKCPP_MAX_INHERITANCE);
   //#include <mockcpp/MethodIndiceCheckerDef.h>
   MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 0);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 1);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 2);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 3);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 4);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 5);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 6);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 7);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 8);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 9);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 10);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 11);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 12);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 13);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 14);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 15);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 16);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 17);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 18);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(0, 19);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 0);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 1);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 2);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 3);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 4);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 5);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 6);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 7);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 8);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 9);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 10);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 11);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 12);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 13);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 14);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 15);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 16);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 17);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 18);
MOCKCPP_SET_METHOD_INDICE_CHECKER_VTBL(1, 19);

}

////////////////////////////////////////////////////////////////////////
VTBL::~VTBL()
{
   freeVtbls(table, MOCKCPP_MAX_INHERITANCE);
}

////////////////////////////////////////////////////////////////////////
FakeObject::
FakeObject(const std::type_info& info, Indices* ind)
   : indices(ind)
{
   initializeVtbls(vptr, vtbl.table, MOCKCPP_MAX_INHERITANCE, info, false);
}

////////////////////////////////////////////////////////////////////////
FakeObject::
~FakeObject()
{
}

///////////////////////////////////////////////////////////////////////
struct MethodIndiceCheckerImpl
   : public MethodIndiceChecker
{
   MethodIndiceCheckerImpl(const std::type_info& info)
      : obj(new FakeObject(info, &indices))
   {
   }

   void* getObject() const
   { return obj; }

   bool getIndice
      ( bool objDeleted
      , unsigned int& vptrIndex
      , unsigned int& vtblIndex)
   {
      vptrIndex = indices.indexOfVPTR;
      vtblIndex = indices.indexOfVTBL;

      if(vptrIndex == invalidIndex)
      {
         if(!objDeleted) delete obj;

         obj = 0;
         return false;
      }

      delete obj;
      obj = 0;

      return true;
   }

   ~MethodIndiceCheckerImpl()
   {
      if(obj != 0) delete obj;
   }

private:
   FakeObject* obj;
   Indices     indices;
};

////////////////////////////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////
MethodIndiceChecker* createMethodIndiceChecker(const std::type_info& info)
{
   return new MethodIndiceCheckerImpl(info);
}

///////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

