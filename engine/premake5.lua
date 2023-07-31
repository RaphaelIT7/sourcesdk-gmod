local current_dir = _SCRIPT_DIR

function IncludeSDKEngine()
	IncludePackage("sourcesdk_engine")

	local _project = project()

	externalincludedirs(current_dir .. "/../engine")

	filter("system:windows or macosx")
		--links("engine")

	filter("system:linux")
		--links(_project.serverside and "engine_srv" or "engine")

	filter({})
end