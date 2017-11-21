/** 
 * Convert .pnm file created by GIMP to a plain-text DAT file.
 *
 * .pnm file is assumed to be Grayscale ("P2"), in ASCII format.
 *
 * For example:
 * <code>
 * P2
 * # CREATOR: GIMP PNM Filter Version 1.1
 * COLUMNS ROWS
 * MAX_INTENSITY (assumed to be 255)
 * COLUMNS*ROWS where each value is 0 (black/land) | 255 (white/water)
 * </code>
 * where 
 * The output file is of form:
 *
 * <code>
 * COLUMNS ROWS
 * ROWS rows each with COLUMNS fields where each field is
 * 1 (land) or 0 (water).
 * </code>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EDGE 4000
#define WATER 0
#define LAND 1

int map[MAX_EDGE][MAX_EDGE];

int main(int argc, char * argv[])
{
    int columns = 200;
    int rows = 200;
    int column = 0;
    int row = 0;
    FILE* fp;
    char inFile[20] = "\0";
    char outFile[20] = "\0";
    // Ideally, expect maximum length of Grayscale value to be < 5.
    int length = 80;
    char line[length];
    char *word;
    int num;

    if (argc == 3)
    {
        strcpy(inFile, argv[1]);
        strcpy(outFile, argv[2]);
    }
    else 
    {
        printf("Usage: pnmreader infile outfile\n"); 
        exit(1); 
    }
    if ((fp = fopen(inFile, "r+")) == NULL)
    {
        printf("Cannot open file %s.\n", inFile);
        exit(1);
    }
    
    // Skip first line, with file type (assumed to be "P2").
    fgets(line, (length - 1), fp);
    printf(line); 

    // Skip second line, with GIMP CREATOR comment.
    fgets(line, (length - 1), fp);
    printf(line);

    // Parse third line into columns and rows.
    word = (char*)malloc(length * sizeof(char));
    fgets(line, (length - 1), fp);
    printf(line);
    columns = strtol(line, &word, 0);
    rows = strtol(word, 0, 0);
    printf("Columns=%d, Rows=%d\n", columns, rows);

    // Skip fourth, line with MAX_INTENSITY (assumed to be 255).
    fgets(line, (length - 1), fp);
    printf(line);

    while (!feof(fp))
    {
        fgets(line, (length - 1), fp);
        num = strtol(line, 0, 0);
        // Land is black is 0, water is white is 255.
        if (num < 128)
        {
            map[row][column++] = LAND;
        }
        else
        {
            map[row][column++] = WATER;
        }
        // Check if need to move to next row.
        if (column == columns)
        {
            if (++row < rows)
            {
                column = 0;
            }
            else
            {
                break;
            }
        }
    }
    fclose(fp);

    // Write columns, rows, map to output file.
    if ((fp = fopen(outFile, "w")) == NULL)
    {
        printf("Cannot open file %s.\n", outFile);
        exit(1);
    }
    fprintf(fp, "%d %d\n", columns, rows);
    for (row = 0; row < rows; row++)
    {
        for (column = 0; column < columns; column++)
        {
            fprintf(fp, "%d ", map[row][column]);
        }
        fprintf(fp, "\n");
    }
    return 0;
}
