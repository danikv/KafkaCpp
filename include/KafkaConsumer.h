/*
 * KafkaConsumer.h
 *
 *  Created on: 29 Sep 2019
 *      Author: danielk
 */

#ifndef INCLUDE_KAFKACONSUMER_H_
#define INCLUDE_KAFKACONSUMER_H_

#include <librdkafka/rdkafkacpp.h>
#include <memory>

class KafkaConsumer {
public:
	KafkaConsumer(const std::vector<std::string>& topics);
	~KafkaConsumer() = default;
	void consumeMessage(double timeout);

private:
	std::unique_ptr<RdKafka::KafkaConsumer> consumer;
};

#endif /* INCLUDE_KAFKACONSUMER_H_ */
