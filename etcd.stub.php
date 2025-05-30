<?php

/** @generate-class-entries */

namespace Dunglas\Etcd {
    final class Client
    {
        /**
         * Creates a new persistent etcd client or returns an existing one.
         *
         * Clients are identified by their names.
         * They are persisted between requests and shared worker instances and persist after the end of the PHP script.
         * The same instance can be used to handle requests concurrently.
         *
         * @param string[] $endpoints
         */
        public static function getOrCreate(string $name, array $endpoints): \Dunglas\Etcd\Client
        {
        }

        /**
         * The name of the instance.
         */
        public readonly string $name;

        /**
         * Puts a key-value pair in the etcd store.
         */
        public function put(string $key, string $value): void
        {
        }

        /**
         * Gets a value from the etcd store by its key.
         * `null` is returned if the key does not exist.
         */
        public function get(string $key): ?string
        {
        }

        /**
         * Deletes a key-value pair from the etcd store by its key.
         * If the key does not exist, nothing happens.
         */
        public function delete(string $key): void
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
