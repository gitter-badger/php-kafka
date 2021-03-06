<?php

/** @generate-function-entries */

namespace Kafka;

class TopicPartition
{
    public function __construct(string $topicName, int $partition, int $offset = 0) {}

    public function getTopicName(): ?string {}

    public function setTopicName(string $topicName): TopicPartition {}

    public function getPartition(): int {}

    public function setPartition(int $partition): TopicPartition {}

    public function getOffset(): int {}

    public function setOffset(int $offset): TopicPartition {}
}
