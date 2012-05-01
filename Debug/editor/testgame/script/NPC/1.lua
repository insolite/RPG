if EVENT_TYPE == EVENT_TYPE_DIALOG then
	if DIALOG_ID == 0 then
		SendDialog(NPC_ID, 'Hello', '<p rect="16;32;240;112">Hello, stranger! I have a work for you... You are to find one man at the east-nothern. You will recognize him...</p><button rect="16;128;128;24" onclick="1">OK, I will do it</button>', CHARACTER_ID);
		end;
	end;
