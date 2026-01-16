#include <doctest/doctest.h>
#include <atlas/parser.h>
#include <stdexcept>

using atlas::parser;

TEST_CASE("parser adds https scheme when missing") {
    const char* argv[] = {
        "atlas",
        "example.com"
    };

    std::string result = parser(2, const_cast<char**>(argv));

    CHECK(result.starts_with("https://"));
    CHECK(result.find("example.com") != std::string::npos);
}

TEST_CASE("parser keeps existing https scheme") {
    const char* argv[] = {
        "atlas",
        "https://example.com"
    };

    std::string result = parser(2, const_cast<char**>(argv));

    CHECK(result == "https://example.com/");
}

TEST_CASE("parser keeps existing http scheme") {
    const char* argv[] = {
        "atlas",
        "http://example.com"
    };

    std::string result = parser(2, const_cast<char**>(argv));

    CHECK(result == "http://example.com/");
}

TEST_CASE("parser normalizes URL") {
    const char* argv[] = {
        "atlas",
        "https://EXAMPLE.com"
    };

    std::string result = parser(2, const_cast<char**>(argv));

    CHECK(result == "https://EXAMPLE.com/");
}

TEST_CASE("parser throws on invalid URL") {
    const char* argv[] = {
        "atlas",
        "http://"
    };

    CHECK_THROWS_AS(
        parser(2, const_cast<char**>(argv)),
        std::invalid_argument
    );
}
