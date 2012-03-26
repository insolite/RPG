#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "MapObject.h"

MapObject::MapObject(SqliteResult sqliteResult)
{
	id = sqliteResult.integers["id"];
	name = new char[sqliteResult.strings["name"].length() + 1];
	strcpy(name, sqliteResult.strings["name"].c_str());

	int i, j, length;

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
		while ((i + j) < length && sqliteResult.strings["tags"][i + j] != '|')
		{
			tags[tagsCount - 1][j] = sqliteResult.strings["tags"][i + j];
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
