#include <jlcxx/jlcxx.hpp>
#include <jlcxx/stl.hpp>

#include <Eigen/Dense>


namespace jleigen
{
  struct WrapMatrix
  {
    template<typename TypeWrapperT>
    void operator()(TypeWrapperT&& wrapped)
    {
      using WrappedT = typename TypeWrapperT::type;
      using ScalarT = typename WrappedT::Scalar;
      wrapped.template constructor<Eigen::Index, Eigen::Index>();
      wrapped.method("cols", &WrappedT::cols);
      wrapped.method("rows", &WrappedT::rows);
      wrapped.method("norm", &WrappedT::norm);
      wrapped.method("setConstant", static_cast<WrappedT& (WrappedT::*)(const ScalarT&)>(&WrappedT::setConstant));

      wrapped.module().set_override_module(jl_base_module);
      wrapped.module().method("getindex", [](const WrappedT& m, int_t i, int_t j) { return m(i-1,j-1); });
      wrapped.module().method("setindex!", [](WrappedT& m, ScalarT value, int_t i, int_t j) { m(i-1,j-1) = value; });
      wrapped.module().unset_override_module();

      wrapped.module().method("toString", [] (const WrappedT& m)
      {
        std::stringstream stream;
        stream << m;
        return stream.str();
      });
    }
  };
}

namespace jlcxx
{

template<typename T>
struct BuildParameterList<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>
{
  typedef ParameterList<T> type;
};

}


JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
{
  using jlcxx::Parametric;
  using jlcxx::TypeVar;
  mod.add_type<Parametric<TypeVar<1>>>("Matrix", jlcxx::julia_type("AbstractMatrix"))
    .apply<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>, Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>>(jleigen::WrapMatrix());
}
