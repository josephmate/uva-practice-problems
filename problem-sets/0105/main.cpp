#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

#define DEBUG


struct BuildingDimension {
	int leftx;
	int height;
	int rightx;
};

#ifdef DEBUG
void                        printBuildingDimensions(vector<BuildingDimension*>*);
#endif


vector<BuildingDimension*>* parseBuildingDimensions();
void                        freeBuildingDimensions(vector<BuildingDimension*>*);
int*                        calculateSkyline(vector<BuildingDimension*>*);
void                        printSkyline(int*);

int main(int argc, const char *argv[])
{
	vector<BuildingDimension*>* buildingDimensions = parseBuildingDimensions();
#ifdef DEBUG
	printBuildingDimensions(buildingDimensions);
#endif
	
	int* skyline = calculateSkyline(buildingDimensions);
	printSkyline(skyline);

	freeBuildingDimensions(buildingDimensions);
	delete skyline;
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
int* calculateSkyline(vector<BuildingDimension*>* buildingDimensions) {
	return new int[0];
}

void printSkyline(int* skyline){
}

#ifdef DEBUG
void printBuildingDimensions(vector<BuildingDimension*>* buildingDimensions) {
	for(int i = 0; i < buildingDimensions->size(); i++) {
		BuildingDimension* buildingDimension = buildingDimensions->at(i);
		printf("%d %d %d\n", buildingDimension->leftx, buildingDimension->height, buildingDimension->rightx);
	}
}
#endif
