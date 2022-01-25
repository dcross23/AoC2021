#include "day19.h"

#define STRIP(s) if(s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';

typedef struct point3d{
	int x,y,z;
}Point3D; 

typedef struct scanner{
	Point3D scans[1000];
	int numScans;
}Scanner;

Point3D* transform(Point3D point){
	Point3D rotations[6];
	rotations[0] = (Point3D) {point.x , point.y , point.z};
	rotations[1] = (Point3D) {point.z , point.y , -point.x};
	rotations[2] = (Point3D) {-point.z, point.y , point.x};
	rotations[3] = (Point3D) {-point.x, point.y , -point.z};
	rotations[4] = (Point3D) {point.x , -point.z, point.y};
	rotations[5] = (Point3D) {point.x , point.z , -point.y};

	Point3D *transforms;
	int idx = 0;

	transforms = malloc(24 * sizeof(Point3D));
	for(int i=0; i<6; i++){
		transforms[idx++] = (Point3D) {rotations[i].x , rotations[i].y , rotations[i].z};
		transforms[idx++] = (Point3D) {rotations[i].y , -rotations[i].x, rotations[i].z};
		transforms[idx++] = (Point3D) {-rotations[i].x, -rotations[i].y, rotations[i].z};
		transforms[idx++] = (Point3D) {-rotations[i].y, rotations[i].x , rotations[i].z};
	}

	return transforms;	
}

Scanner transpose(Scanner sc, int dx, int dy, int dz){
	Scanner newSc; 
	memset(&newSc, 0, sizeof(Scanner));

	newSc.numScans = sc.numScans;
	for(int i=0; i<sc.numScans; i++){
		newSc.scans[i].x = sc.scans[i].x - dx;
		newSc.scans[i].y = sc.scans[i].y - dy;
		newSc.scans[i].z = sc.scans[i].z - dz;
	}
	return newSc;
}

bool equalPoints(Point3D p1, Point3D p2){
	return (p1.x==p2.x && p1.y==p2.y && p1.z==p2.z);
}

Scanner intersection(Scanner sc1, Scanner sc2){
	Scanner intersect;
	memset(&intersect, 0, sizeof(Scanner));

	for(int i=0; i<sc1.numScans; i++){
		for(int j=0; j<sc2.numScans; j++){
			if(equalPoints(sc1.scans[i], sc2.scans[j])){
				intersect.scans[intersect.numScans++] = sc1.scans[i];
				break;
			}
		}
	}
	return intersect;
}

Scanner getUnion(Scanner sc1, Scanner sc2){
	Scanner unionSc;
	memset(&unionSc, 0, sizeof(Scanner));

	for(int i=0; i<sc1.numScans; i++){
		unionSc.scans[unionSc.numScans++] = sc1.scans[i];
	}

	for(int j=0; j<sc2.numScans; j++){
		bool isIn = false;
		for(int k=0; k<unionSc.numScans; k++){
			isIn = equalPoints(unionSc.scans[k], sc2.scans[j]);
			if(isIn) break;
		}

		if(!isIn)
			unionSc.scans[unionSc.numScans++] = sc2.scans[j];
	}

	return unionSc;
}

bool merge(Scanner sc1, Scanner sc2, Scanner* merged, Point3D *distToCenter){
	Scanner unionSc;
	for(int i=0; i<sc1.numScans; i++){
		for(int j=0; j<sc2.numScans; j++){
			int dx = sc2.scans[j].x - sc1.scans[i].x;
			int dy = sc2.scans[j].y - sc1.scans[i].y;
			int dz = sc2.scans[j].z - sc1.scans[i].z;

			Scanner transposed = transpose(sc2, dx, dy, dz);
			Scanner intersect = intersection(sc1, transposed);
			if(intersect.numScans >= 12){
				*merged = getUnion(sc1, transposed);
				distToCenter->x = dx;
				distToCenter->y = dy;
				distToCenter->z = dz;
				return true;
			}
		}
	}
	return false;
}

void getTransformations(Scanner sc, Scanner** sist){
	Scanner spins[sc.numScans];
	int spinsSz = 0, rotationsSz = 0;
	
	*sist = malloc(24 * sizeof(Scanner));
	memset(*sist, 0, 24 * sizeof(Scanner));
	memset(spins, 0, sc.numScans * sizeof(Scanner));

	for(int i=0; i<sc.numScans; i++){
		Point3D *t = transform(sc.scans[i]);
		for(int j=0; j<24; j++){
			spins[spinsSz].scans[spins[spinsSz].numScans++] = t[j];
		}
		spinsSz++;
	}
		
	for(int r=0; r<24; r++){
		for(int i=0; i<spinsSz; i++){
			(*sist)[r].scans[(*sist)[r].numScans++] = spins[i].scans[r];
		}
	}
}

void removeAt(int idx, Scanner (*sc)[50], int *numSc){
	for(int i=idx; i<(*numSc)-1; i++)
		(*sc)[i] = (*sc)[i+1];
	(*numSc)--;
}

bool nextScanner(Scanner refSc, Scanner (*rest)[50], int *restSz, Scanner *result, Point3D *distToCenter){
	Scanner *sist;
	for(int i=0; i<(*restSz); i++){
		getTransformations((*rest)[i], &sist);
		for(int r=0; r<24; r++){
			if(merge(refSc, sist[r], result, distToCenter)){
				removeAt(i, rest, restSz);
				return true;
			}
		}
	}
	return false;
}

int day19_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	char *aux;
	bool first = true;
	Scanner firstSc;
	Scanner remains[50];
	int numRemains = 0;


	while(fgets(line, sizeof(line), f)){
		STRIP(line)
		if(line[0]=='\0') continue;
		
		if(strcmp(line, "--- scanner 0 ---") == 0){
			memset(&firstSc, 0, sizeof(Scanner));

		
		}else if(strncmp(line, "---", 3) == 0){
			memset(&remains[numRemains], 0, sizeof(Scanner));
			numRemains++;	
			first = false;

		}else{
			Scanner *s;
			if(first){
				s = &firstSc;
			}else
				s = &remains[numRemains-1];

			aux = strtok(line, ",");
			s->scans[s->numScans].x = atoi(aux);	
			aux = strtok(NULL, ",");
			s->scans[s->numScans].y = atoi(aux);	
			aux = strtok(NULL, ",");
			s->scans[s->numScans++].z = atoi(aux);	
		}
	}
	
	Scanner stepResult;
	Scanner refSc = firstSc;
	Point3D ignoreForThisPart;

	while(numRemains > 0){
		memset(&stepResult, 0, sizeof(Scanner));
		if(!nextScanner(refSc, &remains, &numRemains, &stepResult, &ignoreForThisPart)){
			printf("ERROR\n"); 
			return -1;
		}
		refSc = stepResult;
	}
	int sol = refSc.numScans;	

	return sol;
}


int calcManhatannDist(Point3D p1, Point3D p2){
	return abs(p1.x - p2.x) + abs(p1.y - p2.y) + abs(p1.z - p2.z);
}


int day19_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	char *aux;
	bool first = true;
	Scanner firstSc;
	Scanner remains[50];
	int numRemains = 0;


	while(fgets(line, sizeof(line), f)){
		STRIP(line)
		if(line[0]=='\0') continue;
		
		if(strcmp(line, "--- scanner 0 ---") == 0){
			memset(&firstSc, 0, sizeof(Scanner));

		
		}else if(strncmp(line, "---", 3) == 0){
			memset(&remains[numRemains], 0, sizeof(Scanner));
			numRemains++;	
			first = false;

		}else{
			Scanner *s;
			if(first){
				s = &firstSc;
			}else
				s = &remains[numRemains-1];

			aux = strtok(line, ",");
			s->scans[s->numScans].x = atoi(aux);	
			aux = strtok(NULL, ",");
			s->scans[s->numScans].y = atoi(aux);	
			aux = strtok(NULL, ",");
			s->scans[s->numScans++].z = atoi(aux);	
		}
	}
	
	Scanner stepResult;
	Scanner refSc = firstSc;
	Point3D distToCenter; //Assuming scanner 0 as center
	Point3D *distances;
	int numDistances = 0;

	distances = malloc((numDistances+1) * sizeof(int));
	distances[numDistances++] = (Point3D) {0,0,0};

	while(numRemains > 0){
		memset(&stepResult, 0, sizeof(Scanner));
		if(!nextScanner(refSc, &remains, &numRemains, &stepResult, &distToCenter)){
			printf("ERROR\n"); 
			return -1;
		}

		distances = realloc(distances, (numDistances+1) * sizeof(Point3D));
		distances[numDistances++] = distToCenter;
		refSc = stepResult;
	}

	int maxManhattanDist = INT_MIN;
	for(int i=0; i<numDistances; i++){
		for(int j=0; j<numDistances; j++){
			if(i != j){
				int manhDist = calcManhatannDist(distances[i], distances[j]);

				if(manhDist > maxManhattanDist) 
					maxManhattanDist = manhDist;
			}
		}
	}	

	return maxManhattanDist;
}



