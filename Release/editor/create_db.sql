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

CREATE TABLE StaticObject (
	id INTEGER PRIMARY KEY,
	name VARCHAR(64),
	tags VARCHAR(1024)
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
	id INTEGER PRIMARY KEY
	);

CREATE TABLE CurrentItem (
	id INTEGER PRIMARY KEY
	);

CREATE TABLE CurrentStaticObject (
	id INTEGER PRIMARY KEY
	);

/*=============Init data=============*/

INSERT INTO MapCell VALUES (1, 'Green grass', 'grass|free|something', 0);
INSERT INTO MapCell VALUES (2, 'Red grass', 'grass', 1);

INSERT INTO NPC VALUES (1, 'Test NPC', '');

INSERT INTO Item VALUES (1, 'Test Item', '');

INSERT INTO StaticObject VALUES (1, 'Test StaticObject', '');
