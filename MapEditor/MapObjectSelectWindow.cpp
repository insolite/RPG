#include "StdAfx.h"
#include "MapObjectSelectWindow.h"

MapObjectSelectWindow::MapObjectSelectWindow(std::string caption, MapObject** _mapObjects, int _mapObjectsCount, int _brushIndex) : FocusingWindow(caption)
{
	int i, j;
	vector<std::string> tags;

	brushIndex = _brushIndex;
	mapObjects = _mapObjects;
	mapObjectsCount = _mapObjectsCount;

	this->setFocusable(true);
	this->setVisible(false);
	
	okButton = new MapObjectSelectOKButton("OK");
	this->add(okButton, 528, 320);

	//Tags collecting
	//TODO: All checked/unchecked
	//tags.push_back("All");
	for (i = 0; i < mapObjectsCount; i++)
	{
		for (j = 0; j < mapObjects[i]->tagsCount; j++)
		{
			if (std::find(tags.begin(), tags.end(), mapObjects[i]->tags[j]) == tags.end())
				tags.push_back(mapObjects[i]->tags[j]);
		}
	}
	tagsCount = tags.size();
	if (tagsCount > 0)
	{
		mapObjectsTags = new TagCheckBox*[tagsCount];
		for (i = 0; i < tagsCount; i++)
		{
			mapObjectsTags[i] = new TagCheckBox(tags[i], true);
			mapObjectsTags[i]->setFocusable(false);
			this->add(mapObjectsTags[i], 8, 8 + 16 * i);
		}
	}

	//NPC select ListBox
	listModel = new StringListModel();
	for (i = 0; i < mapObjectsCount; i++)
		listModel->add(mapObjects[i]->name);
	listBox = new gcn::ListBox(listModel);
	listBox->setSelected(0);
	
	//TODO:
	//Auto resize ListBox. adjustSize doesn't work for width. Sadly...
	listBox->setSize(512, 0);
	listBox->adjustSize();
	
	listBoxScrollArea = new gcn::ScrollArea();
	listBoxScrollArea->setHorizontalScrollPolicy(gcn::ScrollArea::SHOW_AUTO);
	listBoxScrollArea->setVerticalScrollPolicy(gcn::ScrollArea::SHOW_AUTO);
	listBoxScrollArea->setContent(listBox);
	listBoxScrollArea->setSize(256, 320);
	
	this->add(listBoxScrollArea, 128, 8);

	//NPC preview image
	npcPreviewImage = gcn::Image::load("test_preview.bmp");
	npcPreviewIcon = new gcn::Icon(npcPreviewImage); // http://theinsaneatlantian.deviantart.com/art/RPG-Monster-2-252430339?q=boost%3Apopular%20rpg%20monster&qo=36
	this->add(npcPreviewIcon, 400, 8);
	
	//Close button
	closeButton = new ToggleWindowVisibilityButton("x", this);
	this->add(closeButton);

	this->resizeToContent();
	((ToggleWindowVisibilityButton*)closeButton)->Dock();
	this->setPosition((Universe::instance->screenWidth - Universe::instance->toolbarWidth) / 2 - this->getWidth() / 2, Universe::instance->screenHeight / 2 - this->getHeight() / 2);
}


MapObjectSelectWindow::~MapObjectSelectWindow(void)
{
	for (int i = 0; i < tagsCount; i++)
	{
		delete mapObjectsTags[i];
	}
	delete mapObjectsTags;
	delete listModel;
	delete listBox;
	delete listBoxScrollArea;
	delete npcPreviewIcon;
	delete npcPreviewImage;
	delete okButton;
	delete closeButton;
}
