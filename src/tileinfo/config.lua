-- Default tile size
tile_size = {x = 32, y = 32}
-- Init the sprite sheet
model = {} 
model.sprite_sheet = './tileinfo/terrain.png'
-- Create new animation state
default = {name = 'default'}
-- Load frames for the 'default' state
default.frames={}
for i = 0,2 do
	default.frames[i] = {top_left = {x = 576 + i*tile_size.x,
	                                 y = 160}, 
                         size = tile_size}
end
-- Load the 'default' state
model.states = {}
model.states[0] = default
-- Allow to start animation from random frame
model.random_frame = true

GameItem{
	id = 0x1,
	name = 'water',
	model = model
}

-- Init the sprite sheet
model = {} 
model.sprite_sheet = './tileinfo/terrain.png'
-- Create new animation state
default = {name = 'default'}
-- Load frames for the 'default' state
default.frames={}
default.frames[0] = {top_left = {x = 0, y = 704}, 
                         size = tile_size}
-- Load the 'default' state
model.states = {}
model.states[0] = default
-- Allow to start animation from random frame
model.random_frame = false

GameItem{
	id = 0xFFFFFF,
	name = 'undefined',
	model = model
}


-- Init the sprite sheet
model = {} 
model.sprite_sheet = './tileinfo/terrain.png'
-- Create new animation state
states = {[0] = {name = 'default0'},
		  [1] = {name = 'default1'}}
-- Load frames for the states
for i = 0, #states do
	states[i].frames = {}
	states[i].frames[0] = {top_left = {x = 128 + i*tile_size.x,
	                                   y = 160}, 
                         	   size = tile_size}
end
-- Load the 'default' state
model.states = states
-- Allow to start animation from random frame
model.random_frame = false

GameItem{
	id = 0x2,
	name = 'ground',
	model = model
}

-- Init the sprite sheet
model = {} 
model.sprite_sheet = './tileinfo/chicken.png'
-- Create new animation state
states = {[0] = {name = 'eat_up'},
		  [1] = {name = 'eat_left'},
		  [2] = {name = 'eat_down'},
		  [3] = {name = 'eat_right'},
		  [4] = {name = 'walk_up'},
		  [5] = {name = 'walk_left'},
		  [6] = {name = 'walk_down'},
		  [7] = {name = 'walk_right'}}
-- Load frames for the states
for i = 0, #states do
	states[i].frames = {}
	for k = 0, 3 do
		states[i].frames[k] = {top_left = {x = k*tile_size.x,
	                                       y = i*tile_size.y}, 
                         	   size = tile_size}
	end
end
-- Load the 'default' state
model.states = states
-- Allow to start animation from random frame
model.random_frame = false

GameItem{
	id = 0x101,
	name = 'herbivorous',
	model = model
}
