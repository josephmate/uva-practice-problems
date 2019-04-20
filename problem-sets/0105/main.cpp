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
void                        printBuildingDimensions(vector<BuildingDimension*>* input);
#endif


vector<BuildingDimension*>* parseBuildingDimensions();
void                        freeBuildingDimensions(vector<BuildingDimension*>*);

int main(int argc, const char *argv[])
{
	vector<BuildingDimension*>* input = parseBuildingDimensions();
#ifdef DEBUG
	printBuildingDimensions(input);
#endif
	freeBuildingDimensions(input);
	return 0;
}


vector<BuildingDimension*>* parseBuildingDimensions() {
	vector<BuildingDimension*>* input = new vector<BuildingDimension*>();
	int leftx;
	int height;
	int rightx;

	while (fscanf(stdin, "%d %d %d\n", &leftx, &height, &rightx) > 0) {
		BuildingDimension* buildingDimension = new BuildingDimension();
		buildingDimension->leftx = leftx;
		buildingDimension->height = height;
		buildingDimension->rightx = rightx;
		input->push_back(buildingDimension);
	}	 

	return input;
}

void freeBuildingDimensions(vector<BuildingDimension*>* input){
	for(int i = 0; i < input->size(); i++) {
		BuildingDimension* buildingDimension = input->at(i);
		delete buildingDimension;
	}
	delete input;
}

#ifdef DEBUG
void printBuildingDimensions(vector<BuildingDimension*>* input) {
	for(int i = 0; i < input->size(); i++) {
		BuildingDimension* buildingDimension = input->at(i);
		printf("%d %d %d\n", buildingDimension->leftx, buildingDimension->height, buildingDimension->rightx);
	}
}
#endif
