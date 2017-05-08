-- Number of ticks for the whole 
-- animation sequence for one state
animation_time = 16
-- Default tile size
tile_size = {x = 32, y = 32}

-- Init the sprite sheet
model = {} 
model.sprite_sheet = './tileinfo/water.png'
-- Create new animation state
default = {name = 'default'}
-- Load frames for the 'default' state
default.frames={}
for i = 0,4 do
	default.frames[i] = {top_left = {x = i*tile_size.x + 384,
	                                 y = 4*tile_size.y + 194}, 
                         size = tile_size}
end
default.random_frame  = true
default.global_frames = 16
-- Load the 'default' state
model.states = {}
model.states[0] = default
-- Allow to start animation from random frame

GameItem{
	id = 0x1,
	name = 'tile_water',
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
default.random_frame  = false
default.global_frames = 1
-- Load the 'default' state
model.states = {}
model.states[0] = default

GameItem{
	id = 0xFFFFFF,
	name = 'object_undefined',
	model = model
}

-- Init the sprite sheet
model = {} 
model.sprite_sheet = './tileinfo/terrain.png'
-- Create new animation state
default = {name = 'default'}
-- Load frames for the 'default' state
default.frames={}
default.frames[0] = {top_left = {x = 64, y = 704}, 
                         size = tile_size}
default.random_frame  = false
default.global_frames = 1
-- Load the 'default' state
model.states = {}
model.states[0] = default

GameItem{
	id = 0x103,
	name = 'object_corpse',
	model = model
}

-- Init the sprite sheet
model = {} 
model.sprite_sheet = './tileinfo/terrain.png'
-- Create new animation state
default = {name = 'default'}
-- Load frames for the 'default' state
default.frames={}
default.frames[0] = {top_left = {x = 32, y = 704}, 
                         size = tile_size}
default.random_frame  = false
default.global_frames = 1
-- Load the 'default' state
model.states = {}
model.states[0] = default

GameItem{
	id = 0x0,
	name = 'tile_undefined',
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
    states[i].random_frame = false
	states[i].global_frames = 1
end
-- Load the 'default' state
model.states = states
-- Allow to start animation from random frame

GameItem{
	id = 0x2,
	name = 'tile_grass',
	model = model
}

-- Init the sprite sheet
model = {} 
model.sprite_sheet = './tileinfo/chicken.png'
-- Create new animation state
state_idle = 0x20
state_walk = 0x10
dir_up = 0x1
dir_right = 0x2
dir_down = 0x4
dir_left = 0x8
states = {[state_idle | dir_up] = {name = 'eat_up'},
		  [state_idle | dir_left] = {name = 'eat_left'},
		  [state_idle | dir_down] = {name = 'eat_down'},
		  [state_idle | dir_right] = {name = 'eat_right'},
		  [state_walk | dir_up] = {name = 'walk_up'},
		  [state_walk | dir_left] = {name = 'walk_left'},
		  [state_walk | dir_down] = {name = 'walk_down'},
		  [state_walk | dir_right] = {name = 'walk_right'}}
-- Load frames for the states
------------------------------------------------
states[state_idle | dir_up].frames = {}
for k = 0, 3 do
	states[state_idle | dir_up].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 0*tile_size.y}, 
                     	   size = tile_size}
end
states[state_idle | dir_up].random_frame = true
states[state_idle | dir_up].global_frames = 1

------------------------------------------------
states[state_idle | dir_right].frames = {}
for k = 0, 3 do
	states[state_idle | dir_right].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 3*tile_size.y}, 
                     	   size = tile_size}
end
states[state_idle | dir_right].random_frame = true
states[state_idle | dir_right].global_frames = 1
------------------------------------------------
states[state_idle | dir_down].frames = {}
for k = 0, 3 do
	states[state_idle | dir_down].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 2*tile_size.y}, 
                     	   size = tile_size}
end
states[state_idle | dir_down].random_frame = true
states[state_idle | dir_down].global_frames = 1
------------------------------------------------
states[state_idle | dir_left].frames = {}
for k = 0, 3 do
	states[state_idle | dir_left].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 1*tile_size.y}, 
                     	   size = tile_size}
end
states[state_idle | dir_left].random_frame = true
states[state_idle | dir_left].global_frames = 1
------------------------------------------------
states[state_walk | dir_up].frames = {}
for k = 0, 3 do
	states[state_walk | dir_up].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 4*tile_size.y}, 
                     	   size = tile_size}
end
states[state_walk | dir_up].random_frame = true
states[state_walk | dir_up].global_frames = 1
------------------------------------------------
states[state_walk | dir_right].frames = {}
for k = 0, 3 do
	states[state_walk | dir_right].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 7*tile_size.y}, 
                     	   size = tile_size}
end
states[state_walk | dir_right].random_frame = true
states[state_walk | dir_right].global_frames = 1
------------------------------------------------
states[state_walk | dir_down].frames = {}
for k = 0, 3 do
	states[state_walk | dir_down].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 6*tile_size.y}, 
                     	   size = tile_size}
end
states[state_walk | dir_down].random_frame = true
states[state_walk | dir_down].global_frames = 1
------------------------------------------------
states[state_walk | dir_left].frames = {}
for k = 0, 3 do
	states[state_walk | dir_left].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 5*tile_size.y}, 
                     	   size = tile_size}
end
states[state_walk | dir_left].random_frame = true
states[state_walk | dir_left].global_frames = 1
------------------------------------------------
-- Load the 'default' state
model.states = states
-- Allow to start animation from random frame

GameItem{
	id = 0x101,
	name = 'object_grass_eating',
	model = model
}

-- Init the sprite sheet
model = {} 
model.sprite_sheet = './tileinfo/wolf.png'
-- Create new animation state
states = {[state_idle | dir_up] = {name = 'idle_up'},
		  [state_idle | dir_left] = {name = 'idle_left'},
		  [state_idle | dir_down] = {name = 'idle_down'},
		  [state_idle | dir_right] = {name = 'idle_right'},
		  [state_walk | dir_up] = {name = 'walk_up'},
		  [state_walk | dir_left] = {name = 'walk_left'},
		  [state_walk | dir_down] = {name = 'walk_down'},
		  [state_walk | dir_right] = {name = 'walk_right'}}
-- Load frames for the states
for _, state in pairs(states) do
	state.frames = {}
	state.frames[0] = {top_left = {x = 0, y = 0}, 
                     	   size = tile_size}
	state.random_frame = true
	state.global_frames = 1
end
-- Load the 'default' state
model.states = states
-- Allow to start animation from random frame

GameItem{
	id = 0x201,
	name = 'object_predator',
	model = model
}

