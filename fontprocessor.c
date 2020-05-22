#include<ft2build.h>
#include FT_FREETYPE_H
#include<stdio.h>

FT_Library  library;
FT_Face font_face;

void erro_print(char *mesg)
{
	printf("error: %s\n",mesg);
	exit(1);
}

int main(int argc,char *argv[])
{
	FT_UInt glyph_index;
	//TODO : parse arguments
	if FT_Init_FreeType(&library) ? erro_print("library initialization\n");
	//load default font
	if FT_New_Face(library, PATH_WHITE_RABBIT, 0, &font_face) ? erro_print("failed to load font\n");

	error = FT_Set_Char_Size(
          white_face,    /* handle to face object           */
          0,       /* char_width in 1/64th of points  */
          16*64,   /* char_height in 1/64th of points */
          300,     /* horizontal device resolution    */
          300 );   /* vertical device resolution      */
	if(error)
	{
		erro_print("set font size\n");
	}
	error = FT_Set_Pixel_Sizes(
				          white_face,   /* handle to face object */
				          0,      /* pixel_width           */
				          16 );
	if(error)
	{
		erro_print("set pixel size\n");
	}
	glyph_index = FT_Get_Char_Index(white_face, 65);
	if(glyph_index == 0)
	{
		erro_print("character not found!!");
	}
	error = FT_Load_Glyph(
          white_face,          /* handle to face object */
          glyph_index,   /* glyph index           */
          0 );  /* load flags, see below */
	if(error)
	{
		erro_print("failed load glyph from face\n");

	}
	error = FT_Render_Glyph( white_face->glyph,   /* glyph slot  */
			                         FT_RENDER_MODE_MONO);
	if(error)
	{
		erro_print("bitmap conversion failed!!\n");

	}
		return 0;
}
