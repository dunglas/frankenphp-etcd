/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: aa7a4e4871bb448f6bae0d17ad9bb3702809248c */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(
    arginfo_class_Dunglas_Etcd_Client_getOrCreate, 0, 2, Dunglas\\Etcd\\Client,
    0)
ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, endpoints, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Dunglas_Etcd_Client_put,
                                        0, 2, IS_VOID, 0)
ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Dunglas_Etcd_Client_get,
                                        0, 1, IS_STRING, 1)
ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(
    arginfo_class_Dunglas_Etcd_Client_delete, 0, 1, IS_VOID, 0)
ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
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
