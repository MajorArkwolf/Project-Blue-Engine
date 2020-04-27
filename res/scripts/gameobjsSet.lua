-- Generate 15 new GameObjects
local i = 0;
while (i < 15)
do
	-- Generate the new GameObject (of type Static)
	identifier = GameObject_Manager.add(1);
	new_game_object = GameObject_Manager.get(identifier);

	-- Set the newly created GameObject's model
	new_game_object:setModel("res/model/player_male.obj");

	-- Configure the newly created GameObject's position
	new_game_object:setPos(i * 5, 150, 0);

	-- Configure the newly created GameObject's scale
	new_game_object:setScale(1.5, 1.5, 1.5);

	-- Increment the counter to prevent infinite GameObject generation
	i = i + 1;
end

identifier = GameObject_Manager.add(1);
new_game_object = GameObject_Manager.get(identifier);
new_game_object:setModel("res/model/vikings/SM_Env_Rock_01.fbx");
new_game_object:setPos(100, 150, 100);
new_game_object:setScale(1.0, 1.0, 1.0);