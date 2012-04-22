if EVENT_TYPE == EVENT_TYPE_DIALOG then
	if DIALOG_ID == 0 then
		SendDialog(NPC_ID, 'Dialog title #1', '<p rect="16;32;240;48">Test text #1</p><button rect="16;64;64;24" onclick="1">OK</button>', CHARACTER_ID);
	elseif DIALOG_ID == 1 then
		SendDialog(NPC_ID, 'Dialog title #2', '<p rect="16;32;240;48">Test text #2</p><button rect="16;64;64;24" onclick="2">Finish</button>', CHARACTER_ID);
	elseif DIALOG_ID == 2 then
		SendDialog(NPC_ID, 'Dialog title #3', '<p rect="16;32;240;48">Congratulations!</p>', CHARACTER_ID);
		end;
	end;
