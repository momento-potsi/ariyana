fips_begin_module(ari_gfx)
    ari_setup()
    set(CMAKE_CXX_STANDARD 17)
    fips_vs_warning_level(3)
    fips_deps(ari_io sx)
    fips_files(
        Application.hpp
		gfx.hpp                     gfx.cpp
        Material.hpp
        MaterialInstance.hpp
        MaterialParams.hpp
		Mesh.hpp
		SubMesh.hpp
        Vertices.hpp
        Viewport.hpp
    )

    fips_dir(private)
    fips_files(
        tinyktx.h                   tinyktx.cpp
    )

    if (ARI_SERVER)
        fips_dir(private/server)
        fips_files(
            gfx_server.cpp
        )
    elseif (ARI_GLFW AND ARI_OPENGL)
        fips_dir(private/glfw)
        fips_files(
            gfx_glfw.cpp
        )
    else()
        fips_dir(private/sapp)
        fips_files(
            gfx_sapp.cpp
        )
    endif()

    if (FIPS_ANDROID)
        fips_libs(GLESv3 EGL android log)
    endif()

    fips_dir(shaders)
    sokol_shader(mesh.glsl ${slang})
    fips_dir(shaders/basic)
    sokol_shader(basic.glsl ${slang})

fips_end_module()
