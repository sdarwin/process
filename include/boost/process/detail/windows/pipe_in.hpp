// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_PIPE_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_PIPE_IN_HPP

#include <boost/detail/winapi/process.hpp>
#include <boost/detail/winapi/handles.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <cstdio>

namespace boost { namespace process { namespace detail { namespace windows {

struct pipe_in : public ::boost::process::detail::handler_base
{
    ::boost::detail::winapi::HANDLE_ handle;
    template<typename T>
    pipe_in(const T & p) : handle(p.native_source()) {}

    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        boost::detail::winapi::SetHandleInformation(handle,
                boost::detail::winapi::HANDLE_FLAG_INHERIT_,
                boost::detail::winapi::HANDLE_FLAG_INHERIT_);

        e.startup_info.hStdInput = handle;
        e.startup_info.dwFlags  |= boost::detail::winapi::STARTF_USESTDHANDLES_;
        e.inherit_handles = true;
    }
    template<typename WindowsExecutor>
    void on_error(WindowsExecutor &, const std::error_code &) const
    {
        ::boost::detail::winapi::CloseHandle(handle);
    }

    template<typename WindowsExecutor>
    void on_success(WindowsExecutor &) const
    {
        ::boost::detail::winapi::CloseHandle(handle);
    }
};

}}}}

#endif
