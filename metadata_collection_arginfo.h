/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: b5034ed5934be05969a933bc011686f99d63cd60 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Kafka_Metadata_Collection_count, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Kafka_Metadata_Collection_rewind, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Kafka_Metadata_Collection_current, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Kafka_Metadata_Collection_key arginfo_class_Kafka_Metadata_Collection_count

#define arginfo_class_Kafka_Metadata_Collection_next arginfo_class_Kafka_Metadata_Collection_current

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Kafka_Metadata_Collection_valid, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()


ZEND_METHOD(Kafka_Metadata_Collection, count);
ZEND_METHOD(Kafka_Metadata_Collection, rewind);
ZEND_METHOD(Kafka_Metadata_Collection, current);
ZEND_METHOD(Kafka_Metadata_Collection, key);
ZEND_METHOD(Kafka_Metadata_Collection, next);
ZEND_METHOD(Kafka_Metadata_Collection, valid);


static const zend_function_entry class_Kafka_Metadata_Collection_methods[] = {
	ZEND_ME(Kafka_Metadata_Collection, count, arginfo_class_Kafka_Metadata_Collection_count, ZEND_ACC_PUBLIC)
	ZEND_ME(Kafka_Metadata_Collection, rewind, arginfo_class_Kafka_Metadata_Collection_rewind, ZEND_ACC_PUBLIC)
	ZEND_ME(Kafka_Metadata_Collection, current, arginfo_class_Kafka_Metadata_Collection_current, ZEND_ACC_PUBLIC)
	ZEND_ME(Kafka_Metadata_Collection, key, arginfo_class_Kafka_Metadata_Collection_key, ZEND_ACC_PUBLIC)
	ZEND_ME(Kafka_Metadata_Collection, next, arginfo_class_Kafka_Metadata_Collection_next, ZEND_ACC_PUBLIC)
	ZEND_ME(Kafka_Metadata_Collection, valid, arginfo_class_Kafka_Metadata_Collection_valid, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
