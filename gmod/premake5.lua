local current_dir = _SCRIPT_DIR

function IncludeGmod()
	IncludePackage("gmod")

	local _project = project()

	externalincludedirs(current_dir .. "/../gmod")
	externalincludedirs(current_dir .. "/../gmcommon_helper")

	filter({})
end