-- require boost and boost python
add_requires("boost", {
    system = false,
    configs = {
        shared = true,
        python = true,
        pyver = "3.9"
    }
})

-- extension modules
target("mymath")
    set_kind("shared")
    add_packages("boost")
    set_filename("mymath.pyd")
    add_files("./add.cpp")
target_end()

target("student")
    set_kind("shared")
    add_packages("boost")
    set_filename("student.pyd")
    add_files("./student.cpp")
target_end()

target("inc")
    set_kind("shared")
    add_packages("boost")
    set_filename("inc.pyd")
    add_files("./inc.cpp")
target_end()

-- copy to project path
after_build(function(target)
    local dst_dir = "$(projectdir)/"
    os.cp(target:targetdir() .. '/' .. target:name() .. '.pyd', dst_dir)

    -- copy dlls
    local lib_suffix = ".dll"
    local libdir = target:targetdir()
    for libname, pkg in pairs(target:pkgs()) do
        local pkg_path = pkg:installdir()
        if pkg_path ~= nil then
            print("copy dependents: " .. pkg_path)
            os.trycp(pkg_path .. "/lib/*" .. lib_suffix, libdir)
        end
    end
    os.cp(target:targetdir() .. '/*.dll', dst_dir)

end)