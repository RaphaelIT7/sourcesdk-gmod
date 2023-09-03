local current_dir = _SCRIPT_DIR

print("Include")
function IncludeBass()
	//IncludePackage("bass")

	local _project = project()

	links("bass")

	externalincludedirs(current_dir)

	filter({})
end