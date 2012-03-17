#pragma once
//#ifndef _SPRITE_H_
//#define _SPRITE_H_

#include <sys/timeb.h>

class Sprite
{
public:

    __declspec(dllexport) Sprite();
    virtual __declspec(dllexport) ~Sprite() {};

    __declspec(dllexport) void render();

    __declspec(dllexport) void setPosition(float fPositionX, float fPositionY) 
    {
        m_fPositionX = fPositionX; 
        m_fPositionY = fPositionY; 
    }

    __declspec(dllexport) void setSize(float fWidth, float fHeight) 
    { 
        m_fWidth  = fWidth;
        m_fHeight = fHeight;
    }

    __declspec(dllexport) void  setPositionX(float fPositionX) 
	{
		m_fPositionX = fPositionX; 
	}

    __declspec(dllexport) float getPositionX(void) 
	{
		return m_fPositionX; 
	}

    __declspec(dllexport) void  setPositionY(float fPositionY) 
	{ 
		m_fPositionY = fPositionY; 
	}

    __declspec(dllexport) float getPositionY(void)
	{
		return m_fPositionY;
	}
   
    __declspec(dllexport) void  setWidth(float fWidth)
	{
		m_fWidth = fWidth;
	}

    __declspec(dllexport) float getWidth(void) 
	{
		return m_fWidth; 
	}

    __declspec(dllexport) void  setHeight(float fHeight) 
	{ 
		m_fHeight = fHeight;
	}

    __declspec(dllexport) float getHeight(void) 
	{ 
		return m_fHeight;
	}

    __declspec(dllexport) void  setRotation(float fRotation) 
	{ 
		m_fRotation = m_fRotation; 
	}

    __declspec(dllexport) float getRotation(void) 
	{ 
		return m_fRotation; 
	}

    __declspec(dllexport) void  setAlpha(float fAlpha) 
	{ 
		m_fAlpha = fAlpha;
	}

    __declspec(dllexport) float getAlpha(void) 
	{ 
		return m_fAlpha;
	}
    
    __declspec(dllexport) void setTextureID(GLuint textureID) 
	{ 
		m_textureID = textureID;
	}

    __declspec(dllexport) int getTextureID(void) 
	{ 
		return m_textureID;
	}

    __declspec(dllexport) void setTextureWidth(int nTextureWidth)
	{ 
		m_nTextureWidth = nTextureWidth;
	}

    __declspec(dllexport) int getTextureWidth() 
	{ 
		return m_nTextureWidth;
	}

    __declspec(dllexport) void setTextureHeight(int nTextureHeight) 
	{
		m_nTextureHeight = nTextureHeight;
	}

    __declspec(dllexport) int getTextureHeight() 
	{ 
		return m_nTextureHeight;
	}

    __declspec(dllexport) void setFrameWidth(int nFrameWidth)
	{ 
		m_nFrameWidth = nFrameWidth; 
	}

    __declspec(dllexport) int getFrameWidth() 
	{ 
		return m_nFrameWidth;
	}

    __declspec(dllexport) void setFrameHeight(int nFrameHeight) 
	{
		m_nFrameHeight = nFrameHeight;
	}

    __declspec(dllexport) int getFrameHeight() 
	{ 
		return m_nFrameHeight; 
	}

    __declspec(dllexport) void setNumFrameColumns(int nNumFrameColumns) 
	{
		m_nNumFrameColumns = nNumFrameColumns;
	}

    __declspec(dllexport) int getNumFrameColumns() 
	{ 
		return m_nNumFrameColumns;
	}

    __declspec(dllexport) void setNumFrameRows (int nNumFrameRows) 
	{
		m_nNumFrameRows = nNumFrameRows;
	}

    __declspec(dllexport) int getNumFrameRows ()
	{ 
		return m_nNumFrameRows; 
	}

    __declspec(dllexport) void setTotalFrames(int nTotalFrames) 
	{ 
		m_nTotalFrames = nTotalFrames;
	}

    __declspec(dllexport) int getTotalFrames() 
	{ 
		return m_nTotalFrames; 
	}

    __declspec(dllexport) void setOffsetX(int nOffsetX) 
	{ 
		m_nOffsetX = nOffsetX; 
	}

    __declspec(dllexport) int getOffsetX() 
	{ 
		return m_nOffsetX;
	}

    __declspec(dllexport) void setOffsetY(int nOffsetY)
	{ 
		m_nOffsetY = nOffsetY; 
	}

    __declspec(dllexport) int getOffsetY() 
	{ 
		return m_nOffsetY;
	}

    __declspec(dllexport) void setFrameDelay( float fFrameDelay )
	{ 
		m_fFrameDelay = fFrameDelay;
	}

    __declspec(dllexport) float getFrameDelay(void) 
	{ 
		return m_fFrameDelay; 
	}

    __declspec(dllexport) void  setTextureAnimeInfo( int nTextureWidth, int nTextureHeight, 
													 int nFrameWidth,   int nFrameHeight,
													 int nNumFrameColumns, int nNumFrameRows, 
													 int nTotalFrames,
													 int nOffsetX = 0, int nOffsetY = 0 )
    {
        m_nTextureWidth    = nTextureWidth;
        m_nTextureHeight   = nTextureHeight;
        m_nFrameWidth      = nFrameWidth;
        m_nFrameHeight     = nFrameHeight;
        m_nNumFrameColumns = nNumFrameColumns;
        m_nNumFrameRows    = nNumFrameRows;
        m_nTotalFrames     = nTotalFrames;
        m_nOffsetX         = nOffsetX;
        m_nOffsetY         = nOffsetY;
    }

private:

    // Sprite Controls...

    float  m_fPositionX;
    float  m_fPositionY;
    float  m_fWidth;
    float  m_fHeight;
    float  m_fRotation;
    float  m_fAlpha;

    // Texture Animation Settings...

    GLuint m_textureID;
    float  m_fFrameDelay;
    int    m_nNumFrameColumns;
    int    m_nNumFrameRows;
    int    m_nTotalFrames;
    int    m_nTextureWidth;
    int    m_nTextureHeight;
    int    m_nFrameWidth;
    int    m_nFrameHeight;
    int    m_nOffsetX;
    int    m_nOffsetY;

    // Frame tracking variables...

    int    m_nFrameNumber;
    int    m_nCurrentRow;
    int    m_nCurrentColumn;
	timeb  m_lastTime;
    bool   m_bFirstRendering;
};

//#endif /* _SPRITE_H_ */
