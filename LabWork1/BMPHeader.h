/*
Vorobyev Dmitriy | st140149@student.spbu.ru
LabWork 1
*/

#ifndef BMP_HEADER_H
#define BMP_HEADER_H

#include <cstdint>

#pragma pack(push, 1)

struct BMPFileHeader
{
    unsigned short type_;
    unsigned int size_;
    unsigned short reserved1_;
    unsigned short reserved2_;
    unsigned int off_bits_;

};

struct BMPInfoHeader
{
    unsigned int size_;
    int width_;
    int height_;
    unsigned short planes_;
    unsigned short bit_count_;
    unsigned int compression_;
    unsigned int image_size_;
    int resolution_x_;
    int resolution_y_;
    unsigned int colors_;
    unsigned int important_colors_;
};

struct Pixel
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
};

#pragma pack(pop)

#endif
