#include "stdafx.h"
#include "ForwardDeclaration.h"
#include "utilities.h"
#include "SqliteResult.h"
#include "Render.h"
#include "GameObject.h"

GameObject::GameObject(SqliteResult sqliteResult, char* iconPath)
{
	id = sqliteResult.integers["id"];
	strcpy(name, sqliteResult.strings["name"].c_str());

	int i, j, length;
	//TODO: do not load tags when initializationType == Server?
	tagsCount = 0;
	tags = NULL;

	i = 0;
	length = sqliteResult.strings["tags"].length();

	while (i < length)
	{
		tagsCount++;
		tags = (char**)realloc(tags, tagsCount * sizeof(char*));
		tags[tagsCount - 1] = new char[64];
		j = 0;
		while ((i + j) < length && sqliteResult.strings["tags"][i + j] != ',')
		{
			tags[tagsCount - 1][j] = sqliteResult.strings["tags"][i + j];
			j++;
		}
		tags[tagsCount - 1][j] = '\0';
		//printf("%s\n", tags[tagsCount - 1]);
		i += j + 1;
	}

	//Icon
	if (iconPath)
	{
		char path[256];
		sprintf(path, "%s/%d.png", iconPath, id);
		if (FileExists(path))
			icon = Render::instance->driver->getTexture(path);
		else
			icon = NULL;
	}
	else
		icon = NULL;
}

GameObject::~GameObject(void)
{
	for (int i = 0; i < tagsCount; i++)
		delete tags[i];
	delete tags;
}
