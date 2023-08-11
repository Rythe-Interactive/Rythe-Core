#pragma once
#include "../../../util/primitives.hpp"

#include "../../vector/vector_base.hpp"

namespace rsl::math
{
   template<typename Scalar, size_type RowCount, size_type ColCount, size_type ColIdx>
   struct column : vector_base
   {
       using scalar = Scalar;
       static constexpr size_type size = RowCount;
       static constexpr size_type row_count = RowCount;
       static constexpr size_type col_count = ColCount;
       static constexpr size_type col_idx = ColIdx;
       using type = column<Scalar, RowCount, ColCount, ColIdx>;
       using conv_type = vector<scalar, size>;

       scalar mx[col_count][row_count];

       COPY_FUNCS_DECO(constexpr, column, noexcept);

       constexpr operator conv_type() const noexcept;

       constexpr column& operator=(const conv_type& other) noexcept;
   };

   template<size_type RowCount, size_type ColCount, size_type ColIdx>
   struct column<bool, RowCount, ColCount, ColIdx> : vector_base
   {
       using scalar = bool;
       static constexpr size_type size = RowCount;
       static constexpr size_type row_count = RowCount;
       static constexpr size_type col_count = ColCount;
       static constexpr size_type col_idx = ColIdx;
       using type = column<bool, RowCount, ColCount, ColIdx>;
       using conv_type = vector<scalar, size>;

       scalar mx[col_count][row_count];

       COPY_FUNCS_DECO(constexpr, column, noexcept);

       constexpr void set_mask(bitfield8 mask) noexcept;
       constexpr bitfield8 mask() const noexcept;

       constexpr operator conv_type() const noexcept;

       constexpr column& operator=(const conv_type& other) noexcept;
   };

   template<typename Scalar, size_type ColCount, size_type ColIdx>
   struct column<Scalar, 1, ColCount, ColIdx> : vector_base
   {
       using scalar = Scalar;
       static constexpr size_type size = 1;
       static constexpr size_type row_count = 1;
       static constexpr size_type col_count = ColCount;
       static constexpr size_type col_idx = ColIdx;
       using type = column<Scalar, 1, ColCount, ColIdx>;
       using conv_type = vector<scalar, size>;

       scalar mx[col_count][row_count];

       COPY_FUNCS_DECO(constexpr, column, noexcept);

       constexpr operator scalar() const noexcept;

       constexpr operator conv_type() const noexcept;

       constexpr column& operator=(const conv_type& other) noexcept;

       constexpr column& operator=(scalar value) noexcept;
   };

   template<size_type ColCount, size_type ColIdx>
   struct column<bool, 1, ColCount, ColIdx> : vector_base
   {
       using scalar = bool;
       static constexpr size_type size = 1;
       static constexpr size_type row_count = 1;
       static constexpr size_type col_count = ColCount;
       static constexpr size_type col_idx = ColIdx;
       using type = column<bool, 1, ColCount, ColIdx>;
       using conv_type = vector<scalar, size>;

       scalar mx[col_count][row_count];

       COPY_FUNCS_DECO(constexpr, column, noexcept);

       constexpr void set_mask(bitfield8 mask) noexcept;
       constexpr bitfield8 mask() const noexcept;

       constexpr operator scalar() const noexcept;

       constexpr operator conv_type() const noexcept;

       constexpr column& operator=(const conv_type& other) noexcept;

       constexpr column& operator=(scalar value) noexcept;
   };
}
