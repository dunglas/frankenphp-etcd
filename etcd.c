#include <php.h>
#include <zend_exceptions.h>

#include "_cgo_export.h"
#include "etcd.h"
#include "etcd_arginfo.h"

static int (*original_php_register_internal_extensions_func)(void) = NULL;

static zend_function *etcd_get_constructor(zend_object *object) {
  zend_throw_error(NULL, "Cannot directly construct \\Dunglas\\Etcd\\Client, "
                         "use the getOrCreate() method instead");

  return NULL;
}

zend_class_entry *etcd_ce;
static zend_object_handlers etcd_object_handlers;

PHP_MINIT_FUNCTION(etcd) {
  etcd_ce = register_class_Dunglas_Etcd_Client();
  etcd_ce->default_object_handlers = &etcd_object_handlers;

  memcpy(&etcd_object_handlers, &std_object_handlers,
         sizeof(zend_object_handlers));
  etcd_object_handlers.get_constructor = etcd_get_constructor;
  etcd_object_handlers.compare = zend_objects_not_comparable;

  return SUCCESS;
}

PHP_METHOD(Dunglas_Etcd_Client, getOrCreate) {
  zend_string *name;
  zval *endpoints;
  zend_long auto_sync_interval = 0, dial_timeout = 0, dial_keep_alive_time = 0, dial_keep_alive_timeout = 0;

  // clang-format off
  ZEND_PARSE_PARAMETERS_START(2, 6)
  	Z_PARAM_STR(name)
  	Z_PARAM_ARRAY(endpoints)
  	Z_PARAM_OPTIONAL
  	Z_PARAM_LONG(auto_sync_interval)
  	Z_PARAM_LONG(dial_timeout)
	Z_PARAM_LONG(dial_keep_alive_time)
	Z_PARAM_LONG(dial_keep_alive_timeout)
  ZEND_PARSE_PARAMETERS_END();
  // clang-format on

  int endpoints_len = zend_hash_num_elements(Z_ARRVAL_P(endpoints));
  if (endpoints_len == 0) {
    zend_argument_must_not_be_empty_error(2);
    RETURN_THROWS();
  }

  zend_string **go_endpoints = emalloc(sizeof(name) * endpoints_len);
  zval *endpoint;
  int index = 0;
  ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(endpoints), endpoint) {
    if (Z_TYPE_P(endpoint) != IS_STRING) {
      zend_throw_exception(NULL, "$endpoints must be an array of strings", 0);
      RETURN_THROWS();
    }

    go_endpoints[index] = Z_STR_P(endpoint);

    index++;
  }
  ZEND_HASH_FOREACH_END();

  char *error =
      go_client_load_or_create(ZSTR_VAL(name), *go_endpoints, endpoints_len, auto_sync_interval, dial_timeout, dial_keep_alive_time, dial_keep_alive_timeout);
  efree(go_endpoints);

  if (error != NULL) {
    zend_throw_exception(NULL, error, 0);
    free(error);
    RETURN_THROWS();
  }

  zval zval_name;
  ZVAL_STR(&zval_name, name);

  object_init_ex(return_value, etcd_ce);
  zend_update_property_ex(etcd_ce, Z_OBJ_P(return_value),
                          ZSTR_KNOWN(ZEND_STR_NAME), &zval_name);
}

PHP_METHOD(Dunglas_Etcd_Client, put) {
  zend_string *key, *value;
  zend_long timeout = 0;

  // clang-format off
  ZEND_PARSE_PARAMETERS_START(2, 3)
  	Z_PARAM_STR(key)
  	Z_PARAM_STR(value)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(timeout)
  ZEND_PARSE_PARAMETERS_END();
  // clang-format on

  zval *name = zend_read_property_ex(etcd_ce, Z_OBJ_P(ZEND_THIS),
                                     ZSTR_KNOWN(ZEND_STR_NAME), false, NULL);
  char *error = go_client_put(Z_STRVAL_P(name), key, value, timeout);
  if (error != NULL) {
    zend_throw_exception(NULL, error, 0);
    free(error);
    RETURN_THROWS();
  }
}

PHP_METHOD(Dunglas_Etcd_Client, get) {
  zend_string *key;
  zend_long timeout = 0;

  // clang-format off
  ZEND_PARSE_PARAMETERS_START(1, 2)
  	Z_PARAM_STR(key)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(timeout)
  ZEND_PARSE_PARAMETERS_END();
  // clang-format on

  zval *name = zend_read_property_ex(etcd_ce, Z_OBJ_P(ZEND_THIS),
                                     ZSTR_KNOWN(ZEND_STR_NAME), false, NULL);
  struct go_client_get_return ret = go_client_get(Z_STRVAL_P(name), key, timeout);
  if (ret.r1 != NULL) {
    zend_throw_exception(NULL, ret.r1, 0);
    free(ret.r1);
    RETURN_THROWS();
  }

  if (ret.r0 == NULL) {
    RETURN_NULL();
  }

  ZVAL_STRING(return_value, ret.r0);
  free(ret.r0);
}

PHP_METHOD(Dunglas_Etcd_Client, delete) {
  zend_string *key;
  zend_long timeout = 0;

  // clang-format off
  ZEND_PARSE_PARAMETERS_START(1, 2)
    Z_PARAM_STR(key)
	Z_PARAM_OPTIONAL
	Z_PARAM_LONG(timeout)
  ZEND_PARSE_PARAMETERS_END();
  // clang-format on

  zval *name = zend_read_property_ex(etcd_ce, Z_OBJ_P(ZEND_THIS),
                                     ZSTR_KNOWN(ZEND_STR_NAME), false, NULL);
  char *error = go_client_delete(Z_STRVAL_P(name), key, timeout);
  if (error != NULL) {
    zend_throw_exception(NULL, error, 0);
    free(error);
    RETURN_THROWS();
  }
}

PHP_METHOD(Dunglas_Etcd_Client, close) {
  ZEND_PARSE_PARAMETERS_NONE();

  zval *name = zend_read_property_ex(etcd_ce, Z_OBJ_P(ZEND_THIS),
                                     ZSTR_KNOWN(ZEND_STR_NAME), false, NULL);
  char *error = go_client_close(Z_STRVAL_P(name));
  if (error != NULL) {
    zend_throw_exception(NULL, error, 0);
    free(error);
    RETURN_THROWS();
  }
}

zend_module_entry ext_go_module_entry = {STANDARD_MODULE_HEADER,
                                         "frankenphp-etcd",
                                         NULL,            /* Functions */
                                         PHP_MINIT(etcd), /* MINIT */
                                         NULL,            /* MSHUTDOWN */
                                         NULL,            /* RINIT */
                                         NULL,            /* RSHUTDOWN */
                                         NULL,            /* MINFO */
                                         "0.1.0",
                                         STANDARD_MODULE_PROPERTIES};

PHPAPI int register_internal_extensions(void) {
  if (original_php_register_internal_extensions_func != NULL &&
      original_php_register_internal_extensions_func() != SUCCESS) {
    return FAILURE;
  }

  zend_module_entry *module = &ext_go_module_entry;
  if (zend_register_internal_module(module) == NULL) {
    return FAILURE;
  };

  return SUCCESS;
}

void register_extension() {
  original_php_register_internal_extensions_func =
      php_register_internal_extensions_func;
  php_register_internal_extensions_func = register_internal_extensions;
}
