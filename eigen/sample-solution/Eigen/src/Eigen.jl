module Eigen

using CxxWrap

@wrapmodule "/workspaces/eigen-wrapper/build/lib/libjleigen"

function __init__()
  @initcxx
end

Base.size(m::Matrix) = (rows(m),cols(m))
Base.IndexStyle(::Type{<:Matrix}) = IndexCartesian()

end # module
