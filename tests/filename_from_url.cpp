#include <doctest/doctest.h>
#include <atlas/filename_from_url.h>

using atlas::filename_from_url;

TEST_CASE("hostname only returns index.html") {
    CHECK(filename_from_url("https://example.com") == "index.html");
    CHECK(filename_from_url("http://example.com") == "index.html");
}

TEST_CASE("hostname with trailing slash returns index.html") {
    CHECK(filename_from_url("https://example.com/") == "index.html");
}

TEST_CASE("simple file path returns filename") {
    CHECK(
        filename_from_url("https://example.com/file.txt")
        == "file.txt"
    );
}

TEST_CASE("nested path returns last segment") {
    CHECK(
        filename_from_url("https://example.com/a/b/c.zip")
        == "c.zip"
    );
}

TEST_CASE("directory path ending with slash returns index.html") {
    CHECK(
        filename_from_url("https://example.com/a/b/")
        == "index.html"
    );
}

TEST_CASE("query string is stripped") {
    CHECK(
        filename_from_url("https://example.com/file.tar.gz?token=123")
        == "file.tar.gz"
    );
}

TEST_CASE("fragment is stripped") {
    CHECK(
        filename_from_url("https://example.com/file.txt#section")
        == "file.txt"
    );
}

TEST_CASE("query and fragment together are stripped") {
    CHECK(
        filename_from_url("https://example.com/file.txt?x=1#y")
        == "file.txt"
    );
}

TEST_CASE("URL without scheme still works") {
    CHECK(
        filename_from_url("example.com/file.bin")
        == "file.bin"
    );
}

TEST_CASE("path without extension returns last segment") {
    CHECK(
        filename_from_url("https://example.com/download")
        == "download"
    );
}

TEST_CASE("double slashes do not break filename extraction") {
    CHECK(
        filename_from_url("https://example.com//file.txt")
        == "file.txt"
    );
}
