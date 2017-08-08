-- init global variable
g_dump = io.open(os.date("dump_%Y-%m-%d-%H-%M-%S.txt"), "a")
g_dump:write("ptr, name\n")
g_count = 0

-- relative virtual address(rva) to register_whatever function
-- this assume ffxiv sb benchmark
-- YOU MUST EDIT THIS TO RIGHT VALUE TO WORK
-- check http://imgur.com/a/nJCef for disasm
g_addr = {}

g_override_path = {
	-- {"01_roc_r2", "01_gyr_g3"},
	-- {}
	-- {"ex1/01_roc_r2/twn/r2t2/level/r2t2", "ex2/01_gyr_g3/twn/g3t2/level/g3t2"},
	-- {"ex1/01_roc_r2/twn/r2t2", "ex2/01_gyr_g3/twn/g3t2"},

	--
	-- {"ffxiv/wil_w1/twn/w1t1/level/w1t1", "ex2/02_est_e3/fld/e3f1/level/e3f1"},
	-- {"ffxiv/wil_w1/twn/w1t1", "ex2/02_est_e3/fld/e3f1"},

	-- kugane
	{"ffxiv/wil_w1/twn/w1t1/level/w1t1", "ex2/02_est_e3/twn/e3t1/level/e3t1"},
	{"ffxiv/wil_w1/twn/w1t1", "ex2/02_est_e3/twn/e3t1"},

	-- last cutscene dungeon ex2/02_est_e3/dun/e3d1
	--{"ffxiv/wil_w1/twn/w1t1/level/w1t1", "ex2/02_est_e3/dun/e3d1/level/e3d1"},
	--{"ffxiv/wil_w1/twn/w1t1", "ex2/02_est_e3/dun/e3d1"},

}

-- g_addr.load_master = 0x162210 -- looks like below function is called from this
g_addr.load1 = 0x186BB0 -- mostly loads gfx stuff but does calc in it?
g_addr.load2 = 0x186CE0 -- mostly loads gfx stuff
g_addr.load3 = 0x1868A0 -- mostly loads exd data
g_addr.load4 = 0x186E00 -- from this on found it because there are next to each other
g_addr.load5 = 0x186EE0 -- umm, vfx?
g_addr.kugane_workaround = 0xE61416

g_loadseen = {}

g_xiv = {}
g_xiv.proc_name = "ffxiv_dx11.exe"
g_xiv.path 	= "C:\\Users\\Mino\\Games\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\" .. g_xiv.proc_name
-- because I don't want to login and out every single try
g_xiv.arg 	= "DEV.TestSID=3a3f77cc5f7c88136d4a66e36bd27f8535d773d0378b521275468785 DEV.UseSqPack=1 DEV.DataPathType=1 DEV.LobbyHost01=127.0.0.1 DEV.LobbyPort01=54994 DEV.LobbyHost02=127.0.0.1 DEV.LobbyPort02=54994 DEV.LobbyHost03=127.0.0.1 DEV.LobbyPort03=54994 DEV.LobbyHost04=127.0.0.1 DEV.LobbyPort04=54994 DEV.LobbyHost05=127.0.0.1 DEV.LobbyPort05=54994 DEV.LobbyHost06=127.0.0.1 DEV.LobbyPort06=54994 SYS.Region=0 language=1 version=1.0.0.0 DEV.MaxEntitledExpansionID=1 DEV.GMServerHost=localhost"
g_mode = "attach"

function init()
	-- attach debugger
	if g_mode == "create" then
		print(string.format("Launching ffxiv.exe w/ arg %s", g_xiv.arg))
		createProcess(g_xiv.path, g_xiv.arg, true, true)
	elseif g_mode == "attach" then
		print("Looking for "..g_xiv.proc_name)
		while not openProcess(g_xiv.proc_name) do sleep(1) end
		print("Attaching...")
		debugProcess()
		while not getAddress(g_xiv.proc_name) do sleep(1) end
		print("Module loaded")
	else
		print("Unsupported mode!")
		return
	end

	for k, v in pairs(g_addr) do
		-- k = name
		-- v = rva
		print(string.format("Attaching %s breakpoint on 0x%X", k, v))
		debug_setBreakpoint(get_va(v))
	end

	print("Now waiting for breakpoints..")
end

function debugger_onBreakpoint()
	if RIP == get_va(g_addr.load1) then
		-- dump_message("1>>")
		local new_addr = dump_addr(R8)
		if new_addr then
			R8 = new_addr
		end
	elseif RIP == get_va(g_addr.load2) then
		-- dump_message("2>>")
		local new_addr = dump_addr(R8)
		if new_addr then
			R8 = new_addr
		end
	elseif RIP == get_va(g_addr.load3) then
		local new_addr = dump_addr(RSP + 28)
		if new_addr then
			writeQword(RSP + 28, new_addr)
		end
	elseif RIP == get_va(g_addr.load4) then
		-- dump_message("4>>")
		local new_addr = dump_addr(RCX)
		if new_addr then
			RCX = new_addr
		end
	elseif RIP == get_va(g_addr.load5) then
		-- dump_message("5>>")
		local new_addr = dump_addr(RCX)
		if new_addr then
			RCX = new_addr
		end
	elseif RIP == get_va(g_addr.kugane_workaround) then
		if RAX == 0 then
			-- jump and hope it doesn't cause a UB
			print("Workaround hack triggered")
			RIP = get_va(0xE61432)
		end
	else
		-- user bp, update gui on ce, but who gives a shit?
		-- continue execution anyway
		debug_continueFromBreakpoint("co_run")
		return 0
	end

	-- something is missing on the text file because it takes ageeeeeeeeees to write to file
	-- let just wait it


	-- continue execution
	debug_continueFromBreakpoint("co_run")
	--return 0 -- update gui
	return 1
end

function dump_addr(addr)
	local vfspath = readString(addr, 256)

	if not g_loadseen[vfspath] then
		g_loadseen[vfspath] = true -- set seen flag

		local message = string.format("%X, %s", addr, vfspath)
		dump_line(message)
	end

	if vfspath then
		return replace_map_string(addr, vfspath)
	end

	return nil
end

function dump_line(message)
	dump_message(message .. "\n")
end

function dump_message(message)
	g_dump:write(message)
	g_dump:flush()
	print(message)
end

-- mod_base + rva = va
function get_va(rva)
	return getAddress(g_xiv.proc_name) + rva
end

-- rva = va - mod_base
function get_rva(va)
	return va - getAddress(g_xiv.proc_name)
end

-- check mod_base <= va <= mod_base + mod_size
function is_mmod_addr(va)
	local mod_base = getAddress(g_xiv.proc_name)
	local mod_size = getModuleSize(g_xiv.proc_name)

	if mod_base <= va and va <= mod_base + mod_size then
		return true
	end

	return false
end

function replace_map_string(addr, source)
	-- try to replace map strnig
	for _, v in ipairs(g_override_path) do
		local match_pat = v[1]
		local replace_pat = v[2]

		if string.find(source, match_pat) then
			local path_override = string.gsub(source, match_pat, replace_pat)
			dump_line(string.format("OVERRIDE>> %s => %s (w/ %s => %s)", source , path_override, match_pat, replace_pat))

			-- check str len if
			if string.len(source) < string.len(path_override) then
				local new_addr = alloc(256) -- alloc 256 bytes
				writeCString(new_addr, path_override)
				 print(string.format("Replaced string is longer than original, allocating it to 0x%X", new_addr))
				return new_addr
			else
				-- original string len is longer or same
				writeCString(addr, path_override)
				return nil
			end
		end
	end

	-- can't find it
	return nil
end

-- write a string with null
function writeCString(addr, content)
	writeString(addr, content)
	writeBytes(addr + string.len(content), 0) -- put null byte, this assume content is only ASCII char
end

-- no way to free, have fun
function alloc(size)
	-- taken from http://forum.cheatengine.org/viewtopic.php?t=560739&sid=73dc5a565393a034ba16d1d468bb1eeb
  autoAssemble([[
alloc(luatemp, ]]..size..[[)
registersymbol(luatemp)
]])
  return getAddress("luatemp")
end

function split(str)
	local result = {}
	for token in string.gmatch(str..",", "([^,]+),%s*") do
    	table.insert(result, all_trim(token))
	end

	return result
end

init()
