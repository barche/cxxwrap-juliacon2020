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

  struct WrapMap
  {
    template<typename TypeWrapperT>
    void operator()(TypeWrapperT&& wrapped)
    {
      using WrappedT = typename TypeWrapperT::type;
      using ScalarT = typename WrappedT::Scalar;
      wrapped.template constructor<ScalarT*>();
    }
  };

  struct ApplyMatrix
  {
    template<typename T, typename Rows, typename Cols, typename Storage> using apply = Eigen::Matrix<T, Rows::value, Cols::value, Storage::value>;
  };
}

namespace jlcxx
{

template<typename T, int NRows, int NCols, int S>
struct BuildParameterList<Eigen::Matrix<T, NRows, NCols, S>>
{
  using type = ParameterList<T, std::integral_constant<int_t, NRows>, std::integral_constant<int_t, NCols>, std::integral_constant<Eigen::StorageOptions, Eigen::StorageOptions(S)>>;
};

template<typename T, int NRows, int NCols, int S>
struct BuildParameterList<Eigen::Map<Eigen::Matrix<T, NRows, NCols, S>>>
{
  using type = ParameterList<T, std::integral_constant<int_t, NRows>, std::integral_constant<int_t, NCols>, std::integral_constant<Eigen::StorageOptions, Eigen::StorageOptions(S)>>;
};

template<typename T>
struct SuperType<Eigen::Map<T>>
{
  using type = typename Eigen::Map<T>::Base::Base::Base::Base;
};

}


JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
{
  mod.set_const("Dynamic", int_t(Eigen::Dynamic));
  
  mod.add_bits<Eigen::StorageOptions>("StorageOptions", jlcxx::julia_type("CppEnum"));
  mod.set_const("ColMajor", Eigen::ColMajor);
  mod.set_const("RowMajor", Eigen::RowMajor);

  using jlcxx::Parametric;
  using jlcxx::TypeVar;
  using jlcxx::ParameterList;

  using scalar_types = ParameterList<double>;
  using sizes = ParameterList<std::integral_constant<int, 4>, std::integral_constant<int, Eigen::Dynamic>>;
  using storage = ParameterList<std::integral_constant<int, Eigen::ColMajor>, std::integral_constant<int, Eigen::RowMajor>>;

  auto matrix_base = mod.add_type<Parametric<TypeVar<1>, TypeVar<2>, TypeVar<3>, TypeVar<4>>>("Matrix", jlcxx::julia_type("AbstractEigenMatrix"));
  matrix_base.apply_combination<jleigen::ApplyMatrix, scalar_types, sizes, sizes, storage>(jleigen::WrapMatrix());

  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>, TypeVar<3>, TypeVar<4>>>("Map", matrix_base.dt())
    .apply<Eigen::Map<Eigen::Matrix<double,4,4>>>(jleigen::WrapMap());
}
