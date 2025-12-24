/*
Vorobyev Dmitriy | st140149@student.spbu.ru
LabWork 1
*/


#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

class ImageProcessor
{
public:
    virtual void rotate_clockwise_90() = 0;
    virtual void rotate_counter_clockwise_90() = 0;
    virtual void apply_gaussian_filter() = 0;

    virtual ~ImageProcessor();
};

#endif