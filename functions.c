#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_kafka.h"
#include "php_kafka_int.h"
#include "librdkafka/rdkafka.h"
#include "Zend/zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"
#include "functions_arginfo.h"

/* {{{ proto array kafka_get_err_descs()
 * Returns the full list of error codes.
 */
ZEND_FUNCTION(kafka_get_err_descs)
{
    const struct rd_kafka_err_desc *errdescs;
    size_t cnt;
    size_t i;
    int seen_zero = 0;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 0)
	ZEND_PARSE_PARAMETERS_END();

    rd_kafka_get_err_descs(&errdescs, &cnt);

    array_init_size(return_value, cnt);

    for (i = 0; i < cnt; i++) {
        const struct rd_kafka_err_desc *desc = &errdescs[i];
        zval el;

        if (desc->code == 0) {
            if (seen_zero) {
                continue;
            }
            seen_zero = 1;
        }

        ZVAL_NULL(&el);
        array_init(&el);
        add_assoc_long(&el, "code", desc->code);
        if (desc->name) {
            add_assoc_string(&el, "name", (char*) desc->name);
        } else {
            add_assoc_null(&el, "name");
        }
        if (desc->desc) {
            add_assoc_string(&el, "desc", (char*) desc->desc);
        }else {
            add_assoc_null(&el, "desc");
        }
        add_next_index_zval(return_value, &el);
    }
}
/* }}} */

/* {{{ proto string kafka_err2str(int $err)
 * Returns a human readable representation of a kafka error.
 */
ZEND_FUNCTION(kafka_err2str)
{
    zend_long errorCode;
    const char *errstr;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
	    Z_PARAM_LONG(errorCode)
	ZEND_PARSE_PARAMETERS_END();

    errstr = rd_kafka_err2str(errorCode);

    if (errstr) {
        RETURN_STRING(errstr);
    }
}
/* }}} */

/* {{{ proto int kafka_thread_cnt()
 * Retrieve the current number of threads in use by librdkafka.
 */
ZEND_FUNCTION(kafka_thread_cnt)
{
	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 0)
	ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(rd_kafka_thread_cnt());
}
/* }}} */

/* {{{ proto int kafka_offset_tail(int $offset)
 * Start consuming `$cnt` messages from topic's current `.._END` offset.
 */
ZEND_FUNCTION(kafka_offset_tail)
{
    zend_long offset;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
	    Z_PARAM_LONG(offset)
	ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(RD_KAFKA_OFFSET_TAIL(offset));
}

