#include "StdAfx.h"
//#include "../../MapEditor/ClosableWindow.h"
/*
void gcn::Window::draw(gcn::Graphics* graphics)
{
    const Color &faceColor = getBaseColor();
    Color highlightColor, shadowColor;
    const int alpha = getBaseColor().a;
    highlightColor = faceColor + 0x303030;
    highlightColor.a = alpha;
    shadowColor = faceColor - 0x303030;
    shadowColor.a = alpha;

    Rectangle d = getChildrenArea();

    // Fill the background around the content
    graphics->setColor(faceColor);
    // Fill top
    graphics->fillRectangle(Rectangle(0,0,getWidth(),d.y - 1));
    // Fill left
    graphics->fillRectangle(Rectangle(0,d.y - 1, d.x - 1, getHeight() - d.y + 1));
    // Fill right
    graphics->fillRectangle(Rectangle(d.x + d.width + 1,
                                        d.y - 1,
                                        getWidth() - d.x - d.width - 1,
                                        getHeight() - d.y + 1));
    // Fill bottom
    graphics->fillRectangle(Rectangle(d.x - 1,
                                        d.y + d.height + 1,
                                        d.width + 2,
                                        getHeight() - d.height - d.y - 1));

    if (isOpaque())
    {
        graphics->fillRectangle(d);
    }

    // Construct a rectangle one pixel bigger than the content
    d.x -= 1;
    d.y -= 1;
    d.width += 2;
    d.height += 2;

    // Draw a border around the content
    graphics->setColor(shadowColor);
    // Top line
    graphics->drawLine(d.x,
                        d.y,
                        d.x + d.width - 2,
                        d.y);

    // Left line
    graphics->drawLine(d.x,
                        d.y + 1,
                        d.x,
                        d.y + d.height - 1);

    graphics->setColor(highlightColor);
    // Right line
    graphics->drawLine(d.x + d.width - 1,
                        d.y,
                        d.x + d.width - 1,
                        d.y + d.height - 2);
    // Bottom line
    graphics->drawLine(d.x + 1,
                        d.y + d.height - 1,
                        d.x + d.width - 1,
                        d.y + d.height - 1);

    drawChildren(graphics);

    int textX;
    int textY;

    textY = ((int)getTitleBarHeight() - getFont()->getHeight()) / 2;

    switch (getAlignment())
    {
        case Graphics::LEFT:
            textX = 4;
            break;
        case Graphics::CENTER:
            textX = getWidth() / 2;
            break;
        case Graphics::RIGHT:
            textX = getWidth() - 4;
            break;
        default:
            throw GCN_EXCEPTION("Unknown alignment.");
    }

    graphics->setColor(getForegroundColor());
    graphics->setFont(getFont());
    graphics->pushClipArea(Rectangle(0, 0, getWidth() - 100, getTitleBarHeight() - 1));
    graphics->drawText(getCaption(), textX, textY, getAlignment());
    graphics->popClipArea();
	//graphics->pushClipArea(Rectangle(0, 0, getWidth() - 100, getTitleBarHeight() - 1));
	//((ClosableWindow*)this)->closeButton->draw(graphics);
	//graphics->popClipArea();
}
*/