<?php

/** @generate-class-entries */

namespace Dunglas\Etcd {
	final class Client
	{
		/**
		 * @param string[] $endpoints
		 */
		public static function getOrCreate(string $name, array $endpoints): \Dunglas\Etcd\Client {}

		public readonly string $name;

		public function put(string $key, string $value): void {}

		public function get(string $key): ?string {}

		public function delete(string $key): void {}

		public function close(): void {}
	}
}
