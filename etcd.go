package etcd

//#include <zend.h>
//#include "etcd.h"
import "C"
import (
	"go.etcd.io/etcd/client/v3"
	"log/slog"
	"sync"
	"unsafe"
)

func init() {
	C.register_extension()
}

var (
	clientRegistry   = make(map[*C.char]*clientv3.Client)
	clientRegistryMu sync.RWMutex
)

//export go_client_load_or_create
func go_client_load_or_create(name *C.char, phpEndpoints *C.zend_string, phpEndpointsLen C.int) (error *C.char) {
	clientRegistryMu.Lock()
	defer clientRegistryMu.Unlock()

	_, ok := clientRegistry[name]
	if ok {
		slog.Debug("The client already exists")

		return
	}

	endpoints := make([]string, phpEndpointsLen)
	for i := 0; i < int(phpEndpointsLen); i++ {
		endpoints[i] = C.GoStringN((*C.char)(unsafe.Pointer(&phpEndpoints.val)), C.int(phpEndpoints.len))
		phpEndpoints = (*C.zend_string)(unsafe.Add(unsafe.Pointer(phpEndpoints), unsafe.Sizeof(C.zend_string{})))
	}

	// TODO: handle other options
	cfg := clientv3.Config{Endpoints: endpoints, Context: getContext()}
	if logger := getLogger(); logger != nil {
		cfg.Logger = logger
	}

	client, err := clientv3.New(cfg)
	if err != nil {
		error = C.CString(err.Error())

		return
	}

	clientRegistry[name] = client

	slog.Debug("New client created")

	return
}

//export go_client_close
func go_client_close(name *C.char) *C.char {
	clientRegistryMu.Lock()
	defer clientRegistryMu.Unlock()
	defer delete(clientRegistry, name)

	if client, ok := clientRegistry[name]; ok {
		if err := client.Close(); err != nil {
			return C.CString(err.Error())
		}
	}

	return nil
}

//export go_client_put
func go_client_put(name *C.char, key, value *C.zend_string) *C.char {
	clientRegistryMu.RLock()
	defer clientRegistryMu.RUnlock()

	client := clientRegistry[name]
	if _, err := client.Put(getContext(), C.GoStringN((*C.char)(unsafe.Pointer(&key.val)), C.int(key.len)), C.GoStringN((*C.char)(unsafe.Pointer(&value.val)), C.int(value.len))); err != nil {
		return C.CString(err.Error())
	}

	return nil
}

//export go_client_get
func go_client_get(name *C.char, key *C.zend_string) (val *C.char, error *C.char) {
	clientRegistryMu.RLock()
	defer clientRegistryMu.RUnlock()

	client := clientRegistry[name]
	resp, err := client.Get(getContext(), C.GoStringN((*C.char)(unsafe.Pointer(&key.val)), C.int(key.len)))
	if err != nil {
		return nil, C.CString(err.Error())
	}

	if len(resp.Kvs) > 0 {
		val := string(resp.Kvs[0].Value)

		// TODO: use runtime.Pinner to prevent this useless copy
		return C.CString(val), nil
	}

	return nil, nil
}

//export go_client_delete
func go_client_delete(name *C.char, key *C.zend_string) *C.char {
	clientRegistryMu.RLock()
	defer clientRegistryMu.RUnlock()

	client := clientRegistry[name]
	_, err := client.Delete(getContext(), C.GoStringN((*C.char)(unsafe.Pointer(&key.val)), C.int(key.len)))
	if err != nil {
		return C.CString(err.Error())
	}

	return nil
}
