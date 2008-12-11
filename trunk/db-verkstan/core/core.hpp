#pragma once

#include "core/clip.hpp"
#include "core/operator.hpp"

#define DB_MAX_CLIPS 4096
#define DB_MAX_OPERATORS 4096
#define DB_TICKS_PER_BEAT 256

extern Clip* clips[DB_MAX_CLIPS];
extern Operator* operators[DB_MAX_OPERATORS];
extern int beat;
