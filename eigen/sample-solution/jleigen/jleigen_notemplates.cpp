#include <jlcxx/jlcxx.hpp>
#include <jlcxx/stl.hpp>

#include <Eigen/Dense>


JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
{
  mod.add_type<Eigen::MatrixXd>("MatrixXd", jlcxx::julia_type("AbstractMatrixXd"))
    .constructor<Eigen::Index, Eigen::Index>()
    .method("cols", &Eigen::MatrixXd::cols)
    .method("rows", &Eigen::MatrixXd::rows)
    .method("norm", &Eigen::MatrixXd::norm)
    .method("setConstant", static_cast<Eigen::MatrixXd& (Eigen::MatrixXd::*)(const double&)>(&Eigen::MatrixXd::setConstant));

  mod.set_override_module(jl_base_module);
  mod.method("getindex", [](const Eigen::MatrixXd& m, int_t i, int_t j) { return m(i-1,j-1); });
  mod.method("setindex!", [](Eigen::MatrixXd& m, double value, int_t i, int_t j) { m(i-1,j-1) = value; });
  mod.unset_override_module();

  mod.method("toString", [] (const Eigen::MatrixXd& m)
  {
    std::stringstream stream;
    stream << m;
    return stream.str();
  });

}
