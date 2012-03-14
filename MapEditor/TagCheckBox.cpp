#include "StdAfx.h"
#include "TagCheckBox.h"
#include "MapObjectSelectWindow.h"

TagCheckBox::TagCheckBox(std::string caption, bool selected) : CheckBox(caption, selected)
{
}

TagCheckBox::~TagCheckBox(void)
{
}

void TagCheckBox::mouseClicked(gcn::MouseEvent& mouseEvent)
{
	CheckBox::mouseClicked(mouseEvent); //gcn...

	int i, j;
	MapObjectSelectWindow* parent;

	parent = (MapObjectSelectWindow*)this->getParent();

	//TODO: Update through SQL

	parent->listModel->clear();

	i = 0;
	while (i < parent->mapObjectsCount)
	{
		j = 0;
		while (j < parent->mapObjects[i]->tagsCount)
		{
			if (!strcmp(parent->mapObjects[i]->tags[j], parent->mapObjectsTags[i]->getCaption().c_str()))
				break;
			j++;
		}
		if (j < parent->tagsCount)
		{
			parent->listModel->add(parent->mapObjects[i]->name);
		}
		i++;
	}

	/*
	//Patrically modifying
	if (this->isSelected())
	{ //Checked

	}
	else
	{ //Unchecked
		i = 0;
		while (i < parent->mapObjectsCount)
		{
			j = 0;
			while (j < parent->mapObjects[i]->tagsCount)
			{
				if (!strcmp(parent->mapObjects[i]->tags[j], parent->mapObjectsTags[i]->getCaption().c_str()))
					break;
				j++;
			}
			if (j < parent->tagsCount)
			{
				parent->listModel->remove(i);
				parent->mapObjectsCount--;
			}
			i++;
		}
	}
	*/
	//((MapObjectSelectWindow*)this->getParent())->mapObjectsTags[0];
	//((MapObjectSelectWindow*)this->getParent())->listBox[0]->setVisible(false);
	//((MapObjectSelectWindow*)this->getParent())->listModel->remove(0);
}
