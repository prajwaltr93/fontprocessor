#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdio.h>
#include <unistd.h>
#include "fontprocessor.h"

//global declaration
FT_Library  library;
FT_Face font_face;
FT_GlyphSlot  slot;

void error_print(char *mesg, int error) {

	printf("error code : %d error message : %s\n",mesg);
	exit(1);

}

int main(int argc,char *argv[]) {

	FT_UInt glyph_index;
	int opt,error;

	//load library
	if((error = FT_Init_FreeType(&library)) != 0) error_print("library initialization\n",error);

	//load default font
	if((error = FT_New_Face(library, PATH_WHITE_RABBIT, 0, &font_face)) == FT_Err_Unknown_File_Format) error_print("failed to load font\n",error);

  //glyph slot
  slot = font_face->glyph;

  //set pixel size, to overide zero initialization to all size object values
  if((error = FT_Set_Pixel_Sizes(font_face, 0, 1)) != 0) error_print("font size setting\n",error);

  //load glyph to glyph slot
	if((error = FT_Load_Char(font_face, 'A', FT_LOAD_DEFAULT)) != 0) error_print("glyph not found\n",error);

	return 0;
}
