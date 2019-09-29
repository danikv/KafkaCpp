/*
 * KafkaConsumer.cpp
 *
 *  Created on: 29 Sep 2019
 *      Author: danielk
 */

#include "KafkaConsumer.h"
#include "Events.h"
#include "EnvVar.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <cstring>



using Env::getEnv;
using Events::ExampleEventCb;
using Events::ExampleRebalanceCb;



std::unique_ptr<RdKafka::Conf> createConf() {
	ExampleRebalanceCb ex_rebalance_cb;
	std::string errstr;
	auto conf = std::unique_ptr<RdKafka::Conf>(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
	RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
	conf->set("rebalance_cb", &ex_rebalance_cb, errstr);
	conf->set("enable.partition.eof", "true", errstr);

	auto brokers = getEnv("brokers", std::string("localhost"));
	conf->set("metadata.broker.list", brokers, errstr);

	ExampleEventCb ex_event_cb;
	conf->set("event_cb", &ex_event_cb, errstr);
	conf->set("default_topic_conf", tconf, errstr);


	delete tconf;
	return conf;
}


KafkaConsumer::KafkaConsumer(const std::vector<std::string>& topics) {
	std::string errstr;
	auto conf = createConf();
	consumer.reset(RdKafka::KafkaConsumer::create(conf.get(), errstr));
	if (!consumer) {
		std::cerr << "Failed to create consumer: " << errstr << std::endl;
		exit(1);
	}

	//subscribe topics
}

void KafkaConsumer::consumeMessage(double timeout) {
	  auto message = std::unique_ptr<RdKafka::Message>(consumer->consume(1000));
	  switch (message->err()) {
	    case RdKafka::ERR__TIMED_OUT:
	      break;

	    case RdKafka::ERR_NO_ERROR:
	      RdKafka::MessageTimestamp ts;
	      ts = message->timestamp();
	      if ( ts.type != RdKafka::MessageTimestamp::MSG_TIMESTAMP_NOT_AVAILABLE) {
	    	  std::string tsname = "?";
	    	  if (ts.type == RdKafka::MessageTimestamp::MSG_TIMESTAMP_CREATE_TIME)
	    		  tsname = "create time";
	    	  else if (ts.type == RdKafka::MessageTimestamp::MSG_TIMESTAMP_LOG_APPEND_TIME)
	    		  tsname = "log append time";
	    	  std::cout << "Timestamp: " << tsname << " " << ts.timestamp << std::endl;
	      }
	      std::cout << "Key: " << *message->key() << std::endl;
	      printf("%.*s\n",
	               static_cast<int>(message->len()),
	               static_cast<const char *>(message->payload()));
	      break;
	    case RdKafka::ERR__UNKNOWN_PARTITION:
	      std::cerr << "Consume failed: " << message->errstr() << std::endl;
	      break;
	    case RdKafka::ERR__PARTITION_EOF:
	    case RdKafka::ERR__UNKNOWN_TOPIC:
	    default:
	      /* Errors */
	      std::cerr << "Consume failed: " << message->errstr() << std::endl;
	  }
}
