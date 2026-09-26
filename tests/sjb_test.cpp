#include <gtest/gtest.h>

#include "sjb/sjb.hpp"

TEST(Sjb, VersionIsNotEmpty) { EXPECT_FALSE(sjb::version().empty()); }
