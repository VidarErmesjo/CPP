#include "BMP.h"

namespace image {

BMP::BMP(const char *filename) {
    read(filename);
}

BMP::BMP(int32_t width, int32_t height, bool hasAlpha) {
    if (width <= 0 || height <= 0) {
        throw std::runtime_error("The image width and height must be positive numbers.");
    }

    infoHeader.width = width;
    infoHeader.height = height;
    if (hasAlpha) {
        infoHeader.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
        fileHeader.offsetData = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);

        infoHeader.bitCount = 32;
        infoHeader.compression = 3;
        rowStride = width * 4;
        data.resize(rowStride * height);
        fileHeader.fileSize = fileHeader.offsetData + data.size();
    } else {
        infoHeader.size = sizeof(BMPInfoHeader);
        fileHeader.offsetData = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

        infoHeader.bitCount = 24;
        infoHeader.compression = 0;
        rowStride = width * 3;
        data.resize(rowStride * height);

        uint32_t newStride = makeStrideAligned(4);
        fileHeader.fileSize = fileHeader.offsetData + data.size() + infoHeader.height * (newStride - rowStride);
    }
}

void BMP::read(const char *filename) {
    std::ifstream input{filename, std::ios_base::binary};
    
    if (input) {
        input.read((char*) &fileHeader, sizeof(fileHeader));

        if (fileHeader.fileType != 0x4D42) {
            throw std::runtime_error("Error! Unrecognized file format.");
        }

        //printFileHeader();

        input.read((char*) &infoHeader, sizeof(infoHeader));

        //printInfoHeader();
        //printColorHeader();

        // The BMPColorHeader is only used for transparent images
        if (infoHeader.bitCount == 32) {
            // Check if the file has bit mask color information
            if (infoHeader.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader))) {
                input.read((char*) &colorHeader, sizeof(colorHeader));

                // Check if the pixel data is stored as BGRA and if color space type is sRGB
                checkColorHeader(colorHeader);
            } else {
                std::cerr << "Warnig! The file \"" << filename << "\" does not seem to contain bit mask information" << std::endl;
                throw std::runtime_error("Error! Unrecognized file format.");
            }
        }

        // Jump to the pixel data location
        input.seekg(fileHeader.offsetData, input.beg);

        // Adjust the header fields for output.
        // Some editors will put extra info in the image file, we only save the headers and the data.
        if (infoHeader.bitCount == 32) {
            infoHeader.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
            fileHeader.offsetData = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
        }

        fileHeader.fileSize = fileHeader.offsetData;

        if (infoHeader.height < 0) {
            throw std::runtime_error("The program can treat only BMP images with origin in the bottom left corner!");
        }

        data.resize(infoHeader.width * infoHeader.height * infoHeader.bitCount / 8);

        // Here we check if we need to take into account row padding
        if (infoHeader.width % 4 == 0) {
            input.read((char*) data.data(), data.size());
            fileHeader.fileSize += data.size();
        } else {
            rowStride = infoHeader.width * infoHeader.bitCount / 8;
            uint32_t newStride = makeStrideAligned(4);
            std::vector<uint8_t> paddingRow(newStride - rowStride);

            for (int y = 0; y < infoHeader.height; ++y) {
                input.read((char*) (data.data() + rowStride * y), rowStride);
                input.read((char*) paddingRow.data(), paddingRow.size());
            }
            fileHeader.fileSize += data.size() + infoHeader.height * paddingRow.size();
        }
    } else {
        throw std::runtime_error("Unable to open the input image file.");
    }

    input.close();
}

void BMP::write(const char *filename) {
    std::ofstream output{filename, std::ios_base::binary};
    if (output) {
        if (infoHeader.bitCount == 32) {
            writeHeadersAndData(output);
        } else if (infoHeader.bitCount == 24) {
            if (infoHeader.width % 4 == 0) {
                writeHeadersAndData(output);
            } else {
                uint32_t newStride = makeStrideAligned(4);
                std::vector<uint8_t> paddingRow(newStride - rowStride);

                writeHeaders(output);

                for (int y = 0; y < infoHeader.height; ++y) {
                    output.write((const char*) (data.data() + rowStride * y), rowStride);
                    output.write((const char*) paddingRow.data(), paddingRow.size());
                }
            }
        } else {
            throw std::runtime_error("The program can treat only 24 pr 32 bits per pixel");
        }
    } else {
        throw std::runtime_error("Unable to open the output image file.");
    }

    output.close();
}

void BMP::printFileHeader() {
    std::cout << "fileType: " << fileHeader.fileType << std::endl;
    std::cout << "fileSize: " << fileHeader.fileSize << std::endl;
    std::cout << "reserved1: " << fileHeader.reserved1 << std::endl;
    std::cout << "reserved2: " << fileHeader.reserved2 << std::endl;
    std::cout << "offsetData: " << fileHeader.offsetData << std::endl;
}

void BMP::printInfoHeader() {
    std::cout << "size: " << infoHeader.size << std::endl;
    std::cout << "width: " << infoHeader.width << std::endl;
    std::cout << "height: " << infoHeader.height << std::endl;
    std::cout << "bitCount: " << infoHeader.bitCount << std::endl;
    std::cout << "compression: " << infoHeader.compression << std::endl;
    std::cout << "imageSize: " << infoHeader.imageSize << std::endl;
    //std::cout << "height: " << infoHeader.height << std::endl;
}

void BMP::printColorHeader() {
    std::cout << "redMask: " << colorHeader.redMask << std::endl;
    std::cout << "greenMask: " << colorHeader.greenMask << std::endl;
    std::cout << "blueMask: " << colorHeader.blueMask << std::endl;
    std::cout << "alphaMask: " << colorHeader.alphaMask << std::endl;
}

// Check if the pixel data is stored as BGRA and if the color space type is sRGB
void BMP::checkColorHeader(BMPColorHeader &colorHeader) {
    BMPColorHeader expectedColorHeader;
    if (expectedColorHeader.redMask != colorHeader.redMask ||
        expectedColorHeader.blueMask != colorHeader.blueMask ||
        expectedColorHeader.greenMask != colorHeader.greenMask ||
        expectedColorHeader.alphaMask != colorHeader.alphaMask) {
            throw std::runtime_error("Unexpected color mask format! The program expects the pixel data to be in the BGRA format");
    }
    if (expectedColorHeader.colorSpaceType != colorHeader.colorSpaceType) {
        throw std::runtime_error("Unexpected color space type! The program expects sRGB values");
    }
}

void BMP::writeHeaders(std::ofstream &output) {
    output.write((const char*) &fileHeader, sizeof(fileHeader));
    output.write((const char*) &infoHeader, sizeof(infoHeader));
    if (infoHeader.bitCount == 32) {
        output.write((const char*) &colorHeader, sizeof(colorHeader));
    }
}

void BMP::writeHeadersAndData(std::ofstream &output) {
    writeHeaders(output);
    output.write((const  char*) data.data(), data.size());
}

// Add 1 to the rowStride until it is divisible with alignStride
uint32_t BMP::makeStrideAligned(uint32_t alignStride) {
    uint32_t newStride = rowStride;
    while (newStride % alignStride != 0) {
        newStride++;
    }
    return newStride;
}
}