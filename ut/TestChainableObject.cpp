
#include <cppunit/extensions/HelperMacros.h>
#include <Any.h>
#include <ChainableMockObject.h>
#include <Namespace.h>
#include <InvocationMockBuilder.h>
#include <ChainingMockHelper.h>

using namespace mockcpp;

class Foo : public ChainableMockObject
{
public:
	Foo(Namespace* ns = 0)
		: ChainableMockObject("Foo", ns)
	{}

	int foo(int& i, unsigned long j)
	{
		return invoke<int>("foo")(i, j);
	}
};

class TestChainableObject : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestChainableObject );
	CPPUNIT_TEST( testShouldFailIfInvokedTimesIsMoreThanExpectedTimes );
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	void testShouldFailIfInvokedTimesIsMoreThanExpectedTimes()
   {
		Foo foo;

		foo.method("foo")
         .expects(exactly(2))
         .with(eq(1), eq((unsigned long)4))
	      .will(returnValue(3));

		foo.method("foo")
         .expects(never())
         .with(eq(2), eq((unsigned long)2))
	      .will(returnValue(10));

		int i = 1;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
		foo.verify();
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestChainableObject );
