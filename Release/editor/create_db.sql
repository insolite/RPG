/*=============Game Resources=============*/

CREATE TABLE Config (
	`key` VARCHAR(32) PRIMARY KEY,
	`val` VARCHAR(64)
	);

CREATE TABLE MapCell (
	id INTEGER PRIMARY KEY,
	name VARCHAR(64),
	tags VARCHAR(1024),
	cellProperty INTEGER
	);

CREATE TABLE NPC (
	id INTEGER PRIMARY KEY,
	name VARCHAR(64),
	tags VARCHAR(1024)
	);

CREATE TABLE Item (
	id INTEGER PRIMARY KEY,
	name VARCHAR(64),
	tags VARCHAR(1024)
	);

CREATE TABLE `Static` (
	id INTEGER PRIMARY KEY,
	name VARCHAR(64),
	tags VARCHAR(1024)
	);

CREATE TABLE `Character` (
	id INTEGER PRIMARY KEY,
	name VARCHAR(64),
	tags VARCHAR(1024)
);

CREATE TABLE Quest (
	id INTEGER PRIMARY KEY,
	name VARCHAR(64)
);

CREATE TABLE Skill (
	id INTEGER PRIMARY KEY,
	name VARCHAR(64)
);

/*=============Game Data=============*/

CREATE TABLE Location (
	id INTEGER PRIMARY KEY,
	name VARCHAR(64),
	width INTEGER,
	height INTEGER,
	mask BLOB
	);
/*
CREATE TABLE CurrentMapCell (
	id INTEGER PRIMARY KEY
	);
*/
CREATE TABLE CurrentNPC (
	id INTEGER PRIMARY KEY,
	baseId INTEGER,
	x INTEGER,
	y INTEGER,
	locationId INTEGER
	);

CREATE TABLE CurrentItem (
	id INTEGER PRIMARY KEY,
	baseId INTEGER,
	x INTEGER,
	y INTEGER,
	locationId INTEGER
	);

CREATE TABLE CurrentStatic (
	id INTEGER PRIMARY KEY,
	baseId INTEGER,
	x INTEGER,
	y INTEGER,
	locationId INTEGER
	);

CREATE TABLE `CurrentCharacter` (
	id INTEGER PRIMARY KEY,
	baseId INTEGER,
	x INTEGER,
	y INTEGER,
	locationId INTEGER,
	
	login VARCHAR(32),
	password VARCHAR(32)
);

CREATE TABLE CurrentQuest (
	id INTEGER PRIMARY KEY,
	questId INTEGER,
	characterId INTEGER,
	`state` INTEGER
);

CREATE TABLE CurrentSkill (
	id INTEGER PRIMARY KEY,
	skillId INTEGER,
	characterId INTEGER
);

/*=============Init data=============*/

INSERT INTO MapCell VALUES (1, 'Green grass', 'grass|free|something', 0);
INSERT INTO MapCell VALUES (2, 'Red grass', 'grass', 1);

INSERT INTO NPC VALUES (1, 'Test NPC', '');

INSERT INTO Item VALUES (1, 'Test Item', '');

INSERT INTO `Static` VALUES (1, 'Test Static', '');

INSERT INTO `Character` VALUES (1, 'Dwarf', '');
INSERT INTO CurrentCharacter VALUES (1, 1, 'admin', '1234', 1);
