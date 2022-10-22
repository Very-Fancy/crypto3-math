//---------------------------------------------------------------------------//
// Copyright (c) 2021 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2021 Nikita Kaskov <nbering@nil.foundation>
// Copyright (c) 2022 Ekaterina Chukavina <kate@nil.foundation>
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------//

#define BOOST_TEST_MODULE expression_tstr_arithmetic_test

#include <cmath>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>

#include <boost/mpl/apply_wrap.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <nil/crypto3/algebra/fields/arithmetic_params/bls12.hpp>

#include <nil/crypto3/math/polynomial/polynomial.hpp>
#include <nil/crypto3/math/expressions/expression_tstr.hpp>
using namespace nil::crypto3::algebra;
using namespace nil::crypto3::math;
using namespace nil::crypto3::math::expressions_tstr;
typedef fields::bls12_fr<381> FieldType;

BOOST_AUTO_TEST_SUITE(expression_test_suite)
BOOST_AUTO_TEST_CASE(expression_polynomial_expression_1) {
    //
    constexpr const char *v1 = "v1";
    constexpr const char *v0 = "v0";
    //
    polynomial<FieldType::value_type> p0 = {5, 0, 0, 13, 0, 1};
    polynomial<FieldType::value_type> p1 = {13, 0, 1};
    // auto x =p0.evaluate(FieldType::value_type);
    // std::cout<<x.data<<std::endl;
    polynomial<FieldType::value_type> p2;
    p2 = p0 + p1 / p0;

    std::vector<const char *> s = {v0, v1};
    std::vector<polynomial<FieldType::value_type>> ps = {p0, p1};
    auto dictionary = std::make_pair(s, ps);

    using expr_type = X<decltype("v0 + v1 / v0"_tstr)>;
    auto res = ExpressionTstr<expr_type>::eval(dictionary);


    for (std::size_t i = 0; i < res.size(); i++) {
        BOOST_CHECK_EQUAL(res[i].data, p2[i].data);
    }

    FieldType::value_type val0 = FieldType::value_type(5);
    FieldType::value_type val1 = FieldType::value_type(15);
    auto val2 = val0 + val1 * val0;

    std::vector<FieldType::value_type> vals = {val0, val1};
    auto dictionary2 = std::make_pair(s, vals);

    using expr_type2 = X<decltype("v0 + v1 * v0"_tstr)>;
    auto res2 = ExpressionTstr<expr_type2>::eval(dictionary2);
    BOOST_CHECK_EQUAL(res2.data, val2.data);
}
////
// BOOST_AUTO_TEST_CASE(expression_expression_0) {
//
//     constexpr const char *v1 = "v1";
//     constexpr const char *v0 = "v0";
//
//     FieldType::value_type p0 = FieldType::value_type(5);
//     FieldType::value_type p1 = FieldType::value_type(15);
//
//     FieldType::value_type p2 = FieldType::value_type(5) * p0 + p1 / p0;
//
//     std::vector<const char *> s = {v0, v1};
//     std::vector<FieldType::value_type> ps = {p0, p1};
//     auto dictionary = std::make_pair(s, ps);
//     typedef decltype("5 * v0 + v1 / v0"_tstr) expr_str;
//     auto expr_type = ExpressionTstr<FieldType::value_type, X<expr_str>>();
//    // expr_type expr();
//     FieldType::value_type c = expr_type.eval(dictionary);
//    // FieldType::value_type c1 = expr->eval(dictionary);
//     //    for (std::size_t i = 0; i < c.size(); i++) {
//     BOOST_CHECK_EQUAL(c.data, p2.data);
//     // }
// }
// BOOST_AUTO_TEST_CASE(expression_expression_1) {
//
//     constexpr const char *v1 = "v1";
//     constexpr const char *v0 = "v0";
//
//     FieldType::value_type p0 = FieldType::value_type(5);
//     FieldType::value_type p1 = FieldType::value_type(15);
//     FieldType::value_type p2 = p0 + p1 / p0;
//
//     std::vector<const char *> s = {v0, v1};
//
//     std::vector<FieldType::value_type> ps = {p0, p1};
//     auto dictionary = std::make_pair(s, ps);
//     typedef decltype("v0 + v1 / v0"_tstr) expr_str;
//     using expr_type = ExpressionTstr<FieldType::value_type, X<expr_str>>;
//
//     FieldType::value_type c = expr_type::eval(dictionary);
//     BOOST_CHECK_EQUAL(c.data, p2.data);
// }
////
// BOOST_AUTO_TEST_CASE(expression_expression_2) {
//
//     constexpr const char *v1 = "v1";
//     constexpr const char *v0 = "v0";
//
//     FieldType::value_type p0 = FieldType::value_type(5);
//     FieldType::value_type p1 = FieldType::value_type(15);
//     FieldType::value_type p2 = p0 + p1 - p0;
//
//     std::vector<const char *> s = {v0, v1};
//
//     std::vector<FieldType::value_type> ps = {p0, p1};
//     auto dictionary = std::make_pair(s, ps);
//     typedef decltype("v0 + v1 - v0"_tstr) expr_str;
//     using expr_type = ExpressionTstr<FieldType::value_type, X<expr_str>>;
//
//     FieldType::value_type c = expr_type::eval(dictionary);
//     BOOST_CHECK_EQUAL(c.data, p2.data);
// }
//
// BOOST_AUTO_TEST_CASE(expression_expression_3) {
//
//     constexpr const char *v1 = "v1";
//     constexpr const char *v0 = "v0";
//
//     FieldType::value_type p0 = FieldType::value_type(5);
//     FieldType::value_type p1 = FieldType::value_type(15);
//     FieldType::value_type p2 = p0 * p1;
//
//     std::vector<const char *> s = {v0, v1};
//
//     std::vector<FieldType::value_type> ps = {p0, p1};
//     auto dictionary = std::make_pair(s, ps);
//     typedef decltype("v0 * v1"_tstr) expr_str;
//     using expr_type = ExpressionTstr<FieldType::value_type, X<expr_str>>;
//
//     FieldType::value_type c = expr_type::eval(dictionary);
//     BOOST_CHECK_EQUAL(c.data, p2.data);
// }
//
// BOOST_AUTO_TEST_CASE(expression_expression_4) {
//
//     constexpr const char *v1 = "v1";
//     constexpr const char *v0 = "v0";
//
//     FieldType::value_type val0 = FieldType::value_type(5);
//     FieldType::value_type val1 = FieldType::value_type(15);
//     FieldType::value_type val2 = p0 + FieldType::value_type(15) * p1 * p0;
//
//     std::vector<const char *> s = {v0, v1};
//
//     std::vector<FieldType::value_type> ps = {p0, p1};
//     auto dictionary = std::make_pair(s, ps);
//     typedef decltype("v0 + 15 * v1 * v0"_tstr) expr_str;
//     using expr_type = ExpressionTstr<X<decltype("v0 + 15 * v1 * v0"_tstr)>>;
//     auto c = expr_type::eval(dictionary);
//
//     // XExpressionTstr<X<decltype("v0 + 15 * v1 * v0"_tstr)>>();
//     //    expr_type();
//     //auto c = expr_type.template eval<typename FieldType::value_type >(dictionary);
//     //  FieldType::value_type c = expr_type::eval(dictionary);
//     BOOST_CHECK_EQUAL(c.data, p2.data);
//     auto c =
// }
//
// BOOST_AUTO_TEST_CASE(expression_expression_4) {
//
//     constexpr const char *v1 = "v1";
//     constexpr const char *v0 = "v0";
//
//     FieldType::value_type p0 = FieldType::value_type(5);
//     FieldType::value_type p1 = FieldType::value_type(15);
//     FieldType::value_type p2 = p0 + FieldType::value_type(15) * p1 * p0;
//
//     std::vector<const char *> s = {v0, v1};
//
//     std::vector<FieldType::value_type> ps = {p0, p1};
//     auto dictionary = std::make_pair(s, ps);
//     typedef decltype("v0 + 15 * v1 * v0"_tstr) expr_str;
//     using expr_type = ExpressionTstr<X<decltype("v0 + 15 * v1 * v0"_tstr)>>;
//     auto c = expr_type::eval(dictionary);
//
//    // XExpressionTstr<X<decltype("v0 + 15 * v1 * v0"_tstr)>>();
////    expr_type();
//   //auto c = expr_type.template eval<typename FieldType::value_type >(dictionary);
//  //  FieldType::value_type c = expr_type::eval(dictionary);
//    BOOST_CHECK_EQUAL(c.data, p2.data);
//    auto c =
//}

BOOST_AUTO_TEST_SUITE_END()