--TEST--
Kafka\TopicPartition
--FILE--
<?php

$topar = new Kafka\TopicPartition("test", RD_KAFKA_PARTITION_UA);

var_dump($topar);

$topar = new Kafka\TopicPartition("test", RD_KAFKA_PARTITION_UA, 42);

var_dump($topar);

var_dump(array(
    "topic" => $topar->getTopicName(),
    "partition" => $topar->getPartition(),
    "offset" => $topar->getOffset(),
));

$topar
    ->setTopicName("foo")
    ->setPartition(123)
    ->setOffset(43);

var_dump($topar);
--EXPECT--
object(Kafka\TopicPartition)#1 (3) {
  ["topic"]=>
  string(4) "test"
  ["partition"]=>
  int(-1)
  ["offset"]=>
  int(0)
}
object(Kafka\TopicPartition)#2 (3) {
  ["topic"]=>
  string(4) "test"
  ["partition"]=>
  int(-1)
  ["offset"]=>
  int(42)
}
array(3) {
  ["topic"]=>
  string(4) "test"
  ["partition"]=>
  int(-1)
  ["offset"]=>
  int(42)
}
object(Kafka\TopicPartition)#2 (3) {
  ["topic"]=>
  string(3) "foo"
  ["partition"]=>
  int(123)
  ["offset"]=>
  int(43)
}
