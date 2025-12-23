/*
Vorobyev Dmitriy | st140149@student.spbu.ru
LabWork 1
*/

#ifndef BMP_HEADER_H
#define BMP_HEADER_H


struct BMPFileHeader
{
    unsigned short type_;
    unsigned short size_;
    unsigned short off_bits_;

};

struct BMPInfoHeader
{
    unsigned int size_;
    int width_;
    int height_;
    unsigned short plalanes_;
    unsigned short bit_count_;
    unsigned int compression_;
    unsigned int image_size_;
    int resolution_x_;
    int resolution_y_;
    unsigned int colors_;
    unsigned int important_colors_;
};


#endif