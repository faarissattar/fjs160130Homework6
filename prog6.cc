//Faaris Sattar
//fjs160130@utdallas.edu
//CS 3377.502

#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "cdk.h"
#include <inttypes.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader
{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};
int main()
{

  WINDOW *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *myMatrix;           // CDK Screen Matrix

  const char *rowTitles[MATRIX_HEIGHT+1] = {"R0", "R1", "R2", "R3"};
  const char *columnTitles[MATRIX_WIDTH+1] = {"C0", "C1", "C2", "C3"};
  int boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
   */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
			  boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  BinaryFileHeader *header = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();

  ifstream bin ("cs3377.bin", ios::in | ios::binary);
  
  bin.read((char *)header, sizeof(BinaryFileHeader));
 
   stringstream stream;
  
  stream << "0x" << hex << header->magicNumber;
  string magic;
  stream >> magic;
  string magicString = "Magic: " + magic;
  setCDKMatrixCell(myMatrix, 1, 1, magicString.c_str());

  stream.clear();
  stream <<  header->versionNumber;
  string version;
  stream >> version;
  string versionString = "Version: " + version;
  setCDKMatrixCell(myMatrix, 1, 2, versionString.c_str());

  stream.clear();
  stream << header->numRecords;
  string recordnum;
  stream >> recordnum;
  string recordnumString = "numRecords: " + recordnum;
  setCDKMatrixCell(myMatrix, 1, 3, recordnumString.c_str());
  
   bin.read((char *)myRecord, sizeof(BinaryFileRecord));
  stringstream rstream;
  rstream << (int)myRecord->strLength;
  string length;
  rstream >> length;
  string lengthstr = "strLength: " + length;
  setCDKMatrixCell(myMatrix, 2, 1, lengthstr.c_str());
  setCDKMatrixCell(myMatrix, 2, 2, myRecord->stringBuffer );
  
  bin.read((char *)myRecord, sizeof(BinaryFileRecord));
  stringstream cstream;
  cstream << (int)myRecord->strLength;
  string length2;
  cstream >> length2;
  string lengthstr2 = "strLength: " + length2;
  setCDKMatrixCell(myMatrix, 3, 1, lengthstr2.c_str());
  setCDKMatrixCell(myMatrix, 3, 2, myRecord->stringBuffer );
  
  bin.read((char *)myRecord, sizeof(BinaryFileRecord));
  stringstream tstream;
  tstream << (int)myRecord->strLength;
  string length3;
  tstream >> length3;
  string lengthstr3 = "strLength: " + length3;
  setCDKMatrixCell(myMatrix, 4, 1, lengthstr3.c_str());
  setCDKMatrixCell(myMatrix, 4, 2, myRecord->stringBuffer );

  bin.read((char *)myRecord, sizeof(BinaryFileRecord));
  stringstream ystream;
  ystream << (int)myRecord->strLength;
  string length4;
  ystream >> length4;
  string lengthstr4 = "strLength: " + length4;
  setCDKMatrixCell(myMatrix, 5, 1, lengthstr4.c_str());
  setCDKMatrixCell(myMatrix, 5, 2, myRecord->stringBuffer );


  bin.close();
    /*
   * Dipslay a message
   */


  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);


  // Cleanup screen
  endCDK();
}
