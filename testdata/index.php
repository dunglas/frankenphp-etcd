<?php

use Dunglas\Etcd\Client;

header('Content-Type: text/plain; charset=utf-8');

$client = Client::getOrCreate(
    'my-etcd',
    ['http://127.0.0.1:2379'],
    5 * Client::SECOND,
    3 * Client::SECOND,
    3 * Client::SECOND,
    3 * Client::SECOND,
);

echo "Client name: {$client->name}\n";

$client->put('foo', 'bar', 3 * Client::SECOND);
echo 'foo: ' . $client->get('foo', 3 * Client::SECOND) . "\n";

$client->delete('foo');
echo 'foo: ' . $client->get('foo', 3 * Client::SECOND);

$client->close();
