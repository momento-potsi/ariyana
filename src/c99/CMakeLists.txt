fips_begin_sharedlib(cari)
    add_definitions(-DARI_NO_MAIN=1)
    fips_vs_warning_level(3)
    fips_deps(ari_3d ari_2d ari_fs_local ari_net ari_gui)
    fips_files(
        2d.h                    2d.cpp
        3d.h                    3d.cpp
        core.h                  core.cpp
        en.h                    en.cpp
        gfx.h                   gfx.cpp
        gui.h                   gui.cpp
        io.h                    io.cpp
        macros.h
        net.h                   net.cpp
        netSerializer.hpp
        zip_file.hpp
    )
fips_end_sharedlib()