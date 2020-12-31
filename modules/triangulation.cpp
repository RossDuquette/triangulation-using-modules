#include <stdlib.h>
#include <math.h>

#include "topics.h"
#include "triangulation.h"

static float distance(Point pos1, Point pos2)
{
    float del_x = pos1.x - pos2.x;
    float del_y = pos1.y - pos2.y;
    return sqrt(del_x * del_x + del_y * del_y);
}

static Point get_circle_intersections(Circle circ1, Circle circ2,
                                       Circle comparator)
{
    Point intersection;
    float centerdx = circ1.x - circ2.x;
    float centerdy = circ1.y - circ2.y;
    // Distance between circle centers
    float R = sqrt(centerdx * centerdx + centerdy * centerdy);
    if (circ1.r > (R + circ2.r)) {
        // Circle 2 enclosed in circle 1
        intersection.x
            = circ2.x - centerdx * (circ1.r - R - circ2.r) / R;
        intersection.y
            = circ2.y - centerdy * (circ1.r - R - circ2.r) / R;
    } else if (circ2.r > (R + circ1.r)) {
        // Circle 1 enclosed in circle 2
        intersection.x
            = circ1.x + centerdx * (circ2.r - R - circ1.r) / R;
        intersection.y
            = circ1.y + centerdy * (circ2.r - R - circ1.r) / R;
    } else if (R > (circ1.r + circ2.r)) {
        // Imaginary intersection between small circles
        intersection.x = (circ1.x * circ2.r + circ2.x * circ1.r)
            / (circ1.r + circ2.r);
        intersection.y = (circ1.y * circ2.r + circ2.y * circ1.r)
            / (circ1.r + circ2.r);
    } else { // Two intersections
        // From https://gist.github.com/jupdike/bfe5eb23d1c395d8a0a1a4ddd94882ac
        Point intersections[2];
        float R2 = R * R;
        float R4 = R2 * R2;
        float r_diff2 = circ1.r * circ1.r
            - circ2.r * circ2.r;
        float a = r_diff2 / (2 * R2);
        float c = sqrt(2 * (circ1.r * circ1.r + circ2.r * circ2.r)
                       / R2 - (r_diff2 * r_diff2) / R4 - 1);

        float fx = (circ1.x + circ2.x) / 2.0 + a * (circ2.x - circ1.x);
        float gx = c * (circ2.y - circ1.y) / 2.0;
        intersections[0].x = fx + gx;
        intersections[1].x = fx - gx;

        float fy = (circ1.y + circ2.y) / 2.0 + a * (circ2.y - circ1.y);
        float gy = c * (circ1.x - circ2.x) / 2.0;
        intersections[0].y = fy + gy;
        intersections[1].y = fy - gy;

        Point center3(comparator.x, comparator.y);
        float diff1 = distance(intersections[0], center3) - comparator.r;
        float diff2 = distance(intersections[1], center3) - comparator.r;
        if (std::abs(diff1) < std::abs(diff2)) {
            intersection = intersections[0];
        } else {
            intersection = intersections[1];
        }
    }
    return intersection;
}

Point triangulation(Circle circ1, Circle circ2, Circle circ3)
{
    Point intersections[3];
    intersections[0] = get_circle_intersections(circ1, circ2, circ3);
    intersections[1] = get_circle_intersections(circ1, circ3, circ2);
    intersections[2] = get_circle_intersections(circ2, circ3, circ1);

    Point avg;
    for (int i = 0; i < 3; i++) {
        avg.x += intersections[i].x / 3.0;
        avg.y += intersections[i].y / 3.0;
    }
    return avg;
}
