/*
GS
Apr. 2025

A dummy test to check if the gtest framework and build system is working
correctly. Update this with real tests as needed.
*/


// Local includes
// NA, but will be added in the future

// 3rd-party includes
#include "gtest/gtest.h"

// Linux/Unix includes
// NA

// C and C++ includes
// NA

// anonymous namespace
namespace
{

TEST(MainServer, dummyTest)
{
	EXPECT_EQ(1, 2);

	// prove when TESTING is defined
    #ifdef TESTING
	printf(">>> TESTING IS defined! <<<\n\n");
	#else
	printf(">>> TESTING is NOT defined! <<<\n\n");
	#endif
}

} // anonymous namespace
