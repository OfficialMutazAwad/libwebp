// Copyright 2022 Google Inc. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the COPYING file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS. All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.
// -----------------------------------------------------------------------------
//
// Colorspace utilities.

#ifndef WEBP_SHARPYUV_SHARPYUV_CSP_H_
#define WEBP_SHARPYUV_SHARPYUV_CSP_H_

#include "sharpyuv/sharpyuv.h"

#ifdef __cplusplus
extern "C" {
#endif

// Range of YUV values.
typedef enum {
  kSharpYuvRangeFull,     // YUV values between [0;255] (for 8 bit)
  kSharpYuvRangeLimited   // Y in [16;235], YUV in [16;240] (for 8 bit)
} SharpYuvRange;

// Constants that define a YUV color space.
typedef struct {
  // Kr and Kb are defined such that:
  // Y = Kr * r + Kg * g + Kb * b where Kg = 1 - Kr - Kb.
  float kr;
  float kb;
  int bits;  // Only 8 bit is supported by SharpYuvConvert.
  SharpYuvRange range;
} SharpYuvColorSpace;

// Fills in 'matrix' for the given YUVColorSpace.
void SharpYuvComputeConversionMatrix(const SharpYuvColorSpace* yuv_color_space,
                                     SharpYuvConversionMatrix* matrix);

// Enums for precomputed conversion matrices.
typedef enum {
  kSharpYuvMatrixWebp = 0,
  kSharpYuvMarixRec601Limited,
  kSharpYuvMarixRec601Full,
  kSharpYuvMarixRec709Limited,
  kSharpYuvMarixRec709Full,
  kSharpYuvMarixNum
} SharpYuvMatrixType;

// Returns a pointer to a matrix for one of the predefined colorspaces.
const SharpYuvConversionMatrix* SharpYuvGetConversionMatrix(
    SharpYuvMatrixType matrix_type);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // WEBP_SHARPYUV_SHARPYUV_CSP_H_
