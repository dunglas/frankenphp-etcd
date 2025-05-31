package etcd_test

import (
	"github.com/caddyserver/caddy/v2/caddytest"
	_ "github.com/dunglas/frankenphp/caddy"
	"net/http"
	"testing"
)

func TestFrankenPHPEtcd(t *testing.T) {
	tester := caddytest.NewTester(t)
	tester.InitServer(`
		{
			skip_install_trust
			admin localhost:2999
			http_port 9080
			https_port 9443

			frankenphp
		}

		localhost:9080 {
			root testdata/
			php_server
		}
		`, "caddyfile")

	tester.AssertGetResponse("http://localhost:9080/index.php", http.StatusOK, `Client name: my-etcd
foo: bar
foo: `)
}
