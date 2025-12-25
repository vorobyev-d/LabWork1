/*
Vorobyev Dmitriy | st140149@student.spbu.ru
LabWork 1
*/

#include "BitmapImg.h"
#include <gtest/gtest.h>

TEST(BitmapImgTest, LoadAndSaveTest)
{
    BitmapImg img;

    img.load_from_file("test_input.bmp");
    img.save_to_file("test_output.bmp");

    EXPECT_EQ(img.get_width(), 1000);
    EXPECT_EQ(img.get_height(), 667);
}

TEST(BitmapImgTest, RotateClockwise)
{
    BitmapImg img;

    img.load_from_file("test_input.bmp");
    img.rotate_clockwise_90();
    img.save_to_file("test_rotated_cw.bmp");

    EXPECT_EQ(img.get_width(), 667);
    EXPECT_EQ(img.get_height(), 1000);
}

TEST(BitmapImgTest, RotateCounterClockwise)
{
    BitmapImg img;

    img.load_from_file("test_input.bmp");
    img.rotate_counter_clockwise_90();
    img.save_to_file("test_rotated_ccw.bmp");

    EXPECT_EQ(img.get_width(), 667);
    EXPECT_EQ(img.get_height(), 1000);
}

TEST(BitmapImgTest, ApplyGaussianFilter)
{
    BitmapImg img;

    img.load_from_file("test_input.bmp");
    img.apply_gaussian_filter();
    img.save_to_file("test_gaussian_filtered.bmp");

    EXPECT_EQ(img.get_width(), 1000);
    EXPECT_EQ(img.get_height(), 667);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
