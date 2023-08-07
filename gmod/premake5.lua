local current_dir = _SCRIPT_DIR

function IncludeSDKEngine()
	IncludePackage("gmod")

	local _project = project()

	externalincludedirs(current_dir .. "/../gmod")

	filter({})
end