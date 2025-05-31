//go:build nocaddy

package etcd

import (
	"context"
	"go.uber.org/zap"
)

func getLogger() *zap.Logger {
	return nil
}

func getContext() context.Context {
	return context.TODO()
}
