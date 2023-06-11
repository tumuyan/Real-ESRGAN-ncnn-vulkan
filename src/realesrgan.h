// realesrgan implemented with ncnn library

#ifndef REALESRGAN_H
#define REALESRGAN_H

#include <string>

// ncnn
#include "net.h"
#include "gpu.h"
#include "layer.h"

#include "filesystem_utils.h"
#include <filesystem>
#include <chrono>

using namespace std::chrono;
namespace fs = std::filesystem;

class RealESRGAN
{
public:
    RealESRGAN(int gpuid, bool tta_mode = false);
    ~RealESRGAN();

#if _WIN32
    int load(const std::wstring& parampath, const std::wstring& modelpath);
#else
    int load(const std::string& parampath, const std::string& modelpath);
#endif

    int process(const ncnn::Mat& inimage, ncnn::Mat& outimage, path_t& inpath) const;

public:
    // realesrgan parameters
    int scale;
    int tilesize;
    int prepadding;
    int imgcount;

private:
    ncnn::Net net;
    ncnn::Pipeline* realesrgan_preproc;
    ncnn::Pipeline* realesrgan_postproc;
    ncnn::Layer* bicubic_2x;
    ncnn::Layer* bicubic_3x;
    ncnn::Layer* bicubic_4x;
    bool tta_mode;

};

#endif // REALESRGAN_H
