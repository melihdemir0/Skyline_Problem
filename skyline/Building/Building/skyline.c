#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_RECTANGLE_COUNT 2000

int main() {
    // Represents point top point coordinates of buildings.
    typedef struct {
        int x;
        int y;
        bool isTopLeftPoint;
    }
    Coordinate;

    // Allocate coordinate array with rectangle count times 2, because
    // there could be 2 top points for each rectangle at most.
    Coordinate coordinateArray[MAX_RECTANGLE_COUNT * 2];

    int numberOfCoordinates = 0;
    int leftmostBottomXPoint = 0;
    int rightmostBottomXPoint = 0;

    bool shouldContinueGettingInput = true;
    do {
        // Get rectangle information.
        int rectangleWidth, rectangleHeight, startingXPoint;
        scanf_s("%d %d %d", &rectangleWidth, &rectangleHeight, &startingXPoint);
        if (rectangleWidth == -1 || rectangleHeight == -1 || startingXPoint == -1) {
            // If rectangle information provided -1 -1 -1 stop getting input.
            shouldContinueGettingInput = false;
        }
        else {
            // Find leftmost and rightmost X coordinate points.
            if (numberOfCoordinates == 0) {
                leftmostBottomXPoint = startingXPoint;
                rightmostBottomXPoint = startingXPoint + rectangleWidth;
            }
            else {
                if (leftmostBottomXPoint > startingXPoint) {
                    leftmostBottomXPoint = startingXPoint;
                }
                if (rightmostBottomXPoint < startingXPoint + rectangleWidth) {
                    rightmostBottomXPoint = startingXPoint + rectangleWidth;
                }
            }

            // Create top left point of the building and save it.
            Coordinate topLeft;
            topLeft.x = startingXPoint;
            topLeft.y = rectangleHeight;
            topLeft.isTopLeftPoint = true;

            coordinateArray[numberOfCoordinates] = topLeft;
            numberOfCoordinates++;

            // Create top right point of the building and save it.
            Coordinate topRight;
            topRight.x = startingXPoint + rectangleWidth;
            topRight.y = rectangleHeight;
            topRight.isTopLeftPoint = false;

            coordinateArray[numberOfCoordinates] = topRight;
            numberOfCoordinates++;
        }

    } while (shouldContinueGettingInput);

    // Create array to hold sorted coordinates by their X points.
    Coordinate sortedCoordinateArray[MAX_RECTANGLE_COUNT * 2];
    int sortingIndex = 0;
    for (int i = 0; i <= rightmostBottomXPoint; i++) {
        for (int j = 0; j < numberOfCoordinates; j++) {
            if (coordinateArray[j].x == i) {
                sortedCoordinateArray[sortingIndex] = coordinateArray[j];
                sortingIndex++;
            }
        }
    }

    Coordinate diagonalCoordinates[MAX_RECTANGLE_COUNT];
    int diagonalIndex = 0;

    // This array will hold all maximum heights.
    // If we deal with a top left point, we will save that height to this array.
    // If we deal with a top right point, we will find that height from this array and remove it.
    int maxHeightArray[MAX_RECTANGLE_COUNT];
    for (int c = 0; c < MAX_RECTANGLE_COUNT; c++) {
        // Initialize all values to zero.
        maxHeightArray[c] = 0;
    }

    // Last changed maximum height.
    int maximumHeight = 0;

    for (int k = 0; k < numberOfCoordinates; k++) {
        // starting point of the rectange top.
        if (sortedCoordinateArray[k].isTopLeftPoint) {
            // if rectange height is taller than last changed max height, we should replace height
            // and save the point.
            if (maximumHeight < sortedCoordinateArray[k].y) {
                maximumHeight = sortedCoordinateArray[k].y;
                diagonalCoordinates[diagonalIndex] = sortedCoordinateArray[k];
                diagonalIndex++;
            }
            for (int d = 0; d < MAX_RECTANGLE_COUNT; d++) {
                // Save the rectangle height anywhere on the array that is zero.
                if (maxHeightArray[d] == 0) {
                    maxHeightArray[d] = sortedCoordinateArray[k].y;
                    break;
                }
            }
        }
        else {
            // ending point of the rectange top.
            for (int r = 0; r < MAX_RECTANGLE_COUNT; r++) {
                // Find and delete the maximum height of ending point from array.
                if (maxHeightArray[r] == sortedCoordinateArray[k].y) {
                    maxHeightArray[r] = 0;
                    break;
                }
            }

            // Find the new maximum height in the array.
            int newMaxPoint = 0;
            for (int y = 0; y < MAX_RECTANGLE_COUNT; y++) {
                if (maxHeightArray[y] > newMaxPoint) {
                    newMaxPoint = maxHeightArray[y];
                }
            }

            // Find the new maximum height changes after removal, we should save that point
            // with the new maximum height.
            if (newMaxPoint != maximumHeight) {
                maximumHeight = newMaxPoint;
                diagonalCoordinates[diagonalIndex].x = sortedCoordinateArray[k].x;
                diagonalCoordinates[diagonalIndex].y = newMaxPoint;
                diagonalIndex++;
            }
        }
    }

    // Print out the diagonal array by adding the opposite side points.
    for (int a = 0; a < diagonalIndex; a++) {
        if (a == 0) {
            // Add leftmost bottom X point, since diagonal coordinates only hold
            // top leftmost and rightmost coordinates.
            printf("%i 0 ", diagonalCoordinates[a].x);
            printf("%i %i ", diagonalCoordinates[a].x, diagonalCoordinates[a].y);
        }
        else {
            // Print top rightmost point.
            printf("%i %i ", diagonalCoordinates[a].x, diagonalCoordinates[a - 1].y);
            // Print the point.
            printf("%i %i ", diagonalCoordinates[a].x, diagonalCoordinates[a].y);
        }
    }
    return 0;
}