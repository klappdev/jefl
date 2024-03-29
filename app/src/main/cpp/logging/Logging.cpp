/*
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2019 - 2022 https://github.com/klappdev
 *
 * Permission is hereby  granted, free of charge, to any  person obtaining a copy
 * of this software and associated  documentation files (the "Software"), to deal
 * in the Software  without restriction, including without  limitation the rights
 * to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
 * copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
 * IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
 * FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
 * AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
 * LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Logging.hpp"

#include <cstdio>
#include <cstdarg>

#define JEFL_DEBUG 0

namespace jefl::log {

    void info(const char* format, ...) {
        va_list arguments;
        va_start(arguments, format);

        std::vprintf(format, arguments);
        va_end(arguments);
    }

    void info(const std::string& message) {
    	std::printf("%s", message.c_str());
    }

    void debug(const char* format, ...) {
#if JEFL_DEBUG
        va_list arguments;
        va_start(arguments, format);

        std::vprintf(format, arguments);
        va_end(arguments);
#endif
    }

    void debug(const std::string& message) {
#if JEFL_DEBUG
    	std::printf("%s", message.c_str());
#endif
    }

    void error(const char* format, ...) {
        va_list arguments;
        va_start(arguments, format);

        std::vfprintf(stderr, format, arguments);
        va_end(arguments);
    }

    void error(const std::string& message) {
    	std::fprintf(stderr, "%s", message.c_str());
    }
}

