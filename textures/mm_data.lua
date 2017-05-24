textures = './textures/'
-- Number of ticks for the whole 
-- animation sequence for one state
animation_time = 16
-- Default tile size
tile_size = {x = 32, y = 32}

-- Init the sprite sheet
model = {} 
model.sprite_sheet = textures .. 'water.png'
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
model.sprite_sheet = textures .. 'terrain.png'
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
model.sprite_sheet = textures .. 'terrain.png'
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
model.sprite_sheet = textures .. 'terrain.png'
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

dir_up = 0x1
dir_right = 0x2
dir_down = 0x4
dir_left = 0x8
dir_none = 0x0
-- Additional mode
dir_add = 0x10
-- Init the sprite sheet
model = {} 
model.sprite_sheet = textures .. 'terrain.png'
-- Create new animation state
states = {[dir_add] = {name = 'center'},
		  [dir_none] = {name = 'filler'},
		  [dir_up] = {name = 'up'},
		  [dir_up | dir_right] = {name = 'up_right'},
		  [dir_right] = {name = 'right'},
		  [dir_right | dir_down] = {name = 'down_right'},
		  [dir_down] = {name = 'down'},
		  [dir_down | dir_left] = {name = 'down_left'},
		  [dir_left] = {name = 'left'},
		  [dir_left | dir_up] = {name = 'up_left'},
		  [dir_add | dir_down | dir_right] = {name = 'add_down_right'},
		  [dir_add | dir_down | dir_left] = {name = 'add_down_left'},
		  [dir_add | dir_up | dir_right] = {name = 'add_up_right'},
		  [dir_add | dir_up | dir_left] = {name = 'add_up_left'},
		  [dir_down | dir_up] = {name = 'up_down'},
		  [dir_left | dir_right] = {name = 'left_right'},
		  [dir_up | dir_down | dir_left] = {name = 'down_up_left'},
		  [dir_down | dir_up | dir_right] = {name = 'down_up_right'},
		  [dir_right | dir_up | dir_left] = {name = 'right_up_left'},
		  [dir_right | dir_down | dir_left] = {name = 'right_down_left'},
		  [dir_right | dir_up | dir_left | dir_down] = {name = 'down_up_left_right'}}
-- Load frames for the states
-----------------------------------------------------------
	states[dir_add].frames = {}
	states[dir_add].frames[0] = {top_left = {x = 128, y = 96}, 
                         	   size = tile_size}
    states[dir_add].random_frame = false
	states[dir_add].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_none].frames = {}
	states[dir_none].frames[0] = {top_left = {x = 32, y = 96}, 
                         	   size = tile_size}
    states[dir_none].random_frame = false
	states[dir_none].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_up].frames = {}
	states[dir_up].frames[0] = {top_left = {x = 128, y = 64}, 
                         	   size = tile_size}
    states[dir_up].random_frame = false
	states[dir_up].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_up | dir_right].frames = {}
	states[dir_up | dir_right].frames[0] = {top_left = {x = 160, y = 64}, 
                         	   size = tile_size}
    states[dir_up | dir_right].random_frame = false
	states[dir_up | dir_right].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_right].frames = {}
	states[dir_right].frames[0] = {top_left = {x = 160, y = 96}, 
                         	   size = tile_size}
    states[dir_right].random_frame = false
	states[dir_right].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_right | dir_down].frames = {}
	states[dir_right | dir_down].frames[0] = {top_left = {x = 160, y = 128}, 
                         	   size = tile_size}
    states[dir_right | dir_down].random_frame = false
	states[dir_right | dir_down].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_down].frames = {}
	states[dir_down].frames[0] = {top_left = {x = 128, y = 128}, 
                         	   size = tile_size}
    states[dir_down].random_frame = false
	states[dir_down].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_down | dir_left].frames = {}
	states[dir_down | dir_left].frames[0] = {top_left = {x = 96, y = 128}, 
                         	   size = tile_size}
    states[dir_down | dir_left].random_frame = false
	states[dir_down | dir_left].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_left].frames = {}
	states[dir_left].frames[0] = {top_left = {x = 96, y = 96}, 
                         	   size = tile_size}
    states[dir_left].random_frame = false
	states[dir_left].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_left | dir_up].frames = {}
	states[dir_left | dir_up].frames[0] = {top_left = {x = 96, y = 64}, 
                         	   size = tile_size}
    states[dir_left | dir_up].random_frame = false
	states[dir_left | dir_up].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_add | dir_down | dir_right].frames = {}
	states[dir_add | dir_down | dir_right].frames[0] = {top_left = {x = 128, y = 0}, 
                         	   size = tile_size}
    states[dir_add | dir_down | dir_right].random_frame = false
	states[dir_add | dir_down | dir_right].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_add | dir_down | dir_left].frames = {}
	states[dir_add | dir_down | dir_left].frames[0] = {top_left = {x = 160, y = 0}, 
                         	   size = tile_size}
    states[dir_add | dir_down | dir_left].random_frame = false
	states[dir_add | dir_down | dir_left].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_add | dir_up | dir_left].frames = {}
	states[dir_add | dir_up | dir_left].frames[0] = {top_left = {x = 160, y = 32}, 
                         	   size = tile_size}
    states[dir_add | dir_up | dir_left].random_frame = false
	states[dir_add | dir_up | dir_left].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_add | dir_up | dir_right].frames = {}
	states[dir_add | dir_up | dir_right].frames[0] = {top_left = {x = 128, y = 32}, 
                         	   size = tile_size}
    states[dir_add | dir_up | dir_right].random_frame = false
	states[dir_add | dir_up | dir_right].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_down | dir_up].frames = {}
	states[dir_down | dir_up].frames[0] = {top_left = {x = 32, y = 32}, 
                         	   size = tile_size}
    states[dir_down | dir_up].random_frame = false
	states[dir_down | dir_up].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_left | dir_right].frames = {}
	states[dir_left | dir_right].frames[0] = {top_left = {x = 64, y = 96}, 
                         	   size = tile_size}
    states[dir_left | dir_right].random_frame = false
	states[dir_left | dir_right].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_up | dir_down | dir_left].frames = {}
	states[dir_up | dir_down | dir_left].frames[0] = {top_left = {x = 0, y = 32}, 
                         	   size = tile_size}
    states[dir_up | dir_down | dir_left].random_frame = false
	states[dir_up | dir_down | dir_left].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_up | dir_down | dir_right].frames = {}
	states[dir_up | dir_down | dir_right].frames[0] = {top_left = {x = 64, y = 32}, 
                         	   size = tile_size}
    states[dir_up | dir_down | dir_right].random_frame = false
	states[dir_up | dir_down | dir_right].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_up | dir_left | dir_right].frames = {}
	states[dir_up | dir_left | dir_right].frames[0] = {top_left = {x = 64, y = 64}, 
                         	   size = tile_size}
    states[dir_up | dir_left | dir_right].random_frame = false
	states[dir_up | dir_left | dir_right].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_down | dir_up | dir_left | dir_right].frames = {}
	states[dir_down | dir_up | dir_left | dir_right].frames[0] = {top_left = {x = 32, y = 64}, 
                         	   size = tile_size}
    states[dir_down | dir_up | dir_left | dir_right].random_frame = false
	states[dir_down | dir_up | dir_left | dir_right].global_frames = 1
-----------------------------------------------------------
-----------------------------------------------------------
	states[dir_down | dir_left | dir_right].frames = {}
	states[dir_down | dir_left | dir_right].frames[0] = {top_left = {x = 64, y = 128}, 
                         	   size = tile_size}
    states[dir_down | dir_left | dir_right].random_frame = false
	states[dir_down | dir_left | dir_right].global_frames = 1
-----------------------------------------------------------
-- Load the 'default' state
model.states = states
-- Allow to start animation from random frame

GameItem{
	id = 0x2,
	name = 'tile_grass',
	model = model
}

state_idle = 0x200
state_walk = 0x100
-- Init the sprite sheet
model = {} 
model.sprite_sheet = textures .. 'chicken.png'
-- Create new animation state
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
model.sprite_sheet = textures .. 'wolf.png'
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
------------------------------------------------
states[state_idle | dir_up].frames = {}
for k = 0, 0 do
	states[state_idle | dir_up].frames[k] = {top_left = {x = 0,
                                       y = 3*tile_size.y}, 
                     	   size = tile_size}
end
states[state_idle | dir_up].random_frame = true
states[state_idle | dir_up].global_frames = 1

-- Load frames for the states
------------------------------------------------
states[state_idle | dir_left].frames = {}
for k = 0, 0 do
	states[state_idle | dir_left].frames[k] = {top_left = {x =0,
                                       y = 0*tile_size.y}, 
                     	   size = tile_size}
end
states[state_idle | dir_left].random_frame = true
states[state_idle | dir_left].global_frames = 1

-- Load frames for the states
------------------------------------------------
states[state_idle | dir_down].frames = {}
for k = 0, 0 do
	states[state_idle | dir_down].frames[k] = {top_left = {x = 0,
                                       y = 2*tile_size.y}, 
                     	   size = tile_size}
end
states[state_idle | dir_down].random_frame = true
states[state_idle | dir_down].global_frames = 1

-- Load frames for the states
------------------------------------------------
states[state_idle | dir_right].frames = {}
for k = 0, 0 do
	states[state_idle | dir_right].frames[k] = {top_left = {x = 0,
                                       y = 1*tile_size.y}, 
                     	   size = tile_size}
end
states[state_idle | dir_right].random_frame = true
states[state_idle | dir_right].global_frames = 1

-- Load frames for the states
------------------------------------------------
states[state_walk | dir_up].frames = {}
for k = 0, 3 do
	states[state_walk | dir_up].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 3*tile_size.y}, 
                     	   size = tile_size}
end
states[state_walk | dir_up].random_frame = true
states[state_walk | dir_up].global_frames = 1

-- Load frames for the states
------------------------------------------------
states[state_walk | dir_left].frames = {}
for k = 0, 4 do
	states[state_walk | dir_left].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 0*tile_size.y}, 
                     	   size = tile_size}
end
states[state_walk | dir_left].random_frame = true
states[state_walk | dir_left].global_frames = 1

-- Load frames for the states
------------------------------------------------
states[state_walk | dir_down].frames = {}
for k = 0, 2 do
	states[state_walk | dir_down].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 2*tile_size.y}, 
                     	   size = tile_size}
end
states[state_walk | dir_down].random_frame = true
states[state_walk | dir_down].global_frames = 1

-- Load frames for the states
------------------------------------------------
states[state_walk | dir_right].frames = {}
for k = 0, 4 do
	states[state_walk | dir_right].frames[k] = {top_left = {x = k*tile_size.x,
                                       y = 1*tile_size.y}, 
                     	   size = tile_size}
end
states[state_walk | dir_right].random_frame = true
states[state_walk | dir_right].global_frames = 1
-- Load the 'default' state
model.states = states
-- Allow to start animation from random frame

GameItem{
	id = 0x201,
	name = 'object_predator',
	model = model
}

