#ifndef _EXTGO_H
#define _EXTGO_H

void register_extension();

typedef struct go_string {
  size_t len;
  char *data;
} go_string;

#endif
