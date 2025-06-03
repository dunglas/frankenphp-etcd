#ifndef _EXTGO_H
#define _EXTGO_H

#include <php.h>

extern zend_module_entry etcd_module_entry;

typedef struct go_string {
  size_t len;
  char *data;
} go_string;

#endif
