# FrankenPHP Extension for etcd

A high-performance [PHP](https://php.net) client for the [etcd](https://etcd.io) key-value store, designed to work with [FrankenPHP](https://frankenphp.dev).
It leverages [the official etcd v3 client](https://github.com/etcd-io/etcd/tree/main/client/v3), which is written in Go.

This extension enables the creation of global etcd clients that can be shared across all requests and worker script instances,
ensuring efficient resource usage and high performance.

> [!NOTE]
> frankenphp-etcd has mainly been created to demonstrate how to use Go to develop distributable PHP/FrankenPHP extensions.
> Its feature set is currently limited to the basic operations of the etcd client.
>
> The main focus of this project is to be a working example of a PHP extension written in Go.
> Therefore, the focus is on development best practices, code quality and readability rather than on feature completeness.
>
> However, contributions to extend functionality of this extension are very welcome.

## Installation

First, if not already done, follow [the instructions to install a ZTS version of libphp and `xcaddy`](https://frankenphp.dev/docs/compile/#install-php).
Then, use [`xcaddy`](https://github.com/caddyserver/xcaddy) to build FrankenPHP with the `frankenphp-etcd` module:

```console
CGO_ENABLED=1 \
XCADDY_GO_BUILD_FLAGS="-ldflags='-w -s' -tags=nobadger,nomysql,nopgx" \
CGO_CFLAGS=$(php-config --includes) \
CGO_LDFLAGS="$(php-config --ldflags) $(php-config --libs)" \
xcaddy build \
    --output frankenphp \
    --with github.com/dunglas/frankenphp-etcd \
    --with github.com/dunglas/frankenphp/caddy \
    --with github.com/dunglas/mercure/caddy \
    --with github.com/dunglas/vulcain/caddy
    # Add extra Caddy modules and FrankenPHP exntesions here
```

That's all! Your custom FrankenPHP build contains the `frankenphp-etcd` extension.

## Usage

```php
// Create a new global etcd client named "my-etcd-client" or get the existing instance if it already exists.
$client = \Dunglas\Etcd\Client::getOrCreate('my-etcd-client', ['http://127.0.0.1:2379']);

// Put a key-value pair in the etcd store
$client->put('foo', 'bar');

// Retrieve the value of the key "foo"
$client->get('foo');

// Delete the key "foo"
$client->delete('foo');

if (rand(0, 10) > 5) {
    // If the random number is greater than 5, close the client
    // This will affect other requests or worker script instances
    // as the client is shared globally.
    // You usually don't need to close the connection.
	$client->close();
}
```

## Credits

Created by [Kévin Dunglas](https://dunglas.dev) and sponsored by [Les-Tilleuls.coop](https://les-tilleuls.coop).
