package etcd

//#include <zend.h>
//#include "etcd.h"
import "C"
import (
	"context"
	"crypto/tls"
	"github.com/dunglas/frankenphp"
	"go.etcd.io/etcd/client/v3"
	"log/slog"
	"sync"
	"time"
	"unsafe"
)

func init() {
	frankenphp.RegisterExtension(unsafe.Pointer(&C.etcd_module_entry))
}

var (
	clientRegistry   = make(map[string]*clientv3.Client)
	clientRegistryMu sync.RWMutex
)

//export go_client_load_or_create
func go_client_load_or_create(
	phpName *C.zend_string,
	phpEndpoints *C.zend_string,
	phpEndpointsLen C.int,
	autoSyncInterval,
	dialTimeout,
	dialKeepAliveTime,
	dialKeepAliveTimeout int64,
	enableTLS bool,
	maxCallSendMsgSize,
	maxCallRecvMsgSize int64,
	username,
	password *C.zend_string,
	rejectOldCluster,
	permitWithoutStream bool,
) (error *C.char) {
	name := frankenphp.GoString(unsafe.Pointer(phpName))

	clientRegistryMu.Lock()
	defer clientRegistryMu.Unlock()

	_, ok := clientRegistry[name]
	if ok {
		slog.Debug("The client already exists", slog.String("name", name))

		return
	}

	endpoints := make([]string, phpEndpointsLen)
	for i := 0; i < int(phpEndpointsLen); i++ {
		endpoints[i] = frankenphp.GoString(unsafe.Pointer(phpEndpoints))
		phpEndpoints = (*C.zend_string)(unsafe.Add(unsafe.Pointer(phpEndpoints), unsafe.Sizeof(C.zend_string{})))
	}

	// TODO: handle other options
	cfg := clientv3.Config{
		Context:              getContext(),
		Endpoints:            endpoints,
		AutoSyncInterval:     time.Duration(autoSyncInterval),
		DialTimeout:          time.Duration(dialTimeout),
		DialKeepAliveTime:    time.Duration(dialKeepAliveTime),
		DialKeepAliveTimeout: time.Duration(dialKeepAliveTimeout),
		MaxCallSendMsgSize:   int(maxCallSendMsgSize),
		MaxCallRecvMsgSize:   int(maxCallRecvMsgSize),
		Username:             frankenphp.GoString(unsafe.Pointer(username)),
		Password:             frankenphp.GoString(unsafe.Pointer(password)),
		RejectOldCluster:     rejectOldCluster,
		PermitWithoutStream:  permitWithoutStream,
	}
	if enableTLS {
		cfg.TLS = &tls.Config{}
	}

	if logger := getLogger(); logger != nil {
		cfg.Logger = logger
	}

	client, err := clientv3.New(cfg)
	if err != nil {
		error = C.CString(err.Error())

		return
	}

	clientRegistry[name] = client

	slog.Debug("New client created", slog.String("name", name))

	return
}

//export go_client_close
func go_client_close(phpName *C.zend_string) *C.char {
	name := frankenphp.GoString(unsafe.Pointer(phpName))

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
func go_client_put(phpName *C.zend_string, key, value *C.zend_string, timeout int64) *C.char {
	name := frankenphp.GoString(unsafe.Pointer(phpName))

	ctx := getContext()
	if timeout != 0 {
		var cancel context.CancelFunc

		ctx, cancel = context.WithTimeout(ctx, time.Duration(timeout))
		defer cancel()
	}

	clientRegistryMu.RLock()
	defer clientRegistryMu.RUnlock()

	client := clientRegistry[name]
	if _, err := client.Put(ctx, C.GoStringN((*C.char)(unsafe.Pointer(&key.val)), C.int(key.len)), C.GoStringN((*C.char)(unsafe.Pointer(&value.val)), C.int(value.len))); err != nil {
		return C.CString(err.Error())
	}

	return nil
}

//export go_client_get
func go_client_get(phpName *C.zend_string, key *C.zend_string, timeout int64) (val *C.char, error *C.char) {
	name := frankenphp.GoString(unsafe.Pointer(phpName))

	ctx := getContext()
	if timeout != 0 {
		var cancel context.CancelFunc

		ctx, cancel = context.WithTimeout(ctx, time.Duration(timeout))
		defer cancel()
	}

	clientRegistryMu.RLock()
	defer clientRegistryMu.RUnlock()

	client := clientRegistry[name]
	resp, err := client.Get(ctx, C.GoStringN((*C.char)(unsafe.Pointer(&key.val)), C.int(key.len)))
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
func go_client_delete(phpName *C.zend_string, key *C.zend_string, timeout int64) *C.char {
	name := frankenphp.GoString(unsafe.Pointer(phpName))

	ctx := getContext()
	if timeout != 0 {
		var cancel context.CancelFunc

		ctx, cancel = context.WithTimeout(ctx, time.Duration(timeout))
		defer cancel()
	}

	clientRegistryMu.RLock()
	defer clientRegistryMu.RUnlock()

	client := clientRegistry[name]
	_, err := client.Delete(ctx, C.GoStringN((*C.char)(unsafe.Pointer(&key.val)), C.int(key.len)))
	if err != nil {
		return C.CString(err.Error())
	}

	return nil
}
