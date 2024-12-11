#include "ImageSegmentation.h"

#include <iostream>

void ImageSegmentation::regionGrowing(CImg<unsigned char> &image, int seedX, int seedY, int threshold, int distanceType) {   
    int rows = image.height();
    int cols = image.width();
    CImg<unsigned char> region(cols, rows, 1, 3, 0); 
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    if (seedX < 0 || seedX >= cols || seedY < 0 || seedY >= rows) {
        throw runtime_error("Seed point is outside the image boundaries.");
    }

    int seedRed = image(seedX, seedY, 0);   // R channel of seed pixel
    int seedGreen = image(seedX, seedY, 1); // G channel of seed pixel
    int seedBlue = image(seedX, seedY, 2);  // B channel of seed pixel

    const array<pair<int, int>, 8> directions = {{
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},   
        {-1, -1}, {1, -1}, {-1, 1}, {1, 1}  
    }};

    queue<pair<int, int>> pixelQueue;  
    pixelQueue.push({seedX, seedY});

    while (!pixelQueue.empty()) {
        auto [x, y] = pixelQueue.front();
        pixelQueue.pop();

        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && !visited[ny][nx]) {
                visited[ny][nx] = true;

                int currentRed = image(nx, ny, 0);
                int currentGreen = image(nx, ny, 1);
                int currentBlue = image(nx, ny, 2);

                double distance = calculateDistance(currentRed, currentGreen, currentBlue, seedRed, seedGreen, seedBlue, distanceType); //calculating distance between the pixel and seed

                if (distance <= threshold) {
                    region(nx, ny, 0) = currentRed; 
                    region(nx, ny, 1) = currentGreen; 
                    region(nx, ny, 2) = currentBlue;

                    pixelQueue.push({nx, ny});
                }
                
            }
        }
    }

    image = region;
}

double ImageSegmentation::calculateDistance(int r1, int g1, int b1, int r2, int g2, int b2, int distanceType) {
    switch (distanceType) {
        case 0: // Euclidean distance
            return sqrt(pow(r1 - r2, 2) + pow(g1 - g2, 2) + pow(b1 - b2, 2));
        case 1: // Manhattan distance (4-connected neighbourhood)
            return abs(r1 - r2) + abs(g1 - g2) + abs(b1 - b2);
        case 2: // Chebyshev distance (8-connected neighbourhood)
            return std::max({abs(r1 - r2), abs(g1 - g2), abs(b1 - b2)});
        default:
            throw std::invalid_argument("Invalid distance type. Use 0 for Euclidean, 1 for Manhattan, or 2 for Chebyshev.");
    }
}
