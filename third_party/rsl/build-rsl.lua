createProject ("include","rsl","StaticLib")
includedirs {
    "$(SolutionDir)include/rsl/src/"
}

files { 
    "src/**.h",
    "src/**.hpp",
    "src/**.inl",
    "src/**.c",
    "src/**.cpp"
}

targetdir "$(SolutionDir)bin\\lib\\"
libdirs { 
    "$(SolutionDir)bin\\lib\\"
 }


