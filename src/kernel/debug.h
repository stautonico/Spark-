/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef SPARK_DEBUG_H
#define SPARK_DEBUG_H

namespace Kernel::Debug {

void debugf(const char *fmt, ...);
void warnf(const char *fmt, ...);
void errorf(const char *fmt, ...);

} // namespace Kernel


#endif // SPARK_DEBUG_H