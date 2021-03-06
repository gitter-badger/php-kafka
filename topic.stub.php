<?php

/** @generate-function-entries */

namespace Kafka;

abstract class Topic
{
    public function getName(): string {}
}

class ConsumerTopic extends Topic
{
    private function __construct() {}
}

class ProducerTopic extends Topic
{
    private function __construct() {}

    public function produce(int $partition, int $msgFlags, ?string $payload = null, ?string $key = null): void {}

    public function producev(int $partition, int $msgFlags, ?string $payload = null, ?string $key = null, ?array $headers = null, ?int $timestampMs = null): void {}
}
