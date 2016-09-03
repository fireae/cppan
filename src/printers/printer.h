/*
 * Copyright (c) 2016, Egor Pugin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *     3. Neither the name of the copyright holder nor the names of
 *        its contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "context.h"
#include "project.h"

#define CPP_HEADER_FILENAME "cppan.h"
#define CPPAN_EXPORT "CPPAN_EXPORT"
#define CPPAN_EXPORT_PREFIX "CPPAN_API_"
#define CPPAN_LOCAL_BUILD_PREFIX "cppan-build-"

#define INCLUDE_GUARD_PREFIX "CPPAN_INCLUDE_GUARD_"

extern const std::vector<String> configuration_types;
extern const std::vector<String> configuration_types_normal;
extern const std::vector<String> configuration_types_no_rel;

enum class PrinterType
{
    CMake,
    //Ninja,
    // add more here
};

struct Config;

struct Printer
{
    Package d;
    class AccessTable *access_table = nullptr;
    Config *cc = nullptr; // current
    Config *pc = nullptr; // parent
    Config *rc = nullptr; // root
    std::set<String> include_guards;

    virtual void prepare_rebuild() = 0;
    virtual void prepare_build(const path &fn, const String &cppan) = 0;
    virtual int generate() const = 0;
    virtual int build() const = 0;

    virtual void print() = 0;
    virtual void print_meta() = 0;

    virtual void clear_cache(path p) const = 0;
    virtual void clear_exports(path p) const = 0;

    static std::unique_ptr<Printer> create(PrinterType type);
};
