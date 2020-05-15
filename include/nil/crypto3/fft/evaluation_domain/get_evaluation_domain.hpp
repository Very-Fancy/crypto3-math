//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef GET_EVALUATION_DOMAIN_HPP_
#define GET_EVALUATION_DOMAIN_HPP_

#include <memory>

#include <libfqfft/evaluation_domain/evaluation_domain.hpp>

namespace libfqfft {

    template<typename FieldT>
    std::shared_ptr<evaluation_domain<FieldT>> get_evaluation_domain(const size_t min_size);

}    // namespace libfqfft

#include <libfqfft/evaluation_domain/get_evaluation_domain.tcc>

#endif    // GET_EVALUATION_DOMAIN_HPP_