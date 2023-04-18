#pragma once
#include <algorithm>
#include <iostream>
#include "bmpmini.hpp"
#include "Platform.h"

#define black 0
#define white 255

struct Vector2 {
	Vector2(float newx, float newy) {
		x = newx;
		y = newy;
	}

	float x = 0, y = 0;
};

struct Line {
	Line(Vector2 newm1, Vector2 newm2) {
		m1 = newm1;
		m2 = newm2;
	}

	Vector2 m1 = { 0,0 }, m2 = { 0,0 };
};

struct Rectangle {
	Line top, left, bottom, right;
};


namespace MapReader {
	void read() {
		image::BMPMini bmp;
		try {
            bmp.read("m_test_1.bmp");
            //bmp.write("lena_color_copy.bmp");
            auto img = bmp.get();
            img.channels = 1;


			int width = img.width;
			int height = img.height;

			std::vector<Vector2> tempVectors = {};
			std::vector<Line> lineSegments = {};

			int inARow = 0;

			int col = 0;
			int row = 0;

			for (auto i : bmp.pixel_data) {
				//std::cout << (int)i << std::endl;

				if (col == 100) {
					tempVectors.clear();
					col = 0;
					row++;
				}

				if (i == black) {
					std::cout << "terrain at " << col << " " << row << std::endl;
					tempVectors.push_back(Vector2(col, row));

					inARow++;
				}
				else if (i == white) {

					if (tempVectors.size() > 0) {
						lineSegments.push_back(Line(tempVectors.at(0), tempVectors.at(tempVectors.size() - 1)));
						tempVectors.clear();
					}
					inARow = 0;
				}

				
				col++;
			}


			for (auto line : lineSegments) {
				//collect all with same x values
				sf::RectangleShape temprect;
				temprect.setPosition({ line.m1.x, line.m1.y });
				temprect.setSize({ line.m2.x - line.m1.x, line.m2.y - line.m1.y });
				PlatformHelper::createPlatform(temprect);
				
			}

			std::cout << "Cur Col: " << col << std::endl;
			std::cout << "Cur Row: " << row + 1 << std::endl;

			std::cout << "Segment count: " << lineSegments.size() << std::endl;
		}
		catch (const std::exception& e) {
            std::cout << e.what() << std::endl;

		}
	}
}