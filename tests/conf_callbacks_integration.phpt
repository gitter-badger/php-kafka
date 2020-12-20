--TEST--
Kafka\Configuration
--SKIPIF--
<?php
(!isset($_ENV['TESTS_DONT_SKIP_RISKY']) || $_ENV['TESTS_DONT_SKIP_RISKY']) && die("skip Risky/broken test");
require __DIR__ . '/integration-tests-check.php';
--FILE--
<?php
require __DIR__ . '/integration-tests-check.php';

$conf = new Kafka\Configuration();

$conf->set('auto.offset.reset', 'earliest');
$conf->set('metadata.broker.list', getenv('TEST_KAFKA_BROKERS'));

$conf->set('group.id', sprintf("test_kafka_group_%s", uniqid()));

$producer = new Kafka\Producer($conf);

$topicName = sprintf("test_kafka_%s", uniqid());
$topic = $producer->getTopicHandle($topicName);

for ($i = 0; $i < 10; $i++) {
    $topic->produce(0, 0, "message $i");
    $producer->poll(0);
}

$producer->flush(10000);

// Make sure there is enough time for the stats_cb to pick up the consumer lag
sleep(1);

$conf = new Kafka\Configuration();

$conf->set('auto.offset.reset', 'earliest');
$conf->set('metadata.broker.list', getenv('TEST_KAFKA_BROKERS'));
$conf->set('group.id', sprintf("test_kafka_group_%s", uniqid()));
$conf->set('statistics.interval.ms', 10);

$conf->setOffsetCommitCb(function ($consumer, $error, $topicPartitions) {
    echo "Offset " . $topicPartitions[0]->getOffset() . " committed.\n";
});

$statsCbCalled = false;
$conf->setStatsCb(function ($consumer, $json) use (&$statsCbCalled) {
    if ($statsCbCalled) {
        return;
    }

    $statsCbCalled = true;
});

$consumer = new Kafka\Consumer($conf);
$consumer->subscribe([$topicName]);

while (true) {
    $msg = $consumer->consume(15000);

    if (!$msg || RD_KAFKA_RESP_ERR__PARTITION_EOF === $msg->err) {
        break;
    }

    if (RD_KAFKA_RESP_ERR_NO_ERROR !== $msg->err) {
        throw new Exception($msg->getErrorString(), $msg->err);
    }

    $consumer->commit($msg);
}

var_dump($statsCbCalled);

--EXPECT--
Offset 1 committed.
Offset 2 committed.
Offset 3 committed.
Offset 4 committed.
Offset 5 committed.
Offset 6 committed.
Offset 7 committed.
Offset 8 committed.
Offset 9 committed.
Offset 10 committed.
bool(true)
