#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include "include/Graph.hpp"

TEST_CASE("Graph initialization") {
  Graph g();
  // REQUIRE();
  std::cout << "Yahoo" << std::endl;
}
