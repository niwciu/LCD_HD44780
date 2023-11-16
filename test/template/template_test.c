#include "unity/fixture/unity_fixture.h"

// #include "tested_module.h"

TEST_GROUP(template);

TEST_SETUP(template)
{
    /* Init before every test */
}

TEST_TEAR_DOWN(template)
{
    /* Cleanup after every test */
}

TEST(template, FirstTest)
{
    TEST_FAIL_MESSAGE("Implement your test!");
}
