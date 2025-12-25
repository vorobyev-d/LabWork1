/*
Vorobyev Dmitriy | st140149@student.spbu.ru
LabWork 1
*/

#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <string>

class ImageProcessor
{
public:
    virtual void load_from_file(const std::string& filename) = 0;
    virtual void save_to_file(const std::string& filename) const = 0;

    virtual void rotate_clockwise_90() = 0;
    virtual void rotate_counter_clockwise_90() = 0;
    virtual void apply_gaussian_filter() = 0;

    virtual ~ImageProcessor();
};

#endif
