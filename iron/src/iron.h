#pragma once

#define ironBEGIN_NAMESPACE namespace iron {
#define ironEND_NAMESPACE }

#define GRID_SIZE 16

#define ironTolerance 0.000001f

#define ironNullWithEpsilon(f) (abs(f) <= ironTolerance)