#include <doctest/doctest.h>
#include <atlas/config/read_config.h>
#include <fstream>
#include <filesystem>

TEST_CASE("read_config reads download_dir correctly") {
    const std::string config_file = "atlas.conf";
    const std::string backup_file = "atlas.conf.bak";
    bool backed_up = false;

    if (std::filesystem::exists(config_file)) {
        std::filesystem::rename(config_file, backup_file);
        backed_up = true;
    }

    {
        std::ofstream out(config_file);
        out << "download_dir=/tmp/atlas\n";
    }

    auto config = atlas::read_config();
    CHECK(config.download_dir == "/tmp/atlas");

    std::filesystem::remove(config_file);
    if (backed_up) {
        std::filesystem::rename(backup_file, config_file);
    }
}

TEST_CASE("read_config handles comments and empty lines") {
    const std::string config_file = "atlas.conf";
    const std::string backup_file = "atlas.conf.bak";
    bool backed_up = false;

    if (std::filesystem::exists(config_file)) {
        std::filesystem::rename(config_file, backup_file);
        backed_up = true;
    }

    {
        std::ofstream out(config_file);
        out << "# This is a comment\n";
        out << "\n";
        out << "download_dir=downloads\n";
    }

    auto config = atlas::read_config();
    CHECK(config.download_dir == "downloads");

    std::filesystem::remove(config_file);
    if (backed_up) {
        std::filesystem::rename(backup_file, config_file);
    }
}

TEST_CASE("read_config handles missing file") {
    const std::string config_file = "atlas.conf";
    const std::string backup_file = "atlas.conf.bak";
    bool backed_up = false;

    if (std::filesystem::exists(config_file)) {
        std::filesystem::rename(config_file, backup_file);
        backed_up = true;
    }

    auto config = atlas::read_config();
    CHECK(config.download_dir == "");

    if (backed_up) {
        std::filesystem::rename(backup_file, config_file);
    }
}
