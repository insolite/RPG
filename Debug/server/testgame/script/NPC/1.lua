EVENT_TYPE_ATTACK = 0;
EVENT_TYPE_KILL = 1;
EVENT_TYPE_DIALOG = 2;

if EVENT_TYPE == EVENT_TYPE_DIALOG then
	if DIALOG_ID == 0 then
		--string.format("%d", id)
		SendDialog(NPC_ID, 'Dialog title', 'Dialog text', CHARACTER_ID);
		end;
	end;
