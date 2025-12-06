//
// Logging.h
//

#pragma once

#include "fmt/format.h"
#include "glm/vec3.hpp"

// custom formatter for glm::vec specializations

template <glm::length_t L, typename T, glm::qualifier Q>
struct fmt::formatter<glm::vec<L, T, Q>> : fmt::formatter<T>
{
	constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator
	{
		// Delegate to the float formatter for parsing
		return fmt::formatter<T>::parse(ctx);
	}

	auto format(const glm::vec<L, T, Q>& v, format_context& ctx) const
		-> format_context::iterator
	{
		auto out = ctx.out();
		*out++ = '(';

		for (glm::length_t i = 0; i < L; ++i)
		{
			if (i > 0)
			{
				*out++ = ',';
				*out++ = ' ';
			}

			// Use the inherited formatter with user-specified options
			out = fmt::formatter<T>::format(static_cast<T>(v[i]), ctx);
		}

		*out++ = ')';
		return out;
	}
};
