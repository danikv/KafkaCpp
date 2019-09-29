/*
 * Events.h
 *
 *  Created on: 29 Sep 2019
 *      Author: danielk
 */

#ifndef INCLUDE_EVENTS_H_
#define INCLUDE_EVENTS_H_

#include <librdkafka/rdkafkacpp.h>
#include <vector>

namespace Events {

class ExampleEventCb : public RdKafka::EventCb {
public:
	ExampleEventCb() = default;
	~ExampleEventCb() = default;
	void event_cb (RdKafka::Event& event);
};

class ExampleRebalanceCb : public RdKafka::RebalanceCb {
public:
	ExampleRebalanceCb() = default;
	~ExampleRebalanceCb() = default;
	void rebalance_cb (RdKafka::KafkaConsumer *consumer, RdKafka::ErrorCode err,
		  std::vector<RdKafka::TopicPartition*> &partitions);
};

} /* namespace Events */

#endif /* INCLUDE_EVENTS_H_ */
