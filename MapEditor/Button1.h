#pragma once
#include "..\include\guichan\guichan.hpp"
//#include "..\include\guichan\guichan\mouseevent.hpp"
class Button1 :
	public gcn::Button
{
public:
    void mousePressed(gcn::MouseEvent &mouseEvent)
    {
        printf("Action : %d\n", mouseEvent.getButton());
    }

	Button1(char* label) : Button(label)
	{
		
	}
	//~Button1(void);
};

