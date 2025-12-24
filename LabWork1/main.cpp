/*
Vorobyev Dmitriy | st140149@student.spbu.ru
LabWork 1
*/

#include "BitmapImg.h"
#include <iostream>

int main()
{
    try
    {
        std::cout << "starting processing ..."  << std::endl;
        BitmapImg img;

        img.load_from_file("test_input.bmp");

        img.rotate_clockwise_90();
        img.save_to_file("rotated_cw_output.bmp");

        img.load_from_file("test_input.bmp");
        img.rotate_counter_clockwise_90();
        img.save_to_file("rotated_ccw_output.bmp");

        img.apply_gaussian_filter();
        img.save_to_file("gaussian_filtered_output.bmp");

        std::cout << "processing successfully ended" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}