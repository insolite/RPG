-- Skill 'SayHello'
-- SayHello('Hello, World!');

if TARGET_TYPE >= 0 then
	--PlayEffect(TARGET_TYPE, TARGET_ID, 1);
	ChangeHp(TARGET_ID, -5);
	PlayAdvancedEffect(CHARACTER_LOCATION_ID, 1, CHARACTER_X, CHARACTER_Y, TARGET_X, TARGET_Y);
	end;
