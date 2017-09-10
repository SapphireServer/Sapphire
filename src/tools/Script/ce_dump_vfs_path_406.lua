-- init global variable
g_dump = io.open(os.date("dump_%Y-%m-%d-%H-%M-%S.txt"), "a")
g_dump:write("ptr, name\n")
g_count = 0

-- relative virtual address(rva) to register_whatever function
-- this assume ffxiv sb benchmark
-- YOU MUST EDIT THIS TO RIGHT VALUE TO WORK
-- check http://imgur.com/a/nJCef for disasm
g_addr = {}
-- signature: 4053 4881EC60010000 488B??????????4833C4 4889842450010000 C70100000000 488BD9 4585C0 7514
g_addr.load_master = 0x166140 -- looks like below function is called from this

-- signature: 48895C2408 48896C2410 4889742418 57 4883EC40 498BD9 498BF8 488BF2 488BE9 4D85C9 740A
-- rva on benchmark was at 0x1624B0 and it's now located at 0x1663E0 (offseted by 0x3F30)
g_addr.load1 = 0x1663E0 -- mostly loads gfx stuff but does calc in it?

-- these were just calculated from load1 offset (didn't tested)
g_addr.load2 = 0x162410 + 0x3F30 -- mostly loads gfx stuff
g_addr.load3 = 0x1626B0 + 0x3F30 -- mostly loads exd data
g_addr.load4 = 0x162540 + 0x3F30 -- from this on found it because there are next to each other
g_addr.load5 = 0x162360 + 0x3F30 -- umm, vfx?

g_loadseen = {}

g_xiv = {}
g_xiv.proc_name = "ffxiv_dx11.exe"
g_xiv.path 	= "C:\\Users\\Mino\\Desktop\\FFXIV-SB\\game\\" .. g_xiv.proc_name
-- because I don't want to login and out every single try
g_xiv.arg 	= "SYS.Language=1 SYS.Fps=0 SYS.MainAdapter=\"AMD_Radeon_HD_7800_Series(\\\\.\\DISPLAY1)\" SYS.ScreenMode=0 SYS.ScreenWidth=1280 SYS.ScreenHeight=720 SYS.FullScreenWidth=1280 SYS.FullScreenHeight=720 SYS.Gamma=50 SYS.IsSoundAlways=0 SYS.SoundMaster=100 SYS.SoundBgm=100 SYS.SoundSe=100 SYS.SoundVoice=100 SYS.SoundSystem=100 SYS.SoundEnv=100 SYS.IsSndMaster=0 SYS.IsSndBgm=0 SYS.IsSndSe=0 SYS.IsSndVoice=0 SYS.IsSndSystem=0 SYS.IsSndEnv=0 SYS.WaterWet_DX11=1 SYS.OcclusionCulling_DX11=1 SYS.LodType_DX11=1 SYS.ReflectionType_DX11=0 SYS.AntiAliasing_DX11=0 SYS.TranslucentQuality_DX11=0 SYS.GrassQuality_DX11=2 SYS.ShadowLOD_DX11=1 SYS.ShadowVisibilityTypeSelf_DX11=1 SYS.ShadowVisibilityTypeOther_DX11=0 SYS.ShadowTextureSizeType_DX11=1 SYS.ShadowCascadeCountType_DX11=2 SYS.ShadowSoftShadowType_DX11=1 SYS.PhysicsTypeSelf_DX11=2 SYS.PhysicsTypeOther_DX11=2 SYS.TextureFilterQuality_DX11=2 SYS.TextureAnisotropicQuality_DX11=0 SYS.Vignetting_DX11=1 SYS.RadialBlur_DX11=1 SYS.SSAO_DX11=1 SYS.Glare_DX11=2 SYS.DepthOfField_DX11=1 SYS.ParallaxOcclusion_DX11=0 SYS.Tessellation_DX11=0 SYS.GlareRepresentation_DX11=0"
g_mode = "attach"

function init()
	-- attach debugger
	if g_mode == "create" then
		print(string.format("Launching ffxiv.exe w/ arg %s", g_xiv.arg))
		createProcess(g_xiv.path, g_xiv.arg, true, true)
	elseif g_mode == "attach" then
		print("Looking for ffxiv.exe..")
		while not openProcess("ffxiv.exe") do sleep(1) end
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
		dump_addr(R8)
	elseif RIP == get_va(g_addr.load2) then
		-- dump_message("2>>")
		dump_addr(R8)
	elseif RIP == get_va(g_addr.load3) then
		-- dump_message("3>>")
		dump_addr(RCX)
	elseif RIP == get_va(g_addr.load4) then
		-- dump_message("4>>")
		dump_addr(RCX)
	elseif RIP == get_va(g_addr.load5) then
		-- dump_message("5>>")
		dump_addr(RDX)
	elseif RIP == get_va(g_addr.load_master) then
		-- dump_message("master>>")
		dump_addr(RDX)
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

function split(str)
	local result = {}
	for token in string.gmatch(str..",", "([^,]+),%s*") do
    	table.insert(result, all_trim(token))
	end

	return result
end

init()
