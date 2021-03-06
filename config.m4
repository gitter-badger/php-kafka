dnl $Id$
dnl config.m4 for extension kafka

PHP_ARG_WITH(kafka, for kafka support,
[  --with-kafka             Include kafka support])

dnl Check whether the extension is enabled at all
if test "$PHP_KAFKA" != "no"; then

  SEARCH_PATH="/usr/local /usr"     # you might want to change this
  SEARCH_FOR="/include/librdkafka/rdkafka.h"  # you most likely want to change this
  if test -r $PHP_KAFKA/$SEARCH_FOR; then # path given as parameter
    RDKAFKA_DIR=$PHP_KAFKA
  else # search default path list
    AC_MSG_CHECKING([for librdkafka/rdkafka.h" in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        RDKAFKA_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi
  
  if test -z "$RDKAFKA_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the rdkafka distribution])
  fi

  PHP_ADD_INCLUDE($RDKAFKA_DIR/include)

  SOURCES="kafka.c producer.c metadata.c metadata_broker.c metadata_topic.c metadata_partition.c metadata_collection.c configuration.c topic.c message.c functions.c consumer.c topic_partition.c kafka_exception.c"

  LIBNAME=rdkafka
  LIBSYMBOL=rd_kafka_new

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $RDKAFKA_DIR/$PHP_LIBDIR, KAFKA_SHARED_LIBADD)
    AC_DEFINE(HAVE_RDKAFKALIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong rdkafka lib version or lib not found])
  ],[
    -L$RDKAFKA_DIR/$PHP_LIBDIR -lm
  ])

  ORIG_LDFLAGS="$LDFLAGS"
  ORIG_CPPFLAGS="$CPPFLAGS"
  LDFLAGS="-L$RDKAFKA_DIR/$PHP_LIBDIR -lm"
  CPPFLAGS="-I$RDKAFKA_DIR/include"

  AC_MSG_CHECKING([for librdkafka version])
  AC_EGREP_CPP(yes,[
#include <librdkafka/rdkafka.h>
#if RD_KAFKA_VERSION >= 0x000b0000
  yes
#endif
  ],[
    AC_MSG_RESULT([>= 1.4.0])
  ],[
    AC_MSG_ERROR([librdkafka version 1.4.0 or greater required.])
  ])

  LDFLAGS="$ORIG_LDFLAGS"
  CPPFLAGS="$ORIG_CPPFLAGS"

  PHP_SUBST(KAFKA_SHARED_LIBADD)

  PHP_NEW_EXTENSION(kafka, $SOURCES, $ext_shared)
fi
