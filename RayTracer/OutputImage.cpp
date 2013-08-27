#include "StdAfx.h"
#include "OutputImage.h"
#include "Essential.h"
#include <fstream>

OutputImage::OutputImage(int width, int height, float fieldOfView)
	: width(width), height(height), fieldOfView(fieldOfView)
{
	aspectRatio = (float) width / height;
	image = new Vector[width * height];
}


OutputImage::~OutputImage(void)
{
	delete [] image;
}

void OutputImage::saveToPPM(const char *path) const
{
	std::ofstream ofs(path, std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for(unsigned i = 0; i < width * height; ++i)
	{
		ofs << (unsigned char)(efl::min<float>(1.0f, image[i].x) * 255) << 
			(unsigned char)(efl::min<float>(1.0f, image[i].y) * 255) <<
			(unsigned char)(efl::min<float>(1.0f, image[i].z) * 255); 
	}
	ofs.close();
}
