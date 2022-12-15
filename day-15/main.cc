#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <stack>
#include <string>
#include <list>
#include <stdbool.h>
#include <unordered_set>
#include <cstring>
#include <utility>
#include <stdint.h>


struct sensor
{
    // Sensor position.
    std::int64_t sx;
    std::int64_t sy;

    // Beacon position.
    std::int64_t bx;
    std::int64_t by;

    // Manhattan distance sensor - beacon
    std::int64_t distance;
};


std::int64_t manhattan_distance(
        std::int64_t ax,
        std::int64_t ay,
        std::int64_t bx,
        std::int64_t by)
{
    return (std::int64_t) std::llabs(ax - bx) + std::llabs(ay - by);
}



// Returns a sensor object from a line formated like so:
// Sensor at x=2924811, y=3544081: closest beacon is at x=3281893, y=3687621
sensor * parse_sensor_line(std::string line)
{
    int sx_pos = line.find("x=") + 2;
    int sx_end = line.find(",");

    int sy_pos = line.find("y=") + 2;
    int sy_end = line.find(":");

    int bx_pos = line.rfind("x=") + 2;
    int bx_end = line.rfind(",");

    int by_pos = line.rfind("y=") + 2;

    std::string sx_str = line.substr(sx_pos, sx_end - sx_pos);
    std::string sy_str = line.substr(sy_pos, sy_end - sy_pos);

    std::string bx_str = line.substr(bx_pos, bx_end - bx_pos);
    std::string by_str = line.substr(by_pos, -1);

    std::int64_t sx = std::stoll(sx_str);
    std::int64_t sy = std::stoll(sy_str);

    std::int64_t bx = std::stoll(bx_str);
    std::int64_t by = std::stoll(by_str);

    sensor *s = new sensor;
    s->sx = sx;
    s->sy = sy;

    s->bx = bx;
    s->by = by;

    s->distance = manhattan_distance(sx, sy, bx, by);
    return s;
}

int main(int argc, char *argv[])
{
    std::vector<sensor*> sensors;
    int key = 0;
    #define Y_SCAN 2000000
    //std::ifstream infile("input.small");
    std::ifstream infile("input.large");
    std::string line;
    while(std::getline(infile, line)) {
        if (line.empty())
            continue;

        sensor *s = parse_sensor_line(line);
        sensors.push_back(s);
    
    }

    // Find min and max bx positions.
    // So that we can frame the board within known bounds.
    std::int64_t bminx = std::numeric_limits<int64_t>::max();
    std::int64_t bmaxx = std::numeric_limits<int64_t>::min();
    for (sensor * s : sensors) {
        bmaxx = s->bx > bmaxx ? s->bx : bmaxx;
        bminx = s->bx < bminx ? s->bx : bminx;
    }

    // PART I 
    int accept = 0;
    for (std::int64_t i = bminx; i < bmaxx ; i++ ) {
        for (sensor * s : sensors) {
            // Distance from sensor to this grid point.
            std::int64_t s_to_p = manhattan_distance(s->sx, s->sy, i, Y_SCAN);

            // If a beacon is here then stop looking at this point.
            if (s->bx == i && s->by == Y_SCAN)
                break;
            // If the distance to this point is less than or equal to the distance
            // of this sensors closest beacon, then we know that a beacon
            // cannot be here.
            if (s_to_p <= s->distance) {
                accept++;
                break;
            }
        }
    }

    std::cout << "Number of discrete points where a beacon cannot exist: ";
    std::cout << accept << std::endl;
}
