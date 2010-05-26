#ifndef _GrafikKiste_H_
#define  _GrafikKiste_H_

#include "TKiste.h"
#include "grafik.h"
#include "image.h"


class GrafikKiste : public TKiste<GrafikElement> {
  // Private Komponenten und Methoden
 public:
  // �ffentliche Methoden
  GrafikKiste ();
  virtual ~GrafikKiste ();
  void add_offset (int x, int y);
  void draw (Image &I) const;
};

#endif