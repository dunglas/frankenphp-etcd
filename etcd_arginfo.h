/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 309e9e8dcc8c6d27aa2b7460d8e870b93833543f */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(
    arginfo_class_Dunglas_Etcd_Client_getOrCreate, 0, 2, Dunglas\\Etcd\\Client,
    0)
ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, endpoints, IS_ARRAY, 0)
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, autoSyncInterval, IS_LONG, 0, "0")
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, dialTimeout, IS_LONG, 0, "0")
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, dialKeepAliveTime, IS_LONG, 0, "0")
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, dialKeepAliveTimeout, IS_LONG, 0, "0")
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, tls, _IS_BOOL, 0, "false")
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, maxCallSendMsgSize, IS_LONG, 0, "0")
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, maxCallRecvMsgSize, IS_LONG, 0, "0")
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, username, IS_STRING, 0, "\'\'")
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, password, IS_STRING, 0, "\'\'")
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, rejectOldCluster, _IS_BOOL, 0, "false")
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, permitWithoutStream, _IS_BOOL, 0,
                                      "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Dunglas_Etcd_Client_put,
                                        0, 2, IS_VOID, 0)
ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, timeout, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Dunglas_Etcd_Client_get,
                                        0, 1, IS_STRING, 1)
ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, timeout, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(
    arginfo_class_Dunglas_Etcd_Client_delete, 0, 1, IS_VOID, 0)
ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, timeout, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Dunglas_Etcd_Client_close,
                                        0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Dunglas_Etcd_Client, getOrCreate);
ZEND_METHOD(Dunglas_Etcd_Client, put);
ZEND_METHOD(Dunglas_Etcd_Client, get);
ZEND_METHOD(Dunglas_Etcd_Client, delete);
ZEND_METHOD(Dunglas_Etcd_Client, close);

static const zend_function_entry class_Dunglas_Etcd_Client_methods[] = {
    ZEND_ME(Dunglas_Etcd_Client, getOrCreate,
            arginfo_class_Dunglas_Etcd_Client_getOrCreate,
            ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
        ZEND_ME(Dunglas_Etcd_Client, put, arginfo_class_Dunglas_Etcd_Client_put,
                ZEND_ACC_PUBLIC) ZEND_ME(Dunglas_Etcd_Client, get,
                                         arginfo_class_Dunglas_Etcd_Client_get,
                                         ZEND_ACC_PUBLIC)
            ZEND_ME(Dunglas_Etcd_Client, delete,
                    arginfo_class_Dunglas_Etcd_Client_delete, ZEND_ACC_PUBLIC)
                ZEND_ME(Dunglas_Etcd_Client, close,
                        arginfo_class_Dunglas_Etcd_Client_close,
                        ZEND_ACC_PUBLIC) ZEND_FE_END};

static zend_class_entry *register_class_Dunglas_Etcd_Client(void) {
  zend_class_entry ce, *class_entry;

  INIT_NS_CLASS_ENTRY(ce, "Dunglas\\Etcd", "Client",
                      class_Dunglas_Etcd_Client_methods);
  class_entry =
      zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

  zval const_NANOSECOND_value;
  ZVAL_LONG(&const_NANOSECOND_value, 1);
  zend_string *const_NANOSECOND_name =
      zend_string_init_interned("NANOSECOND", sizeof("NANOSECOND") - 1, 1);
  zend_declare_typed_class_constant(
      class_entry, const_NANOSECOND_name, &const_NANOSECOND_value,
      ZEND_ACC_PUBLIC, NULL, (zend_type)ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
  zend_string_release(const_NANOSECOND_name);

  zval const_MICROSECOND_value;
  ZVAL_LONG(&const_MICROSECOND_value, 1000);
  zend_string *const_MICROSECOND_name =
      zend_string_init_interned("MICROSECOND", sizeof("MICROSECOND") - 1, 1);
  zend_declare_typed_class_constant(
      class_entry, const_MICROSECOND_name, &const_MICROSECOND_value,
      ZEND_ACC_PUBLIC, NULL, (zend_type)ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
  zend_string_release(const_MICROSECOND_name);

  zval const_MILLISECOND_value;
  ZVAL_LONG(&const_MILLISECOND_value, 1000000);
  zend_string *const_MILLISECOND_name =
      zend_string_init_interned("MILLISECOND", sizeof("MILLISECOND") - 1, 1);
  zend_declare_typed_class_constant(
      class_entry, const_MILLISECOND_name, &const_MILLISECOND_value,
      ZEND_ACC_PUBLIC, NULL, (zend_type)ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
  zend_string_release(const_MILLISECOND_name);

  zval const_SECOND_value;
  ZVAL_LONG(&const_SECOND_value, 1000000000);
  zend_string *const_SECOND_name =
      zend_string_init_interned("SECOND", sizeof("SECOND") - 1, 1);
  zend_declare_typed_class_constant(
      class_entry, const_SECOND_name, &const_SECOND_value, ZEND_ACC_PUBLIC,
      NULL, (zend_type)ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
  zend_string_release(const_SECOND_name);

  zval const_MINUTE_value;
  ZVAL_LONG(&const_MINUTE_value, 60000000000);
  zend_string *const_MINUTE_name =
      zend_string_init_interned("MINUTE", sizeof("MINUTE") - 1, 1);
  zend_declare_typed_class_constant(
      class_entry, const_MINUTE_name, &const_MINUTE_value, ZEND_ACC_PUBLIC,
      NULL, (zend_type)ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
  zend_string_release(const_MINUTE_name);

  zval const_HOUR_value;
  ZVAL_LONG(&const_HOUR_value, 3600000000000);
  zend_string *const_HOUR_name =
      zend_string_init_interned("HOUR", sizeof("HOUR") - 1, 1);
  zend_declare_typed_class_constant(
      class_entry, const_HOUR_name, &const_HOUR_value, ZEND_ACC_PUBLIC, NULL,
      (zend_type)ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
  zend_string_release(const_HOUR_name);

  zval property_name_default_value;
  ZVAL_UNDEF(&property_name_default_value);
  zend_string *property_name_name =
      zend_string_init("name", sizeof("name") - 1, 1);
  zend_declare_typed_property(class_entry, property_name_name,
                              &property_name_default_value,
                              ZEND_ACC_PUBLIC | ZEND_ACC_READONLY, NULL,
                              (zend_type)ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
  zend_string_release(property_name_name);

  return class_entry;
}
