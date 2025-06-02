package etcd

//#include <zend.h>
import "C"
import "unsafe"

func zendStringToGoString(zendStr *C.zend_string) string {
	if zendStr == nil {
		return ""
	}

	return C.GoStringN((*C.char)(unsafe.Pointer(&zendStr.val)), C.int(zendStr.len))
}
