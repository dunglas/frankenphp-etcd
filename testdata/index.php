<?php

header('Content-Type: text/plain; charset=utf-8');

$client = Dunglas\Etcd\Client::getOrCreate('my-etcd', ['http://127.0.0.1:2379']);

echo "Client name: {$client->name}\n";

$client->put('foo', 'bar');
echo 'foo: ' . $client->get('foo') . "\n";

$client->delete('foo');
echo 'foo: ' . $client->get('foo');

$client->close();
