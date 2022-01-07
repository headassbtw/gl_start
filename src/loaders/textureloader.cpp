#include <bits/types/FILE.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstddef>
#include <loaders/textureloader.hpp>
#include <GLFW/glfw3.h>
using namespace std;
GLuint Loaders::Textures::LoadBMP_Custom(const char *path){

    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;
    unsigned char * data;


    FILE * file = fopen(path,"rb");
    if (!file){
        
        fprintf(stderr,"BMP could not be opened\n");
        return 0;
    }

    if ( fread(header, 1, 54, file)!=54 ){
    fprintf(stderr,"Not a correct BMP file\n");
    return false;
    }
    if ( header[0]!='B' || header[1]!='M' ){
        fprintf(stderr,"Not a correct BMP file\n");
        return 0;
    }
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    if (imageSize==0)    imageSize=width*height*3;
    if (dataPos==0)      dataPos=54;


    data = new unsigned char [imageSize];

    fread(data,1,imageSize,file);

    fclose(file);

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    return textureID;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint MissingFallback;


char sauce[] =
{(char)0x44, (char)0x44, (char)0x53, (char)0x20, (char)0x7C, (char)0x00, (char)0x00, (char)0x00, 
 (char)0x07, (char)0x10, (char)0x0A, (char)0x00, (char)0x10, (char)0x00, (char)0x00, (char)0x00,
 (char)0x10, (char)0x00, (char)0x00, (char)0x00, (char)0x80, (char)0x00, (char)0x00, (char)0x00,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x05, (char)0x00, (char)0x00, (char)0x00,
 (char)0x47, (char)0x49, (char)0x4D, (char)0x50, (char)0x2D, (char)0x44, (char)0x44, (char)0x53,
 (char)0x5C, (char)0x09, (char)0x03, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x20, (char)0x00, (char)0x00, (char)0x00,
 (char)0x04, (char)0x00, (char)0x00, (char)0x00, (char)0x44, (char)0x58, (char)0x54, (char)0x31,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x08, (char)0x10, (char)0x40, (char)0x00,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x1F, (char)0xF8, (char)0x1F, (char)0xF8, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x1F, (char)0xF8, (char)0x1F, (char)0xF8, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x1F, (char)0xF8, (char)0x1F, (char)0xF8, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x1F, (char)0xF8, (char)0x1F, (char)0xF8, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x1F, (char)0xF8, (char)0x1F, (char)0xF8, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x1F, (char)0xF8, (char)0x1F, (char)0xF8, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x1F, (char)0xF8, (char)0x1F, (char)0xF8, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x1F, (char)0xF8, (char)0x1F, (char)0xF8, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0xAA, (char)0xAA, (char)0xAA, (char)0xAA,
 (char)0x1F, (char)0xF8, (char)0x00, (char)0x00, (char)0x05, (char)0x05, (char)0x50, (char)0x50,
 (char)0x1F, (char)0xF8, (char)0x00, (char)0x00, (char)0x05, (char)0x05, (char)0x50, (char)0x50,
 (char)0x1F, (char)0xF8, (char)0x00, (char)0x00, (char)0x05, (char)0x05, (char)0x50, (char)0x50,
 (char)0x1F, (char)0xF8, (char)0x00, (char)0x00, (char)0x05, (char)0x05, (char)0x50, (char)0x50,
 (char)0x1F, (char)0xF8, (char)0x00, (char)0x00, (char)0x11, (char)0x44, (char)0x11, (char)0x44,
 (char)0x10, (char)0x80, (char)0x0F, (char)0x78, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF,
 (char)0x10, (char)0x80, (char)0x0F, (char)0x78, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF};

GLuint Loaders::Textures::LoadSauce(){
	unsigned char header[124];
	char filecode[4]; 
	memcpy(filecode, sauce,4);
	if (strncmp(filecode, "DDS ", 4) != 0) { 
		fprintf(stderr,"somehow sauce wasn't a dds file???\n");
		return 0; 
	}
	
	/* get the surface desc */ 
	memcpy(header,sauce+4,124);

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);

 
	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */ 
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 

	memcpy(buffer,sauce + 128,bufsize);

	unsigned int components  = 3; //hardcoded to 3, as per DXT1 
	unsigned int format;
	format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; //it's always DXT1, i hardcoded it

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
	
	unsigned int blockSize = 8;
	unsigned int offset = 0;

	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
	{ 
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
			0, size, buffer + offset); 
	 
		offset += size; 
		width  /= 2; 
		height /= 2; 

		if(width < 1) width = 1;
		if(height < 1) height = 1;

	} 

	free(buffer); 
	printf("loaded texture in slot %u\n",textureID);
	MissingFallback = textureID;
	return textureID;
}

GLuint Loaders::Textures::LoadDDS(const char *path){
    unsigned char header[124];
	printf("loading texture \"%s\"\n",path);
	FILE *fp; 
 
	/* try to open the file */ 
	fp = fopen(path, "rb"); 
	if (fp == NULL){
		fprintf(stderr,"%s could not be opened\n", path);
		return MissingFallback;
	}
   
	/* verify the type of file */ 
	char filecode[4]; 
	fread(filecode, 1, 4, fp); 
	if (strncmp(filecode, "DDS ", 4) != 0) { 
		fclose(fp); 
		return MissingFallback; 
	}
	
	/* get the surface desc */ 
	fread(&header, 124, 1, fp); 

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);

 
	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */ 
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
	fread(buffer, 1, bufsize, fp); 
	/* close the file pointer */ 
	fclose(fp);

	unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
	unsigned int format;
	switch(fourCC) 
	{ 
	case FOURCC_DXT1: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
		break; 
	case FOURCC_DXT3: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
		break; 
	case FOURCC_DXT5: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
		break; 
	default: 
		free(buffer); 
		return MissingFallback; 
	}

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
	
	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
	unsigned int offset = 0;

	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
	{ 
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
			0, size, buffer + offset); 
	 
		offset += size; 
		width  /= 2; 
		height /= 2; 

		if(width < 1) width = 1;
		if(height < 1) height = 1;

	} 

	free(buffer); 
	printf("loaded texture in slot %u\n",textureID);
	return textureID;
}