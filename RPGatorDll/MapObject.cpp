#include "StdAfx.h"
#include "MapObject.h"

MapObject::MapObject(std::map<std::string, std::string> strings, std::map<std::string, int> integers)
{
	id = integers["id"];
	name = new char[strings["name"].length() + 1];
	strcpy(name, strings["name"].c_str());

	int i, j, length;

	tagsCount = 0;
	tags = NULL;

	i = 0;
	length = strings["tags"].length();

	while (i < length)
	{
		tagsCount++;
		tags = (char**)realloc(tags, tagsCount * sizeof(char*));
		tags[tagsCount - 1] = new char[64];
		j = 0;
		while ((i + j) < length && strings["tags"][i + j] != '|')
		{
			tags[tagsCount - 1][j] = strings["tags"][i + j];
			j++;
		}
		tags[tagsCount - 1][j] = '\0';
		//printf("%s\n", tags[tagsCount - 1]);
		i += j + 1;
	}
}

MapObject::~MapObject(void)
{
	delete name;
	for (int i = 0; i < tagsCount; i++)
		delete tags[i];
	delete tags;
}
