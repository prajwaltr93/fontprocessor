#include<ft2build.h>
#include FT_FREETYPE_H
#include<stdio.h>

#define path_to_font "/home/starkm42/Downloads/white_rabbit/whitrabt.ttf"

FT_Library  library;
FT_Face white_face;

void erro_print(char *mesg)
{
	printf("error: %s\n",mesg);
	exit(1);
}


int main()
{
	FT_UInt glyph_index;
	int error = FT_Init_FreeType(&library);
	if(error)
	{
		erro_print("load library\n");

	}
	else
	{
		printf("success\n");
	}
	//load white rabbit font
	error =  FT_New_Face( library,path_to_font,0,&white_face);
	if(error)
	{
		erro_print("font not loaded\n");
	}

	//loading face params
	printf("number %ld\n",white_face->num_glyphs);
	printf("number %d\n",white_face->num_charmaps);
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
