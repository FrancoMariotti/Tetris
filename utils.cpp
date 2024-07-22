#include "utils.h"
#include "stdio.h"
#include "stdlib.h"

static const unsigned int N_Colors = 7;

static const Color_t *colors[N_Colors] = {&Red,  &Magenta, &Green, &Blue,
                                          &Cian, &Orange,  &Yellow};

int getColorId() {
  return rand() % N_Colors;
}

const Color_t* getColor(int id) {
  return colors[id];
}
