module Eigen

using CxxWrap

abstract type AbstractEigenMatrix{T,Rows,Cols,Storage} <: AbstractMatrix{T} end

@wrapmodule "/workspaces/eigen-wrapper/build/lib/libjleigen"

function __init__()
  @initcxx
end

Base.size(m::Matrix) = (rows(m),cols(m))
Base.IndexStyle(::Type{<:Matrix}) = IndexCartesian()

const Matrix4d = Matrix{Float64, 4, 4, ColMajor}
const MatrixXd = Matrix{Float64, Dynamic, Dynamic, ColMajor}

end # module
