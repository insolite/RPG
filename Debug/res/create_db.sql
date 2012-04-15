/*=============Game Resources=============*/

CREATE TABLE Config (
	`key` VARCHAR(32) PRIMARY KEY,
	`val` VARCHAR(64)
	);

CREATE TABLE MapCell (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(64),
	tags VARCHAR(1024),
	cellProperty INTEGER
	);

CREATE TABLE NPC (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(64),
	tags VARCHAR(1024)
	);

CREATE TABLE Item (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(64),
	tags VARCHAR(1024)
	);

CREATE TABLE `Static` (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(64),
	tags VARCHAR(1024)
	);

CREATE TABLE `Character` (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(64),
	tags VARCHAR(1024)
);

CREATE TABLE Quest (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(64),
	tags VARCHAR(1024)
);

CREATE TABLE Skill (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(64),
	tags VARCHAR(1024)
);

/*=============Game Data=============*/

CREATE TABLE Location (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
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
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	baseId INTEGER,
	x INTEGER,
	y INTEGER,
	locationId INTEGER
	);

CREATE TABLE CurrentItem (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	baseId INTEGER,
	x INTEGER,
	y INTEGER,
	locationId INTEGER,
	currentCharacterId INTEGER,
	`count` INTEGER
	);

CREATE TABLE CurrentStatic (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	baseId INTEGER,
	x INTEGER,
	y INTEGER,
	locationId INTEGER
	);

CREATE TABLE `CurrentCharacter` (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	baseId INTEGER,
	x INTEGER,
	y INTEGER,
	locationId INTEGER,
	
	login VARCHAR(32),
	password VARCHAR(32)
);

CREATE TABLE CurrentQuest (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	baseId INTEGER,
	currentCharacterId INTEGER,
	`state` INTEGER
);

CREATE TABLE CurrentSkill (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	baseId INTEGER,
	currentCharacterId INTEGER
);

/*=============Init resources=============*/

INSERT INTO MapCell(name, tags, cellProperty) VALUES ('Green grass', 'grass,free,something', 0);
INSERT INTO MapCell(name, tags, cellProperty) VALUES ('Red grass', 'grass', 1);

INSERT INTO NPC(name, tags) VALUES ('Test NPC', '');

INSERT INTO Item(name, tags) VALUES ('Test Item', '');

INSERT INTO `Static`(name, tags) VALUES ('Test Static', '');

INSERT INTO Skill(name, tags) VALUES ('SayHello', '');
INSERT INTO Skill(name, tags) VALUES ('Spawn 4 NPCs', '');

INSERT INTO `Character`(name, tags) VALUES ('Dwarf', '');

/*=============Init data=============*/

INSERT INTO CurrentCharacter(baseId, x, y, locationId, login, password) VALUES (1, 4, 8, 1, 'admin', '1234');
INSERT INTO CurrentCharacter(baseId, x, y, locationId, login, password) VALUES (1, 5, 9, 1, 'admin2', '1234');
INSERT INTO CurrentCharacter(baseId, x, y, locationId, login, password) VALUES (1, 2, 5, 1, 'admin3', '1234');
INSERT INTO CurrentCharacter(baseId, x, y, locationId, login, password) VALUES (1, 7, 4, 1, 'admin4', '1234');

/*May occur relation error (currentCharacterId is not actually known)*/
INSERT INTO CurrentSkill(baseId, currentCharacterId) VALUES (1, 1);
INSERT INTO CurrentSkill(baseId, currentCharacterId) VALUES (1, 2);
INSERT INTO CurrentSkill(baseId, currentCharacterId) VALUES (1, 3);
INSERT INTO CurrentSkill(baseId, currentCharacterId) VALUES (1, 4);
INSERT INTO CurrentSkill(baseId, currentCharacterId) VALUES (2, 1);
INSERT INTO CurrentSkill(baseId, currentCharacterId) VALUES (2, 2);
INSERT INTO CurrentSkill(baseId, currentCharacterId) VALUES (2, 3);
INSERT INTO CurrentSkill(baseId, currentCharacterId) VALUES (2, 4);

INSERT INTO CurrentItem(baseId, x, y, locationId, currentCharacterId, `count`) VALUES (1, 0, 0, 0, 1, 10);
INSERT INTO CurrentItem(baseId, x, y, locationId, currentCharacterId, `count`) VALUES (1, 0, 0, 0, 2, 10);
INSERT INTO CurrentItem(baseId, x, y, locationId, currentCharacterId, `count`) VALUES (1, 0, 0, 0, 3, 10);
INSERT INTO CurrentItem(baseId, x, y, locationId, currentCharacterId, `count`) VALUES (1, 0, 0, 0, 4, 10);
