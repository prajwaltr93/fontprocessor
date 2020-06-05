#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdio.h>
#include <unistd.h>
#include "fontprocessor.h"
#include FT_OUTLINE_H
#include FT_BBOX_H

FT_Library  library = NULL;
FT_Face font_face = NULL;

void error_print(char *mesg, int error) {

	printf("error code : %d error message : %s\n",error,mesg);
	exit(1);

}
//user struct for state info
typedef struct _user {
	int state;
} User;

//outlinefunc callbacks

int MoveToFunction(const FT_Vector* to, void* user)
{
	FT_Pos x = to->x;
  FT_Pos y = to->y;

  printf("M %ld %ld\n",x,y);

  return 0;
}

int LineToFunction(const FT_Vector *to,void *user)
{

  FT_Pos x = to->x;
  FT_Pos y = to->y;

  printf("L %ld %ld\n",x,y);

  return 0;
}

int ConicToFunction(const FT_Vector *control, const FT_Vector *to, void *user)
{
  FT_Pos controlX = control->x;
  FT_Pos controlY = control->y;

  FT_Pos x = to->x;
  FT_Pos y = to->y;

  printf("Q %ld %ld, %ld %ld\n",controlX,controlY,x,y);

  return 0;
}

int CubicToFunction(const FT_Vector *controlOne, const FT_Vector *controlTwo, const FT_Vector *to, void *user)
{
  FT_Pos controlOneX = controlOne->x;
  FT_Pos controlOneY = controlOne->y;

  FT_Pos controlTwoX = controlTwo->x;
  FT_Pos controlTwoY = controlTwo->y;

  FT_Pos x = to->x;
  FT_Pos y = to->y;

  printf("C %ld %ld %ld %ld %ld %ld\n",controlOneX, controlOneY, controlTwoX, controlTwoY, x, y);

  return 0;
}


int main(int argc,char *argv[]) {

  FT_GlyphSlot  slot = NULL;
	FT_Outline outline;
	FT_Outline_Funcs outlinefuncs;
	FT_Matrix matrix;
	FT_BBox boundingBox;
	FT_Pos m_xMin;
  FT_Pos m_yMin;
  FT_Pos m_width;
  FT_Pos m_height;
	const FT_Fixed multiplier = 65536L;
	User user = {0};
	int error;

	//load library
	if((error = FT_Init_FreeType(&library))) error_print("library initialization\n",error);

	//load default font
	if((error = FT_New_Face(library, PATH_VICTORIA, 0, &font_face))) error_print("failed to load font\n",error);

	//glyph slot
  slot = font_face->glyph;

  //set pixel size, to overide zero initialization to all size object values
  if((error = FT_Set_Pixel_Sizes(font_face, 64, 0))) error_print("font_face size setting\n",error);

  //load glyph to glyph slot
	if((error = FT_Load_Char(font_face, 'A', FT_LOAD_DEFAULT)) != 0) error_print("glyph not found\n",error);

	//transform
	matrix.xx = 1L * multiplier;
  matrix.xy = 0L * multiplier;
  matrix.yx = 0L * multiplier;
  matrix.yy = -1L * multiplier;

	//outline manupulation
	outline = slot->outline;

	//other attributes necessary for parsing outline
	outlinefuncs.shift = 0;
	outlinefuncs.delta = 0;

	//use outlilne_decompse to get outline data : callbacks
	outlinefuncs.move_to = (FT_Outline_MoveToFunc) MoveToFunction;
  outlinefuncs.line_to = (FT_Outline_LineToFunc) LineToFunction;
  outlinefuncs.conic_to = (FT_Outline_ConicToFunc) ConicToFunction;
  outlinefuncs.cubic_to = (FT_Outline_CubicToFunc) CubicToFunction;

	FT_Outline_Transform(&outline, &matrix);

	FT_Outline_Get_BBox(&outline, &boundingBox);

  FT_Pos xMin = boundingBox.xMin;
  FT_Pos yMin = boundingBox.yMin;
  FT_Pos xMax = boundingBox.xMax;
  FT_Pos yMax = boundingBox.yMax;

  m_xMin = xMin;
  m_yMin = yMin;
  m_width = xMax - xMin;
  m_height = yMax - yMin;

	printf("bounding box : %ld %ld %ld %ld\n",m_xMin,m_yMin,m_width,m_height);

	FT_Outline_Decompose(&outline, &outlinefuncs, (void *) &user);

	return 0;
}
