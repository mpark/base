/* TODO */

#pragma once

#define NO_COPY_SEMANTICS(cls) \
  cls(const cls &) = delete; \
  cls &operator=(const cls &) = delete;

