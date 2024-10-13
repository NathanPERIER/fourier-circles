
cpp_flags = [
    cpp_warning_flags
]

l_args = []


sources = [
]

headers = [
    fcircles_headers_dir
]


fcircles_lib = static_library(
    'fcircles_static', sources,
    dependencies: [fmt_dep, png_dep],
    cpp_args: cpp_flags,
    link_args: l_args,
    include_directories: headers,
    install: false,
    build_by_default: true
)

fcircles_dep = declare_dependency(
    link_with : fcircles_lib,
    dependencies: [fmt_dep, png_dep],
    include_directories : headers
)
