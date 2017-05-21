local ids_file = io.open('ids.hpp', 'w')

function GameItem(prop)
	print (string.format('ID = %d, name = %s', prop.id, prop.name))
	ids_file:write(string.format('#define %s_ID 0x%x\n',
					string.upper(prop.name),
					prop.id))
end

dofile('../textures/mm_data.lua')

ids_file:close()


