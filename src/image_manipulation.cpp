
#include "maincontroller.h"

Image LoadImage (const char* path)
{
        std::ifstream in (path, std::ios::binary);

        std::string s;
        in >> s;

        if (s != "P6") {
                exit (1);
        }

        // Skip comments
        for (;;) {
                getline (in, s);

                if (s.empty ()) {
                        continue;
                }

                if (s [0] != '#') {
                        break;
                }
        }

        std::stringstream str (s);
        int width, height, maxColor;
        str >> width >> height;
        in >> maxColor;

        if (maxColor != 255) {
                exit (1);
        }

        {
                // Skip until end of line
                std::string tmp;
                getline(in, tmp);
        }

        std::vector<char> data (width * height * 3);
        in.read (reinterpret_cast<char*> (data.data ()), data.size ());

        const Image img = { data, width, height };
        return img;
}

void SaveImage (const Image& img, const char* path)
{
        std::ofstream out (path, std::ios::binary);

        out << "P6\n";
        out << img.width << " " << img.height << "\n";
        out << "255\n";
        out.write (img.pixel.data (), img.pixel.size ());
}

Image RGBtoRGBA (const Image& input)
{
        Image result;
        result.width = input.width;
        result.height = input.height;

        for (std::size_t i = 0; i < input.pixel.size (); i += 3) {
                result.pixel.push_back (input.pixel [i + 0]);
                result.pixel.push_back (input.pixel [i + 1]);
                result.pixel.push_back (input.pixel [i + 2]);
                result.pixel.push_back (0);
        }

        return result;
}

Image RGBAtoRGB (const Image& input)
{
        Image result;
        result.width = input.width;
        result.height = input.height;

        for (std::size_t i = 0; i < input.pixel.size (); i += 4) {
                result.pixel.push_back (input.pixel [i + 0]);
                result.pixel.push_back (input.pixel [i + 1]);
                result.pixel.push_back (input.pixel [i + 2]);
        }

        return result;
}
