#include "StdAfx.h"
#include "Sprite.h"

Sprite::Sprite()
{
    m_fPositionY = 0.0f;
    m_fPositionX = 0.0f;
    m_fWidth     = 1.0f;
    m_fHeight    = 1.0f;
    m_fAlpha     = 1.0f;
    m_textureID  = 0;
    m_fRotation  = 0.0f;

    m_nNumFrameColumns = 1;
    m_nNumFrameRows    = 1;
    m_nTotalFrames     = 1;

    m_nTextureWidth  = 256;
    m_nTextureHeight = 256;
    m_nFrameWidth    = 256;
    m_nFrameHeight   = 256;
    m_nOffsetX       = 0;
    m_nOffsetY       = 0;

    m_nFrameNumber    = 0;
    m_nCurrentRow     = 0;
    m_nCurrentColumn  = 0;
    m_bFirstRendering = true;
};


void Sprite::render() 
{
	timeb currentTime;
    float  fElapsed = 0.0f;

    if( m_bFirstRendering == true )
    {
		ftime( &m_lastTime );
        currentTime = m_lastTime;
        m_bFirstRendering = false;
    }
    else
    {
		ftime( &currentTime );

        // This is accurate to one second
        fElapsed  = (float)(currentTime.time - m_lastTime.time);
        // This gets it down to one ms
        fElapsed += (float)((currentTime.millitm - m_lastTime.millitm) / 1000.0f);
    }

    // Set up the rotation and translation matrices
    glPushMatrix();
    glTranslatef( (float)m_fPositionX,(float) m_fPositionY, 0.0f );
    glRotatef( m_fRotation, 0.0f, 0.0f, 1.0f );

    //
    // Push back and cache the current OpenGl state before changing it.
    //

    glPushAttrib( GL_TEXTURE_BIT | GL_DEPTH_TEST | GL_LIGHTING );

    glEnable( GL_TEXTURE_2D );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_LIGHTING );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glEnable( GL_ALPHA_TEST );
    glAlphaFunc( GL_GREATER, 0 );

    glBindTexture( GL_TEXTURE_2D, m_textureID );


    // If the frames of animation don't fill up the whole texture, you'll need 
    // to find the sub-range within the standard texture range (0.0 to 1.0)
    // that the frames do exist within.
    float fSubRange_s = (1.0f / m_nTextureWidth ) * 
                        (m_nFrameWidth  * m_nNumFrameColumns);
    
    float fSubRange_t = (1.0f / m_nTextureHeight) * 
                        (m_nFrameHeight * m_nNumFrameRows);

    // No convert the Width and Height of a frame into texture values...
    float fFrame_s = fSubRange_s / m_nNumFrameColumns;
    float fFrame_t = fSubRange_t / m_nNumFrameRows;

    // Now, calculate the new s/t texture values for the four corners 
    // of the quad based on the current column and row of the animation
    float fLowerLeft_s  = m_nCurrentColumn * fFrame_s;
    float fLowerLeft_t  = 1.0f - (m_nCurrentRow * fFrame_t) - fFrame_t;

	float fLowerRight_s = (m_nCurrentColumn * fFrame_s) + fFrame_s;
    float fLowerRight_t = 1.0f - (m_nCurrentRow * fFrame_t) - fFrame_t;

	float fUpperRight_s = (m_nCurrentColumn * fFrame_s) + fFrame_s;
    float fUpperRight_t = 1.0f - (m_nCurrentRow * fFrame_t);

	float fUpperLeft_s  = m_nCurrentColumn * fFrame_s;
    float fUpperLeft_t  = 1.0f - (m_nCurrentRow * fFrame_t);

    // Apply an offset into texture if the first frame is not located 
    // in the upper left corner of the texture as normal.

    if( m_nOffsetX > 0 || m_nOffsetY > 0 )
    {
        float fOffset_s = (1.0f / m_nTextureWidth ) * m_nOffsetX;
        float fOffset_t = (1.0f / m_nTextureHeight) * m_nOffsetY;

        fLowerLeft_s  += fOffset_s;
        fLowerLeft_t  -= fOffset_t;

	    fLowerRight_s += fOffset_s;
        fLowerRight_t -= fOffset_t;

	    fUpperRight_s += fOffset_s;
        fUpperRight_t -= fOffset_t;

	    fUpperLeft_s  += fOffset_s;
        fUpperLeft_t  -= fOffset_t;
    }

    // We know where the sprite's center is at, now half its width and height
    // to find where its four corners should be placed for generating a GL_QUAD.
    float fRelativeX = (m_fWidth  / 2.0f);
    float fRelativeY = (m_fHeight / 2.0f);

    glBegin( GL_QUADS );
    {
        glColor4f( 1.0f, 1.0f, 1.0f, m_fAlpha );
        glTexCoord2f(fLowerLeft_s, fLowerLeft_t);   // Lower Left of quad
        glVertex2f( -fRelativeX, -fRelativeY );

        glColor4f( 1.0f, 1.0f, 1.0f, m_fAlpha );
        glTexCoord2f(fLowerRight_s, fLowerRight_t); // Lower Right of quad
        glVertex2f( fRelativeX, -fRelativeY );

        glColor4f( 1.0f, 1.0f, 1.0f, m_fAlpha );
        glTexCoord2f(fUpperRight_s, fUpperRight_t); // Upper Right of quad
        glVertex2f( fRelativeX, fRelativeY );

        glColor4f( 1.0f, 1.0f, 1.0f, m_fAlpha );
        glTexCoord2f(fUpperLeft_s, fUpperLeft_t);   // Upper Left of quad
        glVertex2f(-fRelativeX, fRelativeY );
    }
    glEnd();

    glPopAttrib();

    // Pop the matrix that we pushed above
    glPopMatrix();

    // If the frame delay has elapsed, move on to the next frame of animation...
    if( fElapsed >= m_fFrameDelay )
    {
        m_lastTime = currentTime;
        
        ++m_nCurrentColumn;
        ++m_nFrameNumber;

        if( m_nCurrentColumn >= m_nNumFrameColumns )
        {
            m_nCurrentColumn = 0;
            ++m_nCurrentRow;
        }

        if( m_nCurrentRow >= m_nNumFrameRows )
        {
            m_nCurrentRow    = 0;
            m_nCurrentColumn = 0;
        }

        if( m_nFrameNumber >= m_nTotalFrames )
        {
            m_nCurrentRow    = 0;
            m_nCurrentColumn = 0;
            m_nFrameNumber   = 0;
        }
    }
}	