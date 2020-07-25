using BinaryBuilder

json = String(read(ARGS[1]))
buff = IOBuffer(strip(json))
objs = []
while !eof(buff)
    push!(objs, BinaryBuilder.JSON.parse(buff))
end
json_obj = objs[1]

BinaryBuilder.cleanup_merged_object!(json_obj)
json_obj["dependencies"] = Dependency[dep for dep in json_obj["dependencies"] if !isa(dep, BuildDependency)]
BinaryBuilder.rebuild_jll_package(json_obj, download_dir="products", upload_prefix="barche/libfoo")
