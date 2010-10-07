// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef OTS_CMAP_H_
#define OTS_CMAP_H_

#include <vector>

#include "ots.h"

namespace ots {

struct OpenTypeCMAPSubtableRange {
  uint32_t start_range;
  uint32_t end_range;
  uint32_t start_glyph_id;
};

struct OpenTypeCMAP {
  OpenTypeCMAP()
      : subtable_3_0_4_data(NULL),
        subtable_3_0_4_length(0),
        subtable_3_1_4_data(NULL),
        subtable_3_1_4_length(0) {
  }

  // Platform 3, Encoding 0, Format 4, MS Symbol table.
  const uint8_t *subtable_3_0_4_data;
  size_t subtable_3_0_4_length;
  // Platform 3, Encoding 1, Format 4, MS Unicode BMP table.
  const uint8_t *subtable_3_1_4_data;
  size_t subtable_3_1_4_length;

  // Platform 3, Encoding 10, Format 12, MS Unicode UCS-4 table.
  std::vector<OpenTypeCMAPSubtableRange> subtable_3_10_12;
  // Platform 3, Encoding 10, Format 13, MS UCS-4 Fallback table.
  std::vector<OpenTypeCMAPSubtableRange> subtable_3_10_13;
  // Platform 1, Encoding 0, Format 0, Mac Roman table.
  std::vector<uint8_t> subtable_1_0_0;
};

}  // namespace ots

#endif
