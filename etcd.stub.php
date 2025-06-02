<?php

/** @generate-class-entries */

namespace Dunglas\Etcd {
    final class Client
    {
        public const int NANOSECOND = 1;
        public const int MICROSECOND = 1_000;
        public const int MILLISECOND = 1_000_000;
        public const int SECOND = 1_000_000_000;
        public const int MINUTE = 60_000_000_000;
        public const int HOUR = 3_600_000_000_000;

        /**
         * Creates a new persistent etcd client or returns an existing one.
         *
         * Clients are identified by their names.
         * They are persisted between requests and shared worker instances and persist after the end of the PHP script.
         * The same instance can be used to handle requests concurrently.
         *
         * @param string[] $endpoints
         *
         * @see https://pkg.go.dev/github.com/etcd-io/etcd/clientv3#Config
         */
        public static function getOrCreate(
            string $name,
            array $endpoints,
            int $autoSyncInterval = 0,
            int $dialTimeout = 0,
            int $dialKeepAliveTime = 0,
            int $dialKeepAliveTimeout = 0,
            bool $tls = false,
            int $maxCallSendMsgSize = 0,
            int $maxCallRecvMsgSize = 0,
            string $username = '',
            string $password = '',
            bool $rejectOldCluster = false,
            bool $permitWithoutStream = false,
        ): \Dunglas\Etcd\Client {
        }

        /**
         * The name of the instance.
         */
        public readonly string $name;

        /**
         * Puts a key-value pair in the etcd store.
         */
        public function put(string $key, string $value, int $timeout = 0): void
        {
        }

        /**
         * Gets a value from the etcd store by its key.
         * `null` is returned if the key does not exist.
         */
        public function get(string $key, int $timeout = 0): ?string
        {
        }

        /**
         * Deletes a key-value pair from the etcd store by its key.
         * If the key does not exist, nothing happens.
         */
        public function delete(string $key, int $timeout = 0): void
        {
        }

        /**
         * Closes the client and destroys it globally.
         */
        public function close(): void
        {
        }
    }
}
