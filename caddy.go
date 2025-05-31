//go:build !nocaddy

package etcd

import (
	"context"
	"github.com/caddyserver/caddy/v2"
	"go.uber.org/zap"
)

func getLogger() *zap.Logger {
	return caddy.Log()
}

func getContext() context.Context {
	return caddy.ActiveContext()
}
