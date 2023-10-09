-- require boost and boost python
add_requires("boost", {
    system = false,
    configs = {
        shared = false,
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


-- copy to project path
after_build(function(target)
    local dst_dir = "$(projectdir)/"
    os.cp(target:targetdir() .. '/' .. target:name() .. '.pyd', dst_dir)
end)