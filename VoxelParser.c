#include <stdio.h>
#include <string.h>

// prototypes
int loadMyFile();
void printArray();
void printArrayRange();
void normaliseArray();
void sortArray();
void createNewArray();
void printNewArray();
void createNewFile();

int array[12000];
int newArray[12000];
int temp[8];
int total, newSize;
int totalCubes = 0;
char* p;

int main()
{
	    loadMyFile();
	    normaliseArray();
	    sortArray();
	    printArrayRange();
	    createNewArray();
	    printNewArray();
	    createNewFile();
	    return 0;
}

int loadMyFile()
{
	    FILE* ptr_file;
	    char buf[1000];

	    ptr_file = fopen("AntAttackMap.txt", "r");
	    if(!ptr_file)
			return 1;

	    int index = 0;

	    while(fgets(buf, 1000, ptr_file) != NULL)
	    {
			p = strtok(buf, " ec\n\r");

			while(p != NULL)
			{
				    int num;
				    num = atoi(p);
				    array[index] = num;
				    // printf("%d, ", num);
				    p = strtok(NULL, " ec\n\r");
				    index++;
			}
	    }

	    fclose(ptr_file);
	    total = index;
}

void printArray()
{
	    for(int index = 0; index < total; index++)
	    {
			printf("%d, ", array[index]);
	    }
	    printf("\nTotal Elements %d ", total);
	    printf("\nTotal Cubes %d \n", total / 3);
}

void printArrayRange()
{
	    int smallX = 999, smallY = 999, smallZ = 999;
	    int largeX = -999, largeY = -999, largeZ = -999;

	    for(int index = 0; index < total; index = index + 3)
	    {
			// Smallest
			if(array[index] < smallX)
				    smallX = array[index];
			if(array[index + 1] < smallY)
				    smallY = array[index + 1];
			if(array[index + 2] < smallZ)
				    smallZ = array[index + 2];

			// Largest
			if(array[index] > largeX)
				    largeX = array[index];
			if(array[index + 1] > largeY)
				    largeY = array[index + 1];
			if(array[index + 2] > largeZ)
				    largeZ = array[index + 2];
	    }
	    printf("\nWidth = %d ", largeX + 1);
	    printf("\nDepth = %d ", largeY + 1);
	    printf("\nHeight = %d \n", largeZ + 1);
}

void normaliseArray()
{
	    for(int index = 0; index < total; index = index + 3)
	    {
			array[index] += 66;
			array[index + 1] += 46;
			array[index + 2] -= 8;
	    }
}

void sortArray()
{
	    // first pass - sort 3rd element
	    int moreToSort = 1;
	    while(moreToSort)
	    {
			moreToSort = 0;
			for(int index = 0; index < (total - 3); index = index + 3)
			{
				    int X, Y, Z, A, B, C;
				    X = array[index];
				    Y = array[index + 1];
				    Z = array[index + 2];
				    A = array[index + 3];
				    B = array[index + 4];
				    C = array[index + 5];
				    int tempX = X;
				    int tempY = Y;
				    int tempZ = Z;
				    if(C < Z)
				    {
						array[index] = A;
						array[index + 1] = B;
						array[index + 2] = C;
						array[index + 3] = tempX;
						array[index + 4] = tempY;
						array[index + 5] = tempZ;
						moreToSort = 1;
				    }
			}
	    }

	    // 2nd pass - sort 2nd element
	    moreToSort = 1;
	    while(moreToSort)
	    {
			moreToSort = 0;
			for(int index = 0; index < (total - 3); index = index + 3)
			{
				    int X, Y, Z, A, B, C;
				    X = array[index];
				    Y = array[index + 1];
				    Z = array[index + 2];
				    A = array[index + 3];
				    B = array[index + 4];
				    C = array[index + 5];
				    int tempX = X;
				    int tempY = Y;
				    int tempZ = Z;
				    if(B < Y)
				    {
						array[index] = A;
						array[index + 1] = B;
						array[index + 2] = C;
						array[index + 3] = tempX;
						array[index + 4] = tempY;
						array[index + 5] = tempZ;
						moreToSort = 1;
				    }
			}
	    }

	    // third pass - sort 1st element
	    moreToSort = 1;
	    while(moreToSort)
	    {
			moreToSort = 0;
			for(int index = 0; index < (total - 3); index = index + 3)
			{
				    int X, Y, Z, A, B, C;
				    X = array[index];
				    Y = array[index + 1];
				    Z = array[index + 2];
				    A = array[index + 3];
				    B = array[index + 4];
				    C = array[index + 5];
				    int tempX = X;
				    int tempY = Y;
				    int tempZ = Z;
				    if(A < X)
				    {
						array[index] = A;
						array[index + 1] = B;
						array[index + 2] = C;
						array[index + 3] = tempX;
						array[index + 4] = tempY;
						array[index + 5] = tempZ;
						moreToSort = 1;
				    }
			}
	    }
}

void createNewArray()
{
	    unsigned char X, Y, Z, A, B, C;
	    int start = 0;
	    int end = 0;
	    int newIndex = 0;

	    int loopAgain;
	    int endOfArray = 0;
	    do
	    {
			unsigned char blockPattern = 0;
			do
			{
				    loopAgain = 0;

				    X = array[start];
				    Y = array[start + 1];
				    Z = array[start + 2];

				    A = array[end];
				    B = array[end + 1];
				    C = array[end + 2];

				    if((X == A) && (Y == B))
				    {
						blockPattern = blockPattern | (1 << C);
						loopAgain = 1;
						totalCubes++;
				    }
				    end = end + 3;
				    if(end > total)
						endOfArray = 1;
			} while(loopAgain);
			end -= 3;
			newArray[newIndex] = X;
			newArray[newIndex + 1] = Y;
			newArray[newIndex + 2] = blockPattern;
			newIndex += 3;
			newSize = newIndex;
			start = end;
	    } while(endOfArray == 0);
}

void printNewArray()
{
	    for(int index = 0; index < newSize; index++)
	    {
			printf("%d, ", newArray[index]);
	    }
	    printf("\nNew Size =  %d Kb", newSize);
	    printf("\nTotal Cubes =  %d ", totalCubes);
}

void createNewFile()
{
	    FILE* fp;

	    fp = fopen("OUTPUT.txt", "w+");
	    fprintf(fp, "{ \n");
	    for(int index = 0; index < newSize; index++)
	    {
			fprintf(fp, "%d", newArray[index]);
			fprintf(fp, ", ");
	    }
	    fprintf(fp, " }");
	    fclose(fp);
}
