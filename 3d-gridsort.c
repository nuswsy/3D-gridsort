#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define n 50
void prtcube(int G[n][n][n]) {
    int checksum = 0;
    for (int i = 0; i < n; i++)
    {
        printf("\nLayer %d:\n", i);

        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                printf("%5d", G[i][j][k]);
                checksum += G[i][j][k];
            }

            printf("\n");
        }
    }

    printf("\nChecksum = %d\n", checksum);
}
int checkHeap(int G[n][n][n])
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {

				// k direction
				if (k + 1 < n &&
					G[i][j][k] > G[i][j][k + 1])
					return 0;

				// j direction
				if (j + 1 < n &&
					G[i][j][k] > G[i][j + 1][k])
					return 0;

				// i direction
				if (i + 1 < n &&
					G[i][j][k] > G[i + 1][j][k])
					return 0;
			}
		}
	}

	return 1;
}
// Restore heap property inside ONE layer.
// i is fixed. We can only move in j and k directions.
void restoreLayer(int G[n][n][n], int i, int j, int k)
{
    int thisj = j;
    int thisk = k;

    int nextj, nextk;
    int temp;

    while (1)
    {
        // Assume the current root is the smallest
        nextj = thisj;
        nextk = thisk;

        // k direction: right son
        if (thisk + 1 < n)
        {
            if (G[i][thisj][thisk + 1] <
                G[i][nextj][nextk])
            {
                nextj = thisj;
                nextk = thisk + 1;
            }
        }

        // j direction: next-row son
        if (thisj + 1 < n)
        {
            if (G[i][thisj + 1][thisk] <
                G[i][nextj][nextk])
            {
                nextj = thisj + 1;
                nextk = thisk;
            }
        }

        // Current root is already the smallest
        if (nextj == thisj && nextk == thisk)
            break;

        // Swap with the smallest son
        temp = G[i][thisj][thisk];
        G[i][thisj][thisk] = G[i][nextj][nextk];
        G[i][nextj][nextk] = temp;

        // Continue from the new position
        thisj = nextj;
        thisk = nextk;
    }
}


// Restore 3D heap property.
// Can move in i, j and k directions.
void restoreCube(int G[n][n][n], int i, int j, int k)
{
    int thisi = i;
    int thisj = j;
    int thisk = k;

    int nexti, nextj, nextk;
    int temp;

    while (1)
    {
        // Assume the current root is the smallest
        nexti = thisi;
        nextj = thisj;
        nextk = thisk;

        // k direction
        if (thisk + 1 < n)
        {
            if (G[thisi][thisj][thisk + 1] <
                G[nexti][nextj][nextk])
            {
                nexti = thisi;
                nextj = thisj;
                nextk = thisk + 1;
            }
        }

        // j direction
        if (thisj + 1 < n)
        {
            if (G[thisi][thisj + 1][thisk] <
                G[nexti][nextj][nextk])
            {
                nexti = thisi;
                nextj = thisj + 1;
                nextk = thisk;
            }
        }

        // i direction
        if (thisi + 1 < n)
        {
            if (G[thisi + 1][thisj][thisk] <
                G[nexti][nextj][nextk])
            {
                nexti = thisi + 1;
                nextj = thisj;
                nextk = thisk;
            }
        }

        // No son is smaller
        if (nexti == thisi &&
            nextj == thisj &&
            nextk == thisk)
        {
            break;
        }

        // Swap root with the smallest son
        temp = G[thisi][thisj][thisk];

        G[thisi][thisj][thisk] =
            G[nexti][nextj][nextk];

        G[nexti][nextj][nextk] = temp;

        // Continue sift-down
        thisi = nexti;
        thisj = nextj;
        thisk = nextk;
    }
}


// Check whether the entire cube is sorted in
// i -> j -> k row-major order
int checkSorted(int G[n][n][n])
{
    int* p = &G[0][0][0];

    for (int x = 0; x < n * n * n - 1; x++)
    {
        if (p[x] > p[x + 1])
            return 0;
    }

    return 1;
}
int main()
{
    int G[n][n][n];

    int i, j, k;
    int checksum = 0;
    int min;
	int thisi, thisj, thisk, nexti, nextj, nextk;
    int i1,j1,k1;
    int temp;
    int interchange;
    srand(17);

    // Generate random data
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                G[i][j][k] = rand() % 200;
            }
        }
    }
    printf("Raw Data:\n");
    prtcube(G);

    //this is for 3-directions sorting:
    //1.layer
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            
            for (int k = 0;k < n-1;k++) {
                min = k;
                for (thisk = k + 1;thisk < n;thisk++) {
                    if (G[i][j][thisk] < G[i][j][min]) {
                        min = thisk;
                    }
                    

                }
				temp = G[i][j][k];
				G[i][j][k] = G[i][j][min];
				G[i][j][min] = temp;
            }
        }
    }

    //2.collum
	for (int i = 0;i < n;i++) {
		for (int k = 0;k < n;k++) {
			for (int j = 0;j < n-1;j++) {
				min = j;
				for (thisj = j + 1;thisj < n;thisj++) {
					if (G[i][thisj][k] < G[i][min][k]) {
						min = thisj;
					}
					
				}
				temp = G[i][j][k];
				G[i][j][k] = G[i][min][k];
				G[i][min][k] = temp;
			}
		}
	}

    //3.row

	for (int j = 0;j < n;j++) {
		for (int k = 0;k < n;k++) {
			for (int i = 0;i < n-1;i++) {
				min = i;
				for (thisi = i + 1;thisi < n;thisi++) {
					if (G[thisi][j][k] < G[min][j][k]) {
						min = thisi;
					}
					
				}
				temp = G[i][j][k];
				G[i][j][k] = G[min][j][k];
				G[min][j][k] = temp;
			}
		}
	}


    // Display the 3D grid
	printf("\n\nAfter 3-direction sort:\n");
	prtcube(G);

	if (checkHeap(G))
		printf("3D heap property established!\n");
	else
		printf("3D heap property FAILED!\n");
	
	



    // =====================================================
    // STAGE 1:
    // Interchange BETWEEN different layers
    // =====================================================

    for (i = 0; i < n - 1; i++)
    {
        /*
           G[i + 1][0][0] is the root of the
           next layer.

           Process the elements in Layer i
           in row-major order.
        */

        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                // The first element of the layer
                // does not need to be processed again
                if (j == 0 && k == 0)
                    continue;

                if (G[i][j][k] > G[i + 1][0][0])
                {
                    // Interchange
                    temp = G[i][j][k];
                    G[i][j][k] = G[i + 1][0][0];
                    G[i + 1][0][0] = temp;

                    /*
                       The larger value is now at the root
                       of the remaining 3D region.

                       Restore the 3D heap property.
                    */
                    restoreCube(G, i + 1, 0, 0);
                }
            }
        }
    }
    // =====================================================
    // STAGE 2:
    // INSIDE each layer.
    // =====================================================
for (i = 0; i < n; i++)
    {
        // Work on Layer i

        for (j = 0; j < n - 1; j++)
        {
            // G[i][j + 1][0] is the root of the
            // remaining part of this layer

            for (k = 1; k < n; k++)
            {
                if (G[i][j][k] > G[i][j + 1][0])
                {
                    // Interchange
                    temp = G[i][j][k];
                    G[i][j][k] = G[i][j + 1][0];
                    G[i][j + 1][0] = temp;

                    // The larger value has been moved to
                    // G[i][j + 1][0].
                    // Restore the 2D heap inside this layer.
                    restoreLayer(G, i, j + 1, 0);
                }
            }
        }
    }


    printf("\n\nAfter restoration inside each layer:\n");
    prtcube(G);

    // =====================================================
    // FINAL OUTPUT
    // =====================================================

    printf("\n\nAfter interchange and restoration:\n");
    prtcube(G);


    // Check local 3D heap property
    if (checkHeap(G))
    {
        printf("\n3D heap property maintained.\n");
    }
    else
    {
        printf("\nWARNING: 3D heap property failed.\n");
    }


    // Check complete row-major sorting
    if (checkSorted(G))
    {
        printf("\n====================================\n");
        printf("3D GRID SORT SUCCESS: SORTED!\n");
        printf("====================================\n");
    }
    else
    {
        printf("\n====================================\n");
        printf("3D GRID SORT FAILED: NOT SORTED!\n");
        printf("====================================\n");
    }

   
    return 0;
}