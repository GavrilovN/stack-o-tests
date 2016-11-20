#include <stack.hpp>
#include <catch.hpp>
#include <iostream>

SCENARIO("count", "[count]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
}

SCENARIO("push", "[push]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
  REQUIRE(s.top()==1);
}

SCENARIO("pop", "[pop]"){
  stack<int> s;
  s.push(1); s.pop();
  REQUIRE(s.count()==0);
}

SCENARIO("prisv", "[prisv]"){
  stack<int> s;
  s.push(1);
  stack<int> s2;
  s2=s;
  REQUIRE(s.count()==1);
  REQUIRE(s.top()==1);
}

SCENARIO("cop", "[cop]"){
  stack<int> s;
  s.push(1);
  stack<int> s2=s;
  REQUIRE(s2.count()==1);
  REQUIRE(s2.top()==1);
}

SCENARIO("top", "[top]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.top()==1);
}

SCENARIO("empty", "[empty]"){
  stack<int> s1, s2;
  s1.push(1);
  REQUIRE(!s1.empty());
  REQUIRE(s2.empty());
}

class Test
{
public:
  static ssize_t  counter;
  Test()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    ++counter;
  }
  Test( Test const & )
  {
   std::cout << __PRETTY_FUNCTION__ << std::endl;
    ++counter;
  }
  ~Test()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    --counter;
  }
};

ssize_t Test::counter = 0;

SCENARIO("allocator::~allocator") {

  {
    allocator<Test> allocator{ 4 };
    allocator.construct( allocator.get() + 1, Test() );
    allocator.construct( allocator.get() + 2, Test() );

    REQUIRE( Test::counter == 2 );
  }

  REQUIRE( Test::counter == 0 );
}
