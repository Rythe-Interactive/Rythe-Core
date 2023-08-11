-- group "include"
-- project "rsl"
--     location "src/rsl/"
--     kind "StaticLib"
createProject("include","rsl","StaticLib")
includedirs {"src/impl/"}
files { "src/impl/**.h", "src/impl/**.hpp" ,"src/impl/**.inl","src/impl/**.c", "src/impl/**.cpp" }
--group ""
