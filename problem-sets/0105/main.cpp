#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

#define DEBUG


struct Skyline {
	int minX;
	int maxX;
	int* heights;
};

struct BuildingDimension {
	int leftx;
	int height;
	int rightx;
};

#ifdef DEBUG
void                        printBuildingDimensions(vector<BuildingDimension*>*);
void                        printDebugSkyline(Skyline* skyline);
#endif


vector<BuildingDimension*>* parseBuildingDimensions();
void                        freeBuildingDimensions(vector<BuildingDimension*>*);
Skyline*                    calculateSkyline(vector<BuildingDimension*>*);
int                         getSkylineIndex(Skyline*, int);
void                        freeSkyline(Skyline*);
void                        printSkyline(Skyline*);

int main(int argc, const char *argv[])
{
	vector<BuildingDimension*>* buildingDimensions = parseBuildingDimensions();
#ifdef DEBUG
	printBuildingDimensions(buildingDimensions);
#endif
	
	Skyline* skyline = calculateSkyline(buildingDimensions);
#ifdef DEBUG
	printDebugSkyline(skyline);
#endif
	printSkyline(skyline);

	freeBuildingDimensions(buildingDimensions);
	freeSkyline(skyline);
	return 0;
}


vector<BuildingDimension*>* parseBuildingDimensions() {
	vector<BuildingDimension*>* buildingDimensions = new vector<BuildingDimension*>();
	int leftx;
	int height;
	int rightx;

	while (fscanf(stdin, "%d %d %d\n", &leftx, &height, &rightx) > 0) {
		BuildingDimension* buildingDimension = new BuildingDimension();
		buildingDimension->leftx = leftx;
		buildingDimension->height = height;
		buildingDimension->rightx = rightx;
		buildingDimensions->push_back(buildingDimension);
	}	 

	return buildingDimensions;
}

void freeBuildingDimensions(vector<BuildingDimension*>* buildingDimensions){
	for(int i = 0; i < buildingDimensions->size(); i++) {
		BuildingDimension* buildingDimension = buildingDimensions->at(i);
		delete buildingDimension;
	}
	delete buildingDimensions;
}

/**
 * Since the max x is 10,000, we can probably keep an array of max(x dimensions),
 * and incrementally compute the max height, building by building.
 * I'm estimating the runtime will be
 * N * 10,000 * 10,000
 * where N is the number of buildings, and 10,000 is the max x dimension.
 * This is because you could have N buildings of length 10,000.
 * The array is critical here because index into the array is O(1) and the
 * array represents the max height found so far at x cordinate i-1
 */
Skyline* calculateSkyline(vector<BuildingDimension*>* buildingDimensions) {
	Skyline* skyline = new Skyline();
	skyline->minX = INT_MAX;
	skyline->maxX = 0;

	// computing the bounds of the skyline
	for(int i = 0; i < buildingDimensions->size(); i++) {
		BuildingDimension* buildingDimension = buildingDimensions->at(i);
		if(buildingDimension->leftx < skyline->minX) {
			skyline->minX = buildingDimension->leftx;
		}
		if(buildingDimension->rightx > skyline->maxX) {
			skyline->maxX = buildingDimension->rightx;
		}
	}

	int len = skyline->maxX-skyline->minX;
	skyline->heights = new int[len];
	for(int i = 0; i < len; i++) {
		skyline->heights[i] = 0;
	}

	// compute the maxes so far, building by building
	for(int i = 0; i < buildingDimensions->size(); i++) {
		BuildingDimension* buildingDimension = buildingDimensions->at(i);
		for(int j = buildingDimension->leftx; j <= buildingDimension->rightx; j++) {
			int idx = getSkylineIndex(skyline, j);
			if(buildingDimension->height > skyline->heights[idx]) {
				skyline->heights[idx] = buildingDimension->height;
			}
		}
	}

	return skyline;
}

int getSkylineIndex(Skyline* skyline, int x) {
	return x-skyline->minX;
}


void printSkyline(Skyline* skyline){
}

void freeSkyline(Skyline* skyline) {
	delete skyline->heights;
	delete skyline;
}

#ifdef DEBUG
void printBuildingDimensions(vector<BuildingDimension*>* buildingDimensions) {
	for(int i = 0; i < buildingDimensions->size(); i++) {
		BuildingDimension* buildingDimension = buildingDimensions->at(i);
		printf("%d %d %d\n", buildingDimension->leftx, buildingDimension->height, buildingDimension->rightx);
	}
	printf("================\n");
}
void printDebugSkyline(Skyline* skyline){
	int len = skyline->maxX-skyline->minX;
	printf("leftmost:  %d\n", skyline->minX);
	printf("rightmost: %d\n", skyline->maxX);
	for(int i = 0; i < len; i++) {
		printf("%d ", skyline->heights[i]);
	}
	printf("\n");
	printf("================\n");
}
#endif
