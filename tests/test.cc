// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <mylibrary/model.h>

using namespace mylibrary;


TEST_CASE("IsValidFile") {
    SECTION("Valid File JPG") {
        REQUIRE(IsValidFile("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/blurryimage.jpg"));
    }
    SECTION("Valid File PNG") {
        REQUIRE(IsValidFile("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/test.png"));
    }
    SECTION("Valid File JPEG") {
        REQUIRE(IsValidFile("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/replace.jpeg"));
    }
}

TEST_CASE("IsInvalidFile") {
    SECTION("Invalid File JPG") {
        REQUIRE(!IsValidFile("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/blurryimages.jpg"));
    }
    SECTION("Invalid File PNG") {
        REQUIRE(!IsValidFile("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/tests.png"));
    }
    SECTION("Invalid File JPEG") {
        REQUIRE(!IsValidFile("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/replacements.jpeg"));
    }
    SECTION("File Does Not Exist Non Image") {
        REQUIRE(!IsValidFile("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/words.txt"));
    }
    SECTION("Files Exist Non Image") {
        REQUIRE(!IsValidFile("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/testFile.txt"));
    }
}

TEST_CASE("Valid Compression Value") {
    Mat image_cv = imread("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/test1.jpeg", IMREAD_GRAYSCALE);

    SECTION("k = 1.0") {
        REQUIRE(CompressImage(image_cv, 1));
    }
    SECTION("k = 0") {
        REQUIRE(CompressImage(image_cv, 0));
    }
    SECTION("k > 0 && k < 1") {
        REQUIRE(CompressImage(image_cv, .85));
    }

}

TEST_CASE("Invalid Compression Value") {
    Mat image_cv = imread("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/test1.jpeg", IMREAD_GRAYSCALE);

    SECTION("k = -.5") {
        REQUIRE(!CompressImage(image_cv, -.5 ));
    }
    SECTION("k = 1.5") {
        REQUIRE(!CompressImage(image_cv, 1.5));
    }

}
